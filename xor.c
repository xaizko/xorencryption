#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(char *cleartext, char *key);

int main(int argc, char *argv[]) {
    char *cleartext;
    char *key;

    // Check if the user provided the required arguments
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <message> <key> <mode (1) encrypt (2) decrypt>\n", argv[0]);
        return -1;
    }
    
    cleartext = argv[1];
    key = argv[2];

    encrypt(cleartext, key);

}

void encrypt(char *cleartext, char *key){
    char *ciphertext;
    //Xor encryption
    int len = strlen(cleartext);
    ciphertext = malloc(len + 1); 

    //loop through the cleartext and xor each byte with the key
    for (int i = 0; i < len; i++) {
        ciphertext[i] = cleartext[i] ^ key[i % strlen(key)];
    }
    ciphertext[len] = '\0';

    // Print the ciphertext in hexadecimal format
    printf("Ciphertext (hex): ");
    for (int i = 0; i < len; i++) {
        printf("%02x ", (unsigned char)ciphertext[i]);
    }
    printf("\n");
    free(ciphertext);
}