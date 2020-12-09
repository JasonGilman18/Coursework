#include <stdexcept>
#include <string>
using namespace std;

class DequeException: public out_of_range
{
public:
   DequeException(const string & message = "")
                        : out_of_range(message.c_str())
   { }
}; // end DequeException