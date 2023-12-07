#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    uint32_t total = 0;
    FILE* fp = fopen("encoded.txt", "r+");
    
    if(fp == NULL) exit(EXIT_FAILURE);

    while((read = getline(&line, &len, fp)) != -1){
        uint8_t digits[64];
        uint8_t digitIndx = 0;
        for(char* linePtr = line; *linePtr !='\0'; linePtr++){
            if(isdigit(*linePtr)){
                uint8_t digit = *linePtr - '0';
                digits[digitIndx++] = digit;
            }
        }
        uint16_t twoDigit = (digits[0] * 10) + digits[digitIndx-1];
        total += twoDigit;
        
    }
    printf("\nTotal is: %i\n",total);
    free(line);
    return 0;
}

