#include <iostream>
#include "../includes/practice.hpp"


int main()
{

    WorkShop* workshop = new WorkShop();
    std::cout << *workshop << std::endl;


    Worker* one = new Worker();
    std::cout << *one << std::endl;

    Hammer* ham = new Hammer();

    Shovel* tool = new Shovel();
    one->addTool(tool);
    std::cout << *one << std::endl;

    workshop->recruit(one);
    one->work();

    std::cout << *workshop << std::endl;

    Worker* scd = new Worker({3, 5, 1}, {5, 42});
    scd->addTool(ham);
    std::cout << *scd << std::endl;
    workshop->recruit(scd);
    one->giveTool(*scd, "Hammer");
    
    scd->giveTool(*one, "Hammer");
    
    std::cout << *one << std::endl;
    std::cout << *scd << std::endl;
    std::cout << *workshop << std::endl;
    workshop->executeWorkDay();


    delete workshop;
    delete scd;
    delete one;
    return (0);
}