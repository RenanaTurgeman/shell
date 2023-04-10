#include <string.h>

void codecB_encode(char* message) {
    int len = strlen(message);
    for (int i = 0; i < len; i++) {
        message[i] = (char)(message[i] + 3);
    }
}

void codecB_decode(char* message) {
    int len = strlen(message);
    for (int i = 0; i < len; i++) {
        message[i] = (char)(message[i] - 3);
    }
}
