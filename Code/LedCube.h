#include <stdbool.h>

// Define cube dimensions
#define WIDTH 6
#define HEIGHT 6
#define LENGTH 12

// Initialize values & reference tables for columns, layers, and rows
const int cols[] = {40, 36, 35, 33, 32, 34};
const int lyrs[] = {37, 38, 22, 23, 24, 39};
const int rows[] = {41, 42, 25, 26, 44, 27, 28, 43, 45, 29, 30, 31};

// 3D Point data structure
typedef struct {
  int x;
  int y;
  int z;
  bool val;
} Point3D;

// Main interface for Layercake
bool screen[LENGTH][HEIGHT][WIDTH];

// Test data - block text of the word "HI" with 6 points of depth
bool hi[LENGTH][HEIGHT][WIDTH] = {{{1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1}},
                                  {{1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1}},
                                  {{1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1}},
                                  {{1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1}},
                                  {{0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0}},
                                  {{0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0}},
                                  {{1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1}},
                                  {{1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1}},
                                  {{0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0}},
                                  {{0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0}},
                                  {{1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1}},
                                  {{1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1}}};

// Initialize the values of the screen
void initLayercake() {
  // Set all pins to output mode
  for (int i = 0; i < LENGTH; i++) {
    pinMode(rows[i], OUTPUT);
    if (i < WIDTH)
      pinMode(cols[i], OUTPUT);
    if (i < HEIGHT)
      pinMode(lyrs[i], OUTPUT);
  }

  // Set all LEDs to 0 (off)
  for (int i = 0; i < LENGTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      for (int k = 0; k < WIDTH; k++) {
        screen[i][j][k] = 0;
      }
    }
  }
}

// Multiplexing function
void displayScreen() {
  for (int i = 0; i < LENGTH; i++)
    for (int j = 0; j < HEIGHT; j++)
      for (int k = 0; k < WIDTH; k++) {
        if (screen[i][j][k]) {
          digitalWrite(rows[i], HIGH);
          digitalWrite(lyrs[j], HIGH);
          digitalWrite(cols[k], HIGH);
        }

        // Quickly turn LED off for multiplexing
        delay(0.5);
        digitalWrite(rows[i], LOW);
        digitalWrite(lyrs[j], LOW);
        digitalWrite(cols[k], LOW);
      }
}

// Display text animations
void textScroll(int gap) {
  for (int i = 0; i < 12; i++) {
    // Skip already rendered frames for rapport
    if (i == 0 && screen[0][0][WIDTH - 1])
      i = 12 - gap;

    for (int ii = 0; ii < 10; ii++)
      displayScreen();

    for (int j = 0; j < 12; j++)
      for (int k = 0; k < 6; k++) {
        screen[j][k][WIDTH - 1 - (i % 6)] =
            (i < 6) ? hi[j][k][WIDTH - 1 - (i % 6)] : 0;
        if (i >= gap)
          screen[j][k][WIDTH - i % (gap - 1)] = hi[j][k][WIDTH - i % (gap - 1)];
      }
  }
}

void textBounce() {
  for (int i = 0; i < 12; i++) {
    for (int ii = 0; ii < 10; ii++)
      displayScreen();

    for (int j = 0; j < 12; j++)
      for (int k = 0; k < 6; k++) {
        if (i < 6)
          screen[j][k][WIDTH - 1 - (i % 6)] = hi[j][k][WIDTH - 1 - (i % 6)];
        else
          screen[j][k][i % 6] = 0;
      }
  }
}

// Extra functions for a simple bouncing ball
typedef struct {
  float x;
  float y;
  float z;
  int r;
  float vx;
  float vy;
  float vz;
} Ball;

bool checkBounds(float *a, int r, int b) {
  if (*a - r > 0 && *a + r < b)
    return true;
  else
    *a = (*a - r <= 0) ? 0 + r + 1 : b - r - 1;

  return false;
}

void bounceBall(Ball *b1) {
  // Check for wall collision and update velocity if needed
  if (!checkBounds(&b1->x, b1->r, LENGTH - 1))
    b1->vx = -1 * b1->vx;
  if (!checkBounds(&b1->y, b1->r, HEIGHT - 1))
    b1->vy = -1 * b1->vy;
  if (!checkBounds(&b1->z, b1->r, WIDTH - 1))
    b1->vz = -1 * b1->vz;

  // Update position
  b1->x += b1->vx;
  b1->y += b1->vy;
  b1->z += b1->vz;
}

void renderBall(Ball b) {
  int x = (int)b.x;
  int y = (int)b.y;
  int z = (int)b.z;

  screen[x][y][z] = 1;
  screen[x + b.r][y][z] = 1;
  screen[x - b.r][y][z] = 1;
  screen[x][y + b.r][z] = 1;
  screen[x][y - b.r][z] = 1;
  screen[x][y][z + b.r] = 1;
  screen[x][y][z - b.r] = 1;
}

void unrenderBall(Ball b) {
  int x = (int)b.x;
  int y = (int)b.y;
  int z = (int)b.z;

  screen[x][y][z] = 0;
  screen[x + b.r][y][z] = 0;
  screen[x - b.r][y][z] = 0;
  screen[x][y + b.r][z] = 0;
  screen[x][y - b.r][z] = 0;
  screen[x][y][z + b.r] = 0;
  screen[x][y][z - b.r] = 0;
}
