#include <iostream>
#include "bts.h"


int main()
{

    std::cout << "tests:" << std::endl;

    BTS t;
    t.insert_node(3);
    t.insert_node(4);
    t.insert_node(1);
    t.insert_node(13);
    t.insert_node(14);
    t.print();

    t.delete_node(13);
    t.print();

}