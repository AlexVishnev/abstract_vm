#include <iostream>
#include "Core.hpp"

#include <list>
#include <string>
#include <fstream>
#include <unistd.h>


#define PRINT_GREEN(x) std::cout << "\033[0;32m" << x << "\033[0m" << std::endl;


int	main(const int argc, char const *argv[])
{

	Core().__initd(argc, argv);
	return 0;
}
