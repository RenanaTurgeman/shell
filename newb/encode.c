// encode tool implementation

#include <stdio.h>
#include "codecA.h"
#include "codecB.h"
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: encode/decode <codec> <message>\n");
        return 1;
    }

    char* codec = argv[1];
    char* message = argv[2];
    char* encoded;

    if (strcmp(codec, "codecA") == 0) {
        encoded = codecA_encode(message);
    } else if (strcmp(codec, "codecB") == 0) {
        encoded = codecB_encode(message);
    } else {
        printf("Unknown codec: %s\n", codec);
        return 1;
    }

    printf("%s\n", encoded);
    free(encoded);
    return 0;
}
