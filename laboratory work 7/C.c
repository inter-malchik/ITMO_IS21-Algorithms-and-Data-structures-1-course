#include <stdio.h>
#include <stdbool.h>

#define CANON_ROOT data[0]

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

AVLnode *small_right_rotate(AVLnode *root) {
    struct Node *A = root, *B = A->left;
    struct Node *Y = B->right;
    B->right = B->parent;
    B->parent = A->parent;
    A->parent = B;
    A->left = Y;
    if (Y != NULL)
        Y->parent = A;
    return B;
}

AVLnode *big_right_rotate(AVLnode *root) {
    struct Node *A = root, *B = A->left, *C = B->right;
    struct Node *X = C->left, *Y = C->right;
    C->parent = A->parent;
    B->parent = C;
    A->parent = C;
    C->right = A;
    C->left = B;
    B->right = X;
    if (X != NULL)
        X->parent = A;
    A->left = Y;
    if (Y != NULL)
        Y->parent = B;
    return C;
}

int main(int argc, char **argv) {
    FILE *fin = fopen("addition.in", "r"), *fout = fopen("addition.out", "w");
    unsigned N;
    fscanf(fin, "%u", &N);
    AVLnode data[N + 1];
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
    int new_node_key;
    fscanf(fin, "%d", &new_node_key);
    if (N == 0) {
        fprintf(fout, "1\n%d 0 0", new_node_key);
        return 0;
    }
    data[N].key = new_node_key;
    data[N].right = NULL;
    data[N].left = NULL;
    data[N].parent = NULL;
    struct Node *current = &CANON_ROOT;
    struct Node *new_node = &data[N];
    while (1) {
        if (new_node_key < current->key) {
            if (current->left != NULL)
                current = current->left;
            else {
                current->left = new_node;
                new_node->parent = current;
                break;
            }
        } else if (new_node_key > current->key) {
            if (current->right != NULL)
                current = current->right;
            else {
                current->right = new_node;
                new_node->parent = current;
                break;
            }
        }
    }
    walk(&CANON_ROOT, 0);
    fclose(fin);
    struct Node *head = new_node;
    do {
        head = head->parent;
        if (head->balance > 1) {
            if (head->right != NULL) {
                if (head->right->balance != -1)
                    head = small_left_rotate(head);
                else
                    head = big_left_rotate(head);
                if (head->parent == NULL)
                    continue;
                if (head->parent->key < head->key)
                    head->parent->right = head;
                else
                    head->parent->left = head;
                walk((CANON_ROOT.parent == NULL) ? &CANON_ROOT : &CANON_ROOT.parent, 0);
            }
        } else if (head->balance < -1) {
            if (head->left != NULL) {
                if (head->left->balance != 1)
                    head = small_right_rotate(head);
                else
                    head = big_right_rotate(head);
                if (head->parent == NULL)
                    continue;
                if (head->parent->key < head->key)
                    head->parent->right = head;
                else
                    head->parent->left = head;
                walk((CANON_ROOT.parent == NULL) ? &CANON_ROOT : &CANON_ROOT.parent, 0);
            }
        }
    } while (head->parent != NULL);
    fprintf(fout, "%d\n", N + 1);
    AVLprint bufer_print[N + 1];
    bufer_print[0].Node = (head->parent == NULL) ? head : head->parent;
    int end = 1;
    for (int i = 0; i < N + 1; i++) {
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