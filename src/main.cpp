#include <iostream>

#include <list>
#include <string>


int     main(int argc, char const *argv[])
{
    std::list<std::string > comands;




    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
            comands.push_back(argv[i]);
    }

    
    for(auto i : comands)
    {
        std::cout << i << std::endl;
    }
    
    std::cout << "HELLO MOTHERFUCKER" << std::endl;
    return 0;
}
