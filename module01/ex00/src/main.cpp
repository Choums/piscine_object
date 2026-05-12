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

    Position p2 = {3, 5, 1};
    Statistic s2 = {5, 42};
    Worker* scd = new Worker(p2, s2);
    scd->addTool(ham);
    std::cout << *scd << std::endl;
    workshop->recruit(scd);

    std::cout << *workshop << std::endl;


    one->giveTool(*scd, "Hammer");
    scd->giveTool(*one, "Hammer");
    
    std::cout << *one << std::endl;
    std::cout << *scd << std::endl;
    std::cout << *workshop << std::endl;
    workshop->executeWorkDay();
    
    std::vector<Worker*> v1;
    v1.push_back(one);

    WorkShop* workshop2 = new WorkShop(v1);
    std::cout << *workshop2 << std::endl;
    
    workshop2->executeWorkDay();
    std::cout << *one << std::endl;

    delete workshop2;
    delete workshop;
    delete scd;
    delete one;
    return (0);
}