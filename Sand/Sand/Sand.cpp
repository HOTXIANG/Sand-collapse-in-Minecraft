#include <stdio.h>
#include <stdlib.h>
#define maxDistance 11
#define maxHeight 15
#define SAND_EMPTY 0
#define SAND_NORMAL 1
#define SAND_RED 2
void move_minecraft(int*** h, int rows, int cols);
int main() {
    int i, j, k;
    int*** h = (int***)malloc(maxDistance * sizeof(int**));
    for (i = 0; i < maxDistance; i++) {
        h[i] = (int**)malloc(maxDistance * sizeof(int*));
        for (j = 0; j < maxDistance; j++) {
            h[i][j] = (int*)malloc(maxHeight * sizeof(int));
        }
    }

    // 初始化数组元素为0
    for (i = 0; i < maxDistance; i++) {
        for (j = 0; j < maxDistance; j++) {
            for (k = 0; k < maxHeight; k++) {
                h[i][j][k] = SAND_EMPTY;
            }
        }
    }

    // 初始沙子
    h[4][4][0] = SAND_NORMAL;
    h[4][4][1] = SAND_NORMAL;
    h[4][4][2] = SAND_NORMAL;
    h[4][4][3] = SAND_NORMAL;
    h[4][4][4] = SAND_NORMAL;
    h[4][4][5] = SAND_NORMAL;
    h[4][4][6] = SAND_NORMAL;
    h[4][4][7] = SAND_NORMAL;
    h[4][4][8] = SAND_NORMAL;
    h[4][4][9] = SAND_NORMAL;
    h[4][4][10] = SAND_NORMAL;

    move_minecraft(h, maxDistance, maxDistance);

    // 打印x=4平面上的沙子分布
    for (i = 0; i < maxDistance; i++) {
        for (j = 0; j < maxHeight; j++) {
            printf("%d ", h[4][i][j]);
        }
        printf("\n");
    }

    // 释放内存
    for (i = 0; i < maxDistance; i++) {
        for (j = 0; j < maxDistance; j++) {
            free(h[i][j]);
        }
        free(h[i]);
    }
    free(h);

    return 0;
}

void move_minecraft(int*** h, int rows, int cols) {
    int x, y, z, i, j, delta;
    int moved = 0;

    for (x = 0; x < rows; x++) {
        for (y = 0; y < cols; y++) {
            for (z = maxHeight - 1; z >= 0; z--) {
                //最后的z为找到的更高的沙堆中的最高的沙子的z轴坐标
                if (h[x][y][z] != SAND_EMPTY) {
                    // 东（右）
                    if (y + 1 < cols) {
                        for (i = 0; i < maxHeight; i++) { //最后的i的大小为东边一格沙堆中的最高的沙子的z轴坐标+1
                            if (h[x][y + 1][i] == SAND_EMPTY) {
                                break;
                            }
                        }
                        delta = z - i + 1;
                        if (delta >= 3) {
                            for (int j = 0; j < delta / 2; j++) {
                                h[x][y + 1][i - 1 + delta / 2 - j] = h[x][y][z - j];
                                h[x][y][z - j] = SAND_EMPTY;
                            }
                            moved = 1;
                        }
                    }
                    // 南（下）
                    if (x + 1 < rows) {
                        for (i = 0; i < maxHeight; i++) {
                            if (h[x + 1][y][i] == SAND_EMPTY) {
                                break;
                            }
                        }
                        delta = z - i;
                        if (delta >= 3) {
                            for (int j = 0; j < delta / 2; j++) {
                                h[x + 1][y][i - 1 + delta / 2 - j] = h[x][y][z - j];
                                h[x][y][z - j] = SAND_EMPTY;
                            }
                            moved = 1;
                        }
                    }
                    // 西（左）
                    if (y - 1 >= 0) {
                        for (i = 0; i < maxHeight; i++) {
                            if (h[x][y - 1][i] == SAND_EMPTY) {
                                break;
                            }
                        }
                        delta = z - i;
                        if (delta >= 3) {
                            for (int j = 0; j < delta / 2; j++) {
                                h[x][y - 1][i - 1 + delta / 2 - j] = h[x][y][z - j];
                                h[x][y][z - j] = SAND_EMPTY;
                            }
                            moved = 1;
                        }
                    }
                    // 北（上）
                    if (x - 1 >= 0) {
                        for (i = 0; i < maxHeight; i++) {
                            if (h[x - 1][y][i] == SAND_EMPTY) {
                                break;
                            }
                        }
                        delta = z - i;
                        if (delta >= 3) {
                            for (int j = 0; j < delta / 2; j++) {
                                h[x - 1][y][i - 1 + delta / 2 - j] = h[x][y][z - j];
                                h[x][y][z - j] = SAND_EMPTY;
                            }
                            moved = 1;
                        }
                    }
                    break;
                }
            }
        }
    }

    // 如果有沙子移动，则递归调用 move_minecraft
    if (moved) {
        move_minecraft(h, rows, cols);
    }
}