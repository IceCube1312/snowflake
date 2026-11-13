#ifndef SNOWFLAKE
#define SNOWFLAKE

#include "../ray/include/raylib.h"
#include "../ray/include/raymath.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH 1280
#define HEIGHT 900
#define FRAME_RATE 120

// Palettes
#define TERMINAL_GREEN   (Color){1, 15, 6, 255}
#define GRID_DIM         (Color){53, 79, 47,255}
#define ICE_WHITE        (Color){152, 250, 233, 255}
#define SEED_COLOR       (Color){61, 255, 228, 255}
#define WALKER_COLOR     (Color){0, 240, 255, 100}

#define GRID_COLS 360
#define GRID_ROWS 290
#define CELL_RAD 2.0f

#define NUM_WALKER 24000
#define FAST_FORWARD_STEPS 1200
#define FREEZE_THRESHOLD 10

// Gradient sticking probability table indexed by frozen neighbor count N (0 to 6)
extern const int STICKING_PROB[7];

typedef enum {
	CELL_EMPTY = 0,
	CELL_SEED,
	CELL_FROZEN,
	CELL_WALKER
} CELL_STATE;

typedef struct {
	int x;
	int y;
} Walker;

// Hex neighbor offsets
extern const int HEX_EVEN[6][2];
extern const int HEX_ODD[6][2];
extern Walker walkers[NUM_WALKER];

// Grid, simulation, and projection functions
void grid_init(void);
void walkers_update(void);
void freeze_cell_symmetric(int x, int y);
int count_frozen_neighbors(int x, int y);
void draw_simulation(void);
Vector2 hex_to_screen(int x, int y);
void draw_hex_lattice(void);


#endif
