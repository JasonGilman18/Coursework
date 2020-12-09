//Jason Gilman
//126006979

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	string input = argv[1];
	cout << "String input: " << input << endl;
	int length = input.length();
	pid_t pid;
	for(int i = length-1;i >= 0;i--)
	{
		pid = fork();					//If you cannot create processes inside the loop, how do you iterate through the string?
		if(pid == 0)					//returned to the child.
		{
			cout << input.at(i);
			break;						//break stops forked process from creating childern.
		}
	}
}