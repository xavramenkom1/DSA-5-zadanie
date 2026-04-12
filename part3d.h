#pragma once

#include <stdlib.h>
#include <stdio.h>


typedef struct HashTable {
    int size;
    int* table;
} HashTable;


int h1(int key, int size){
    return key % size;
}

int h2(int key, int size){
    return 1 + (key % (size - 1));
}

HashTable* create(int size){
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->table = (int*)malloc(sizeof(int) * size);

    for(int i = 0; i < size; i++){
        ht->table[i] = -1;
    }

    return ht;
}

void insert(HashTable* ht, int key){
    for(int i = 0; i < ht->size; i++){
        int index = (h1(key, ht->size) + i * h2(key, ht->size)) % ht->size;

        if(ht->table[index] == -1 || ht->table[index] == -2){
            ht->table[index] = key;
            return;
        }
    }

    printf("Table full!\n");
}

int search(HashTable* ht, int key){
    for(int i = 0; i < ht->size; i++){
        int index = (h1(key, ht->size) + i * h2(key, ht->size)) % ht->size;

        if(ht->table[index] == -1){
            return 0; // nt found
        }

        if(ht->table[index] == key){
            return 1;
        }
    }

    return 0;
}


void deleteKey(HashTable* ht, int key){
    for(int i = 0; i < ht->size; i++){
        int index = (h1(key, ht->size) + i * h2(key, ht->size)) % ht->size;

        if(ht->table[index] == -1){
            return;
        }

        if(ht->table[index] == key){
            ht->table[index] = -2;
            return;
        }
    }
}

void freeTable(HashTable* ht){
    free(ht->table);
    free(ht);
}