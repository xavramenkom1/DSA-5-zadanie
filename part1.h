// AVL BST
#pragma once

#include <stdlib.h>

typedef struct Node{ // Binarny strom
    int key;
    struct Node* l;
    struct Node* r;
    struct Node* parent;
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

Node* initializeNode(int key, Node* parent){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->l = NULL;
    node->r = NULL;
    node->parent = parent;
    node->height = 1; 

    return node;

}

Node* rightRotate(Node* y){
    Node* x = y->l;
    Node* T2 = x->r;

    x->r = y;
    y->l = T2;

    if(T2 != NULL){
        T2->parent = y;
    }

    x->parent = y->parent;
    y->parent = x;

    y->height = 1 + maxInt(height(y->l), height(y->r));
    x->height = 1 + maxInt(height(x->l), height(x->r));

    return x;
}

Node* leftRotate(Node* x){
    Node* y = x->r;
    Node* z = y->l;

    y->l = x;
    x->r = z;

    if(z != NULL){
        z->parent = x;
    }

    y->parent = x->parent;
    x->parent = y;

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


Node* balance(Node* node){
    if(node == NULL) return node;

    node->height = 1 + maxInt(height(node->l), height(node->r));

    int bf = getBalance(node);

    if(bf > 1 && getBalance(node->l) >= 0){
        node = rightRotate(node);
    }
    else if(bf > 1 && getBalance(node->l) < 0){
        node->l = leftRotate(node->l);
        node = rightRotate(node);
    }
    else if(bf < -1 && getBalance(node->r) > 0){
        node->r = rightRotate(node->r);
        node = leftRotate(node);
    }
    else if(bf < -1 && getBalance(node->r) <= 0){
        node = leftRotate(node);
    }
    if(node->l) node->l->parent = node;
    if(node->r) node->r->parent = node;

    return node;
}

Node* insert(Node* node, int key, Node* parent){
    if(node == NULL){
        return initializeNode(key, parent);
    }

    if(key < node->key){
        node->l = insert(node->l, key, node);
    } else if(key > node->key){
        node->r = insert(node->r, key, node);
    } else {
        return node;
    }

    return balance(node);
}

Node* deleteNode(Node* root, int key){
    if(root == NULL){
        return root;
    }

    if(key < root->key){
        root->l = deleteNode(root->l, key);
        if(root->l) root->l->parent = root;
    } 
    else if(key > root->key){
        root->r = deleteNode(root->r, key);
        if(root->r) root->r->parent = root;
    } 
    else {
        if(root->l == NULL || root->r == NULL){
            Node* temp = root->l ? root->l : root->r;

            if(temp == NULL){
                free(root);
                return NULL;
            } else {
                temp->parent = root->parent;
                free(root);
                return temp;
            }
        } 
        else {
            Node* temp = minValueNode(root->r);
            root->key = temp->key;

            root->r = deleteNode(root->r, temp->key);
            if(root->r) root->r->parent = root;
        }
    }

    return balance(root);
}