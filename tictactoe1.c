#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Max_players 3
#define Max_symbols 3

const char  symbols[Max_symbols] = {'X','Y','Z'};
typedef struct{
	int mode;  // if 0 human , if 1  computer
        char symbol ;
} Player;

char **board;
int N;
FILE *logFile;



// functions for the board 


// code to create an empty board 
 void createboard(int size) {
	 N = size;
	 board  = (char **)malloc( N * sizeof(char *));
	 for (int = i =0; i<N; i++){
		 board[i] =(char *)malloc(N * sizeof(char));
		 for (int j = 0; j<N; j++){
			 board[i][j] = ' ';
		 }
	 }
 }

// display the board
//
void displayBoard() {
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf(" ");
        for (int j = 0; j < N; j++) {
            printf(" %c ", board[i][j]);
            if (j != N - 1) printf("|");
        }
        printf("\n");
        if (i != N - 1) {
            printf(" ");
            for (int j = 0; j < N; j++) {
                printf("---");
                if (j != N - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}


// Log the current board state to a file
void logBoard() {
    if (!logFile) return;
    fprintf(logFile, "\n");
    for (int i = 0; i < N; i++) {
        fprintf(logFile, " ");
        for (int j = 0; j < N; j++) {
            fprintf(logFile, " %c ", board[i][j]);
            if (j != N - 1) fprintf(logFile, "|");
        }
        fprintf(logFile, "\n");
        if (i != N - 1) {
            fprintf(logFile, " ");
            for (int j = 0; j < N; j++) {
                fprintf(logFile, "---");
                if (j != N - 1) fprintf(logFile, "+");
            }
            fprintf(logFile, "\n");
        }
    }
    fprintf(logFile, "\n");
    fflush(logFile);
}
