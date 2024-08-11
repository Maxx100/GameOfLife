#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const int HEIGHT = 25, WIDTH = 80;
int **map, **temp;

void render() {
    printf("\e[1;1H\e[2J");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (map[i][j] == 0) printf(" ");
            else printf("#");
        }
        printf("\n");
    }
}

void fill() {
    int x, y;
    while (scanf("%d%d", &x, &y) == 2) {
        if (x < 0 || x > 24 || y < 0 || y > 79) printf("Invalid coords\n");
        else {
            map[x][y] = 1;
        }
    }
}

void update() {
    int neighbours;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            temp[i][j] = 0;
            neighbours = 0;
            neighbours += map[(i + 1) % HEIGHT][j];
            neighbours += map[(i - 1 + HEIGHT) % HEIGHT][j];

            neighbours += map[(i + 1) % HEIGHT][(j + 1) % WIDTH];
            neighbours += map[i][(j + 1) % WIDTH];
            neighbours += map[(i - 1 + HEIGHT) % HEIGHT][(j + 1) % WIDTH];

            neighbours += map[(i + 1) % HEIGHT][(j - 1 + WIDTH) % WIDTH];
            neighbours += map[i][(j - 1 + WIDTH) % WIDTH];
            neighbours += map[(i - 1 + HEIGHT) % HEIGHT][(j - 1 + WIDTH) % WIDTH];

            if (map[i][j] == 1 && neighbours == 2 || neighbours == 3) temp[i][j] = 1;
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            map[i][j] = temp[i][j];
        }
    }
}

int main() {
    map = malloc(HEIGHT * sizeof(int*));
    temp = malloc(HEIGHT * sizeof(int*));
    for (int i = 0; i < HEIGHT; i++) {
        map[i] = calloc(WIDTH, sizeof(int));
        temp[i] = calloc(WIDTH, sizeof(int));
    }
    printf("Mode: 1, 2, 3 - examples, 3 - hand-write\n");
    int cmd; scanf("%d", &cmd);
    if (cmd == 1) {
        map[2][1] = 1;
        map[2][2] = 1;
        map[2][3] = 1;
    } else if (cmd == 2) {
        map[3][3] = 1;
        map[3][4] = 1;
        map[3][5] = 1;
        map[2][5] = 1;
        map[1][4] = 1;
    } else if (cmd == 3) {
        map[10][10] = 1;
        map[9][10] = 1;
        map[11][10] = 1;
        map[10][9] = 1;
        map[10][11] = 1;
    } else {
        fill();
    }
    while (1) {
        render();
        Sleep(300);
        update();
    }
    return 0;
}
