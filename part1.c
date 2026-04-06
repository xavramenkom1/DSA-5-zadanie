#include <stdio.h>
#include <stdlib.h>

typedef struct Node{ // Binarny strom
    int key;
    struct Node* left;
    struct Node* right;
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

Node* initializeNode(int key, Node* parent){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    node->height = 1; 

    return node;

}

Node* rightRotate(Node* y){
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    if(T2 != NULL){
        T2->parent = y;
    }

    x->parent = y->parent;
    y->parent = x;

    y->height = 1 + maxInt(height(y->left), height(y->right));
    x->height = 1 + maxInt(height(x->left), height(x->right));

    return x;
}

Node* leftRotate(Node* x){
    Node* y = x->right;
    Node* z = y->left;

    y->left = x;
    x->right = z;

    if(z != NULL){
        z->parent = x;
    }

    y->parent = x->parent;
    x->parent = y;

    x->height = 1 + maxInt(height(x->left), height(x->right));
    y->height = 1 + maxInt(height(y->left), height(y->right));

    return y;
}
int getBalance(Node* n){
    return n ? height(n->left) - height(n->right) : 0;
}


Node* insert(Node* node, int key, Node* parent){
    if(node == NULL){
        return initializeNode(key, parent);
    }

    if(key < node->key){
        node->left = insert(node->left, key, node);
    } else if(key > node->key){
        node->right = insert(node->right, key, node);
    } else {
        return node;
    }

    node->height = 1 + maxInt(height(node->left), height(node->right));

    int balance = getBalance(node);

    if(balance > 1 && key < node->left->key){
        return rightRotate(node);
    }

    if(balance < -1 && key > node->right->key){
        return leftRotate(node);
    }

    if(balance > 1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if(balance < -1 && key < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(Node* root){
    if(root != NULL){
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void printTree(Node* root, int space){
    if(root == NULL){
        return;
    }

    space += 5;

    printTree(root->right, space);

    printf("\n");
    for(int i = 5; i < space; i++){
        printf(" ");
    }
    printf("%d\n", root->key);

    printTree(root->left, space);
}

int main(){
    Node* root = NULL;

    int arr[] = {10, 20, 30, 40, 50, 25, 92, 85, 70, 60, 80, 90, 95, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500};
    int n = sizeof(arr)/sizeof(arr[0]);

    for(int i = 0; i < n; i++){
        root = insert(root, arr[i], NULL);
    }

    printTree(root, 0);

    printf("Root: %d\n", root->key);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");
}