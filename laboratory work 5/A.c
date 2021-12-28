# include <stdio.h>

unsigned int answer = 0;

struct Node {
    int key;
    int left;
    int right;
};

void walk(unsigned int index, struct Node tree[], unsigned int length) {
    struct Node current_node = tree[index];
    if (current_node.right >= 0) {
        walk(current_node.right, tree, length + 1);
    }
    if (current_node.left >= 0) {
        walk(current_node.left, tree, length + 1);
    }
    answer = (length > answer) ? length : answer;
}

int main() {
    FILE *fin, *fout;
    fin = fopen("height.in", "r");
    fout = fopen("height.out", "w");
    unsigned int N;
    fscanf(fin, "%u", &N);
    if (N == 0) {
        fclose(fin);
        fprintf(fout, "0");
        fclose(fout);
        return 0;
    }
    struct Node search_tree[N];
    for (unsigned int i = 0; i < N; i++) {
        struct Node temp_node;
        fscanf(fin, "%d %u %u", &temp_node.key, &temp_node.left, &temp_node.right);
        temp_node.left--;
        temp_node.right--;
        search_tree[i] = temp_node;
    }
    walk(0, search_tree, 1);
    fclose(fin);
    fprintf(fout, "%u", answer);
    fclose(fout);
    return 0;
}