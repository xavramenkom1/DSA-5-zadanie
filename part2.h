// Splay BST
#pragma once

#include <stdlib.h>

typedef struct Node
{ // Binarny strom
    int key;
    struct Node *l;
    struct Node *r;
    struct Node *parent;
    int height;
} Node;

int maxInt(int a, int b)
{
    return (a > b) ? a : b;
}

void rotateLeft(Node **root, Node *x)
{
    if (!x || !x->r) return;

    Node *y = x->r;
    x->r = y->l;

    if (y->l) y->l->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        *root = y;
    else if (x == x->parent->l)
        x->parent->l = y;
    else
        x->parent->r = y;

    y->l = x;
    x->parent = y;
}
void rotateRight(Node **root, Node *x)
{
    if (!x || !x->l) return;

    Node *y = x->l;
    x->l = y->r;

    if (y->r) y->r->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        *root = y;
    else if (x == x->parent->l)
        x->parent->l = y;
    else
        x->parent->r = y;

    y->r = x;
    x->parent = y;
}

void splay(Node **root, Node *x)
{
    while (x->parent)
    {
        Node *p = x->parent;
        Node *g = p->parent;

        if (!g)
        {
            if (p->l == x)
                rotateRight(root, p);
            else
                rotateLeft(root, p);
        }
        else if (g->l == p && p->l == x)
        {
            rotateRight(root, g);
            rotateRight(root, p);
        }
        else if (g->r == p && p->r == x)
        {
            rotateLeft(root, g);
            rotateLeft(root, p);
        }
        else if (g->r == p && p->l == x)
        {
            rotateRight(root, p);
            rotateLeft(root, g);
        }
        else
        {
            rotateLeft(root, p);
            rotateRight(root, g);
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
            z = z->l;
        else if (key > z->key)
            z = z->r;
        else
        {
            splay(root, z);
            return z;
        }
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->l = newNode->r = NULL;
    newNode->parent = p;

    if (!p)
        *root = newNode;
    else if (key < p->key)
        p->l = newNode;
    else
        p->r = newNode;

    splay(root, newNode);
    return newNode;
}

Node *search(Node **root, int key)
{
    Node *z = *root;
    while (z)
    {
        if (key < z->key)
            z = z->l;
        else if (key > z->key)
            z = z->r;
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
    if (!node) return;

    splay(root, node);

    Node *LSub = node->l;
    Node *RSub = node->r;

    if (LSub) LSub->parent = NULL;
    if (RSub) RSub->parent = NULL;

    free(node);

    if (!LSub)
    {
        *root = RSub;
        return;
    }

    splay(&LSub, LSub);

    Node *maxL = LSub;
    while (maxL->r) maxL = maxL->r;

    splay(&LSub, maxL);

    LSub->r = RSub;
    if (RSub) RSub->parent = LSub;

    *root = LSub;
}