#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define HASH_TABLE_SIZE 65521
#define AMOUNT_OF_OPERATIONS 100000
#define K 91
#define LEN_OF_KEYS_AND_ARGS 21

struct TreeNode {
    char key[LEN_OF_KEYS_AND_ARGS];
    char value[LEN_OF_KEYS_AND_ARGS];
    struct TreeNode *next;
};

struct LinkHead {
    struct TreeNode *start;
};

unsigned int hashify(char value[]) {
    unsigned long result = 0;
    unsigned int argument = 1;
    char string_size = (char) strlen(value);
    for (char i = 0; i < string_size; i++) {
        result += value[i] * argument;
        argument = argument * K;
    }
    return result % HASH_TABLE_SIZE;
}

int main() {
    static struct TreeNode operations[AMOUNT_OF_OPERATIONS];
    unsigned index = 0;
    struct LinkHead hashtable[HASH_TABLE_SIZE];
    for (unsigned short i = 0; i < HASH_TABLE_SIZE; i++) {
        hashtable[i].start = NULL;
    }
    FILE *fin, *fout;
    fin = fopen("map.in", "r");
    fout = fopen("map.out", "w");
    while (true) {
        char command[7];
        char string_key[LEN_OF_KEYS_AND_ARGS];
        char string_value[LEN_OF_KEYS_AND_ARGS];
        if (feof(fin) || fscanf(fin, "%s %s ", command, string_key) < 0)
            break;
        unsigned int key = hashify(string_key);
        if (strcmp(command, "put") == 0) {
            fscanf(fin, "%s", string_value);
            struct TreeNode new_node;
            strcpy(new_node.key, string_key);
            strcpy(new_node.value, string_value);
            new_node.next = NULL;
            operations[index] = new_node;
            if (hashtable[key].start == NULL) {
                hashtable[key].start = &operations[index];
                index++;
            } else {
                bool found = false;
                struct TreeNode *current = hashtable[key].start;
                while (current->next != NULL) {
                    found = (strcmp(current->key, string_key) == 0) ? true : found;
                    if (found) {
                        strcpy(current->value, string_value);
                        break;
                    }
                    current = current->next;
                }
                if (found)
                    continue;
                else if (strcmp(current->key, string_key) == 0) {
                    strcpy(current->value, string_value);
                    continue;
                }
                current->next = &operations[index];
                index++;
            }

        } else if (strcmp(command, "get") == 0) {
            if (hashtable[key].start == NULL) {
                fprintf(fout, "none\n");
                continue;
            } else {
                bool found = false;
                struct TreeNode *current = hashtable[key].start;
                while (current->next != NULL) {
                    if (found)
                        break;
                    if (strcmp(current->key, string_key) == 0) {
                        found = true;
                        fprintf(fout, "%s\n", current->value);
                        continue;
                    }
                    current = current->next;
                }
                if ((strcmp(current->key, string_key) == 0) && (!found)) {
                    fprintf(fout, "%s\n", current->value);
                    continue;
                } else if (!found) {
                    fprintf(fout, "none\n");
                }
            }
        } else if (strcmp(command, "delete") == 0) {
            if (hashtable[key].start == NULL)
                continue;
            struct TreeNode *current = hashtable[key].start;
            struct TreeNode *previous = NULL;
            bool found = false;
            while (current->next != NULL) {
                if (strcmp(current->key, string_key) == 0) {
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
                if (strcmp(current->key, string_key) == 0) {
                    if (previous == NULL) {
                        hashtable[key].start = NULL;
                    } else {
                        previous->next = NULL;
                    }
                }
            }
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

