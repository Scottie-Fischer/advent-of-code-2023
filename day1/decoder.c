#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static const int FAILURE = 0;

/*
    Author: Scott Fischer
    Purpose:  This file will parse through an input txt, find the first and last number in each line, and give a total
        - Note: these numbers can be spelled or digits: (one or 1)
*/


uint8_t detectDigit(char string[32]){
    if(strstr(string, "one") != NULL) {
        return 1;
    }else if(strstr(string, "two") != NULL){
        return 2;
    }
    else if(strstr(string, "three") != NULL){
        return 3;
    }
    else if(strstr(string, "four") != NULL){
        return 4;
    }
    else if(strstr(string, "five") != NULL){
        return 5;
    }
    else if(strstr(string, "six") != NULL){
        return 6;
    }
    else if(strstr(string, "seven") != NULL){
        return 7;
    }
    else if(strstr(string, "eight") != NULL){
        return 8;
    }
    else if(strstr(string, "nine") != NULL){
        return 9;
    }
    return FAILURE;
}


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
        uint8_t stringIndx = 0;
        char string[64];

        for(char* linePtr = line; *linePtr !='\0'; linePtr++){
            char c = *linePtr;
            string[stringIndx++] = c;

            //Check for digit spelled out if alphabetical
            if(isalpha(c) && c != '\n'){
                uint8_t x = detectDigit(string);
                if(x != 0){
                    memset(string, '\0', sizeof(string));
                    stringIndx = 0;
                    string[stringIndx++] = c; 
                    digits[digitIndx++] = x;
                }
            }
            
            //Reset string buffer and add digit
            else if(isdigit(*linePtr)){
                memset(string, '\0', sizeof(string));
                stringIndx = 0;
                uint8_t digit = *linePtr - '0';
                digits[digitIndx++] = digit;
            }
        }
        memset(string, '\0', sizeof(string));
        stringIndx = 0;
        //Compute first and last digits for line
        uint16_t twoDigit = (digits[0] * 10) + digits[digitIndx-1];
        total += twoDigit;
        memset(digits, '\0', sizeof(digits));
    }
    printf("\nTotal is: %i\n",total);
    free(line);
    return 0;
}

