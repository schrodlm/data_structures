#include <iostream>
#include "avl_tree.hpp"
#include <cassert>

int main()
{

    //co udelat dnes?
    // 1) ukazuje to spatne leftTreeSize protoze to nemenis v tech rotacich
    // 2) vyresit to, aby se nic nepridavalo, kdyz se nemeni po insertu struktura stromu -> tedy kdyz dávám prvek na duplikaci


    std::cout << "tests:" << std::endl;

    AVL t;
    // t.insert_node(6, "ham");
    // t.insert_node(4, "sausage");
    // t.insert_node(2, "cacti");
    // t.insert_node(1, "bison meat");
    // t.insert_node(1, "shower gel");
    // t.insert_node(13, "muffin");
    // t.insert_node(13, "chocolate");
    // t.insert_node(14, "eggs");
    // t.insert_node(11, "legs");


    // t.insert_node(2, "d");
    // t.insert_node(3, "dds");
    // t.insert_node(4, "ddsfg");
    // t.print();

    // t.insert_node(5, "fdf");
    // t.insert_node(6, "fdfdfdf");
    // t.print();

    // t.insert_node(1, "fdfdfdf");
    // t.insert_node(0, "fdfdfdf");
    // t.print();

    // t.printAllInfo();


    // AVL c;
    // c.insert_node(6, "fdf");
    // c.insert_node(8, "fdf");
    // c.insert_node(7, "fdf");

    // c.print();
    // c.printAllInfo();



    // AVL d;

    // for(int i = 0; i < 30; i ++)
    // {
    //     d.insert_node(i, "dds");
    // }




    // d.print();
    // d.printAllInfo();



    AVL l;

    l.insert_node(1, "fdfd");
    l.insert_node(2, "fdfd");
    l.insert_node(5, "fdfd");


    l.insert_node(3, "fdfd");
    l.insert_node(3, "gggg");
    l.insert_node(3, "ggggffdfd");
    l.insert_node(3, "ggv");
    l.insert_node(3, "gggf");
    l.insert_node(6, "fdfd");


    l.delete_node(5, "fdfd");

    l.print();
    l.printAllInfo();


    // l.insert_node(4, "fdfd");

    // l.print();
    // l.printAllInfo();

    // l.insert_node(8, "fdfd");
    // l.insert_node(13, "fdfd");


    // l.print();
    // l.printAllInfo();


    // t.printNodeInfo(13);
    // t.printNodeInfo(4);


    // assert(t.delete_node(13));

    // t.insert_node(12);
    // t.insert_node(13);
    // t.insert_node(15);
    // t.insert_node(16);

    // assert(!t.delete_node(100));
    // t.print();

    // t.delete_node(14);
    // t.print();

    // std::cout << "Max: " << t.findMax() << std::endl;
    // std::cout << "Min: " << t.findMin() << std::endl;

    // std::cout << "16 is in the list: " <<  std::boolalpha <<t.find(16) << std::endl;
    // std::cout << "71 is in the list: " << t.find(71) << std::endl;

    


}