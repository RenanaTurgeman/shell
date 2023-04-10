#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZE 1024

int compare_files(char* file1, char* file2, int ignore_case, int verbose) {
    FILE* fp1 = fopen(file1, "r");
    FILE* fp2 = fopen(file2, "r");
    if (!fp1 || !fp2) {
        printf("Error opening files.\n");
        return -1;
    }

    char buf1[BUF_SIZE];
    char buf2[BUF_SIZE];
    int line_num = 1;
    int is_equal = 1;
    while (fgets(buf1, BUF_SIZE, fp1) != NULL && fgets(buf2, BUF_SIZE, fp2) != NULL) {
        if (ignore_case) {
            int len = strlen(buf1);
            for (int i = 0; i < len; i++) {
                buf1[i] = tolower(buf1[i]);
            }
            len = strlen(buf2);
            for (int i = 0; i < len; i++) {
                buf2[i] = tolower(buf2[i]);
            }
        }
        if (strcmp(buf1, buf2) != 0) {
            is_equal = 0;
            if (verbose) {
                printf("Line %d is distinct.\n", line_num);
            }
            break;
        }
        line_num++;
    }

    if (is_equal && fgets(buf2, BUF_SIZE, fp2) == NULL) {
        if (verbose) {
            printf("The files are equal.\n");
        }
        return 0;
    } else {
        if (verbose) {
            printf("The files are distinct.\n");
        }
        return 1;
    }

    fclose(fp1);
    fclose(fp2);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        //This line checks if the number of command line arguments is less than three, 
        //which means that the required arguments (file1 and file2) have not been provided. 
        printf("Usage: cmp <file1> <file2> [-v] [-i]\n");
        return -1;
    }

    int ignore_case = 0;
    int verbose = 0;

    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            ignore_case = 1;
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        }
    }

    int result = compare_files(argv[1], argv[2], ignore_case, verbose);

    return result;
}
