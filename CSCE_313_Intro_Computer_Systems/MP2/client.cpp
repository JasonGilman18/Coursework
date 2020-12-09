//Jason Gilman
//126006979

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#include <errno.h>
#include <unistd.h>

#include "reqchannel.hpp"


std::string int2string(int number) {
  std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}


int main(int argc, char * argv[]) {

  std::cout << "CLIENT STARTED:" << std::endl << std::endl;
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
	std::cout << "Establishing control channel... client side " << std::endl << std::flush;
	RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
	std::cout << "done." << std::endl;

	std::string reply1 = chan.send_request("hello");
	std::cout << "Reply to request 'hello' is '" << reply1 << "'" << std::endl;
	
	clock_t t;
	t = clock();	//initial clock reading
	
	int iterations = 1000;
	//send 100 requests for generate_data()
	for(int i = 0; i < iterations; i++) 
	{
		std::string request_string("data TestPerson" + int2string(i));
		std::string reply_string = chan.send_request(request_string);
		std::cout << "reply to request " << i << ":" << reply_string << std::endl;;
	}
	
	t = clock() - t;//secondary clock reading - initial clock reading.
	std::cout << "For " << iterations << " data requests, it took " << t << " clock ticks." << std::endl;
	
 
	std::string reply4 = chan.send_request("quit");
	std::cout << "Reply to request 'quit' is '" << reply4 << std::endl;
	
	usleep(1000000);
  }
}