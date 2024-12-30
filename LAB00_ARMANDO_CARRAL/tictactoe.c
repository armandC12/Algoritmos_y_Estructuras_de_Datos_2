#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define BOARD_SIZE 3
#define CELL_MAX (BOARD_SIZE * BOARD_SIZE - 1)

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    int cell = 0;
    printf("\t .................................................\n");
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int column = 0; column < BOARD_SIZE; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        printf("\t .................................................\n");
    }
}

char get_winner(char board[BOARD_SIZE][BOARD_SIZE])
{
    char winner = '-';
    char gamer_one = 'X';
    char gamer_two = 'O';
    int count_diag_one = 0;
    int count_diag_two = 0;
    int count_diag_inv_one = 0;
    int count_diag_inv_two = 0;
    bool cell = false;

    /* VERIFICACION DE FILA */
    for (unsigned int row = 0; row < BOARD_SIZE; ++row) {
        //FILA
        int count_gamer_one = 0;
        int count_gamer_two = 0;
        for (unsigned int column = 0; column < BOARD_SIZE; ++column) {
            if (board[row][column] == gamer_one && count_gamer_one < BOARD_SIZE) {
                count_gamer_one +=1;
            }
            else if (board[row][column] == gamer_two && count_gamer_two < BOARD_SIZE) {
                count_gamer_two +=1;
            }
        
            if (count_gamer_one == BOARD_SIZE) {
                winner = gamer_one;
            }
            else if (count_gamer_two == BOARD_SIZE) {
                winner = gamer_two;
            }
        }
        //COLUMNA
        count_gamer_one = 0;
        count_gamer_two = 0;        
        for (unsigned int column = 0; column < BOARD_SIZE; ++column) {
            if (board[column][row] == gamer_one && count_gamer_one < BOARD_SIZE) {
                count_gamer_one +=1;
            }
            else if (board[column][row] == gamer_two && count_gamer_two < BOARD_SIZE) {
                count_gamer_two +=1;
            }
        
            if (count_gamer_one == BOARD_SIZE) {
                winner = gamer_one;
            }
            else if (count_gamer_two == BOARD_SIZE) {
                winner = gamer_two;
            }
        }
        //DIAGONAL IZQ a DER
        for (unsigned int column = 0; column < BOARD_SIZE; ++column) {
            if (row == column && board[row][column] == gamer_one && count_diag_one < BOARD_SIZE) {
                count_diag_one +=1;
            }
            else if (row == column && board[row][column] == gamer_two && count_diag_two < BOARD_SIZE) {
                count_diag_two +=1;
            }
        
            if (count_diag_one == BOARD_SIZE) {
                winner = gamer_one;
            }
            else if (count_diag_two == BOARD_SIZE) {
                winner = gamer_two;
            }
        }
        //DIAGONAL DER a IZQ
        for (unsigned int column = 0; column < BOARD_SIZE; ++column) {
            cell = row+column == BOARD_SIZE-1;
            if (cell && board[row][column] == gamer_one && count_diag_inv_one < BOARD_SIZE) {
                count_diag_inv_one +=1;
            }
            else if (cell && board[row][column] == gamer_two && count_diag_inv_two < BOARD_SIZE) {
                count_diag_inv_two +=1;
            }
        
            if (count_diag_inv_one == BOARD_SIZE) {
                winner = gamer_one;
            }
            else if (count_diag_inv_two == BOARD_SIZE) {
                winner = gamer_two;
            }
        }
    }

    return winner;
}

bool has_free_cell(char board[BOARD_SIZE][BOARD_SIZE])  //SUPONEMOS NO HAY UNA CELDAS VACÍA.
{
    bool cell = false;
    for (unsigned int row = 0; row < BOARD_SIZE; ++row) {
        for (unsigned int column = 0; column < BOARD_SIZE; ++column) {
            if (board[row][column] == '-' ) {
                cell = true;
            }
        }
    }

    return cell;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[BOARD_SIZE][BOARD_SIZE] = {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
    };

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al 8): ",
               turn);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / BOARD_SIZE;
            int colum = cell % BOARD_SIZE;
            if (board[row][colum] == '-') {         // SI LA CELDA ESTA VACIA INGRESO...
                board[row][colum] = turn;           // A LA CELDA LE ASIGNO EL CARACTER DEL JUGADOR DE TURNO 
                turn = turn == 'X' ? 'O' : 'X';     
                winner = get_winner(board);         // VERIFICO SI HAY UN GANADOR, CASO CONTRARIO SE SIGUE JUGANDO.
            } else {                                // CASO CONTRARIO, LA CELDA ESTA OCUPADA.
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
