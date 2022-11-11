#include <iostream>
#include "bts.h"


int main()
{

    std::cout << "tests:" << std::endl;

    BTS t;
    t.insert_node(3);
    t.insert_node(4);
    t.insert_node(2);
    t.insert_node(1);
    t.insert_node(13);
    t.insert_node(14);
    t.insert_node(11);
    t.print();

    t.delete_node(13);

    t.insert_node(12);
    t.insert_node(13);
    t.insert_node(15);
    t.insert_node(16);

    t.print();

    t.delete_node(14);
    t.print();

    std::cout << "Max: " << t.findMax() << std::endl;
    std::cout << "Min: " << t.findMin() << std::endl;

    std::cout << "16 is in the list: " <<  std::boolalpha <<t.find(16) << std::endl;
    std::cout << "71 is in the list: " << t.find(71) << std::endl;

    


}