#include <iostream>
#include "bts.h"

Node::Node(const int val)
{
    this->val = val;
    left = nullptr;
    right = nullptr;
}

BTS::BTS() : root(nullptr){};

BTS::~BTS()
{
    delete_tree(this->root);
}

void BTS::delete_tree(Node *node)
{
    if (!node)
        return;

    delete_tree(node->left);
    delete_tree(node->right);

    delete node;

    return;
}

void BTS::insert_node(const int e)
{
    // empty tree
    if (!root)
    {
        root = new Node(e);
        return;
    }

    Node **tmp = &root;

    while ((*tmp))
    {
        if ((*tmp)->val > e)
        {
            tmp = &(*tmp)->left;
        }

        else if ((*tmp)->val < e)
        {
            tmp = &(*tmp)->right;
        }

        // value is a duplicate
        else
            return;
    }

    *tmp = new Node(e);
}

bool BTS::delete_node(const int e)
{
    // empty tree
    if (!root)
        return false;

       Node **del  = &root;

    //finding node
    while ((*del))
    {
        if ((*del)->val > e)
        {
            del = &(*del)->left;
        }

        else if ((*del)->val < e)
        {
            del = &(*del)->right;
        }

        //node found
        else break;
    }

    // node was not found
    if(!(*del)) return false;

    // 1.case - node is a leaf
    if(!(*del)->left && !(*del)->right)
    {
        delete *del;
        *del = nullptr;
        return true;
    }

    //2.case - node has one child

        //only left child
    if((*del)->left && !(*del)->right)
    {
        Node* tmp = (*del)->left;
        delete *del;
        *del = tmp;
        return true;
    }
    
    if((*del)->right && !(*del)->left)
    {
        Node* tmp = (*del)->right;
        delete *del;
        *del = tmp;
        return true;
    }

return true;

}

void BTS::print()
{
    print_inner("", root, false);
}

void BTS::print_inner(const std::string &prefix, const Node *node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");

        // print the value of the node
        std::cout << node->val << std::endl;

        // enter the next tree level - left and right branch
        print_inner(prefix + (isLeft ? "│   " : "    "), node->left, true);
        print_inner(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

