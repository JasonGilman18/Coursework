/* 
    File: dataserver.cpp

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 

    Dataserver main program for MPs in CSCE 313
*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cassert>
#include <cstring>
#include <sstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "netreqchannel.hpp"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* VARIABLES */
/*--------------------------------------------------------------------------*/

static int nthreads = 0;

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

//void handle_process_loop(RequestChannel & _channel);

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- SUPPORT FUNCTIONS */
/*--------------------------------------------------------------------------*/

std::string int2string(int number) {
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- GENERATE THE DATA */
/*--------------------------------------------------------------------------*/

std::string generate_data() {
  // Generate the data to be returned to the client.
  usleep(1000 + (rand() % 5000));
  return int2string(rand() % 100);
}

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- THREAD FUNCTIONS */
/*--------------------------------------------------------------------------*/

/*
void handle_data_requests(int* fd,const string &req) {

  if(req.strcmp("hello"))
	  process_hello(fd,req);
  else if(req.strcmp("data"))
	  process_data(fd,req);
}
*/
/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- INDIVIDUAL REQUESTS */
/*--------------------------------------------------------------------------*/

void process_hello(int* fd,const string &req) {
  
  string s = "The server says hello back!";
  write(*fd,s.c_str(),s.length()+1);
  
}

void process_data(int* fd, const string &req) {
  
  std::string data = generate_data();
  if(data.length() < 255)
	  write(*fd,data.c_str(),data.length()+1);
}

/*
void process_newthread(RequestChannel & _channel, const std::string & _request) {
  int error;
  nthreads ++;

  // -- Name new data channel

  std::string new_channel_name = "data" + int2string(nthreads) + "_";
 
  // -- Pass new channel name back to client

  _channel.cwrite(new_channel_name);

  // -- Construct new data channel (pointer to be passed to thread function)
  
  RequestChannel * data_channel = new RequestChannel(new_channel_name, RequestChannel::Side::SERVER);

  // -- Create new thread to handle request channel

  pthread_t thread_id;
  //  std::cout << "starting new thread " << nthreads << std::endl;
  if ((error = pthread_create(& thread_id, nullptr, handle_data_requests, data_channel))) {
    fprintf(stderr, "p_create failed: %s\n", strerror(error));
  }  

}
*/
/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- THE PROCESS REQUEST LOOP */
/*--------------------------------------------------------------------------*/

void process_request(int* fd,const string &req) {

  if(req.compare("hello")==0)
	  process_hello(fd,req);
  else if(req.compare("data")==0)
	  process_data(fd,req);

}
/*
void handle_process_loop(RequestChannel & _channel) {

  for(;;) {

    std::cout << "Reading next request from channel (" << _channel.name()
	      << ") ..." << std::flush;
    std::string request = _channel.cread();
    std::cout << " done (" << _channel.name() << ")." << std::endl;
    std::cout << "New request is " << request << std::endl;

    if (request.compare("quit") == 0) {
      _channel.cwrite("bye");
      usleep(10000);          // give the other end a bit of time.
      break;                  // break out of the loop;
    }

    process_request(_channel, request);
  }
  
}
*/
void* connection_handler(void* f)
{
	int* fd = (int*)f;
	for(;;)
	{	
		char buf[255];
		read(*fd,buf,255);
		string req = buf;
		
		if(req.compare("quit")==0)
		{
			string s = "Server shutting down.";
			write(*fd,s.c_str(),s.length()+1);
		}
		process_request(fd,req);
	}
}

/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

int main(int argc, char * argv[]) {
	/*
  //  std::cout << "Establishing control channel... " << std::flush;
  RequestChannel control_channel("control", RequestChannel::Side::SERVER);
  //  std::cout << "done.\n" << std::endl;

  handle_process_loop(control_channel);
	*/
	
	unsigned short portNum = 13325;
	int backlog;
	int pN;
	pN = atoi(argv[1]);
	backlog = atoi(argv[2]);	
	cout << "Server has started on port: " << pN << endl;
	cout << "Backlog: " << backlog << endl;
	NetworkRequestChannel server(portNum, connection_handler);
	server.~NetworkRequestChannel();
	return 0;
}

