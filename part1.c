#include <stdio.h>
#include <stdlib.h>

typedef struct Node{ // Binarny strom
    int key;
    Node* left;
    Node* right;
    Node* parent;
} Node;

Node* initializeNode(int key, Node* parent){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;

    return node;

}

Node* insert(Node* root, int key, Node* parent){
    if(root == NULL){
        return initializeNode(key, parent);
    }
    if(key < root->key){
        root->left = insert(root->left, key, root);
    }
    else{
        root->right = insert(root->right, key, root);
    }
    return root;
}



int main(){



}