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

template <typename Product>
struct Node
{
private:
public:
    Node(const size_t val, const Product p, Node<Product> *parent);
    Node<Product> *parent;
    Node<Product> *left;
    Node<Product> *right;
    size_t val = 0;
    int leftTreeSize = 0;
    int balanceFactor = 0;
    int height = 1;
    std::list<Product> products;
};

template <typename Product>
class AVL
{
public:
    AVL();
    ~AVL();


    void insert_node(const Product p, const size_t e);
    bool delete_node(const Product p, const size_t e);
    // used when deleting node with two children
    Node<Product> *findLeftMax(Node<Product> *node);

    int findMin() const;
    int findMax() const;
    bool find(const size_t e) const;

    void pred(const size_t e) const;
    void next(const size_t e) const;
    const Product &findNth(int rank) const;
    size_t findNth(size_t e, Product p) const;

    void print();
    size_t printNodeInfo();
    void printAllInfo();

    // used in the destructor
    void delete_tree(Node<Product> *node);

private:
    bool insert_node(const size_t e, const Product p, Node<Product> *node);
    bool delete_node(const size_t e, const Product p, Node<Product> *node);
    bool delete_node(const size_t e, Node<Product> *node);

    void print_inner(const std::string &prefix, const Node<Product> *node, bool isLeft);
    void printAllInfo(Node<Product> *node);
    size_t printNodeInfo(Node<Product> *node);

    void RL_rotation(Node<Product> *x, Node<Product> *y, Node<Product> *z);
    void LR_rotation(Node<Product> *x, Node<Product> *y, Node<Product> *z);
    void R_rotation(Node<Product> *x, Node<Product> *y);
    void L_rotation(Node<Product> *x, Node<Product> *y);
    void balanceCheck(Node<Product> *node);

    const Product &findNth(int rank, Node<Product> *node) const;
    size_t findNth(size_t e, Product p, Node<Product> *node) const;

    Node<Product> *root;
};

#include <iostream>
#include <list>
#include <algorithm>
#include "avl_tree.hpp"


/**
 * @brief Construct a new Node:: Node object
 *
 * @param val       --> Number of sold products
 * @param p         --> Product
 */
template <typename Product>
Node<Product>::Node(const size_t val, const Product p, Node<Product> *parent)
{
    this->val = val;
    this->parent = parent;
    left = nullptr;
    right = nullptr;

    this->products.push_back(p);
}

template <typename Product>
AVL<Product>::AVL() : root(nullptr) {}

template <typename Product>
AVL<Product>::~AVL()
{
    delete_tree(this->root);
}

/**
 * @brief Deletes whole tree - used in a Destructor
 *
 * @param node
 */
template <typename Product>
void AVL<Product>::delete_tree(Node<Product> *node)
{
    if (!node)
        return;

    delete_tree(node->left);
    delete_tree(node->right);

    delete node;

    return;
}

/**
 * @brief Recursively inserts node and since inserting changes structure of the tree
 *          - balances itself if needed
 *          - if the node was sucesfully inserted on they way back from recursion -> changes sizeOfLeftTree if needed
 *          - if node with that value already exist just add this nodes
 *
 * @param e            --> element to insert
 */
template <typename Product>
void AVL<Product>::insert_node(const Product p, const size_t e)
{

    // base case
    if (!this->root)
    {
        root = new Node<Product>(e, p, nullptr);
        return;
    }

    insert_node(e, p, root);
}

template <typename Product>
bool AVL<Product>::insert_node(const size_t e, const Product p, Node<Product> *node)
{

    // this number of sold products is already in the tree
    if (node->val == e)
    {
        node->products.push_back(p);
        return false;
    }

    // GOES INTO LEFT SUBTREE
    if (node->val > e)
    {
        if (node->left == nullptr)
        {
            node->left = new Node<Product>(e, p, node);
            int rightSubtreeHeight = 0;
            (node->right) ? rightSubtreeHeight = node->right->height : 0;
            node->height = std::max(rightSubtreeHeight, node->left->height) + 1;
            node->balanceFactor = rightSubtreeHeight - node->left->height;
            node->leftTreeSize++;

            return true;
        }
        node->leftTreeSize++;

        if (!insert_node(e, p, node->left))
            return false;
    }

    // GOES INTO RIGHT SUBTREE
    else if (node->val < e)
    {
        if (node->right == nullptr)
        {
            node->right = new Node<Product>(e, p, node);
            int leftSubtreeHeight = 0;
            (node->left) ? leftSubtreeHeight = node->left->height : 0;
            node->height = std::max(leftSubtreeHeight, node->right->height) + 1;
            node->balanceFactor = node->right->height - leftSubtreeHeight;
            return true;
        }
        if (!insert_node(e, p, node->right))
            return false;
    }

    balanceCheck(node);

    return true;
}

