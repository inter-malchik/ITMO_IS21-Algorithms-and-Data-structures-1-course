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
    struct TreeNode *next_node;
    struct TreeNode *successor;
    struct TreeNode *predecessor;
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
    fin = fopen("linkedmap.in", "r");
    fout = fopen("linkedmap.out", "w");
    struct TreeNode *previous_node_added = NULL;
    while (true) {
        char command[7];
        char string_key[LEN_OF_KEYS_AND_ARGS];
        char string_value[LEN_OF_KEYS_AND_ARGS];
        if (feof(fin) || fscanf(fin, "%s %s ", command, string_key) < 0)
            break;
        unsigned int key = hashify(string_key);
        if (strcmp(command, "put") == 0) {
            fscanf(fin, "%s", string_value);
            if (hashtable[key].start == NULL) {
                struct TreeNode new_node;
                strcpy(new_node.key, string_key);
                strcpy(new_node.value, string_value);
                new_node.next_node = NULL;
                new_node.predecessor = previous_node_added;
                new_node.successor = NULL;
                operations[index] = new_node;
                hashtable[key].start = &operations[index];
                if (previous_node_added != NULL)
                    previous_node_added->successor = &operations[index];
                previous_node_added = &operations[index];
                index++;
            } else {
                bool found = false;
                struct TreeNode *current = hashtable[key].start;
                while (current->next_node != NULL) {
                    found = (strcmp(current->key, string_key) == 0) ? true : found;
                    if (found) {
                        strcpy(current->value, string_value);
                        break;
                    }
                    current = current->next_node;
                }
                if ((!found) && (strcmp(current->key, string_key) == 0)) {
                    strcpy(current->value, string_value);
                } else if (!found) {
                    struct TreeNode new_node;
                    strcpy(new_node.key, string_key);
                    strcpy(new_node.value, string_value);
                    new_node.next_node = NULL;
                    new_node.predecessor = previous_node_added;
                    new_node.successor = NULL;
                    operations[index] = new_node;
                    current->next_node = &operations[index];
                    if (previous_node_added != NULL)
                        previous_node_added->successor = &operations[index];
                    previous_node_added = &operations[index];
                }
                index++;
            }
        } else if (strcmp(command, "get") == 0) {
            if (hashtable[key].start == NULL) {
                fprintf(fout, "none\n");
                continue;
            } else {
                bool found = false;
                struct TreeNode *current = hashtable[key].start;
                while (current->next_node != NULL) {
                    if (found)
                        break;
                    if (strcmp(current->key, string_key) == 0) {
                        found = true;
                        fprintf(fout, "%s\n", current->value);
                        continue;
                    }
                    current = current->next_node;
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
            struct TreeNode *cur = hashtable[key].start;
            struct TreeNode *prev = NULL;
            bool found = false;
            while (cur->next_node != NULL) {
                if (strcmp(cur->key, string_key) == 0) {
                    if (prev != NULL)
                        prev->next_node = cur->next_node;
                    else {
                        hashtable[key].start = cur->next_node;
                    }
                    if (cur->successor != NULL)
                        cur->successor->predecessor = cur->predecessor;
                    if (cur->predecessor != NULL)
                        cur->predecessor->successor = cur->successor;
                    found = true;
                    if (previous_node_added == cur) {
                        previous_node_added = previous_node_added->predecessor;
                    }
                    break;
                }
                prev = cur;
                cur = cur->next_node;
            }
            if (!found) {
                if (strcmp(cur->key, string_key) == 0) {
                    if (prev == NULL) {
                        hashtable[key].start = NULL;
                    } else {
                        prev->next_node = NULL;
                    }
                    if (cur->successor != NULL)
                        cur->successor->predecessor = cur->predecessor;
                    if (cur->predecessor != NULL)
                        cur->predecessor->successor = cur->successor;
                    if (previous_node_added == cur) {
                        previous_node_added = previous_node_added->predecessor;
                    }
                }
            }
        } else if (strcmp(command, "prev") == 0) {
            if (hashtable[key].start == NULL) {
                fprintf(fout, "none\n");
                continue;
            } else {
                bool found = false;
                struct TreeNode *current = hashtable[key].start;
                while (current->next_node != NULL) {
                    if (found)
                        break;
                    if (strcmp(current->key, string_key) == 0) {
                        found = true;
                        if (current->predecessor != NULL) {
                            fprintf(fout, "%s\n", current->predecessor->value);
                        } else
                            fprintf(fout, "none\n");
                        continue;
                    }
                    current = current->next_node;
                }
                if ((strcmp(current->key, string_key) == 0) && (!found)) {
                    if (current->predecessor != NULL) {
                        fprintf(fout, "%s\n", current->predecessor->value);
                    } else
                        fprintf(fout, "none\n");
                    continue;
                } else if (!found)
                    fprintf(fout, "none\n");
            }
        } else if (strcmp(command, "next") == 0) {
            if (hashtable[key].start == NULL) {
                fprintf(fout, "none\n");
                continue;
            } else {
                bool found = false;
                struct TreeNode *current = hashtable[key].start;
                while (current->next_node != NULL) {
                    if (found)
                        break;
                    if (strcmp(current->key, string_key) == 0) {
                        found = true;
                        if (current->successor != NULL) {
                            fprintf(fout, "%s\n", current->successor->value);
                        } else
                            fprintf(fout, "none\n");
                        continue;
                    }
                    current = current->next_node;
                }
                if ((strcmp(current->key, string_key) == 0) && (!found)) {
                    if (current->successor != NULL) {
                        fprintf(fout, "%s\n", current->successor->value);
                    } else
                        fprintf(fout, "none\n");
                    continue;
                } else if (!found)
                    fprintf(fout, "none\n");
            }
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}