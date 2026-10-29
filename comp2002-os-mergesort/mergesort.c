/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
    int index = leftstart, st = leftstart, len = rightend - leftstart + 1;

    while (leftstart <= leftend && rightstart <= rightend) {
        if (A[leftstart] < A[rightstart]) {
            B[index++] = A[leftstart++];
        } else {
            B[index++] = A[rightstart++];
        }
    }

    while (leftstart <= leftend)     B[index++] = A[leftstart++];
    while (rightstart <= rightend)     B[index++] = A[rightstart++];

    memcpy(&A[st], &B[st], sizeof(int) * len);
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
    // base case
    if (left >= right) return;

    // recursion
    int mid = left + (right - left) / 2;
    my_mergesort(left, mid);
    my_mergesort(mid + 1, right);
    
    // merge both halves
    merge(left, mid, mid + 1, right);
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
    struct argument *in = (struct argument *)arg;

    int left = in->left;
    int right = in->right;
    int level = in->level;

    // base case
    if (left >= right) return NULL;

    // stop creating threads after cutoff
    if (level >= cutoff) {
        my_mergesort(left, right);
        return NULL;
    }

    my_mergesort(left, right);

    return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
    struct argument *p = malloc(sizeof(struct argument));
    p->left = left;
    p->right = right;
    p->level = level;
    return p;
}

