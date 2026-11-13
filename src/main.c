#include "snowflake.h"

int main(int argc, char **argv){
	srand(time(NULL));
	(void)argc;
	(void)argv;

	InitWindow(WIDTH, HEIGHT, "SNOWFLAKE // WORK PLEASE");
	assert(IsWindowReady());
	SetTargetFPS(FRAME_RATE);

	grid_init();

	bool paused = false;

	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_SPACE)) paused = !paused;
		if (IsKeyPressed(KEY_R)) grid_init();

		if (!paused) {
			int steps = IsKeyDown(KEY_W) ? FAST_FORWARD_STEPS : 1;
			for (int s = 0; s < steps; s++) {
				walkers_update();
			}
		}

		BeginDrawing();
		ClearBackground(TERMINAL_GREEN);

		draw_hex_lattice();

		Vector2 seed_pos = hex_to_screen(GRID_COLS / 2, GRID_ROWS / 2);
		DrawCircleV(seed_pos, CELL_RAD * 1.5f, SEED_COLOR);

		draw_simulation();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
