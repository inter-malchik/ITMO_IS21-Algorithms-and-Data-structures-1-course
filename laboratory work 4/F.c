# include <stdio.h>
# include <stdbool.h>

int main(int argc, char **argv) {
    bool touched_ground;
    bool condition;
    FILE *fin, *fout;
    fin = fopen("garland.in", "r");
    fout = fopen("garland.out", "w");
    unsigned short int n;
    double A, curr, key, prev1, prev2, delta = 0.00001, answer = 1000000;
    fscanf(fin, "%hd %lf", &n, &A);
    double lower_bound = 0, higher_bound = A;
    while (lower_bound < higher_bound - delta) {
        touched_ground = false;
        condition = true;
        key = (lower_bound + higher_bound) / 2.0;
        prev1 = key;
        prev2 = A;
        for (unsigned short i = 3; i <= n; i++) {
            curr = 2 * prev1 + 2 - prev2;
            if (curr < 0) {
                condition = false;
                break;
            } else if (curr > 0) {
                prev2 = prev1;
                prev1 = curr;
                continue;
            } else {
                if (!touched_ground) {
                    touched_ground = true;
                    prev2 = prev1;
                    prev1 = curr;
                    continue;
                } else {
                    condition = false;
                    break;
                }
            }
        }
        if (!condition) {
            lower_bound = key;
        } else {
            answer = (prev1 < answer) ? prev1 : answer;
            higher_bound = key;
        }
    }
    char buf[30];
    unsigned short int amount = sprintf(buf, "%.3lf", answer) - 1;
    for (unsigned short i = 0; i < amount; i++) {
        fprintf(fout, "%c", buf[i]);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}