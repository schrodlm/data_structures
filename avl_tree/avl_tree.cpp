#include <iostream>
#include <list>
#include <algorithm>
#include "avl_tree.hpp"

#define Product std::string

/**
 * @brief Construct a new Node:: Node object
 *
 * @param val       --> Number of sold products
 * @param p         --> Product
 */
Node::Node(const int val, const Product p, Node *parent)
{
    this->val = val;
    this->parent = parent;
    left = nullptr;
    right = nullptr;

    this->products.push_back(p);
}

AVL::AVL() : root(nullptr){};

AVL::~AVL()
{
    delete_tree(this->root);
}

/**
 * @brief Deletes whole tree - used in a Destructor
 *
 * @param node
 */
void AVL::delete_tree(Node *node)
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
void AVL::insert_node(const int e, const Product p)
{

    // base case
    if (!this->root)
    {
        root = new Node(e, p, nullptr);
        return;
    }

    insert_node(e, p, root);
}

bool AVL::insert_node(const int e, const Product p, Node *node)
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
            node->left = new Node(e, p, node);
            int rightSubtreeHeight = 0;
            (node->right) ? rightSubtreeHeight = node->right->height : 0;
            node->height = std::max(rightSubtreeHeight, node->left->height) + 1;
            node->balanceFactor = rightSubtreeHeight - node->left->height;
            node->leftTreeSize++;

            return true;
        }
        if (!insert_node(e, p, node->left))
            return false;

        node->leftTreeSize++;
    }

    // GOES INTO RIGHT SUBTREE
    else if (node->val < e)
    {
        if (node->right == nullptr)
        {
            node->right = new Node(e, p, node);
            int leftSubtreeHeight = 0;
            (node->left) ? leftSubtreeHeight = node->left->height : 0;
            node->height = std::max(leftSubtreeHeight, node->right->height) + 1;
            node->balanceFactor = node->right->height - leftSubtreeHeight;
            return true;
        }
        if (!insert_node(e, p, node->right))
            return false;
    }

    int leftChildBF = (node->left) ? node->left->balanceFactor : 0;

    int rightChildBF =(node->right) ? node->right->balanceFactor : 0;

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
    if (node->balanceFactor == -2 && leftChildBF == -1)
        R_rotation(node, node->left);
    // Double rotation LR
    else if (node->balanceFactor == -2 && leftChildBF == 1)
        LR_rotation(node, node->left, node->left->right);

    // Primitive rotation L
    else if (node->balanceFactor == 2 && rightChildBF == 1)
        L_rotation(node, node->right);

    // Double rotation RL
    else if (node->balanceFactor == 2 && rightChildBF == -1)
        RL_rotation(node, node->right, node->right->left);

    return true;
}

/**
 * @brief Deletes a node and since deleting changes structure of the tree - it also balanced itself if needed
 *
 * @param e                --> element to remove
 * @return true
 * @return false
 */
bool AVL::delete_node(const int e, Product p)
{
    // base case
    if (!root)
    {
        return false;
    }

    return delete_node(e, p, root);
}

bool AVL::delete_node(const int e, Product p, Node *node)
{
    // node doesnt exist
    if (!node)
        return false;

    //============================================
    // NODE WAS FOUND
    //============================================
    if(node->val == e)
    {
        // check if the product to delete is the only one in the list
        if (node->products.size() > 1)
        {
            node->products.remove(p);
            return false;
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
                root = node->left;
            else if (node->parent->val < e)
            {
                node->parent->right = node->left;
            }
            else
                node->parent->left = node->left;
        }

        else if (node->right && !node->left)
        {
            if (!node->parent)
                root = node->right;
            else if (node->parent->val < e)
            {
                node->parent->right = node->right;
            }
            else
                node->parent->left = node->right;

            delete node;
        }

        // 3.case: Node has two children
        else
        {
            Node *tmp = findLeftMax(node);
            std::list<Product> l = tmp->products;
            int val = tmp->val;

            // overloaded delete_node function just for this case
            delete_node(tmp->val, root);

            node->products = l;
            node->val = val;

            return false;
        }
        return true;
    }


    //============================================
    // FINDING NODE
    //============================================

    if (node->val > e)
    {
        if (!delete_node(e, p, node->left))
            return false;

        node->leftTreeSize--;
    }

    else if (node->val < e)
    {
        if (!delete_node(e, p, node->right))
            return false;

    }

    //============================================
    // BACKTRACKING AND CHECKING STRUCTURE OF THE TREE
    //============================================
    

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
        if (node->balanceFactor == -2 && leftChildBF == -1)
            R_rotation(node, node->left);
        // Double rotation LR
        else if (node->balanceFactor == -2 && leftChildBF == 1)
            LR_rotation(node, node->left, node->left->right);

                // Primitive rotation L
        else if (node->balanceFactor == 2 && rightChildBF == 1)
            L_rotation(node, node->right);

        // Double rotation RL
        else if (node->balanceFactor == 2 && rightChildBF == -1)
            RL_rotation(node, node->right, node->right->left);

        return true;
}

