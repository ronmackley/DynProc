#include <iostream>

extern "C"
{
	void	myFunc() { std::cout << "Hello!" << std::endl;  return; }
}	

