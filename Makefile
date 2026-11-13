CC = gcc
CFLAGS = -O2 -Wall -Wextra -Isrc -Iray/include

SRC = src/main.c src/snowflake.c
OBJ = $(SRC:.c=.o)

ifeq ($(OS),Windows_NT)
    # ---------------------------------------------------------
    # Windows (w64devkit / MinGW)
    # ---------------------------------------------------------
    EXEC = snowflake.exe
    LDFLAGS = ray/lib/libraylib.a -lopengl32 -lgdi32 -lwinmm
    CLEAN_CMD = rm -f src/*.o $(EXEC)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        # -----------------------------------------------------
        # macOS (Homebrew / System Clang)
        # -----------------------------------------------------
        CC = clang
        EXEC = snowflake
        CFLAGS += -I/opt/homebrew/include -I/usr/local/include
        LDFLAGS = -L/opt/homebrew/lib -L/usr/local/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
        CLEAN_CMD = rm -f src/*.o $(EXEC)
    else
        # -----------------------------------------------------
        # Linux
        # -----------------------------------------------------
        EXEC = snowflake
        LDFLAGS = -Lray/lib -Wl,-rpath,'$$ORIGIN/ray/lib' -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
        CLEAN_CMD = rm -f src/*.o $(EXEC)
    endif
endif

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

src/%.o: src/%.c src/snowflake.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(CLEAN_CMD)

run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