/**
 * @brief Deletes a node and since deleting changes structure of the tree - it also balanced itself if needed
 *
 * @param e                --> element to remove
 * @return true
 * @return false
 */
template <typename Product>
bool AVL<Product>::delete_node(Product p, const size_t e)
{
    // base case
    if (!root)
    {
        return false;
    }

    return delete_node(e, p, root);
}

template <typename Product>
bool AVL<Product>::delete_node(const size_t e, Product p, Node<Product> *node)
{
    // node doesnt exist
    if (!node)
        return false;

    //============================================
    // NODE WAS FOUND
    //============================================
    if (node->val == e)
    {
        // check if the product to delete is the only one in the list
        if (node->products.size() > 1)
        {
            node->products.remove(p);
            return true;
        }

        // 1.case: Node is a leaf
        if (!node->left && !node->right)
        {
            // node to delete is a root
            if (!node->parent)
                root = nullptr;
            else if (node->parent->val < e)
                node->parent->right = nullptr;
            else
                node->parent->left = nullptr;

            delete node;
        }
        // 2.case: Node has one child
        else if (node->left && !node->right)
        {
            if (!node->parent)
            {
                root = node->left;
                root->parent = nullptr;
            }
            else if (node->parent->val < e)
            {
                node->parent->right = node->left;
                node->left->parent = node->parent;
            }
            else
            {
                node->parent->left = node->left;
                node->left->parent = node->parent;
            }
            delete node;
        }

        else if (node->right && !node->left)
        {
            if (!node->parent)
            {
                root = node->right;
                root->parent = nullptr;
            }
            else if (node->parent->val < e)
            {
                node->parent->right = node->right;
                node->right->parent = node->parent;
            }
            else
            {
                node->parent->left = node->right;
                node->right->parent = node->parent;
            }

            delete node;
        }

        // 3.case: Node has two children
        else
        {
            Node<Product> *tmp = findLeftMax(node);
            int val = tmp->val;

            node->leftTreeSize -= tmp->products.size();
            node->products.swap(tmp->products);

            // overloaded delete_node function just for this case
            delete_node(tmp->val, root);

            node->val = val;
            // we go once left, so we have to decrease left size of this node

            return true;
        }
        return true;
    }

    //============================================
    // FINDING NODE
    //============================================

    if (node->val > e)
    {
        node->leftTreeSize--;

        if (!delete_node(e, p, node->left))
            return false;
    }

    else if (node->val < e)
    {
        if (!delete_node(e, p, node->right))
            return false;
    }

    //============================================
    // BACKTRACKING AND CHECKING STRUCTURE OF THE TREE
    //============================================

    balanceCheck(node);

    return true;
}

template <typename Product>
bool AVL<Product>::delete_node(const size_t e, Node<Product> *node)
{
    // node was found
    if (node->val == e)
    {

        // 1.case: Node is a leaf
        if (!node->left && !node->right)
        {
            if (node->parent->val < e)
                node->parent->right = nullptr;
            else
                node->parent->left = nullptr;

            delete node;
        }
        // 2.case: Node has one child
        else if (node->left && !node->right)
        {
            if (node->parent->val < e)
            {
                node->parent->right = node->left;
                node->left->parent = node->parent;
            }
            else
            {
                node->parent->left = node->left;
                node->left->parent = node->parent;
            }

            delete node;
        }

        else if (node->right && !node->left)
        {
            if (node->parent->val < e)
            {
                node->parent->right = node->right;
                node->right->parent = node->parent;
            }
            else
            {
                node->parent->left = node->right;
                node->right->parent = node->parent;
            }

            delete node;
        }
        return true;
    }

    if (node->val > e)
    {
        delete_node(e, node->left);
    }

    else if (node->val < e)
    {
        delete_node(e, node->right);
    }

    balanceCheck(node);

    return true;
}

