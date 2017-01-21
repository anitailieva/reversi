//
// Created by anitailieva on 02/12/16.
//
#include "board.h"
#include <stdio.h>
#include <string.h>

Board currentBoard;
int present = BLACK;
int count;

// input for the players names
char playerB[20];
char playerW[20];
FILE *fp;

// takes input from user
char input[3];

// write in file
char file[3]={"  "};

// Set currentBoard to starting position
void initBoard(Board* board){
        
	int x,y;
        for( y=0;y<BOARD_SIZE;y++){
            for( x=0;x<BOARD_SIZE;x++){
                board->fields[x][y]=NONE;
            }
        }
        board->fields[3][3]=WHITE;
        board->fields[4][4]=WHITE;
        board->fields[3][4]=BLACK;
        board->fields[4][3]=BLACK;

	// opening file in write mode to clear old data, so that the file shows only last moves        
	fp = fopen("moves.txt", "w");
        fclose(fp);

}

// checking if move is valid or not
int validMove (const int x, const int y) {
        int i, j;
        int counter = 0;
        int moved = 0;


	// x and y are the coordinates of the board which helps us check where user makes a move
	// if the value of x and y is less than 0 than this means the value is not valid
        if (x < 0 || BOARD_SIZE <= x || y < 0 || BOARD_SIZE <= y) 
    	return 0;
	if(currentBoard.fields[x][y] != NONE) return 0;
        

	// if the moves are valid then track the position and save it
        if (y > 1 && currentBoard.fields[x][y-1] == -present) {  		
            for (j = y - 2; j >= 0; j-- ) {
                if (currentBoard.fields[x][j] == present) { 
    		moved += 1; 	
    		counter += y-j-1; 
    		break; }

                if (currentBoard.fields[x][j] == NONE) { 
    		break; }
            }
        }

        if (y < BOARD_SIZE-2 && currentBoard.fields[x][y+1] == -present) {
            for (j = y + 2; j < BOARD_SIZE; j++ ) {
                if (currentBoard.fields[x][j] == present) { 
    		moved += 2; 
    		counter += j-y-1;
    		break; }

                if (currentBoard.fields[x][j] == NONE) { 
    		break; }
            }
        }

        if (x > 1 && currentBoard.fields[x-1][y] == -present) {  		
            for (i = x - 2; i >= 0; i-- ) {
                if (currentBoard.fields[i][y] == present) { 
    		moved += 4; 
    		counter += x-i-1; 
    		break; }

                if (currentBoard.fields[i][y] == NONE) { 
    		break; }
            }
        }

        if (x < BOARD_SIZE-2 && currentBoard.fields[x+1][y] == -present) {
            for (i = x + 2; i < BOARD_SIZE; i++ ) {
                if (currentBoard.fields[i][y] == present) { 
    		moved += 8; 
    		counter += i-x-1; 
    		break; }

                if (currentBoard.fields[i][y] == NONE) { 
    		break; }
            }
        }

        if (x > 1 && y > 1 && currentBoard.fields[x-1][y-1] == -present) {
            for ( i = x - 2, j = y - 2;  i >= 0 && j >= 0;  i--, j--) {
                if (currentBoard.fields[i][j] == present) { 
    		moved += 16; 
    		counter += y-j-1; 
    		break; }

                if (currentBoard.fields[i][j] == NONE) { 
    		break; }
            }
        }

        if (x < BOARD_SIZE-2 && y > 1 && currentBoard.fields[x+1][y-1] == -present) {  		
            for (i = x + 2, j = y - 2; i < BOARD_SIZE && j >= 0;  i++, j--){
                if (currentBoard.fields[i][j] == present) { 
    		moved += 32; 
    		counter += y-j-1;
    		break; }

                if (currentBoard.fields[i][j] == NONE) { 
    		break; }
            }
        }

        if (x > 1 && y < BOARD_SIZE-2 && currentBoard.fields[x-1][y+1] == -present) {  		
            for (i = x - 2, j = y + 2;  i >= 0 && j < BOARD_SIZE;  i--, j++) {
                if (currentBoard.fields[i][j] == present) { 
    		moved += 64; 
    		counter += j-y-1;
    		break; }

                if (currentBoard.fields[i][j] == NONE) { 
    		break; }
            }
        }

        if (x < BOARD_SIZE-2 && y < BOARD_SIZE-2 && currentBoard.fields[x+1][y+1] == -present) {  		
            for (i = x + 2, j = y + 2;  i < BOARD_SIZE && j < BOARD_SIZE;  i++, j++) {
                if (currentBoard.fields[i][j] == present) { 
    		moved += 128; 
    		counter += j-y-1; 
    		break; }

                if (currentBoard.fields[i][j] == NONE) { 
    		break; }
            }
        }

    	if (currentBoard.fields[x][y] != NONE ) 
    	return 0;

	// returning the valid position made by user
        return moved;
}


