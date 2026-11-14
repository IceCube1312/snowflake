#include "snowflake.h"

uint8_t grid[GRID_ROWS][GRID_COLS];
static uint8_t hit_count[GRID_ROWS][GRID_COLS];

// 6 neighbor directions for even and odd rows: E, W, NE, NW, SE, SW
const int HEX_EVEN[6][2] = {
	{ 1,  0}, // East
	{-1,  0}, // West
	{ 0, -1}, // North-East
	{-1, -1}, // North-West
	{ 0,  1}, // South-East
	{-1,  1}  // South-West
};

const int HEX_ODD[6][2] = {
	{ 1,  0}, // East
	{-1,  0}, // West
	{ 1, -1}, // North-East
	{ 0, -1}, // North-West
	{ 1,  1}, // South-East
	{ 0,  1}  // South-West
};

const int STICKING_PROB[7] = { 0, 30, 15, 70, 85, 95, 100 };
//const int STICKING_PROB[7] = { 0, 100, 100, 100,100, 100, 100 };

Walker walkers[NUM_WALKER];

static void walker_spawn_edge(Walker *w) {
	int edge = rand() % 4;
	if (edge == 0){ 
		w->x = rand() % GRID_COLS; w->y = 0; 
	}
	else if (edge == 1){ 
		w->x = rand() % GRID_COLS; w->y = GRID_ROWS - 1; 
	}
	else if (edge == 2){ 
		w->x = 0; w->y = rand() % GRID_ROWS; 
	}
	else{ 
		w->x = GRID_COLS - 1; w->y = rand() % GRID_ROWS; 
	}

}

void grid_init(void) {
	for (int y = 0; y < GRID_ROWS; y++) {
		for (int x = 0; x < GRID_COLS; x++) {
			grid[y][x] = CELL_EMPTY;
			hit_count[y][x] = 0;
		}
	}
	grid[GRID_ROWS / 2][GRID_COLS / 2] = CELL_SEED;

	for (int i = 0; i < NUM_WALKER; i++) {
		walker_spawn_edge(&walkers[i]);
	}
}

int count_frozen_neighbors(int x, int y) {
	int count = 0;
	const int (*offset)[2] = (y & 1) ? HEX_ODD : HEX_EVEN;
	for (int d = 0; d < 6; d++) {
		int cx = x + offset[d][0];
		int cy = y + offset[d][1];
		if (cx >= 0 && cx < GRID_COLS && cy >= 0 && cy < GRID_ROWS) {
			if (grid[cy][cx] == CELL_SEED || grid[cy][cx] == CELL_FROZEN) {
				count++;
			}
		}
	}
	return count;
}

void freeze_cell_symmetric(int x, int y) {
	int x0 = GRID_COLS / 2;
	int y0 = GRID_ROWS / 2;

	int r0 = y0;
	int q0 = x0 - (y0 - (y0 & 1)) / 2;

	int r = y;
	int q = x - (y - (y & 1)) / 2;

	int dq = q - q0;
	int dr = r - r0;

	int q_curr = dq;
	int r_curr = dr;

	for (int i = 0; i < 6; i++) {
		int r_abs = r_curr + r0;
		int q_abs = q_curr + q0;

		int ny = r_abs;
		int nx = q_abs + (ny - (ny & 1)) / 2;

		if (nx >= 0 && nx < GRID_COLS && ny >= 0 && ny < GRID_ROWS) {
			grid[ny][nx] = CELL_FROZEN;
		}

		int q_next = -r_curr;
		int r_next = q_curr + r_curr;
		q_curr = q_next;
		r_curr = r_next;
	}
}

void walkers_update(void) {
	for (int i = 0; i < NUM_WALKER; i++) {
		int dir = rand() % 6;
		const int (*offset)[2] = (walkers[i].y & 1) ? HEX_ODD : HEX_EVEN;
		int nx = walkers[i].x + offset[dir][0];
		int ny = walkers[i].y + offset[dir][1];

		if (nx < 0 || nx >= GRID_COLS || ny < 0 || ny >= GRID_ROWS) {
			walker_spawn_edge(&walkers[i]);
			continue;
		}

		if (grid[ny][nx] != CELL_EMPTY) {
			continue;
		}

		int neighbors = count_frozen_neighbors(nx, ny);
		if (neighbors > 0) {
			if (neighbors > 6) neighbors = 6;
			int roll = rand() % 100;

			if (roll < STICKING_PROB[neighbors]) {
				hit_count[ny][nx]++;
				if (hit_count[ny][nx] >= FREEZE_THRESHOLD) {
					grid[ny][nx] = CELL_FROZEN;
					//freeze_cell_symmetric(nx, ny);
				}
				walker_spawn_edge(&walkers[i]);
				continue;
			}
		}

		walkers[i].x = nx;
		walkers[i].y = ny;
	}
}

// Map grid coordinate (x, y) to screen pixels (Sx, Sy), centered on screen
Vector2 hex_to_screen(int x, int y) {
	float dx = sqrtf(3.0f) * CELL_RAD;
	float dy = 1.5f * CELL_RAD;

	float grid_width  = GRID_COLS * dx;
	float grid_height = GRID_ROWS * dy;

	float origin_x = (WIDTH  - grid_width)  / 2.0f;
	float origin_y = (HEIGHT - grid_height) / 2.0f;

	float sx = origin_x + x * dx + ((y & 1) ? (dx * 0.5f) : 0.0f);
	float sy = origin_y + y * dy;

	return (Vector2){sx, sy};
}

void draw_hex_lattice(void) {
	for (int y = 0; y < GRID_ROWS; y += 1) {
		for (int x = 0; x < GRID_COLS; x += 1) {
			Vector2 pos = hex_to_screen(x, y);
			DrawPixelV(pos, GRID_DIM);
		}
	}
}

void draw_simulation(void) {
	for (int y = 0; y < GRID_ROWS; y++) {
		for (int x = 0; x < GRID_COLS; x++) {
			if (grid[y][x] == CELL_FROZEN) {
				Vector2 pos = hex_to_screen(x, y);
				DrawCircleV(pos, CELL_RAD * 0.9f, ICE_WHITE);
			}
		}
	}
	for (int i = 0; i < NUM_WALKER; i++) {
		Vector2 pos = hex_to_screen(walkers[i].x, walkers[i].y);
		DrawCircleV(pos, CELL_RAD * 0.8f, WALKER_COLOR);
	}
}
