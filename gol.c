#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COLS      20
#define ROWS      10
#define NUM_CELLS COLS*ROWS
#define ALIVE     'g'
#define DEAD      '_'

char cells[NUM_CELLS];

void init_glider() {
    memset(cells, DEAD, NUM_CELLS);
    cells[COLS*1 + 4] = ALIVE;
    cells[COLS*2 + 5] = ALIVE;
    cells[COLS*3 + 3] = ALIVE;
    cells[COLS*3 + 4] = ALIVE;
    cells[COLS*3 + 5] = ALIVE;
}

void next_state() {
    char next_cells[NUM_CELLS];
    memcpy(next_cells, cells, sizeof(cells));

    for (size_t i=1; i < ROWS-1; ++i) {
        for (size_t j=1; j < COLS-1; ++j) {
            size_t k = j + i*COLS;
            int neighbours = 0;

            if (cells[k + 1 + COLS] == ALIVE) neighbours++;
            if (cells[k + 1] == ALIVE)        neighbours++;
            if (cells[k + 1 - COLS] == ALIVE) neighbours++;
            if (cells[k + 0 + COLS] == ALIVE) neighbours++;
            if (cells[k + 0 - COLS] == ALIVE) neighbours++;
            if (cells[k - 1 + COLS] == ALIVE) neighbours++;
            if (cells[k - 1] == ALIVE)        neighbours++;
            if (cells[k - 1 - COLS] == ALIVE) neighbours++;

            if (cells[k] == ALIVE) {
                if (neighbours < 2 || neighbours > 3) next_cells[k] = DEAD;
            }
            if (cells[k] == DEAD) {
                if (neighbours == 3) next_cells[k] = ALIVE;
            }
       }
   	} 

    memcpy(cells, next_cells, sizeof(cells));
}

void print_state() {
   for (size_t i=0; i < ROWS; ++i) {
        for (size_t j=0; j < COLS; ++j) {
            putchar(cells[j + i*COLS]);
        }
        putchar('\n');
   	}
}

int main(void) {
    printf("The canvas size is: %d x %d\n", COLS, ROWS);
    printf("This is a Glider:\n\n");

    init_glider();
    
    while (1){
    	print_state();

    	printf("\033[%dA", ROWS);
	    printf("\033[%dD", COLS);
    	fflush(stdout);

        next_state();

	    usleep(500*1000);
    }

    return 0;
}
