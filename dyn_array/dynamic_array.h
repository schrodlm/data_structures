
#pragma once

#include <iostream>

/**
 * @brief Array dynamically saved on the heap -> is resizable
 *
 */
template<typename _T>
class DynArray
{
public:
    DynArray();
    ~DynArray();
    void push_back(const _T element);
    void push_back_malloc(const _T element);
    void pop_back();
    void insert(size_t pos, const _T element);

    void increase_size();
    const _T back() const;
    
    const int size() const; 
    void print() const;

private:
    _T *m_Data;
    size_t m_Size;
    size_t m_Pos = 0;
};