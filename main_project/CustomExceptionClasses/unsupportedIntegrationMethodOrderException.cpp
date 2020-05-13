#include <exception>
#include <string>

using namespace std;

class unsupportedIntegrationMethodOrderException : public exception
{
private:
    string message = "Currently no numerical integration method for inductors/capacitors supports this order";
public:
    const char * what () const throw () override
    {
    	return message.c_str();
    }
};