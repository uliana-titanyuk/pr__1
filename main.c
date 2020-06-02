#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD 512

// assumes that results has emough memory for the result
int search(const char* input_file, char* result) {
    char tmp[MAX_WORD] = { 0 };

    FILE* f = fopen(input_file, "r");

    size_t wlen = 0;
    size_t rlen = 0;
    char* start = tmp;
    char* wp = tmp;
    char* we = tmp + sizeof(tmp) / sizeof(tmp[0]) - 1;

    if (!f) {
        fprintf(stderr, "can't open file %s\n", input_file);
        return -1;
    }

    for (; wp < we; ) {
        int c = fgetc(f);
        if (c == EOF) break;
        if (isspace(c) || !isupper(c) || c == ',' || c == '.' || c == '\r' || c == '\n') {
            *wp = 0;
            if (wlen >= rlen && wlen > 0 && *(wp - 1) == 'A') {
                strncpy(result, tmp, sizeof(tmp));
                rlen = wlen;
            }
            memset(tmp, 0, sizeof(tmp));
            wlen = 0;
            wp = tmp;
        }
        else {
            if (wp < we) {
                *wp++ = c;
                wlen++;
            }
        }
    }

    fclose(f);

    return 0;
}


int main(int argc, char** argv) {

    if (argc < 2) {
        fprintf(stderr, "there should be a file");
        exit(-1);
    }

    char word[MAX_WORD + 1] = { 0 };
    int ok = search(argv[1], word);
    printf("%s\n", word);

    return ok;
}