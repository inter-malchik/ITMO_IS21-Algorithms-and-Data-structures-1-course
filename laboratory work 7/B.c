#include <stdio.h>
#include <stdbool.h>

typedef struct Node {
    int key;
    int balance;
    struct Node *right;
    struct Node *left;
    struct Node *parent;
} AVLnode;

typedef struct NodePrint {
    struct Node *Node;
    int leftN;
    int rightN;
} AVLprint;

AVLnode *small_left_rotate(AVLnode *root) {
    struct Node *A = root, *B = A->right;
    struct Node *Y = B->left;
    B->left = B->parent;
    B->parent = A->parent;
    A->parent = B;
    A->right = Y;
    if (Y != NULL)
        Y->parent = A;
    return B;
}

AVLnode *big_left_rotate(AVLnode *root) {
    struct Node *A = root, *B = A->right, *C = B->left;
    struct Node *X = C->left, *Y = C->right;
    C->parent = A->parent;
    B->parent = C;
    A->parent = C;
    C->right = B;
    C->left = A;
    A->right = X;
    if (X != NULL)
        X->parent = A;
    B->left = Y;
    if (Y != NULL)
        Y->parent = B;
    return C;
}

int walk(AVLnode *current_node, int length) {
    int len_right = length, len_left = length;
    if (current_node->right == NULL && current_node->left == NULL) {
        current_node->balance = 0;
        return length;
    }
    if (current_node->right != NULL) {
        len_right = walk(current_node->right, length + 1);
    }
    if (current_node->left != NULL) {
        len_left = walk(current_node->left, length + 1);
    }
    current_node->balance = len_right - len_left;
    return (len_right > len_left) ? len_right : len_left;
}

int main(int argc, char **argv) {
    FILE *fin = fopen("rotation.in", "r"), *fout = fopen("rotation.out", "w");
    unsigned N;
    fscanf(fin, "%u", &N);
    AVLnode data[N];
    for (unsigned i = 0; i < N; i++) {
        data[i].balance = 0;
        data[i].right = NULL;
        data[i].left = NULL;
        data[i].parent = NULL;
    }
    for (unsigned i = 0; i < N; i++) {
        int K, L, R;
        fscanf(fin, "%d %d %d", &K, &L, &R);
        data[i].key = K;
        L--;
        if (L >= 0) {
            data[i].left = &data[L];
            data[L].parent = &data[i];
        }
        R--;
        if (R >= 0) {
            data[i].right = &data[R];
            data[R].parent = &data[i];
        }
    }
    walk(&data[0], 1);
    fclose(fin);
    struct Node *head = &data[0];
    struct Node *result;
    bool small_rotate = head->right->balance != -1 ? true : false;
    if (small_rotate)
        result = small_left_rotate(head);
    else
        result = big_left_rotate(head);
    fprintf(fout, "%d\n", N);
    AVLprint bufer_print[N];
    bufer_print[0].Node = result;
    int end = 1;
    for (int i = 0; i < N; i++) {
        if (bufer_print[i].Node->left != NULL) {
            bufer_print[end].Node = bufer_print[i].Node->left;
            bufer_print[i].leftN = end;
            end++;
        } else
            bufer_print[i].leftN = -1;

        if (bufer_print[i].Node->right != NULL) {
            bufer_print[end].Node = bufer_print[i].Node->right;
            bufer_print[i].rightN = end;
            end++;
        } else
            bufer_print[i].rightN = -1;
        fprintf(fout, "%d %d %d\n", bufer_print[i].Node->key, bufer_print[i].leftN + 1, bufer_print[i].rightN + 1);
    }
    return 0;
}