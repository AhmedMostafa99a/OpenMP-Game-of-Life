#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h> 

#define RESET "\033[0m"
#define GREEN "\033[36m"  
#define SEP "\033[32m"   
#define RED "\033[31m"     
#define YELLOW "\033[33m"  

#define arr(grid, i, j, cols) (grid[((i) * ((cols) + 2)) + (j)])


int count_neighbors(int *grid, int i, int j, int cols) {
    int alive_n = 0;
    alive_n += arr(grid, i - 1, j - 1, cols);
    alive_n += arr(grid, i - 1, j, cols);
    alive_n += arr(grid, i - 1, j + 1, cols);
    alive_n += arr(grid, i, j - 1, cols);
    alive_n += arr(grid, i, j + 1, cols);
    alive_n += arr(grid, i + 1, j - 1, cols);
    alive_n += arr(grid, i + 1, j, cols);
    alive_n += arr(grid, i + 1, j + 1, cols);
    return alive_n;
}

void display(int *grid, int r, int c) {
    printf("\nThe state of generation is:\n\n");
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (arr(grid, i, j, c) == 1) {
                printf("🟩"); 
            } else {
                printf("⬛");
            }
        }
        printf("\n");
    }
    printf(SEP "===================\n" RESET);
}

void next_gen(int *grid, int r, int c) {
    int total_arrs = (r + 2) * (c + 2);
    int *nextGrid = (int *)calloc(total_arrs, sizeof(int));

    #pragma omp parallel for collapse(2)
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            int alive_n = count_neighbors(grid, i, j, c);
            if (arr(grid, i, j, c) == 1) {
                arr(nextGrid, i, j, c) = (alive_n == 2 || alive_n == 3) ? 1 : 0;
            } else {
                arr(nextGrid, i, j, c) = (alive_n == 3) ? 1 : 0;
            }
        }
    }

    // Copy nextGrid to grid
    #pragma omp parallel for collapse(2)
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            arr(grid, i, j, c) = arr(nextGrid, i, j, c);
        }
    }
    
    free(nextGrid);
}

void run(int *grid, int r, int c, int run_time) {
    for (int gen = 1; gen <= run_time; gen++) {
        printf("Generation %d:", gen);
        display(grid, r, c);
        next_gen(grid, r, c);
    }
}


void init_random(int *grid, int r, int c) {
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            arr(grid, i, j, c) = rand() % 2;
        }
    }
}

void init_percentage(int *grid, int r, int c, int percentage) {
    int alive_arrs = (r * c * percentage) / 100;
    while (alive_arrs > 0) {
        int i = (rand() % r) + 1;
        int j = (rand() % c) + 1;

        if (arr(grid, i, j, c) == 0) {
            arr(grid, i, j, c) = 1;
            alive_arrs--;
        }
    }
}

int main() {
    int rows, cols, run_time;
    char ch;

    srand(time(NULL)); 

    do {
        printf("=== Hello in Game Of Life === \n");
        int option;
        printf("Choose an option:\n");
        printf("[1] Random initialization\n");
        printf("[2] Percentage-based initialization\n");
        printf("[3] Exit Program \n");
        
        printf(GREEN "Enter your choice: " RESET);
        fflush(stdout);
        scanf("%d", &option);

        if (option == 3) {
            printf("Exiting the program.\n");
            return 0;
        }

        if (option != 1 && option != 2) {
            printf(RED "Invalid option.\n" RESET);
            continue;
        }

        printf(GREEN "Enter the size of the grid (rows cols):\n" RESET);
        fflush(stdout);
        scanf("%d %d", &rows, &cols);

        int total_arrs = (rows + 2) * (cols + 2);
        int *grid = (int *)calloc(total_arrs, sizeof(int));

        if (option == 1) {
            init_random(grid, rows, cols);
        } 
        else if (option == 2) {
            int percentage;
            do {
                printf(GREEN "Enter the percentage of alive arrs (0-100)%%: " RESET);
                fflush(stdout);
                scanf("%d", &percentage);
            } while (percentage < 0 || percentage > 100);
            init_percentage(grid, rows, cols, percentage);
        }

        printf(GREEN "Enter the number of generations to simulate:\n" RESET);
        fflush(stdout);
        scanf("%d", &run_time);

        if (run_time > 0) {
            run(grid, rows, cols, run_time);
        } else {
            printf(RED "Invalid run time.\n" RESET);
        }

        free(grid); 

        printf(YELLOW "Do you want to play again? (y/n): " RESET);
        fflush(stdout);
        scanf(" %c", &ch);
        
    } while (ch == 'Y' || ch == 'y');
    
    printf("Game Over, Good bye \n");
    return 0;
}
