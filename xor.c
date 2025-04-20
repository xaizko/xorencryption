#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(char *cleartext, char *key, int mode);
unsigned char hex_to_byte(const char *hex);

int main(int argc, char *argv[]) {
    char *cleartext;
    char *key;
    int mode; 

    // Check if the user provided the required arguments
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <message> <key> <mode (1) encrypt (2) decrypt>\n", argv[0]);
        fprintf(stderr, "Keep in mind that decryption mode only works with hex strings.\n");
        return -1;
    }
    
    cleartext = argv[1];
    key = argv[2];
    mode = atoi(argv[3]);

    encrypt(cleartext, key, mode);

}

void encrypt(char *input, char *key, int mode) {
    char *output;
    int len;

    if (mode == 1) {
        // ENCRYPTION MODE
        len = strlen(input);
        output = malloc(len + 1);

        // XOR encryption
        for (int i = 0; i < len; i++) {
            output[i] = input[i] ^ key[i % strlen(key)];
        }
        output[len] = '\0';

        // Print ciphertext in hex
        printf("Ciphertext (hex): ");
        for (int i = 0; i < len; i++) {
            printf("%02x ", (unsigned char)output[i]);
        }
        printf("\n");
    } else if (mode == 2) {
        // DECRYPTION MODE
    
        int inputLen = strlen(input);
        int hexByteCount = 0;
    
        // Count how many bytes (every pair of hex digits)
        for (int i = 0; i < inputLen; i++) {
            if (input[i] != ' ')
                hexByteCount++;
        }
        hexByteCount /= 2; // This is the real byte count because we counted every non space as a byte so divide by 2 to get the real byte count
    
        // Allocate memory for the output string and add 1 for null terminator
        output = malloc(hexByteCount + 1);
        //outIndex is the index for the output string
        int outIndex = 0;
    
        for (int i = 0; i < inputLen; ) {
            // Skip spaces
            if (input[i] == ' ') {
                i++;
                continue;
            }
            
            // Copies two characters from the input string to a temporary string and converts it to a byte
            char hex[3] = { input[i], input[i + 1], '\0' };
            unsigned int byte;
            sscanf(hex, "%x", &byte);
            
            //Xor the byte with the key and store it in the output string
            output[outIndex] = (char)(byte ^ key[outIndex % strlen(key)]); 
            outIndex++;
            i += 2; // Need to increment by 2 because we are reading two characters at a time
        }
        
        // Null terminate the output string
        output[outIndex] = '\0';
        printf("Decrypted text: %s\n", output);
    }

    free(output);
}
