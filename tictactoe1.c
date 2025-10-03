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
    fflush(logFile)
	  
	  // free dynamically aloocate board

  void freeboard(){ 
     for(int i=0; i<N;i++)
     free(board[i]);
    free(board);
  }

// cheking the validity of a move 
  
 void validityofmove(int row , int cel){
        return (row >= 0 && row < N && col >= 0 && col < N && board[row][col] == ' ');
}

 // get a move form a human 
 //  
    
  void usermove( int *row , int *col,char symbol){
	  do{
		  printf("Player '%c', enter move (row and column):", symbol);
		  scanf("%d %d", row, col);
		 if (!validityofmove(*row, *col)){
			 printf("move is not valid. \n");
		 }
	  }while(!validityofmove(*row, *col));
  }

// create random move to computer
   void computemove(int *row , int *col){
	   do{
		   *row = rand() % N;
		   *col = rand() % N;
	   }while (!validityofmove(*row, *col));
	   printf("computer choose : %d %d \n", *row, *col);
	   }
}

void logmove(int playernum, char symbol, int row, int col){
	if(logFile){
		fprintf(logFile , "player %d (%c) moved to (%d,%d)\n", playerNum + 1, symbol,row,col);
		fflush(logFile);
	}
}

// checking if a player won 
// first check rowns and columns
 int check(char symbol){

	 for(int i = o; i<N; i++){
		 int rowwin = 1, colwin = 1;
		 for ( int j = 0; j<N; j++){
			        if (board[i][j] != symbol) rowwin = 0;
            if (board[j][i] != symbol) colwin = 0;
        }
        if (rowwin || colwin) return 1;
    }

	 // checking diagonals
	  
	 int diagon1win = 1, diagon2win = 1;
	 for(int i = 0; i<N; i++){
		        if (board[i][i] != symbol) diagonal1win = 0;
        if (board[i][N - 1 - i] != symbol) diagonal2Win = 0;
    }
    return diagonal1win || diagonal2win;
}

// check if draw
//
	  
int draw(){
	for(int i = 0; i<N; i++)
		for(int j=0; j<N;j++)
			if (board[i][j] == ' ' ) return 0;
	return 1;
}