//Prints the currentBoard using traditional ascii-art type graphics
void printBoard(const Board* board)
    {
        printf("    a   b   c   d   e   f   g   h  \n");
        int y,x;
        for( y = 0; y < BOARD_SIZE;y++){
            printf("  +---+---+---+---+---+---+---+---+\n");
            printf(" %d",y + 1); //Computer counts from 0, the game counts from 1!
            for( x = 0; x < BOARD_SIZE; x++){
                printf("| ");
                switch (board->fields[x][y] ) {
                    case BLACK: printf("@ ");
                        break;
                    case WHITE: printf(". ");
                        break;
                    case NONE : printf("  ");
                        break;
                }
            }
            printf("| %d\n",y+1); //Computer counts from 0, the game counts from 1!
        }
        printf("  +---+---+---+---+---+---+---+---+\n");
        printf("    a   b   c   d   e   f   g   h  \n");
}

// make a move
int turned (int x, int y) {

        int i, j;
        int reversed = 0;
	
	// if the position is valid , it will return the method validMove
        int pos = validMove(x, y);

	// if it is not valid it will return 0;
        if (!pos) return 0;

	// getting the position of the board where we want to make our move
        currentBoard.fields[x][y] = present;

	// checking all possible moves a user can enter
        if (pos & 1) {
            for (j = y - 1; currentBoard.fields[x][j] == -present;  j-- ) {
                currentBoard.fields[x][j] = present;
                reversed++;
            }
        }
        pos >>= 1;

        if (pos & 1) {
            for (j = y + 1; currentBoard.fields[x][j] == -present;  j++ ) {
                currentBoard.fields[x][j] = present;
                reversed++;
            }
        }
        pos >>= 1;

        if (pos & 1) {
            for (i = x - 1; currentBoard.fields[i][y] == -present;  i-- ) {
                currentBoard.fields[i][y] = present;
                reversed++;
            }
        }
        pos >>= 1;

        if (pos & 1 ) {
            for (i = x + 1; currentBoard.fields[i][y] == -present;  i++ ) {
                currentBoard.fields[i][y] = present;
                reversed++;
            }
        }
        pos >>= 1;

        if (pos & 1 ) {
            for (i = x - 1, j = y - 1; currentBoard.fields[i][j] == -present;  i--, j-- ) {
                currentBoard.fields[i][j] = present;
                reversed++;
            }
        }
        pos >>= 1;

        if (pos & 1 ) {
            for (i = x + 1, j = y - 1;  currentBoard.fields[i][j] == -present; i++, j-- ) {
                currentBoard.fields[i][j] = present;
                reversed++;
            }
        }
        pos >>= 1;

        if (pos & 1 ) {
            for (i = x - 1, j = y + 1;  currentBoard.fields[i][j] == -present; i--, j++ ) {
                currentBoard.fields[i][j] = present;
                reversed++;
            }
        }
        pos >>= 1;

        if (pos & 1 ) {
            for (i = x + 1, j = y + 1;  currentBoard.fields[i][j] == -present; i++, j++ ) {
                currentBoard.fields[i][j] = present;
                reversed++;
            }
        }
        pos >>= 1;

        present = -present;

        for (i=0; i < BOARD_SIZE; i++ ) {
            for (j=0; j < BOARD_SIZE; j++ ) {
                if (validMove(i, j) ) {
                    return reversed;
		}
            }
        }

        present = -present;
        for (i = 0; i < BOARD_SIZE; i++ ) {
            for (j = 0; j < BOARD_SIZE; j++ ) {
                if (validMove(i, j) ) {
                    return reversed;
                }
            }
        }

        return -1;
    }


