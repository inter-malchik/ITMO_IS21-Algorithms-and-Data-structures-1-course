#include <stdio.h>


unsigned int find_parent(unsigned int n) { //returns the parent index
    return n / 2;
}

void check_heap(int heap[], unsigned int size, FILE* output_file) {
    for (unsigned int i = 2; i <= size; i++) {
        if (heap[i] >= heap[find_parent(i)]) {
            continue;
        }
        else {
            fprintf(output_file, "NO");
            return;
        }
    }
    fprintf(output_file, "YES");
}

int main() {
    FILE *fin, *fout;
    fin = fopen("isheap.in", "r");
    fout = fopen("isheap.out", "w");
    static int arr[100001];
    unsigned int size_of_heap;
    fscanf(fin, "%u", &size_of_heap);
    for (unsigned int i = 1; i <= size_of_heap; i++) {
        fscanf(fin, "%d", &arr[i]);
    }
    check_heap(arr, size_of_heap, fout);
    return 0;
}