#include <stdio.h>

typedef struct Node {
    int key;
    int balance;
    struct Node *right;
    struct Node *left;
    struct Node *parent;
} AVLnode;

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
    FILE *fin = fopen("balance.in", "r"), *fout = fopen("balance.out", "w");
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
    for (unsigned i = 0; i < N; i++) {
        fprintf(fout, "%d\n", data[i].balance);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}