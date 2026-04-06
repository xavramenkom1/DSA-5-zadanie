#include "part1.h"
#include "part2.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    clock_t start, end;

    Node* root = NULL;

    printf("-------AVL insert TEST-------\n");
    for(int n = 10; n < 10000; n *= 100){ // AVL insert TEST
        start = clock();
        for(int i = 0; i < n; i++){
            root = insertAVL(root, rand() % 1000000, NULL);
        }
        end = clock();
        printf("n = %d, Time = %f seconds\n", n, ((double)(end - start)) / CLOCKS_PER_SEC);
    }
    printf("-------Splay insert TEST-------\n");

    for(int n = 10; n < 10000; n *= 100){ // Splay insert TEST
        Node* rootSplay = NULL;
        start = clock();
        for(int i = 0; i < n; i++){
            insertSplay(&rootSplay, rand() % 1000000);
        }
        end = clock();
        printf("n = %d, Time = %f seconds\n", n, ((double)(end - start)) / CLOCKS_PER_SEC);
    }
    printf("-------AVL delete TEST-------\n");
    // for(int n = 10; n < 10000; n *= 100){ // AVL delete TEST
    //     start = clock();
    //     for(int i = 0; i < n; i++){
    //         root = deleteAVL(root, rand() % 1000000);
    //     }
    //     end = clock();
    //     printf("n = %d, Time = %f seconds\n", n, ((double)(end - start)) / CLOCKS_PER_SEC);
    // }

    printf("-------splay delete TEST-------\n");
    for(int n = 10; n < 10000; n *= 100){ // Splay delete TEST
        Node* rootSplay = NULL;
        start = clock();
        for(int i = 0; i < n; i++){
            deleteSplay(&rootSplay, rand() % 1000000);
        }
        end = clock();
        printf("n = %d, Time = %f seconds\n", n, ((double)(end - start)) / CLOCKS_PER_SEC);
    }

    printf("-------AVL search TEST-------\n");
    // for(int n = 10; n < 10000; n *= 100){ // AVL search TEST
    //     start = clock();
    //     for(int i = 0; i < n; i++){
    //         searchAVL(root, rand() % 1000000);
    //     }
    //     end = clock();
    //     printf("n = %d, Time = %f seconds\n", n, ((double)(end - start)) / CLOCKS_PER_SEC);
    // }

    printf("-------splay search TEST-------\n");

    for(int n = 10; n < 10000; n *= 100){ // Splay search TEST
        Node* rootSplay = NULL;
        start = clock();
        for(int i = 0; i < n; i++){
            searchSplay(&rootSplay, rand() % 1000000);
        }
        end = clock();
        printf("n = %d, Time = %f seconds\n", n, ((double)(end - start)) / CLOCKS_PER_SEC);
    }
}