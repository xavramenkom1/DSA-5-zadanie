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

    if (!x->parent) *root = y;
    else if (x == x->parent->l) x->parent->l = y;
    else x->parent->r = y;

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

    if (!x->parent) *root = y;
    else if (x == x->parent->l) x->parent->l = y;
    else x->parent->r = y;

    y->r = x;
    x->parent = y;
}

void splay(Node **root, Node *x)
{
    while (x->parent)
    {
        Node *p = x->parent;
        Node *g = p->parent;

        if (!g) // Zig
        {
            if (p->l == x)
                rotateRight(root, p);
            else
                rotateLeft(root, p);
        }
        else if (g->l == p && p->l == x) // Zig-Zig (skos do lava a doleva)
        {
            rotateRight(root, g);
            rotateRight(root, p);
        }
        else if (g->r == p && p->r == x) // Zag-Zag (skos doprava a doprava)
        {
            rotateLeft(root, g);
            rotateLeft(root, p);
        }
        else if (g->r == p && p->l == x) // Zig-Zag (skos doleva a doprava)
        {
            rotateRight(root, p);
            rotateLeft(root, g);
        }
        else // Zag-Zig :) (skos doprava a doleva)
        {
            rotateLeft(root, p);
            rotateRight(root, g);
        }
    }
}

Node *insert(Node **root, int key)
{
    Node *n = *root;
    Node *p = NULL;

    while (n)
    {
        p = n;
        if (key < n->key)
            n = n->l;
        else if (key > n->key)
            n = n->r;
        else // key already exists
        {
            splay(root, n);
            return n;
        }
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->l = newNode->r = NULL;
    newNode->parent = p;

    if (!p) *root = newNode;
    else if (key < p->key) p->l = newNode;
    else p->r = newNode;

    splay(root, newNode);
    return newNode;
}

Node *search(Node **root, int key)
{
    Node *n = *root;
    while (n)
    {
        if (key < n->key)
            n = n->l;
        else if (key > n->key)
            n = n->r;
        else
        {
            splay(root, n);
            return n;
        }
    }
    return NULL;
}

void deleteNode(Node **root, int key)
{
    Node *n = search(root, key);
    if (!n) return;

    splay(root, n);

    Node *LSub = n->l;
    Node *RSub = n->r;

    if (LSub) LSub->parent = NULL;
    if (RSub) RSub->parent = NULL;

    free(n);

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