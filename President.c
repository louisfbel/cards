#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// terminal game PRESIDENT

// full deck
#define DECK_SIZE 54

// Suits
typedef enum {
    HEARTS,     // 0
    SPADES,     // 1
    DIAMONDS,   // 2
    CLUBS,      // 3
    JOKER       // 4
} Suits;

// each card holds a suit and a value
typedef struct {
    int suit;
    Suits value;
} Card;

// each card in a stack with pointers to a card and a next stacked card
typedef struct stacked {
    Card* card;
    struct stacked* next;
} Stacked_card;

// 4 Players. 
int players[4] = {1, 2, 3, 4};

// regular card deck
Card deck[DECK_SIZE];

// Stack of cards
Stacked_card* stack = NULL;

// returns the string value of the suit
char* get_suit(Suits suit) {
    switch(suit) {
        case 0:
            return "hearts";
        case 1:
            return "spades";
        case 2:
            return "diamonds";
        case 3:
            return "clubs";
        default:
            return "joker";
    };
}

// recursively frees each node in a linked list
void freeNode(Stacked_card *n)
{
    // base case
    if (n == NULL)
    {
        return;
    }

    // free next recursively
    freeNode(n->next);

    // Free current node
    free(n);
}

// fill deck with cards
void load() {
    // regular cards
    for (int i = 0; i < 52; i ++){
        deck[i].value = (i % 13) + 1;
        deck[i].suit = i / 13;
    };

    // jokers
    deck[52].value = 14;
    deck[52].suit = 4;
    deck[53].value = 14;
    deck[53].suit = 4;
}

// rearrange deck in a pseudorandom order
void shuffle() {
    // array to store cards already processed
    int used[DECK_SIZE];
    for (int i = 0; i < DECK_SIZE; i ++) {
        used[i] = 0;
    };

    // reset stacked deck
    freeNode(stack);
    stack = NULL;

    // randomly order stacked deck
    for (int i = 0; i < DECK_SIZE; i ++) {
        // current card
        Stacked_card *new = malloc(sizeof(Stacked_card));
        if (new == NULL) {
            printf("ERROR: node issue");
        };

        // generate random and find next open position
        int pos = rand() % DECK_SIZE;
        while (used[pos] == 1) {
            pos = (pos + 1) % DECK_SIZE;
        };

        // place card at next open position in top of pile
        used[pos] = 1;
        new->card = &deck[pos];
        new->next = stack;
        stack = new;
    };
};

int main() {
     // seed random with current time
    srand(time(NULL));

    // load deck
    load();

    // print deck
    printf("Unshuffled deck:\n");
    for (int i = 0; i < DECK_SIZE; i ++){
        printf("%i of %s\n", deck[i].value, get_suit(deck[i].suit));
    };

    shuffle();

    // get current card
    Stacked_card *current = stack;

    // print shuffled deck
    printf("Shuffled deck:\n");
    for (int i = 0; i < DECK_SIZE; i ++) {
        printf("%i of %s\n", current->card->value, get_suit(current->card->suit));

        // get next card in stack
        current = current->next;
    };

    // free every card in the stack.
    freeNode(stack);

    return 0;
};

