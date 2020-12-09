//Jason Gilman
//126006979

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <iomanip>

#include "netreqchannel.hpp"
#include "Buffer.hpp"
#include "Semaphore.hpp"
#include "Request.hpp"

using namespace std;

std::string int2string(int number) {
  std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

//declare helper methods
void* requestThread(void* v);
//void* workingThread(void* v);
void* eventHandler(void* event);
void* statThread(void* v);

//need to be global
Buffer* mainBuffer;
Buffer* joeBuffer;
Buffer* janeBuffer;
Buffer* johnBuffer;
int countJoe = 0;
int countJane = 0;
int countJohn = 0;
int nP;
int sB;
int nW;
char* hN;
int pN;
int* id0 = new int(0);
int* id1 = new int(1);
int* id2 = new int(2);
Request* kill = new Request("KILL", -9999, -9999);
Request* start = new Request("START", 9999,9999);
pthread_mutex_t myLock;
vector<NetworkRequestChannel*> NetChan;

int main(int argc, char * argv[])
{
  nP = atoi(argv[1]);	//number of data requests
  sB = atoi(argv[2]);	//size of buffer
  nW = atoi(argv[3]);	//number worker threads
  hN = argv[4];
  pN = atoi(argv[5]);
  
 
  pthread_mutex_init(&myLock,NULL);
  
  std::cout << "CLIENT STARTED:" << std::endl;
  
  pid_t pid = fork();
  
  if(pid == 0) //if pid is 0 it is the child process, so run the data server. execv should replace the child process with a call to dataserver.
  {
	  std::string temp = "./dataserver";
	  //char *cmd = temp.c_str();
	  char *cmd = (char*)"./dataserver";
	  char *args[2];
	  //args[0] = temp.c_str();
	  args[0] = (char*)"./dataserver";
	  args[1] = NULL;
	  execvp(cmd,args);
  }
  else
  {
	  /*
	std::cout << "Establishing control channel... client side " << std::endl << std::flush;
	RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
	std::cout << "done." << std::endl;
	*/
	Buffer* mainBuffer = new Buffer(sB);
	Buffer* joeBuffer = new Buffer(sB);
	Buffer* janeBuffer = new Buffer(sB);
	Buffer* johnBuffer = new Buffer(sB);
	
	pthread_t statThreads[3];
	pthread_t requestThreads[3];
	//pthread_t workerThreads[nW];
	pthread_t eventHandlerThread;
	
	//creating requestThreads
	cout << "Creating request threads now." << endl;
	pthread_create(&requestThreads[0], NULL, requestThread,(void*)id0);
	pthread_create(&requestThreads[1], NULL, requestThread, (void*)id1);
	pthread_create(&requestThreads[2], NULL, requestThread, (void*)id2);
	cout << "request threads done." << endl;
	
	//creating worker threads
	/*
	string serverMessage;
	cout << "Creating worker threads now. " << endl;
	for(int i=0;i<nW;i++)
	{
		serverMessage = chan.send_request("newthread");
		cout << "Thread " << i+1 << " reply: " << serverMessage << endl;
		//cout << i << endl;
		RequestChannel* workingChannel = new RequestChannel(serverMessage, RequestChannel::CLIENT_SIDE);
		
		pthread_create(&workerThreads[i],NULL,workingThread,(void*)workingChannel);
	}
	cout << "worker threads done." << endl;
	*/
	//create eventHandler
	pthread_create(&eventHandlerThread, NULL, eventHandler, NULL);
	
	
	//creating statThreads
	cout << "Creating stat threads now." << endl;
	pthread_create(&statThreads[0],NULL, statThread, (void*)id0);
	pthread_create(&statThreads[1],NULL, statThread, (void*)id1);
	pthread_create(&statThreads[2],NULL, statThread, (void*)id2);
	cout << "stat threads done." << endl;
	
	pthread_join(requestThreads[0],NULL);
	pthread_join(requestThreads[1],NULL);
	pthread_join(requestThreads[2],NULL);
	pthread_join(eventHandlerThread,NULL);
	pthread_join(statThreads[0],NULL);
	pthread_join(statThreads[1],NULL);
	pthread_join(statThreads[2],NULL);
	
	//mainBuffer->add(*kill);
	/*
	std::string reply4 = chan.send_request("quit");
	std::cout << "Reply to request 'quit' is '" << reply4 << std::endl;
	*/
	
	cout << "HISTOGRAM DATA: " << endl << "Joe	-	" << countJoe << endl << "Jane	-	" << countJane << endl << "John	-	" << countJohn << endl;
	
	usleep(1000000);
  }
}

//helper methods
void* requestThread(void* v)
{
	int id = *((int*)v);
	for(int q=0;q<nP;q++)
	{
		if(id == 0)
			mainBuffer->add(Request("Joe",0,q));
		else if(id == 1)
			mainBuffer->add(Request("Jane",1,q));
		else if(id == 2)
			mainBuffer->add(Request("John",2,q));
	}
	
}

/*
void* workingThread(void* v)
{
	RequestChannel* wC = (RequestChannel*)v;
	for(;;)
		{
			Request re = mainBuffer->remove();
			int reID = re.getID();
			if(reID == kill->getID())
			{
				pthread_mutex_lock(&myLock);
				joeBuffer->add(*kill);
				janeBuffer->add(*kill);
				johnBuffer->add(*kill);
				pthread_mutex_unlock(&myLock);
			}
			string serverReply = wC->send_request(re.getData());
			if(reID == 0)
				joeBuffer->add(Request(serverReply, reID, re.getCount()));
			else if(reID == 1)
				janeBuffer->add(Request(serverReply, reID, re.getCount()));
			else if(reID == 2)
				johnBuffer->add(Request(serverReply, reID, re.getCount()));
		}
}
*/

void* eventHandler(void* event)
{
	//RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
	//RequestChannel* wC[nW];
	int clientID[nW];
	for(int i=0;i<nW;i++)
	{
		NetworkRequestChannel* chan = new NetworkRequestChannel(hN,pN);
		NetChan.push_back(chan);
		clientID[i] = -1;
	}
	
	Request req = Request("",0,0); //empty req
	
	int workerCount = 0;
	for(int i=0;i<nW;i++)
	{
		req = mainBuffer->remove();
		workerCount++;
		NetChan[i]->cwrite(req.getData());
		clientID[i] = req.getID();
	}
	
	bool done = false;
	fd_set read;
	int max = 0;
	int selection;
	string response;
	int requestCount = 0;
	while(!done)
	{
		FD_ZERO(&read);
		for(int i=0; i<nW;i++)
		{
			if(NetChan[i]->read_fd() > max)
				max = NetChan[i]->read_fd();
			FD_SET(NetChan[i]->read_fd(),&read);
		}
		selection = select(max+1,&read,NULL,NULL,NULL);
		
		if(selection)
		{
			for(int i=0;i<nW;i++)
			{
				if(FD_ISSET(NetChan[i]->read_fd(), &read))
				{
					response = NetChan[i]->cread();
					requestCount++;
					int idTemp = clientID[i];
					if(idTemp == 0)
						joeBuffer->add(Request(response,idTemp,0));
					else if(idTemp == 1)
						janeBuffer->add(Request(response,idTemp,0));
					else if(idTemp == 2)
						johnBuffer->add(Request(response,idTemp,0));
					
					if(workerCount < requestCount*2)
					{
						req = mainBuffer->remove();
						clientID[i] = req.getID();
						NetChan[i]->cwrite(req.getData());
						workerCount++;
					}
				}
			}
		}
	}
	for(int i=0;i<nW;i++)
	{
		NetChan[i]->send_request("quit");
	}
	//chan.send_request("quit");
	johnBuffer->add(*kill);
	janeBuffer->add(*kill);
	johnBuffer->add(*kill);
}

void* statThread(void* v)
{
	int id = *((int*)v);
	for(;;)
	{
		if(id == 0)
		{
			Request re0 = joeBuffer->remove();
			countJoe++;
		}
		else if(id == 1)
		{
			Request re1 = janeBuffer->remove();
			countJane++;
		}
		else if(id == 2)
		{
			Request re2 = johnBuffer->remove();
			countJohn++;
		}
	}
}


