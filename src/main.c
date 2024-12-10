

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_regex(char *file_name, char ***names, char ***regexes, int *number) {
    FILE *fp;
    char line[1024];
    int capacity = 10;
    int count = 0;
    char **name_arr = NULL;
    char **regex_arr = NULL;
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        perror("Error opening file");
        *number = 0;
        return;
    }
    name_arr = (char **) malloc(capacity * sizeof(char *));
    regex_arr = (char **) malloc(capacity * sizeof(char *));
    if (name_arr == NULL || regex_arr == NULL) {
        perror("Error allocating memory");
        fclose(fp);
        *number = 0;
        return;
    }
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\r\n")] = 0;
        if (line[0] == '\0')
            continue;
        char *name = strdup(line);
        if (name == NULL) {
            perror("Error allocating memory for name");
            break;
        }
        if (fgets(line, sizeof(line), fp) == NULL) {
            fprintf(stderr, "Error: missing regex for name '%s'\n", name);
            free(name);
            break;
        }
        line[strcspn(line, "\r\n")] = 0;
        char *regex = strdup(line);
        if (regex == NULL) {
            perror("Error allocating memory for regex");
            free(name);
            break;
        }
        if (count >= capacity) {
            capacity *= 2;
            char **temp_names = realloc(name_arr, capacity * sizeof(char *));
            char **temp_regexes = realloc(regex_arr, capacity * sizeof(char *));
            if (temp_names == NULL || temp_regexes == NULL) {
                perror("Error reallocating memory");
                free(name);
                free(regex);
                break;
            }
            name_arr = temp_names;
            regex_arr = temp_regexes;
        }

        name_arr[count] = name;
        regex_arr[count] = regex;
        count++;
    }
    fclose(fp);
    *names = name_arr;
    *regexes = regex_arr;
    *number = count;
}

void read_inputs(char *file_name, char ***inputs, int *number) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        *number = 0;
        *inputs = NULL;
        return;
    }
    size_t capacity = 10;
    size_t count = 0;
    char **array = malloc(capacity * sizeof(char *));
    if (array == NULL) {
        perror("Failed to allocate memory");
        fclose(fp);
        *number = 0;
        *inputs = NULL;
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        if (count >= capacity) {
            capacity *= 2;
            char **new_array = realloc(array, capacity * sizeof(char *));
            if (new_array == NULL) {
                perror("Failed to reallocate memory");
                for (size_t i = 0; i < count; i++) {
                    free(array[i]);
                }
                free(array);
                fclose(fp);
                *number = 0;
                *inputs = NULL;
                return;
            }
            array = new_array;
        }
        array[count] = malloc((len + 1) * sizeof(char));
        if (array[count] == NULL) {
            perror("Failed to allocate memory for line");
            for (size_t i = 0; i < count; i++) {
                free(array[i]);
            }
            free(array);
            fclose(fp);
            *number = 0;
            *inputs = NULL;
            return;
        }
        strcpy(array[count], buffer);
        count++;
    }
    fclose(fp);
    *inputs = array;
    *number = (int) count;
}


int main(int argc, char *argv[]) {
    return 0;
}