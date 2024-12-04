// A simple variant of the game Snake
//
// Used for teaching in classes
//
// Author:
// Franz Regensburger
// Ingolstadt University of Applied Sciences
// (C) 2011
//
// The board model


#include <curses.h>
#include "worm.h"
#include "board_model.h"
#include "messages.h"


// *************************************************
// Placing and removing items from the game board
// Check boundaries of game board
// *************************************************

// Place an item onto the curses display.
void placeItem(struct board* aboard, int y, int x, enum BoardCodes board_code, chtype symbol, enum ColorPairs color_pair) {

    //  Store item on the display (symbol code)
    move(y, x);                         // Move cursor to (y,x)
    attron(COLOR_PAIR(color_pair));     // Start writing in selected color
    addch(symbol /*@006*/);                      // Store symbol on the virtual display
    attroff(COLOR_PAIR(color_pair));    // Stop writing in selected color

    aboard->cells[y][x] = board_code;
}

// Getters

// Get the last usable row on the display
int getLastRowOnBoard(struct board* aboard){
    return aboard -> last_row;
}

// Get the last usable column on the display
int getLastColOnBoard(struct board* aboard){
    return aboard -> last_col;
}

int getNumberOfFoodItems(struct board* aboard){
    return aboard -> food_items;
}

enum BoardCodes getContentAt(struct board* aboard, struct pos position){
    return aboard -> cells[position.y][position.x];
}

void setNumberOfFoodItems (struct board* aboard, int n){
    aboard->food_items = n;
}

void decrementNumberOfFoodItems(struct board* aboard){
    aboard->food_items -= 1;
}

enum ResCodes initializeLevel(struct board* aboard) {
    int y,x;

    for (y = 0; @002 ; y++) {
        for (x = 0; @002 ; x++) {
        placeItem(aboard,y,x,BC_FREE_CELL,SYMBOL_FREE_CELL,COLP_FREE_CELL);
        }
    }

    // Draw a line in order to separate the message area
    // Note: we cannot use function placeItem() since the message area
    // is outside the board!
    y = aboard->last_row + 1;

    for (x=0; @003 ; x++) {
        move(y, x);
        attron(COLOR_PAIR(COLP_BARRIER));
        addch(SYMBOL_BARRIER);
        attroff(COLOR_PAIR(COLP_BARRIER));
    }
    // Draw a line to signal the rightmost column of the board.
    for (y=0; y <= aboard->last_row ; y++) {
        placeItem(aboard,y,aboard->last_col,
        BC_BARRIER,SYMBOL_BARRIER,COLP_BARRIER);
    }
    // Barriers: use a loop
    for ( @004 ) {
        @004
        placeItem(aboard,y,x,BC_BARRIER,SYMBOL_BARRIER,COLP_BARRIER);
    }
    for ( @005 ) {
        @005
        placeItem(aboard,y,x,BC_BARRIER,SYMBOL_BARRIER,COLP_BARRIER);
    }
    // Food
    placeItem(aboard, 3, 3,BC_FOOD_1,SYMBOL_FOOD_1,COLP_FOOD_1);
    @006
    // Initialize number of food items
    // Attention: must match number of items placed on the board above
    aboard->food_items = 10;
    return RES_OK;
}
