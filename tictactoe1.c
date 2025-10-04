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
	 for (int  i =0; i<N; i++){
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
	  
	  // free dynamically aloocate board

  void freeboard(){ 
     for(int i=0; i<N;i++)
     free(board[i]);
    free(board);
  }

// cheking the validity of a move 
  
 int  validityofmove(int row , int col){
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
   void computermove(int *row , int *col){
	   do{
		   *row = rand() % N;
		   *col = rand() % N;
	   }while (!validityofmove(*row, *col));
	   printf("computer choose : %d %d \n", *row, *col);
	   }


void logmove(int playernum, char symbol, int row, int col){
	if(logFile){
		fprintf(logFile , "player %d (%c) moved to (%d,%d)\n", playernum + 1, symbol,row,col);
		fflush(logFile);
	}
}

// checking if a player won 
// first check rowns and columns
 int check(char symbol){

	 for(int i = 0; i<N; i++){
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
		        if (board[i][i] != symbol) diagon1win = 0;
        if (board[i][N - 1 - i] != symbol) diagon2win = 0;
    }
    return diagon1win || diagon2win;
}

// check if draw
//
	  
int draw(){
	for(int i = 0; i<N; i++)
		for(int j=0; j<N;j++)
			if (board[i][j] == ' ' ) return 0;
	return 1;
}

int main() {
	srand(time(NULL));
	int gameMode;

	printf("TIC-Tac-Toe! \n");
          
	

           do  {
                printf("Enter board size N (3 <= N <= 10): ");
                scanf("%d", &N);
      } while (N < 3 || N > 10); 

	// getting the game mode 
	

            printf("select the game mode \n");
	    printf("1. user vs user\n");
	    printf("2. user vs computer \n");
	    printf("3. three players  \n");
	    printf( " enter your choice ( 1-3) \n");
	    scanf("%d", &gameMode);


         int numPlayers;
    Player players[Max_players];

    if (gameMode == 1) {  // Two Users
        numPlayers = 2;
        players[0].mode = 0; players[0].symbol = 'X';
        players[1].mode = 0; players[1].symbol = 'O';
    } 
    else if (gameMode == 2) {  // User vs Computer
        numPlayers = 2;
        players[0].mode = 0; players[0].symbol = 'X'; // User
        players[1].mode = 1; players[1].symbol = 'O'; // Computer
    } 
    else if (gameMode == 3) {  // Three players
        numPlayers = 3;
        // At least one human
        for (int i = 0; i < 3; i++) {
            char choice;
            printf("Is Player %d (%c) a computer? (y/n): ", i + 1, symbols[i]);
            scanf("%c", &choice);
            players[i].mode = (choice == 'y' || choice == 'Y') ? 1 : 0;
            players[i].symbol = symbols[i];
        }
    } 
    else {
        printf("Invalid choice!\n");
        return 1;
    }

    
    createboard(N);

    // Open log file
    logFile = fopen("game_log.txt", "w");
    if (!logFile) {
        perror("Error opening log file");
        printf("Continuing without logging...\n");
    }

    // --- Game loop ---
    int currentPlayer = 0;
    int gameOver = 0;
    displayBoard();

    while (!gameOver) {
        int row, col;
        Player p = players[currentPlayer];

        printf("Turn: Player %d (%c)\n", currentPlayer + 1, p.symbol);

        if (p.mode) {
            computermove(&row, &col);
        } else {
            usermove(&row, &col, p.symbol);
        }

        board[row][col] = p.symbol;
        logmove(currentPlayer, p.symbol, row, col);
        logBoard();
        displayBoard();

        if (check(p.symbol)) {
            printf("Player %d (%c) WINS!\n", currentPlayer + 1, p.symbol);
            if (logFile)
                fprintf(logFile, "Player %d (%c) wins!\n", currentPlayer + 1, p.symbol);
            gameOver = 1;
        } else if (draw()) {
            printf("The game is a DRAW.\n");
            if (logFile)
                fprintf(logFile, "Game ended in a draw.\n");
            gameOver = 1;
        }

        currentPlayer = (currentPlayer + 1) % numPlayers;
    }

    if (logFile) fclose(logFile);
    freeboard();
    return 0;
}
