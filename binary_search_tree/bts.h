#include <iostream>

/*
    This data structure uses list like connections between its keys/nodes

    Definition of a binary tree:
    1) always has a root
    2) every vortex has max 2 children
    3) we diffirentiate between children -> left|right
*/

struct Node
{
private:
public:
    Node(const int val);
    Node *left;
    Node *right;
    int val;
};

class BTS
{
public:
    BTS();
    ~BTS();
    void insert_node(const int e);
    bool delete_node(const int e);
    //used when deleting node with two children
    Node* findLeftMax(Node* node);

    int findMin() const;
    int findMax() const;
    bool find(const int e) const;

    void pred(const int e) const;
    void next(const int e) const;

    void print();

    //used in the destructor
    void delete_tree(Node* node);



private:
    void print_inner(const std::string& prefix, const Node* node, bool isLeft);
    Node *root;

};