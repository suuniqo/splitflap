
/*** includes ***/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/charset/alphabet.h"
#include "../src/error/die.h"


/*** defines ***/

#define MAX_WORD_LEN 32
#define FILE_PATH_WORDLIST "assets/englishdict.txt"


/*** sorter ***/

void sort_word_arr(char** word_arr, long lines) {

    for (long i = 0; i < lines - 2; i++) {
        long dist_min = MAX_WORD_LEN * get_alphabet_length() * MAX_WORD_LEN;
        int word_idx = -1;

        for (int j = i + 1; j < lines; j++) {
            int dist = get_word_dist(word_arr[i], word_arr[j]); 

            if (dist < dist_min) {
                dist_min = dist;
                word_idx = j;
            }
        }

        char *buff = word_arr[i + 1];
        word_arr[i + 1] = word_arr[word_idx];
        word_arr[word_idx] = buff;
    }
}


/*** file ***/

long get_file_lines(FILE *word_list) {
    long counter = 0;

    do {
        char c = fgetc(word_list);
        if (c == '\n')
            counter++;
    } while(!feof(word_list) && !ferror(word_list));

    rewind(word_list);
    return counter;
}

void get_file_words(FILE* word_list, char **word_arr, int lines) {
    char buff[MAX_WORD_LEN];
    for (int i = 0; i < lines; i++) {
        fgets(buff, MAX_WORD_LEN, word_list);
        word_arr[i] = strdup(buff);
        word_arr[i][strlen(word_arr[i]) - 1] = '\0';
    }
}

void load_file_words(const char* file_path, char **word_arr, int lines) {
    if (remove(file_path) != 0)
        die("error deleting file");

    FILE *word_list;
    if ((word_list = fopen(FILE_PATH_WORDLIST, "w")) == NULL)
        die("error accesing text file");

    for (int i = 0; i < lines; i++) {
        if (str_is_alphabet(word_arr[i]))
            fprintf(word_list, "%s\n", word_arr[i]);
    }
    fclose(word_list);
}

char **get_word_arr(FILE *word_list, int lines) {

    char **word_arr = (char **)malloc(lines);

    get_file_words(word_list, word_arr, lines);
    fclose(word_list);

    return word_arr;
}

void free_word_arr(char **word_arr, int lines) {
    for (int i = 0; i < lines; i++)
        free(word_arr[i]);
    free(word_arr);
}

int main() {

    FILE *word_list;
    if ((word_list = fopen(FILE_PATH_WORDLIST, "r")) == NULL)
        die("error accesing text file");
    long lines = get_file_lines(word_list);

    char **word_arr = get_word_arr(word_list, lines);
    fclose(word_list);

    sort_word_arr(word_arr, lines);
    load_file_words(FILE_PATH_WORDLIST, word_arr, lines);
    free_word_arr(word_arr, lines);

    return EXIT_SUCCESS;
}
