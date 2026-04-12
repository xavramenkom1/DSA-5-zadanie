// Splay BST
#pragma once

#include <stdlib.h>

typedef struct Node
{ // Binarny strom
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    int height;
} Node;

int maxInt(int a, int b)
{
    return (a > b) ? a : b;
}

void rotateLeft(Node **root, Node *x)
{
    if (x->right) return;
    Node *y = x->right;
    x->right = y->left;

    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    
    if (!x->parent) *root = y;
    
    else if (x == x->parent->left) x->parent->left = y;
    
    else x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

void rotateRight(Node **root, Node *x)
{
    Node *y = x->left;
    if (!y) return;
    x->left = y->right;
    
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    
    
    if (!x->parent) *root = y;
    
    else if(x == x->parent->left) x->parent->left = y;
    
    else x->parent->right = y;
    
    y->right = x;
    x->parent = y;
}

void splay(Node **root, Node *x)
{
    while (x->parent)
    {
        if (!x->parent->parent)
        { // Zig
            if (x->parent->left == x)
                rotateRight(root, x->parent);
            else
                rotateLeft(root, x->parent);
        }
        else if (x->parent->left == x && x->parent->parent->left == x->parent)
        { // Zig-Zig
            rotateRight(root, x->parent->parent);
            rotateRight(root, x->parent);
        }
        else if (x->parent->right == x && x->parent->parent->right == x->parent)
        { // Zig-Zig
            rotateLeft(root, x->parent->parent);
            rotateLeft(root, x->parent);
        }
        else if (x->parent->left == x && x->parent->parent->right == x->parent)
        { // Zig-Zag
            rotateRight(root, x->parent);
            rotateLeft(root, x->parent);
        }
        else
        { // Zag-Zig :)
            rotateLeft(root, x->parent);
            rotateRight(root, x->parent);
        }
    }
}

Node *insert(Node **root, int key)
{
    Node *z = *root;
    Node *p = NULL;

    while (z)
    {
        p = z;
        if (key < z->key)
            z = z->left;
        else if (key > z->key)
            z = z->right;
        else
        {
            splay(root, z);
            return z;
        }
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->parent = p;

    if (!p)
        *root = newNode;
    else if (key < p->key)
        p->left = newNode;
    else
        p->right = newNode;

    splay(root, newNode);
    return newNode;
}

Node *search(Node **root, int key)
{
    Node *z = *root;
    while (z)
    {
        if (key < z->key)
            z = z->left;
        else if (key > z->key)
            z = z->right;
        else
        {
            splay(root, z);
            return z;
        }
    }
    return NULL;
}

void deleteNode(Node **root, int key)
{
    Node *node = search(root, key);
    if (!node)
        return;

    splay(root, node);

    Node *leftSub = node->left;
    Node *rightSub = node->right;

    if (leftSub)
        leftSub->parent = NULL;
    if (rightSub)
        rightSub->parent = NULL;

    free(node);

    if (!leftSub)
    {
        *root = rightSub;
    }
    else
    {
        Node *maxLeft = leftSub;
        while (maxLeft->right)
            maxLeft = maxLeft->right;
        splay(&leftSub, maxLeft);
        leftSub->right = rightSub;
        if (rightSub)
            rightSub->parent = leftSub;
        *root = leftSub;
    }
}