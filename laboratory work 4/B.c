# include <stdio.h>
# include <stdbool.h>

# define BOUND 1000000

struct Queue {
    long int data[BOUND];
    unsigned int head;
    unsigned int tail;
};

int main(int argc, char **argv) {
    FILE *fin, *fout;
    fin = fopen("queue.in", "r");
    fout = fopen("queue.out", "w");
    struct Queue our_queue;
    our_queue.tail = 0;
    our_queue.head = 0;
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
                fprintf(fout, "%ld", our_queue.data[our_queue.tail]);
                our_queue.tail++;
                if (our_queue.tail == BOUND) {
                    our_queue.tail = 0;
                }
                break;
            case '+':
                fscanf(fin, " %ld\n", &n);
                our_queue.data[our_queue.head] = n;
                our_queue.head++;
                if (our_queue.head == BOUND) {
                    our_queue.head = 0;
                }
                break;
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

