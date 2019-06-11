
#pragma once

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"

#define NO_COLOR "\033[0m"

#define PRINT_GREEN(x) std::cout << GREEN << x << NO_COLOR << std::endl;
#define PRINT_ERROR(x) std::cerr << RED << x << NO_COLOR << std::endl;
#define PRINT_WARNING(x) std::cout << YELLOW << x << NO_COLOR << std::endl;