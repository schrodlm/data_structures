
#pragma once

#include <iostream>

/**
 * @brief Array dynamically saved on the heap -> is resizable
 *
 */
class DynArray
{
public:
    DynArray();
    ~DynArray();
    void push_back(const int element);
    void push_back_malloc(const int element);
    void pop_back();
    void insert(size_t pos, const int element);

    void increase_size();
    const int back() const;
    
    const int size() const; 
    void print() const;

private:
    int *m_Data;
    size_t m_Size;
    size_t m_Pos = 0;
};