#include <iostream>

#include <dlfcn.h>
//#include <link.h>

using namespace std;

typedef	 void*	dlObjectHandle;

template < typename tn >
class ExternalFunction
{
	dlObjectHandle		d_externalObject;
	tn					(*d_externalFunction)();

  public:
	ExternalFunction( const char* a_objectName,
					  const char* a_function ) : d_externalFunction(NULL)
	{
		// Open the object. NULL object name is OK. It just means
		// open the current object.
		d_externalObject = ::dlopen( a_objectName, RTLD_LAZY );
		if( d_externalObject == NULL )
		{
			cerr << "ExternalFunction(): " << dlerror() << endl;
			exit(-1);
		}
		// Get the function out of the object we just opened
		//! assert( a_function != NULL );
		//! assert( *a_function != '\0' );
		d_externalFunction = (tn(*)())::dlsym( d_externalObject,
											   a_function );
		if( d_externalFunction == NULL )
		{
			cerr << "ExternalFunction(): " << dlerror() << endl;
			exit(-1);
		}
		
	}

	~ExternalFunction()
	{
		if( ::dlclose( d_externalObject ) != 0 )
		{
			cerr << "~ExternalFunction(): " << dlerror() << endl;
		}
	}

	tn		operator()()
	{
		return (*d_externalFunction)();
	}

	   

};
int main( int argc, char** argv )
{
	
	ExternalFunction<void> exf("./mf.so", "myFunc");
	//cerr << exf() << endl;
	exf();
}
