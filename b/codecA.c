#include <ctype.h>
#include <string.h>

void codecA_encode(char* message) {
    int len = strlen(message);
    for (int i = 0; i < len; i++) {
        if (islower(message[i])) {
            message[i] = toupper(message[i]);
        }
        else if (isupper(message[i])) {
            message[i] = tolower(message[i]);
        }
    }
}

void codecA_decode(char* message) {
    codecA_encode(message);
}
