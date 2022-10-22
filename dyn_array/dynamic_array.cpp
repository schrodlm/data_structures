#include <iostream>
#include <chrono>
#include <string>
#include "dynamic_array.h"
#include <cstring>


/**
 * @brief have to initiliaze my array by allocating data
 * 
 */
template<typename _T>
DynArray<_T>::DynArray()
{
    m_Size = 3;
    this->m_Data = (_T*)malloc(m_Size * sizeof(_T));
}


/**
 * @brief have to deallocate the memory allocated by malloc/realloc
 * 
 */
template<typename _T>
DynArray<_T>::~DynArray()
{
    free(m_Data);
}

template<typename _T>
void DynArray<_T>::increase_size()
{
    m_Data = (_T *)realloc(m_Data, (m_Size = (m_Size * 2 + 2)) * sizeof(_T));
}

/**
 * @brief slower pushback that uses malloc rather then realloc - it works exactly the same but is slower 
 *          -> have it here so I can debug why is it so much slower
 * 
 */
template<typename _T>
void DynArray<_T>::push_back_malloc(const _T element)
{
    if (m_Size > m_Pos)
    {
        this->m_Data[m_Pos++] = element;
        return;
    }

    //Array is too small to add another element, making it bigger

    _T *temp_Data = (_T *)malloc((m_Size = (m_Size * 2 + 2)) * sizeof(_T));

    for (int i = 0; i < (int)m_Pos; i++)
    {
        temp_Data[i] = this->m_Data[i];
    }

    free(m_Data);

    m_Data = temp_Data;

    this->m_Data[m_Pos++] = element;
    return;
}


/**
 * @brief insert element to the last place in the array, might have to reallocate the heap 
 * 
 */
template<typename _T>
void DynArray<_T>::push_back(const _T element)
{
    if (m_Size > m_Pos)
    {
        this->m_Data[m_Pos++] = element;
        return;
    }

    // std::cout << "array is too small to add this element, making it bigger" << std::endl;
    increase_size();

    this->m_Data[m_Pos++] = element;
    return;
}


/**
 * @brief removes last element from the array
 * 
 */
template<typename _T>
void DynArray<_T>::pop_back()
{
    m_Pos--;
}

/**
 * @brief insert one element into specified place
 *  
 */
template<typename _T>
void DynArray<_T>::insert(size_t pos, const _T element)
{
    if(pos > m_Pos) throw std::runtime_error("Provided position out of bounds.");

    if (m_Size > m_Pos)
    {
        //moves memory from source to destination by a number of bytes
        // it is used instead of memcpy when copied memory is being overlapped (slightly slower than memcpy)
        memmove(m_Data + pos + 1,m_Data + pos, (m_Pos-pos) * sizeof(_T));
    }
    else 
    {
        std::cout << "Insert is increasing size for element: " << element << std::endl;
        increase_size();

    }
        m_Data[pos] = element;
        m_Pos++;
        return;
}
template<typename _T>
const _T DynArray<_T>::back() const
{
    return m_Data[m_Pos-1];
}

template<typename _T>
const int DynArray<_T>::size() const
{
    return this->m_Pos;
}

template<typename _T>
void DynArray<_T>::print() const
{
    std::cout << "{";
    for (int i = 0; i < (int)m_Pos; i++)
    {
        std::cout << m_Data[i];
        if(i+1 < (int)m_Pos) std::cout << ", "; 
    }
    std::cout << "}" << std::endl;
}

    template class DynArray<int>;
    template class DynArray<std::string>;



