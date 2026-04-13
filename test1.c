#include "part1.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inorder(Node* root){
    if(root){
        inorder(root->l);
        printf("%d ", root->key);
        inorder(root->r);
    }
}

int main(){

    int n[200] = {10, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500,10000, 10500, 11000, 11500, 12000, 12500, 13000, 13500, 14000, 14500,15000, 15500, 16000, 16500, 17000, 17500, 18000, 18500, 19000, 19500,20000, 20500, 21000, 21500, 22000, 22500, 23000, 23500, 24000, 24500, 25000, 25500, 26000, 26500, 27000, 27500, 28000, 28500, 29000, 29500,30000, 30500, 31000, 31500, 32000, 32500, 33000, 33500, 34000, 34500,35000, 35500, 36000, 36500, 37000, 37500, 38000, 38500, 39000, 39500,40000, 40500, 41000, 41500, 42000, 42500, 43000, 43500, 44000, 44500,45000, 45500, 46000, 46500, 47000, 47500, 48000, 48500, 49000, 49500,50000, 50500, 51000, 51500, 52000, 52500, 53000, 53500, 54000, 54500,55000, 55500, 56000, 56500, 57000, 57500, 58000, 58500, 59000, 59500,60000, 60500, 61000, 61500, 62000, 62500, 63000, 63500, 64000, 64500,65000, 65500, 66000, 66500, 67000, 67500, 68000, 68500, 69000, 69500,70000, 70500, 71000, 71500, 72000, 72500, 73000, 73500, 74000, 74500,75000, 75500, 76000, 76500, 77000, 77500, 78000, 78500, 79000, 79500,80000, 80500, 81000, 81500, 82000, 82500, 83000, 83500, 84000, 84500,85000, 85500, 86000, 86500, 87000, 87500, 88000, 88500, 89000, 89500,90000, 90500, 91000, 91500, 92000, 92500, 93000, 93500, 94000, 94500,95000, 95500, 96000, 96500, 97000, 97500, 98000, 98500, 99000, 99500};
    int size = sizeof(n) / sizeof(n[0]);
    Node* root = NULL;

    printf("AVL Insert:\n");

    for(int i = 0; i < size; i++){
        root = NULL;
        clock_t start = clock();

        for(int j = 0; j < n[i]; j++){
            root = insert(root, j);
        }

        clock_t end = clock();

        double time = (double)(end - start) / CLOCKS_PER_SEC;

        // printf("Time for n = %d: %f seconds\n", n[i], time);
        printf("%d %.6f\n", n[i], ((double)(end - start) / CLOCKS_PER_SEC) * 1000000 / n[i]); // Time per insert operation
    }
    putchar('\n');
    printf("AVL Search:\n");

    for (int i = 0; i < size; i++) {
        int N = n[i];
        Node* root = NULL;
        for (int j = 0; j < N; j++) {
            root = insert(root, rand() % N);
        }

        clock_t start = clock();

        int ops = 1000000;
        volatile Node* res = NULL; // ChatGPT suggested using volatile to prevent compilator optimization
        for (int i = 0; i < ops; i++) {
            res = search(root, rand() % N);
        }
        clock_t end = clock();

        // printf("n=%d time=%f sec\n", N, (double)(end - start) / CLOCKS_PER_SEC);
        printf("%d %.5f\n", N, ((double)(end - start) / CLOCKS_PER_SEC) * 1e6 / ops); // Time per search operation
    }
    putchar('\n');
    printf("AVL Delete:\n");
    for (int i = 0; i < size; i++) {
        int N = n[i];

        Node* root = NULL;
        for (int j = 0; j < N; j++) {
            root = insert(root, j);
        }

        clock_t start = clock();
        for (int j = 0; j < N; j++) {
            root = deleteNode(root, rand() % N);
        }
        clock_t end = clock();

        // printf("n=%d time=%f sec\n", N, (double)(end - start) / CLOCKS_PER_SEC);
        printf("%d %.6f\n", N, ((double)(end - start) / CLOCKS_PER_SEC) * 1000000 / N); // Time per delete operation
    }      

}