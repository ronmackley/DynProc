#include <iostream>

extern "C"
{
	void	myFunc() { std::cout << "Hello, world!" << std::endl;  return; }
}	

