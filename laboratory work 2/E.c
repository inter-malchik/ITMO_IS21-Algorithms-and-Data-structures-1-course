#include <stdio.h>
unsigned int n;

int qsort_modk(int arr[n], unsigned int k, unsigned int left, unsigned int right) {
    unsigned int i;
    unsigned int j;
    int key;
    while (left < right) {
        key = ((left <= k <= right)) ? arr[k] : arr[(left + right) / 2];
        i = left;
        j = right;
        while (i <= j) {
            while (arr[i] < key) {
                i++;
            }
            while (arr[j] > key) {
                j--;
            }
            if (i <= j) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }
        if (i >= j) {
            left = (j < k) ? i : left;
            right = (k < i) ? j : right;
        }
    }
    return arr[k];
}


int main() {
    FILE *fin, *fout;
    fin = fopen("kth.in", "r");
    fout = fopen("kth.out", "w");
    unsigned int k, i;
    int A, B, C, a1, a2;
    fscanf(fin, "%u %u\n%d %d %d %d %d", &n, &k, &A, &B, &C, &a1, &a2);
    static int ournums[30000000];
    ournums[0] = a1;
    ournums[1] = a2;
    for (i = 0; i < n; i++) {
        if (i >= 2) {
            ournums[i] = A * ournums[i - 2] + B * ournums[i - 1] + C;
        }
    }
    fprintf(fout, "%d", qsort_modk(ournums, k - 1, 0, n - 1));
    fclose(fin);
    fclose(fout);
    return 0;
}