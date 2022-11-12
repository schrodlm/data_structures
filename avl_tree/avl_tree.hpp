#pragma once

#include <iostream>
#include <list>
/*
    This data structure uses list like connections between its keys/nodes

    Definition of a binary tree:
    1) always has a root
    2) every vortex has max 2 children
    3) we diffirentiate between children -> left|right
*/

#define Product std::string

struct Node
{
private:
public:
    Node(const int val, const Product p, Node* parent);
    Node *left;
    Node *right;
    Node *parent;
    int val;
    int leftTreeSize = 0;
    int rightTreeSize = 0;
    int balanceFactor = 0;
    int height = 1;
    std::list<Product> products;

};

class AVL
{
public:
    AVL();
    ~AVL();
    void insert_node(const int e, const Product p);
    bool delete_node(const int e, const Product p);
    //used when deleting node with two children
    Node* findLeftMax(Node* node);

    int findMin() const;
    int findMax() const;
    bool find(const int e) const;

    void pred(const int e) const;
    void next(const int e) const;

    void print();
    void printNodeInfo(const int e);
    void printAllInfo();


    //used in the destructor
    void delete_tree(Node* node);



private:
    bool insert_node(const int e, const Product p, Node* node);
    bool delete_node(const int e, const Product p, Node* node);
    bool delete_node(const int e, Node* node);


    void print_inner(const std::string& prefix, const Node* node, bool isLeft);
    void printAllInfo(Node* node);


    void RL_rotation(Node* x, Node* y, Node* z);
    void LR_rotation(Node* x, Node* y, Node* z);
    void R_rotation(Node* x, Node* y);
    void L_rotation(Node* x, Node* y);

    Node *root;

};