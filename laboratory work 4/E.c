#include <stdio.h>

int binary_search_left(int arr[], int left_ind, int right_ind, int key, int length) {
    while (left_ind < right_ind - 1) {
        int mid_ind = left_ind + (right_ind - left_ind) / 2;
        if (arr[mid_ind] < key) {
            left_ind = mid_ind;
        } else {
            right_ind = mid_ind;
        }
    }
    if ((right_ind < length) && (arr[right_ind] == key)) {
        return right_ind + 1;
    } else {
        return -1;
    }
}

int binary_search_right(int arr[], int left_ind, int right_ind, int key, int length) {
    while (left_ind < right_ind - 1) {
        int mid_ind = left_ind + (right_ind - left_ind) / 2;
        if (arr[mid_ind] <= key) {
            left_ind = mid_ind;
        } else {
            right_ind = mid_ind;
        }
    }
    if ((left_ind < length) && (arr[left_ind] == key)) {
        return left_ind + 1;
    } else {
        return -1;
    }
}

int main(int argc, char **argv) {
    FILE *fin, *fout;
    fin = fopen("binsearch.in", "r");
    fout = fopen("binsearch.out", "w");
    int n;
    fscanf(fin, "%ud", &n);
    int data[n];
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%d", &data[i]);
    }
    int m;
    int key;
    fscanf(fin, "%ud", &m);
    int left_ans, right_ans;
    for (int i = 0; i < m; i++) {
        fscanf(fin, "%d", &key);
        left_ans = binary_search_left(data, -1, n, key, n);
        right_ans = binary_search_right(data, -1, n, key, n);
        fprintf(fout, "%d %d", left_ans, right_ans);
        if (m - i > 1) {
            fputc('\n', fout);
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}