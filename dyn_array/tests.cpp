#include <iostream>
#include <vector>
#include <chrono>
#include "dynamic_array.h"

int main()
{
    DynArray s;

    s.push_back(2);
    s.push_back(1);
    std::cout << "Size of the array is: " << s.size() << std::endl;

    s.push_back(4);
    s.push_back(3);

    // std::cout << "Size of the array is: " << s.size() << std::endl;

    s.print();
    // std::cout << "Last element in the array is: " << s.back() << std::endl;
    // s.pop_back();
    // s.print();

    s.insert(2, 7);
    s.insert(1, 9);
    s.insert(s.size()-1, 17);
    s.insert(s.size(), 13);
    s.insert(s.size(), 5);




    s.print();


    //trying out of bounds
    try
    {
        s.insert(10, 2);
    }

    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }

    /*
        Push_back time testing
    */
    // std::vector<int> pokus;

    // auto start = std::chrono::steady_clock::now();
    // for (int i = 0; i < 1000000000; i++)
    // {
    //     s.push_back(i);
    // }
    // auto end = std::chrono::steady_clock::now();

    // std::cout << "Elapsed time in microseconds: "
    //           << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    //           << " milliseconds" << std::endl;

    // start = std::chrono::steady_clock::now();
    // for (int i = 0; i < 1000000000; i++)
    // {
    //     s.push_back_malloc(i);
    // }
    // end = std::chrono::steady_clock::now();

    // std::cout << "Elapsed time in microseconds: "
    //           << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    //           << " milliseconds" << std::endl;

    // start = std::chrono::steady_clock::now();
    // for (int i = 0; i < 1000000000; i++)
    // {
    //     pokus.push_back(i);
    // }
    // end = std::chrono::steady_clock::now();

    // std::cout << "Elapsed time in microseconds: "
    //           << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    //           << " milliseconds" << std::endl;
}