bool AVL::delete_node(const int e, Node *node)
{
        // node was found
    if(node->val == e)
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
            }
            else
                node->parent->left = node->left;

            delete node;
        }

        else if (node->right && !node->left)
        {
            if (node->parent->val < e)
            {
                node->parent->right = node->right;
            }
            else
                node->parent->left = node->right;
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
        if (node->balanceFactor == -2 && leftChildBF == -1)
            R_rotation(node, node->left);
        // Double rotation LR
        else if (node->balanceFactor == -2 && leftChildBF == 1)
            LR_rotation(node, node->left, node->left->right);

                // Primitive rotation L
        else if (node->balanceFactor == 2 && rightChildBF == 1)
            L_rotation(node, node->right);

        // Double rotation RL
        else if (node->balanceFactor == 2 && rightChildBF == -1)
            RL_rotation(node, node->right, node->right->left);

    return true;

}

Node *AVL::findLeftMax(Node *node)
{
    node = node->left;

    while (node->right)
    {
        node = node->right;
    }

    return node;
}

void AVL::print()
{
    print_inner("", root, false);
}

void AVL::print_inner(const std::string &prefix, const Node *node, bool isLeft)
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

void AVL::printNodeInfo(const int e)
{
    Node *node = root;

    while (node)
    {
        if (node->val < e)
        {
            node = node->right;
        }
        else if (node->val > e)
            node = node->left;
        else
        {
            std::cout << "{ ";
            for (auto &i : node->products)
            {
                std::cout << i << ",";
            }
            std::cout << " }" << std::endl;

            std::cout << "leftTreeSize: \t" << node->leftTreeSize << std::endl;
            return;
        }
    }
}

void AVL::printAllInfo()
{
    printAllInfo(root);
}

void AVL::printAllInfo(Node *node)
{
    if (!node)
        return;

    printAllInfo(node->left);

    std::cout << "Node:\t" << node->val << std::endl;

    std::cout << "Products:" << std::endl;
    std::cout << "{ ";
    for (auto &i : node->products)
    {
        std::cout << i << ",";
    }
    std::cout << " }" << std::endl;

    std::cout << "leftTreeSize:\t" << node->leftTreeSize << std::endl;
    if (node->parent)
        std::cout << "Parent:\t" << node->parent->val << std::endl;

    std::cout << "height:\t" << node->height << std::endl;
    std::cout << "BF:\t" << node->balanceFactor << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << std::endl;

    printAllInfo(node->right);
}

int AVL::findMax() const
{
    Node *max = root;

    while (max->right)
    {
        max = max->right;
    }

    return max->val;
}

int AVL::findMin() const
{
    Node *min = root;

    while (min->left)
    {
        min = min->left;
    }

    return min->val;
}

bool AVL::find(const int e) const
{
    Node *toFind = root;

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

void AVL::L_rotation(Node *x, Node *y)
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

    y->leftTreeSize += (x->leftTreeSize + 1);

    if (x == root)
        root = y;
}

void AVL::R_rotation(Node *x, Node *y)
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
        x->leftTreeSize = x->left->leftTreeSize + 1;
    else
        x->leftTreeSize = 0;

    if (x == root)
        root = y;
}

void AVL::RL_rotation(Node *x, Node *y, Node *z)
{
    R_rotation(y, z);
    L_rotation(x, z);
}

void AVL::LR_rotation(Node *x, Node *y, Node *z)
{
    L_rotation(y, z);
    R_rotation(x, z);
}