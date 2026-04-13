#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* next;
} Node;

typedef struct HashTable {
    int size;
    Node** table;
} HashTable;


int hash(int key, int size){
    return key % size;
}


HashTable* createTable(int size){
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->table = (Node**)malloc(sizeof(Node*) * size);

    for(int i = 0; i < size; i++){
        ht->table[i] = NULL;
    }

    return ht;
}

Node* createNode(int key){
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->next = NULL;
    return n;
}

void insert(HashTable* ht, int key){
    int index = hash(key, ht->size);

    Node* newNode = createNode(key);

    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

volatile Node* search(HashTable* ht, int key){
    int index = hash(key, ht->size);

    Node* curr = ht->table[index];

    while(curr != NULL){
        if(curr->key == key){
            return curr;
        }
        curr = curr->next;
    }

    return NULL;
}

void deleteByKey(HashTable* ht, int key){
    int index = hash(key, ht->size);

    Node* curr = ht->table[index];
    Node* prev = NULL;

    while(curr != NULL){
        if(curr->key == key){
            if(prev == NULL){
                // -first elem
                ht->table[index] = curr->next;
            } else {
                prev->next = curr->next;
            }

            free(curr);
            return;
        }

        prev = curr;
        curr = curr->next;
    }
}

void freeTable(HashTable* ht){
    for(int i = 0; i < ht->size; i++){
        Node* curr = ht->table[i];

        while(curr != NULL){
            Node* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }

    free(ht->table);
    free(ht);
}