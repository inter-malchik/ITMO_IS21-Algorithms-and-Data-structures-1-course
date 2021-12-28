#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define HASH_TABLE_SIZE 65521
#define AMOUNT_OF_OPERATIONS 1000000

struct TreeNode {
    int key;
    struct TreeNode *next;
};

struct LinkHead {
    struct TreeNode *start;
};

int main() {
    static struct TreeNode operations[AMOUNT_OF_OPERATIONS];
    unsigned index = 0;
    struct LinkHead hashtable[HASH_TABLE_SIZE];
    for (unsigned short i = 0; i < HASH_TABLE_SIZE; i++) {
        hashtable[i].start = NULL;
    }
    FILE *setin, *setout;
    setin = fopen("set.in", "r");
    setout = fopen("set.out", "w");
    while (true) {
        char command[7];
        int number;
        if (feof(setin) || fscanf(setin, "%s %d", command, &number) < 0)
            break;
        bool negative = number < 0;
        unsigned int key = (!negative ? number : -number) % HASH_TABLE_SIZE;
        if (strcmp(command, "insert") == 0) {
            struct TreeNode new_node = {number, NULL};
            if (hashtable[key].start == NULL) {
                operations[index] = new_node;
                hashtable[key].start = &operations[index];
                index++;
            } else {
                bool found = false;
                struct TreeNode *current = hashtable[key].start;
                while (current->next != NULL) {
                    found = (current->key == number) ? true : found;
                    if (found)
                        break;
                    current = current->next;
                }
                found = (current->key == number) ? true : found;
                if (!found) {
                    operations[index] = new_node;
                    current->next = &operations[index];
                    //printf("inserted\n");
                    index++;
                }
            }
        } else if (strcmp(command, "exists") == 0) {
            if (hashtable[key].start == NULL) {
                fprintf(setout, "false\n");
                continue;
            } else {
                bool found = false;
                struct TreeNode *current = hashtable[key].start;
                while (current->next != NULL) {
                    if (found)
                        break;
                    if (current->key == number) {
                        found = true;
                        continue;
                    }
                    current = current->next;
                }
                found = (current->key == number) ? true : found;
                if (found) {
                    fprintf(setout, "true\n");
                    continue;
                } else {
                    fprintf(setout, "false\n");
                }
            }
        } else if (strcmp(command, "delete") == 0) {
            if (hashtable[key].start == NULL)
                continue;
            struct TreeNode *current = hashtable[key].start;
            struct TreeNode *previous = NULL;
            bool found = false;
            while (current->next != NULL) {
                if (current->key == number) {
                    if (previous != NULL)
                        previous->next = current->next;
                    else
                        hashtable[key].start = current->next;
                    found = true;
                    break;
                }
                previous = current;
                current = current->next;
            }
            if (!found) {
                if (current->key == number) {
                    if (previous == NULL) {
                        hashtable[key].start = NULL;
                    } else {
                        previous->next = NULL;
                    }
                }
            }
        }
    }
    fclose(setin);
    fclose(setout);
    return 0;
}