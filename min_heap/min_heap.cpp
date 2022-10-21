#include <iostream>
#include <vector>

/*
    HeapInsert(H,k)     - O(log n)  -> inserts a new key into the heap H
    HeapFindMin(H)      - O(1)      -> finds and returns minimum from all the elements in heap H
    HeapExtractMin(H)   - O(log n)  -> deletes a minimum from heap H a returns it


    Indexes in heap 
        Heap is represented not in a binary tree but in a vector/array, it is much faster and thanks to how minHeap is structured it is also fairly easy 
        to manipulate its elements

        We have a vortex V with index of i  -> left child is at 2i
                                            -> right child is at 2i + 1
                                            -> parent is at i/2
                                            -> i mod 2 shows if it is connected to parents left or right side -> if 1 -> right, else left
*/

class MinHeap
{
public:
    MinHeap()
    {
        heap.push_back(0);
    }

    MinHeap(std::vector<int> vec);
    MinHeap& insert(int element);
    int top();
    bool pop();
    void print();
private:

MinHeap& bubbleUp(int p);
void bubbleDown(int p);

std::vector<int> heap;
int size = 0;

};

//its slower than to create build function -> look into it
MinHeap::MinHeap(std::vector<int> vec)
{
    this->heap.push_back(0);
    for(int i : vec)
    {
        this->insert(i);
    }
}


MinHeap& MinHeap::insert(int element)
{
    size++;
    heap.push_back(element);

   return this->bubbleUp(element);
}

int MinHeap::top()
{
    if(size == 0) throw std::runtime_error("Heap is empty");
    return heap[1];
}

bool MinHeap::pop()
{
    if(heap.empty()) return false;

    std::swap(this->heap[this->size],this->heap[1]);

    this->heap.pop_back();

    --size;

    this->bubbleDown(1);

    return true;
    
}

void MinHeap::bubbleDown(int pos)
{
    int element = this->heap[pos];

    while(pos*2 < this->size)
    {
        int child;
        if(this->heap[pos*2] < this->heap[(pos*2)+1])
        {
            child = this->heap[pos*2];

            if(child >= element)
                return;

            std::swap(this->heap[pos*2], this->heap[pos]);

            pos = pos*2;
        } 
        
        else
        {
            child = this->heap[pos*2+1]; 
            if(child >= element)
                return;

            std::swap(this->heap[pos*2+1], this->heap[pos]);

            pos = pos*2+1;
        } 

        
         
    }
}

MinHeap& MinHeap::bubbleUp(int element)
{
    int pos = this->size;
    while(pos != 1)
    {
        int parent_pos = pos / 2;
        int parent = this->heap[parent_pos];
        
        //the structure of the heap was not broken
        if(parent <= element)
            return *this;

        std::swap(this->heap[pos], this->heap[parent_pos]);
        
        pos = parent_pos;
        
    }
    
    return *this;

}

void MinHeap::print()
{
    for(int i = 1; i < (int)this->heap.size(); i++)
    {
        std::cout << this->heap[i] << std::endl;
    }
}

int main()
{

    // MinHeap h;

    // h.insert(5).insert(4).insert(3).insert(10).insert(6).insert(1);
    // h.insert(2);
    // h.insert(13).insert(4).insert(4).insert(7).insert(8).insert(3).insert(5);
    // h.print();
    // std::cout << "-----------------" << std::endl;
    // h.pop();
    // h.pop();
    // h.pop();
    // h.print();
    // std::cout << "Smallest element in heap is: " << h.top() << std::endl;


    // MinHeap k;

    // k.insert(567).insert(87).insert(9).insert(1);
    // std::cout << "Smallest element in heap is: " << k.top() << std::endl;
    // k.pop();
    // std::cout << "Smallest element in heap is: " << k.top() << std::endl;
    // k.print();


    std::vector<int> vec_toPush{30,11,23,41,3,42,13,7};
    MinHeap t(vec_toPush);
    std::cout << "Smallest element in heap is: " << t.top() << std::endl;
    t.pop();
    std::cout << "Popped the smallest element!" << std::endl;
    std::cout << "Smallest element in heap is: " << t.top() << std::endl;

}