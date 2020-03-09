//INSTRUCTION TO SET UP PINS: Want pins in order, on the 1588BS side. Start from digital 2. Skip 5 and 11. What would have been in A4 is now placed in digital pin 0;
//Potentiometer pin = A4;

//y
#define row_1 7
#define row_2 3
#define row_3 9
#define row_4 2
#define row_5 A3
#define row_6 10
#define row_7 A5
#define row_8 A0

//x
#define col_1 12
#define col_2 13
#define col_3 A2
#define col_4 8
#define col_5 A1
#define col_6 6
#define col_7 4
#define col_8 0

//Arrays storing the rows and columns of the 64-LED matrix
byte rows[] = {
  row_1, row_2, row_3, row_4, row_5, row_6, row_7, row_8
};

byte cols[] = {
  col_1, col_2, col_3, col_4, col_5, col_6, col_7, col_8
};
