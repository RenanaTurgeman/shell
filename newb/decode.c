// decode tool implementation

#include <stdio.h>
#include "codecA.h"
#include "codecB.h"
#include <string.h>
#include <stdlib.h>
int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: encode/decode <codec> <message>\n");
        return 1;
    }

    char* codec = argv[1];
    char* message = argv[2];
    char* decoded;

    if (strcmp(codec, "codecA") == 0) {
        decoded = codecA_decode(message);
    } else if (strcmp(codec, "codecB") == 0) {
        decoded = codecB_decode(message);
    } else {
        printf("Unknown codec: %s\n", codec);
        return 1;
    }

    printf("%s\n", decoded);
    free(decoded);
    return 0;
}
