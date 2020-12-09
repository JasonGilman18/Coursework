#include <iostream>
#include <stdexcept>
#include "Node.h"
#include "DoublyLinkedList.h"

using namespace std;

int main()
try 
{
	/*
    DoublyLinkedList ll;
    cout << ll << endl << endl;
    ll.insert_front(7);
    cout << ll << endl << endl;
    ll.insert_front(11);
    cout << ll << endl << endl;
    ll.insert_front(27);
    cout << ll << endl << endl;
*/

	DoublyLinkedList ll(10);
	ll.insert_front(9);
	ll.insert_back(12);
	ll.insert_at(11,2);
	ll.delete_at(1);
	cout << ll << endl;
	
    return 0;
}
catch(runtime_error& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "error\n";
    return 2;
}