# include <stdio.h>
# include <stdlib.h>

enum Operations {
    NOTHING,
    ADDITION,
    SUBSTRACTION,
    MULTIPLICATION
};

struct Stack {
    signed int values[100];
    unsigned short tail;
};

void put(struct Stack *stack, enum Operations operation, signed int value) {
    if (operation == NOTHING) {
        stack->values[stack->tail] = value;
        stack->tail++;
        return;
    }
    signed int value_last, value_prev;
    value_last = stack->values[stack->tail - 1];
    stack->tail--;
    value_prev = stack->values[stack->tail - 1];
    stack->tail--;
    switch (operation) {
        case ADDITION:
            stack->values[stack->tail] = value_prev + value_last;
            break;
        case SUBSTRACTION:
            stack->values[stack->tail] = value_prev - value_last;
            break;
        case MULTIPLICATION:
            stack->values[stack->tail] = value_prev * value_last;
            break;
    }
    stack->tail++;
}

int main(int argc, char **argv) {
    FILE *fin, *fout;
    fin = fopen("postfix.in", "r");
    fout = fopen("postfix.out", "w");
    char buffer[11];
    for (char i = 0; i <= 10; i++) {
        buffer[i] = '\0';
    }
    struct Stack our_stack;
    our_stack.tail = 0;
    enum Operations operation;
    signed int number;
    while (!feof(fin)) {
        if (fscanf(fin, "%10s", buffer) == -1) {
            break;
        }
        number = 0;
        switch (buffer[0]) {
            case '+':
                operation = ADDITION;
                break;
            case '-':
                operation = SUBSTRACTION;
                break;
            case '*':
                operation = MULTIPLICATION;
                break;
            default:
                number = atoi(buffer);
                operation = NOTHING;
                break;
        }
        put(&our_stack, operation, number);
    }
    fclose(fin);
    fprintf(fout, "%d", our_stack.values[our_stack.tail - 1]);
    fclose(fout);
    return 0;
}