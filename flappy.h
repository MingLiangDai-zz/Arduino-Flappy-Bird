#include "initialize.h"

//This array would make all 64 LED's light up
byte ALL[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};

//Function for drawing objects onto the 64-LED matrix
void draw(byte object[]) {
  //Looping through the rows
  for (int i = 0; i < 8; i++) {
    digitalWrite(rows[i], HIGH);
    //Looping through the LED's within each row
    for (int k = 0; k < 8; k++) {
      digitalWrite(cols[k], (~object[i] >> (7-k)) & 1);
      digitalWrite(cols[k], HIGH);
    }
    digitalWrite(rows[i], LOW);
  }
}

//Board/bird -> I'm going to refer the "bird" as the board///////////////////////////////////////////////////
//The x position of the board/bird. No y position because the board stays at the bottom of the playing field
int board_x;

//Function for the movement of the board
void move_board() {
  //The x position of the board takes in input from the potentiometer
  board_x = 1 + (analogRead(A4)/1023.0) * 6;
}

//Function for drawing the board
void drawboard() {
  //Initializing and declaring the array storing the position of the player-board
  byte *p_board = new byte[8]{};
  for (int i = 0; i < 8; i++) {
    p_board[i] = 0;
  }
  
  //Input x and y of the board using the array defined above
  for (int i = 0; i <= board_x; i++) {
    if (i == board_x) {
      p_board[i] = 1;
      p_board[i-1] = 1;
    }
  }
  //Drawing the board and deleting dynamically allocated array
  draw(p_board);
  delete[] p_board;
  p_board = 0;
}



//Pipes/////////////////////////////////////////
//Position for the pipe
int x = 4;
int y = 7;

//Bounds of the pipe, used for calculations later on
byte upper = 7;
byte lower = 2;

int new_x;


//Function for calculating the new spawn x-position of pipe
void get_x() {
  if (board_x <= 1) {
    new_x = board_x + 2;
  } else if (board_x >= 6) {
    new_x = board_x - 4;
  } else {
    new_x = board_x + 2;
  }
}


//boolean for checking if the pipe and respawn
bool can_back = false;

//Function for applying the movement of the pipe
void travel() {
  if (can_back) {
      x = new_x;
      y = 7;
      can_back = false;
  } else {
    y--;
  }
  if (y == 0 && (x == board_x || (x - 1) == board_x)) {
    can_back = true;
  }
}


//Function for drawing the pipe
void drawpipe() {
  //Array for storing the x and y position of the pipe
  byte *p_pipe = new byte[8]{};
  for (int i = 0; i < 8; i++) {
    p_pipe[i] = 0;
  }
  //Input x and y by using the array above
  for (int i = 0; i < 8; i++) {
    if (!(i >= x - 2 && i <= x)) {
      p_pipe[i] = 1 << y;
    }
  }
  //Drawing the pipe, deleting dynamically allocated array, freeing up memory, preventing memory leak
  draw(p_pipe);
  delete[] p_pipe;
  p_pipe = 0;
}

//Game variables, at default values
int velocity = 200;
int counter = 0;
int speedup = 0;

//Function for resetting the game, setting all game variables back to default
void reset_game() {
  for (int i = 0; i < 5; i++) {
    delay (100);
    draw(ALL);
    y = 7;
    x = 4;
    speedup = 0;
    counter = 0;
    velocity = 200;
  }
}

//Function for running the game, calling above functions to make the game run
void start_game() {
  counter++;
  drawboard();
  move_board();
  drawpipe();
  get_x();
  speedup++;

  //After a certain time interval, the difficulty of the game increases
  if(speedup == 3500) {
    speedup = 0;
    if (velocity > 100) {
      velocity-=50;
    }
  }
  if (counter >= velocity) {
    travel();
    counter = 0;
  }

  //Lose, reset
  if (y == 0 && !(x == board_x || (x - 1) == board_x)) {
      reset_game();
  }
}
