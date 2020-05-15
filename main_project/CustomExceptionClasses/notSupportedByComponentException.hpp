#ifndef NOTSUPPORTEDBYCOMPONENTEXCEPTION
#define NOTSUPPORTEDBYCOMPONENTEXCEPTION

#include <exception>
#include <string>

using namespace std;

class notSupportedByComponentException : public exception
{
private:
    string message = "This method is not supported by the component";
public:
    const char * what () const throw () override
    {
    	return message.c_str();
    }
};

#endif