template <typename Product>
Node<Product> *AVL<Product>::findLeftMax(Node<Product> *node)
{
    node = node->left;

    while (node->right)
    {
        node = node->right;
    }

    return node;
}

template <typename Product>
void AVL<Product>::print()
{
    print_inner("", root, false);
}

template <typename Product>
void AVL<Product>::print_inner(const std::string &prefix, const Node<Product> *node, bool isLeft)
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

template <typename Product>
size_t AVL<Product>::printNodeInfo()
{
    return printNodeInfo(root);
}

template <typename Product>
size_t AVL<Product>::printNodeInfo(Node<Product> *node)
{
    if (!node)
        return 0;

    return node->products.size() + printNodeInfo(node->left) + printNodeInfo(node->right);
}


/**
 * @brief Prints data that will generate graph by a third party program called Graphviz
 * 
 * @tparam Product 
 */
template <typename Product>
void AVL<Product>::printAllInfo()
{
    std::cout << "digraph {" << std::endl;
    std::cout << "node [shape=circle, width=0.4]" << std::endl;
    printAllInfo(root);
    std::cout << "}" << std::endl;
}

template <typename Product>
void AVL<Product>::printAllInfo(Node<Product> *node)
{
    if (!node)
        return;

    std::string parent = "root";
    if (node->parent)
        parent = std::to_string(node->parent->val);

    std::cout << node->val << " [label = <<FONT POINT-SIZE=\"24.0\" FACE=\"ambrosia\">" << node->val << "</FONT><BR/>leftTreeSize:" << node->leftTreeSize << "<BR/>should be:" << countTreeSize(node->left) << "<BR/>parent:" << parent << "<BR/>products:" << node->products.size() << ">]" << std::endl;
    if (node->left)
        std::cout << node->val << "->" << node->left->val << std::endl;

    if (node->right)
        std::cout << node->val << "->" << node->right->val << std::endl;

    printAllInfo(node->left);
    printAllInfo(node->right);
}

template <typename Product>
int AVL<Product>::findMax() const
{
    Node<Product> *max = root;

    while (max->right)
    {
        max = max->right;
    }

    return max->val;
}

template <typename Product>
int AVL<Product>::findMin() const
{
    Node<Product> *min = root;

    while (min->left)
    {
        min = min->left;
    }

    return min->val;
}

template <typename Product>
bool AVL<Product>::find(const size_t e) const
{
    Node<Product> *toFind = root;

    while (toFind)
    {
        if (toFind->val > e)
            toFind = toFind->left;

        if (toFind->val < e)
            toFind = toFind->right;

        else
            return true;
    }

    return false;
}

/*
=======================================================
                   Rotations
=======================================================
*/

template <typename Product>
void AVL<Product>::L_rotation(Node<Product> *x, Node<Product> *y)
{
    x->right = y->left;
    y->left = x;
    if (x->right)
        x->right->parent = x;
    y->parent = x->parent;
    x->parent = y;

    if (y->parent)
    {
        if (y->parent->val > y->val)
            y->parent->left = y;

        else
            y->parent->right = y;
    }

    int leftSubtreeHX = 0;
    if (x->left)
        leftSubtreeHX = x->left->height;
    int rightSubtreeHX = 0;
    if (x->right)
        rightSubtreeHX = x->right->height;

    x->height = std::max(leftSubtreeHX, rightSubtreeHX) + 1;

    int leftSubtreeHY = 0;
    if (y->left)
        leftSubtreeHY = y->left->height;
    int rightSubtreeHY = 0;
    if (y->right)
        rightSubtreeHY = y->right->height;

    // x->height = std::max(leftSubtreeHX, rightSubtreeHX) + 1;
    y->height = std::max(leftSubtreeHY, x->height) + 1;

    x->balanceFactor = (rightSubtreeHX - leftSubtreeHX);
    y->balanceFactor = (rightSubtreeHY - leftSubtreeHY);

    y->leftTreeSize += (x->leftTreeSize + x->products.size());

    if (x == root)
        root = y;
}

