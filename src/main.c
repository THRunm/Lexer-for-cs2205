

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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