// finding out who the winner is
int calculateTheWinner() {

    	int count = 0;
    	int empty = 0;
    	int k = 0;
        	int i, j;
        	
    	//going through each cell in the board 
        for (i = 0; i < BOARD_SIZE; i++ ) {
            for (j = 0; j < BOARD_SIZE; j++ ) {
                k += currentBoard.fields[i][j];
    	
    	// if the piece is "@", it means it belongs to BLACK and it counts the pieces           
    	if(currentBoard.fields[i][j]==BLACK) 
    		count++;
    	// if there is no sign, it means the piece is empty, it counts the empty pieces
                else if(currentBoard.fields[i][j]==NONE) 
    		empty++;
            }
        }

 
       	printf("\tPlayer @ : %d \n", count);
    	printf("\tPlayer . : %d \n", BOARD_SIZE * BOARD_SIZE - count - empty);

        if(k < 0) 
    	return WHITE;
        else if(k > 0) 
    	return BLACK;
        else              
    	return NONE;
}


// start to play the game
void play(){

        int result = 1, x, y;
        char input[3];
        char file[3] = {"  "};

        while (result > 0 ) {
            printBoard(&currentBoard);

            if (present == BLACK) {
                printf("\n\t%s's turn (@)\n",playerB);
            }
            else {
                printf("\n\t%s's turn (.)\n",playerW);
            }
            fp = fopen("moves.txt", "a");
    	
	// infinity loop, needs a break to exit the loop
            while (1) {
    		
                printf("\n\tEnter your coordinates(E.g.(B3)(b 3)(B,3))=> ");
               	
		int i = 0;
		while((input[i] = getchar()) != '\n')
		i++;
		input[i] = '\0';

                if((input[0] >= 'a' && input[0] <= 'h') || (input[0] >= 'A' && input[0] <= 'H')) {

                    x = (input[0] >= 'a' && input[0] <= 'h') ? input[0] % 'a' : input[0] % 'A';
                    file[0] = input[0];

    		
                if((input[1] ==' ' || input[1] == ',') && (input[2] >= '0' && input[2]<='8' && input[3] =='\0'))
                    {
			// 48 is the ASCII value for 0
                        y = input[2] % 48 - 1;
                        file[1] = input[2];
                    }
    		
                    else if((input[1] >= '0' && input[1] <= '8') && input[2] =='\0')
                    {
                        y = input[1] % 48 - 1;
                        file[1] = input[1];
                    }
                    else
                    {
                        printf("\n\tThe input is not valid. Try again\n\n");
                        continue;
                    }
                }	
                else
                {
                    printf("\n\tThe input is not valid. Try again\n\n");
                    continue;
                }

    		
    		// if you place a piece in a position where you don't get a straight (horizontal, vertical,
    		// or diagonal) line, you are being asked to place again
                result = turned(x, y);
                if (result == 0 ) {
                    printf("\n\t (%c,%d) You can't place a piece here! Place again\n\n", input[0], y+1);
                }
                else {
    		// if the position you chose give you a straight line, it writes the move you made to the file
                    fputs(file,fp);
			
		// adding space after move is written to the file
                    fprintf(fp," ");
                    fclose(fp);
                    break;
                }

            }
        }

    	// prints the board 
        printBoard(&currentBoard);
        	
    	    switch (calculateTheWinner() ) {
    	        case BLACK: printf("\tThe winner is (@): %s \n\n",playerB);
    	            break;
    	        case WHITE: printf("\tThe winner is (.): %s \n\n",playerW);
    	            break;
    	        case NONE : printf("\tIt's a tie!\n\n");
                break;
        }

}

//Demonstrates currentBoard functionality
int main(void)
    {
	
       	printf("Enter the player name for black side: ");
    	fgets(playerB, sizeof(playerB), stdin);
	//Removes \n from input    	
	playerB[strlen(playerB)-1]='\0';
   

    	printf("Enter the player name for white side: ");
    	fgets(playerW, sizeof(playerW), stdin);
	// Removes \n from input     
	playerW[strlen(playerW)-1]='\0';
	
        initBoard(&currentBoard);
        play();

    }


