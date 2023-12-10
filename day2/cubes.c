#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum Limits{
    Red = 12,
    Green = 13,
    Blue = 14
};

static const LIMIT_RED = 12;
static const LIMIT_GREEN = 13;
static const LIMIT_BLUE = 14;
static const POSSIBLE_GAME = 1;
static const IMPOSSIBLE_GAME = 0;

/*
    Author: Scott Fischer
    Purpose:  
*/

void removeSpaces(char* str){
    char* c = str;
    //breaks when *str == '\0'
    while(*str++ = *c++){
        while(*c == ' '){
            c++;
        }
    }
}
int parseRound(char* str){
    char* colorSet;
    while ((colorSet = strsep(&str, ","))){
        int count = atoi(colorSet);
        while(isnumber(*colorSet)){
            colorSet++;
        }
        
        colorSet[strcspn(colorSet, "\n")] = 0;    //Remove new line char
        if(strcmp(colorSet,"blue") == 0){
            if(count > LIMIT_BLUE) return IMPOSSIBLE_GAME;
        }
        else if(strcmp(colorSet,"red") == 0) {
            if(count > LIMIT_RED) return IMPOSSIBLE_GAME;
        }
        else if(strcmp(colorSet,"green") == 0){
            if(count > LIMIT_GREEN) return IMPOSSIBLE_GAME;
        }
        else{
            printf("ERROR: %s\n", colorSet);
        }
    }
    return POSSIBLE_GAME;
}

int parseGame(char* str){
    char* round;
    int possible = POSSIBLE_GAME;
    while ((round = strsep(&str, ";"))){
        if(parseRound(round) == 0){
            possible = IMPOSSIBLE_GAME;
        }
    }
    return possible;
}

int getGameNumber(char* gameHeader){
    char* c = gameHeader;
    while(isalpha(*c)){c++;}
    return atoi(c);

}

int main(){
    char* line = NULL;
    size_t lineLen = 0;
    ssize_t read;
    FILE* filePtr = fopen("games.txt", "r+");
    int total = 0;

    if(filePtr == NULL) exit(EXIT_FAILURE);
    while((read = getline(&line, &lineLen, filePtr)) != -1){
        //char* gameLabel = strtok(line, ":");   //Filter the Games
        removeSpaces(line);
        char* gameNumber = strtok(line, ":");
        char* gameInfo = strtok(NULL, ":");
        char* ptr = gameInfo;
        int possible = parseGame(gameInfo);
        if(possible){
            total += getGameNumber(gameNumber);
        }        
    }
    printf("TOTAL VALUE OF POSSIBLE GAMES: %i\n", total);

}