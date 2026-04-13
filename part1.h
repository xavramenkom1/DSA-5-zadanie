// AVL BST
#pragma once

#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* l;
    struct Node* r;
    int height;
} Node;

int maxInt(int a, int b){
    return (a > b) ? a : b;
}

int height(Node* node){
    if(node == NULL){
        return 0;
    }
    return node->height;
}

Node* minValueNode(Node* node){
    Node* current = node;
    while(current->l != NULL){
        current = current->l;
    }
    return current;
}

int getBalance(Node* n){
    return n ? height(n->l) - height(n->r) : 0;
}

Node* initializeNode(int key){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->l = NULL;
    node->r = NULL;
    node->height = 1; 

    return node;
}

Node* rightRotate(Node* y){
    Node* x = y->l;
    Node* T2 = x->r;

    x->r = y;
    y->l = T2;

    y->height = 1 + maxInt(height(y->l), height(y->r));
    x->height = 1 + maxInt(height(x->l), height(x->r));

    return x;
}

Node* leftRotate(Node* x){
    Node* y = x->r;
    Node* T2 = y->l;

    y->l = x;
    x->r = T2;

    x->height = 1 + maxInt(height(x->l), height(x->r));
    y->height = 1 + maxInt(height(y->l), height(y->r));

    return y;
}

Node* search(Node* root, int key){
    if(root == NULL || root->key == key){
        return root;
    }

    if(key < root->key){
        return search(root->l, key);
    } else {
        return search(root->r, key);
    }
}


Node* balance(Node* n){
    if(!n) return n;

    n->height = 1 + maxInt(height(n->l), height(n->r));
    int bf = getBalance(n);

    // LL
    if(bf > 1 && getBalance(n->l) >= 0)
        return rightRotate(n);

    // LR
    if(bf > 1 && getBalance(n->l) < 0){
        n->l = leftRotate(n->l);
        return rightRotate(n);
    }

    // RR
    if(bf < -1 && getBalance(n->r) <= 0)
        return leftRotate(n);

    // RL
    if(bf < -1 && getBalance(n->r) > 0){
        n->r = rightRotate(n->r);
        return leftRotate(n);
    }

    return n;
}

Node* insert(Node* n, int key){
    if(!n) return initializeNode(key);

    if(key < n->key)
        n->l = insert(n->l, key);
    else if(key > n->key)
        n->r = insert(n->r, key);
    else
        return n;

    return balance(n);
}

Node* deleteNode(Node* root, int key){
    if(!root) return root;

    if(key < root->key){
        root->l = deleteNode(root->l, key);
    }
    else if(key > root->key){
        root->r = deleteNode(root->r, key);
    }
    else {
        if(!root->l || !root->r){
            Node* temp = root->l ? root->l : root->r;

            if(!temp){
                free(root);
                return NULL;
            } else {
                Node* old = root;
                root = temp;
                free(old);
            }
        }
        else {
            Node* temp = minValueNode(root->r);
            root->key = temp->key;
            root->r = deleteNode(root->r, temp->key);
        }
    }

    return balance(root);
}