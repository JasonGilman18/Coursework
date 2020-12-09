#include <stdio.h>
#include "Deque.h"

int main(int argc, char *argv[])
{
	Deque intQ(4);

	printf ( "empty(1): %d\n", intQ.empty ( ) ? 1 : 0 );
	intQ.insertFront ( 4 );
	printf ( "removeBack(4): %d\n", intQ.removeBack ( ) );
	intQ.insertFront ( 5 );
	intQ.insertFront ( 12 );
	intQ.insertBack ( 7 );
	intQ.insertBack ( 13 );
	printf ( "front(12): %d\n", intQ.front ( ) );
	printf ( "back(13): %d\n", intQ.back ( ) );
	printf ( "size(4): %d\n", intQ.size ( ) );
	printf ( "empty(0): %d\n", intQ.empty ( ) ? 1 : 0 );
	printf ( "removeBack(13) :%d\n", intQ.removeBack ( ) );
	printf ( "removeBack(7) :%d\n", intQ.removeBack ( ) );
	printf ( "removeBack(5) :%d\n", intQ.removeBack ( ) );
	printf ( "removeFront(12) :%d\n", intQ.removeFront ( ) );
	printf ( "size(0): %d\n", intQ.size ( ) );
	printf ( "empty(1): %d\n", intQ.empty ( ) ? 1 : 0 );
	return 0;
}