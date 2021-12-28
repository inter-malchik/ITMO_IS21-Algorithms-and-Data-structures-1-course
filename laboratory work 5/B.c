# include <stdio.h>
# include <stdbool.h>

bool answer = true;

struct Node {
    int key;
    int left;
    int right;
};

void alert(FILE *filename, bool verdict) {
    if (verdict) {
        fprintf(filename, "YES");
    } else {
        fprintf(filename, "NO");
    }
    fclose(filename);
}

void check(int index, struct Node tree[], int low, int high) {
    if (!answer) {
        return;
    }
    struct Node current_node = tree[index];
    if ((current_node.key <= low) || (current_node.key >= high)) {
        answer = false;
        return;
    }
    if ((current_node.left < 0) && (current_node.right < 0)) {
        return;
    }
    if (current_node.left > 0) {
        int left_key = tree[current_node.left].key;
        if (left_key < current_node.key) {
            int new_high = (current_node.key < high) ? current_node.key : high;
            check(current_node.left, tree, low, new_high);
        } else {
            answer = false;
        }
    }
    if (current_node.right > 0) {
        int right_key = tree[current_node.right].key;
        if (right_key > current_node.key) {
            int new_low = (current_node.key > low) ? current_node.key : low;
            check(current_node.right, tree, new_low, high);
        } else {
            answer = false;
        }
    }
}

int main() {
    FILE *fin, *fout;
    fin = fopen("check.in", "r");
    fout = fopen("check.out", "w");
    unsigned int N;
    fscanf(fin, "%u", &N);
    if (N == 0) {
        alert(fout, true);
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
    fclose(fin);
    int border = 1000000000;
    check(0, search_tree, -border - 1, border + 1);
    alert(fout, answer);
    return 0;
}