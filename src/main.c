#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5

void slotMachineGame() {
    int cash = 1000;
    int bet = 5;
    int numO, numT, numTh;
    int jackWin;
    int yesNo;
    int spins;

    srand(time(NULL)); 
    printf("Welcome to the Slot Machines! You start with $1000. The bet is $5.\n");
    printf("Match all three numbers to win $100 times the number shown.\n");
    printf("\n");

    do {
        printf("How many spins would you like to make (up to 10)? ");
        scanf("%d", &spins);

        if (spins < 1 || spins > 10) {
            printf("Invalid number of spins. Please choose between 1 and 10.\n");
            continue; 
        }

        for (int i = 0; i < spins; i++) {
            numO = rand() % 6 + 1;
            numT = rand() % 6 + 1;
            numTh = rand() % 6 + 1;

            cash -= bet; 

            printf("Current Balance = $%4d    ", cash);
            printf("Spin #%d: %d %d %d    ", i + 1, numO, numT, numTh);

            if (numO == numT && numT == numTh) {
                jackWin = bet * 30;
                cash += jackWin;
                printf("Jackpot! You win $%d!\n", jackWin);
            } else {
                printf("Sorry, no matches.\n");
            }

            if (cash < bet) {
                printf("You're out of money! Game over.\n");
                return; 
            }
        }

        printf("Would you like to spin again (Yes=1, No=0)? ");
        scanf("%d", &yesNo);

    } while (yesNo == 1);

    printf("Game over. Your final balance was $%d.\n", cash);
}

void initializeField(char field[SIZE][SIZE], int bombs) {

    // --- INITIALIZE BOMB COUNTER ---
    int count = 0;
    // --- FILL FIELD WITH DIAMONDS ---
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            field[i][j] = 'D'; 
        }
    }

    // --- PLACE BOMBS RANDOMLY ---
    while (count < bombs) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        if (field[row][col] != '*') { 
            field[row][col] = '*';
            count++;
        }
    }
}

void printField(char field[SIZE][SIZE], int reveal) {

    // --- ITERATE THROUGH FIELD ---
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // --- REVEAL OR HIDE SQUARE ---
            if (reveal) {
                printf("%c ", field[i][j]); 
            } else {
                printf("? "); 
            }
        }
        printf("\n");
    }
}

void minefieldGame() {
    // --- VARIABLE DECLARATIONS ---
    char field[SIZE][SIZE];   
    int bombs, row, col, diamonds = 0;  
    int bet = 5;             
    double winnings = bet;    
    int totalDiamonds;        
    int remainingSquares = SIZE * SIZE; 

    // --- GAME START AND INPUT ---
    printf("Welcome to the Minefield Game!\n"); 
    printf("Choose the number of bombs (1 to 25): "); 
    scanf("%d", &bombs); 

    // --- INPUT VALIDATION ---
    if (bombs < 1 || bombs > 25) { 
        printf("Invalid number of bombs.\n"); 
        return; 
    }

    // --- FIELD INITIALIZATION AND DISPLAY ---
    initializeField(field, bombs); 
    printField(field, 0);          

    totalDiamonds = (SIZE * SIZE) - bombs; 

    // --- MAIN GAME LOOP ---
    while (1) { 
        // --- GET USER INPUT ---
        printf("Enter row (1-5) and column (1-5): "); 
        scanf("%d %d", &row, &col); 

        // --- INPUT VALIDATION ---
        if (row < 1 || row > SIZE || col < 1 || col > SIZE) { 
            printf("Invalid coordinates. Try again.\n"); 
            continue; 
        }

        // --- ADJUST FOR 0-BASED INDEXING ---
        row--;  
        col--; 

        // --- CHECK CHOSEN SQUARE ---
        if (field[row][col] == '*') { 
            // --- BOMB HIT ---
            printf("Boom! You hit a bomb. Game over.\n"); 
            printField(field, 1); 
            break; 
        } else if (field[row][col] == 'D') { 
            // --- DIAMOND FOUND ---
            diamonds++;          
            field[row][col] = 'R'; 
            remainingSquares--;    

            double probabilityToChooseDiamond = (double)(totalDiamonds - diamonds) / remainingSquares; 
            winnings *= (1.0 / probabilityToChooseDiamond);  

            printf("You found a diamond! Total diamonds: %d. Winnings multiplied by %.2f.\n", diamonds, (1.0 / probabilityToChooseDiamond)); 
            printf("Your winnings: $%.2f\n", winnings); 
        }

        // --- PRINT UPDATED FIELD ---
        printField(field, 0); 

        // --- CONTINUE OR QUIT ---
        char choice; 
        printf("Do you want to continue? (y/n): "); 
        scanf(" %c", &choice); 
        if (choice != 'y') { 
            break; 
        }
    }

    // --- GAME OVER ---
    printf("Game over. You found %d diamonds.\n", diamonds); 
}

void menu() {
    int choice;

    printf("Select a game to play:\n");
    printf("1. Slot Machine\n");
    printf("2. Minefield\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            slotMachineGame();
            break;
        case 2:
            minefieldGame();
            break;
        default:
            printf("Invalid choice. Please select again.\n");
            menu(); 
            break;
    }
}

int main(void) {
    srand(time(NULL)); 
    menu(); 
    return 0;
}