template <typename Product>
void AVL<Product>::R_rotation(Node<Product> *x, Node<Product> *y)
{
    x->left = y->right;
    y->right = x;
    if (x->left)
        x->left->parent = x;
    y->parent = x->parent;
    x->parent = y;

    if (y->parent)
    {
        if (y->parent->val > y->val)
            y->parent->left = y;

        else
            y->parent->right = y;
    }

    int leftSubtreeHX = 0;
    if (x->left)
        leftSubtreeHX = x->left->height;
    int rightSubtreeHX = 0;
    if (x->right)
        rightSubtreeHX = x->right->height;

    x->height = std::max(leftSubtreeHX, rightSubtreeHX) + 1;

    int leftSubtreeHY = 0;
    if (y->left)
        leftSubtreeHY = y->left->height;
    int rightSubtreeHY = 0;
    if (y->right)
        rightSubtreeHY = y->right->height;

    y->height = std::max(leftSubtreeHY, x->height) + 1;

    x->balanceFactor = (rightSubtreeHX - leftSubtreeHX);
    y->balanceFactor = (rightSubtreeHY - leftSubtreeHY);

    if (x->left)
    {
        x->leftTreeSize = countTreeSize(x->left);
    }
    else
        x->leftTreeSize = 0;

    if (x == root)
        root = y;
}

template <typename Product>
int countTreeSize(Node<Product> *node)
{
    if (!node)
        return 0;

    return node->products.size() + countTreeSize(node->left) + countTreeSize(node->right);
}

template <typename Product>
void AVL<Product>::RL_rotation(Node<Product> *x, Node<Product> *y, Node<Product> *z)
{
    R_rotation(y, z);
    L_rotation(x, z);
}

template <typename Product>
void AVL<Product>::LR_rotation(Node<Product> *x, Node<Product> *y, Node<Product> *z)
{
    L_rotation(y, z);
    R_rotation(x, z);
}

template <typename Product>
void AVL<Product>::balanceCheck(Node<Product> *node)
{
    int rightChildBF = (node->right) ? node->right->balanceFactor : 0;
    int leftChildBF = (node->left) ? node->left->balanceFactor : 0;
    // Information about height of subtrees
    int leftSubstreeHeight;
    (node->left) ? leftSubstreeHeight = node->left->height : leftSubstreeHeight = 0;
    int rightSubtreeHeight;
    (node->right) ? rightSubtreeHeight = node->right->height : rightSubtreeHeight = 0;

    node->height = std::max(rightSubtreeHeight, leftSubstreeHeight) + 1;

    // Calculating balanceFactor of this node
    node->balanceFactor = rightSubtreeHeight - leftSubstreeHeight;

    // should we rotate?

    // Primitive rotation L
    if (node->balanceFactor == -2 && leftChildBF <= 0)
        R_rotation(node, node->left);
    // Double rotation LR
    else if (node->balanceFactor == -2 && leftChildBF == 1)
        LR_rotation(node, node->left, node->left->right);

    // Primitive rotation L
    else if (node->balanceFactor == 2 && rightChildBF >= 0)
        L_rotation(node, node->right);

    // Double rotation RL
    else if (node->balanceFactor == 2 && rightChildBF == -1)
        RL_rotation(node, node->right, node->right->left);
}

template <typename Product>
const Product &AVL<Product>::findNth(int rank) const
{
    return findNth(rank, root);
}

template <typename Product>
const Product &AVL<Product>::findNth(int rank, Node<Product> *node) const
{
    int current_rank_low = node->leftTreeSize + 1;
    int current_rank_max = node->leftTreeSize + node->products.size();

    if (rank >= current_rank_low && rank <= current_rank_max)
    {
        typename std::list<Product>::iterator it = node->products.begin();
        std::advance(it, rank - current_rank_low);
        return *it;
    }

    if (current_rank_low > rank)
        return findNth(rank, node->left);

    else
        return findNth(rank - current_rank_max, node->right);
}

template <typename Product>
size_t AVL<Product>::findNth(size_t e, Product p) const
{
    return findNth(e, p, root);
}

template <typename Product>
size_t AVL<Product>::findNth(size_t e, Product p, Node<Product> *node) const
{
    size_t product_nth = 0;

    while (node->val != e)
    {

        if (node->val > e)
        {
            node = node->left;
        }

        else if (node->val < e)
        {
            product_nth += node->leftTreeSize + node->products.size();
            node = node->right;
        }
    }

    for (auto it = node->products.begin(); *it != p; it++)
    {
        product_nth++;
    }
    product_nth += node->leftTreeSize;

    return product_nth;
}