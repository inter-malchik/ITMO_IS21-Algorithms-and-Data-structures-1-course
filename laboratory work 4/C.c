# include <stdio.h>
# include <stdbool.h>

#define BOUND 10001
bool first_output = true;

enum Brackets {
    ROUND_OPEN,
    ROUND_CLOSE,
    SQUARE_OPEN,
    SQUARE_CLOSE
};

struct Stack {
    enum Brackets data[BOUND];
    short int head;
};

bool put_in_bracket_stack(struct Stack *bracket_stack, enum Brackets sign) {
    if (bracket_stack->head == 0) {
        bracket_stack->data[0] = sign;
        bracket_stack->head++;
        return true;
    }
    enum Brackets last = bracket_stack->data[bracket_stack->head - 1];
    if ((last == ROUND_OPEN && sign == ROUND_CLOSE) ||
        (last == SQUARE_OPEN && sign == SQUARE_CLOSE)) {
        bracket_stack->head--;
        return true;
    }
    if ((last == ROUND_OPEN || last == SQUARE_OPEN) &&
        (sign == ROUND_OPEN || sign == SQUARE_OPEN)) {
        bracket_stack->data[bracket_stack->head] = sign;
        bracket_stack->head++;
        return true;
    }
    return false;

}

void alert(char *verdict, FILE *out_file) {
    if (first_output) {
        first_output = false;
    } else {
        putc('\n', out_file);
    }
    fprintf(out_file, "%s", verdict);
}

int main(int argc, char **argv) {
    FILE *fin, *fout;
    fin = fopen("brackets.in", "r");
    fout = fopen("brackets.out", "w");
    char buffer[BOUND];
    struct Stack brackets;
    bool insertion_result;
    char *temp;
    while (!feof(fin)) {
        brackets.head = 0;
        if (!fgets(buffer, BOUND, fin)) {
            continue;
        }
        if (buffer[0] == '\n') {
            continue;
        }
        unsigned short int i = 0;
        while (buffer[i] != '\0') {
            switch (buffer[i]) {
                case '(':
                    insertion_result = put_in_bracket_stack(&brackets, ROUND_OPEN);
                    break;
                case ')':
                    insertion_result = put_in_bracket_stack(&brackets, ROUND_CLOSE);
                    break;
                case '[':
                    insertion_result = put_in_bracket_stack(&brackets, SQUARE_OPEN);
                    break;
                case ']':
                    insertion_result = put_in_bracket_stack(&brackets, SQUARE_CLOSE);
                    break;
            }
            i++;
            if (!insertion_result) {
                alert("NO", fout);
                break;
            }
        }
        if (!insertion_result) {
            continue;
        }
        if (brackets.head == 0) {
            alert("YES", fout);
        } else {
            alert("NO", fout);
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
