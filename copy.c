#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int force = 0, verbose = 0;
    char *file1, *file2;

    // Check if the minimum required arguments are present
    if (argc < 3) {
        printf("Usage: copy <file1> <file2> [-f] [-v]\n");
        return 1;
    }

    // Parse the arguments
    file1 = argv[1];
    file2 = argv[2];
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            force = 1;
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        }
    }

    // Check if file2 exists and force flag is not set
    if (!force) {
        FILE *fp = fopen(file2, "r");
        if (fp != NULL) {
            fclose(fp);
            if (verbose) {
                printf("target file exists\n");
            }
            return 1;
        }
    }

    // Open the input file
    FILE *fin = fopen(file1, "rb");
    if (fin == NULL) {
        if (verbose) {
            printf("general failure\n");
        }
        return 1;
    }

    // Open the output file
    FILE *fout = fopen(file2, "wb");
    if (fout == NULL) {
        fclose(fin);
        if (verbose) {
            printf("general failure\n");
        }
        return 1;
    }

    // Copy the contents of the input file to the output file
    char buffer[1024];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), fin)) > 0) {
        fwrite(buffer, 1, n, fout);
    

    // Close the files
    fclose(fin);
    fclose(fout);

    if (verbose) {
        printf("success\n");
    }
    return 0;
}
