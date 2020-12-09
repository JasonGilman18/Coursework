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
#include <netdb.h>
#include <stdio.h>
#include <cstring>

#include "netreqchannel.hpp"

using namespace std;

NetworkRequestChannel::NetworkRequestChannel(const string _server_host_name, const unsigned short _port_no)
{
	//fd socket file descriptor
	
	sockaddr_in s;
	ostringstream oss;
	oss << _port_no;
	string port = oss.str();
	
	memset(&s,0,sizeof(s));
	s.sin_family = AF_INET;
	
	if(hostent* h = gethostbyname(_server_host_name.c_str()))
		memcpy(&s.sin_addr, h->h_addr, h->h_length);
	
	if(servent* ser = getservbyname(port.c_str(),"tcp"))
		s.sin_port = ser->s_port;
	
	fd = socket(AF_INET,SOCK_STREAM,0);
}

NetworkRequestChannel::NetworkRequestChannel(const unsigned short _port_no, void * (*connection_handler) (void *))
{
	ostringstream oss;
	oss << _port_no;
	string port = oss.str();
	
	sockaddr_in server;
	int size = sizeof(server);
	memset(&server,0,size);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	
	if(servent* ser = getservbyname(port.c_str(),"tcp"))
		server.sin_port = ser->s_port;
	
	int connection = socket(AF_INET,SOCK_STREAM,0);
	for(;;)
	{
		pthread_t thread;
		pthread_attr_t a;
		pthread_attr_init(&a);
		int* allow = new int;
		*allow = accept(connection,(sockaddr*)&server,(socklen_t*)&size);
		if(allow < 0)
			delete allow;
		void* con = (void*)&connection;
		pthread_create(&thread, &a, connection_handler, con);
	}
}

NetworkRequestChannel::~NetworkRequestChannel()
{
	close(fd);
}

string NetworkRequestChannel::send_request(string _request)
{
	cwrite(_request);
	std::string s = cread();
	return s;
}

string NetworkRequestChannel::cread()
{
	char buf[255];

	if (read(fd, buf, 255) < 0) {
    perror(std::string("Error reading from pipe!").c_str());
  }
  
  std::string s = buf;

  std::cout << "NetworkRequestChannel reads [" << buf << "]" << std::endl;
  
  return s;
}

int NetworkRequestChannel::cwrite(string _msg)
{
  if (_msg.length() >= 255) {
    std::cerr << "Message too long for Channel!" << std::endl;
  }

  std::cout << "NetworkRequestChannel writing [" << _msg << "]";

  const char * s = _msg.c_str(); // NOTE: c_str() is NOT thread safe!!

  if (write(fd, s, strlen(s)+1) < 0) {
    perror(std::string("NetworkRequestChannel Error writing to pipe!").c_str());
  }

  std::cout << "done writing." << std::endl;
}

int NetworkRequestChannel::read_fd()
{
	return fd;
}