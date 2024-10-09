#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int cash = 1000;
    int bet = 5;
    int numO, numT, numTh;
    int jackWin;
    int yesNo;
    int spins; 

    srand(time(NULL)); // Initialize random number generator
    printf("Welcome to the Slot Machines! You start with $1000. The bet is $5.\n");
    printf("Match all three numbers to win $100 times the number shown.\n");
    printf("\n");

    do {
        printf("How many spins would you like to make? ");
        scanf("%d", &spins);

        for (int i = 0; i < spins; i++) {
            numO = rand() % 6 + 1;   
            numT = rand() % 6 + 1;   
            numTh = rand() % 6 + 1; 

            cash -= bet;

            printf("Current Balance = $%4d    ", cash);
            printf("Spin #%d: %d %d %d    ", i + 1, numO, numT, numTh);

            // Jackpot condition: all three numbers match
            if (numO == numT && numT == numTh) {
                jackWin = bet * 30;
                cash += jackWin;
                printf("Jackpot! You win $%d!\n", jackWin);
            }
            else {
                printf("Sorry, no matches.\n");
            }

            if (cash < bet) {
                printf("You're out of money! Game over.\n");
                return 0;
            }
        }

        printf("Would you like to spin again (Yes=1, No=0)? ");
        scanf("%d", &yesNo);

    } while (yesNo == 1);

    printf("Game over. Your final balance was $%d.\n", cash);
    return 0;
}
