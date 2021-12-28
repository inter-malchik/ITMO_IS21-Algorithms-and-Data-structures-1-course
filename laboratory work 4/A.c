# include <stdio.h>
# include <stdbool.h>

struct Stack {
    long int values[1000000];
    unsigned int tail;
};

int main(int argc, char **argv) {
    FILE *fin, *fout;
    fin = fopen("stack.in", "r");
    fout = fopen("stack.out", "w");
    struct Stack our_stack;
    unsigned int m;
    long int n;
    bool first_output = true;
    char operaton;
    fscanf(fin, "%u\n", &m);
    for (unsigned int i = 0; i < m; i = i + 1) {
        fscanf(fin, "\n%c", &operaton);
        switch (operaton) {
            case '-':
                if (first_output) {
                    first_output = false;
                } else {
                    putc('\n', fout);
                }
                fprintf(fout, "%ld", our_stack.values[our_stack.tail]);
                our_stack.tail--;
                break;
            case '+':
                fscanf(fin, " %ld\n", &n);
                our_stack.values[our_stack.tail + 1] = n;
                our_stack.tail++;
                break;
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

