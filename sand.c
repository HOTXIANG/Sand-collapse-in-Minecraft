#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define maxDistance 11
#define maxHeight 15
#define SAND_EMPTY 0
#define SAND_NORMAL 1
#define SAND_RED 2
void move_minecraft(int ***h, int rows, int cols);
int main() {
    int i, j, k;
    int ***h = (int ***)malloc(maxDistance * sizeof(int **));
    for (i = 0; i < maxDistance; i++) {
        h[i] = (int **)malloc(maxDistance * sizeof(int *));
        for (j = 0; j < maxDistance; j++) {
            h[i][j] = (int *)malloc(maxHeight * sizeof(int));
        }
    }
    if (h == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
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
    h[4][4][6] = SAND_RED;
    h[4][4][7] = SAND_RED;
    h[4][4][8] = SAND_RED;
    h[4][4][9] = SAND_RED;
    h[4][4][10] = SAND_RED;
    
    move_minecraft(h, maxDistance, maxDistance);

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

void move_minecraft(int ***h, int rows, int cols) {
    int x, y, z, i, j,delta_e,delta_s,delta_w,delta_n;
    int e,s,w,n;
    int deltaSum;
    int moved = 0;
    int maxToMin[4]={0,0,0,0}; //maxToMin数组的下标从0到3分别为east,south,west,north
    int sort[4]={0,1,2,3}; //0,1,2,3分别代表east,south,west,north
    int temp=0;
    int flag[4]={0,0,0,0}; //flag数组的下标从0到3分别为east,south,west,north
    int count=0,crushCount=0;

    for (x = 0; x < rows; x++) {
        for (y = 0; y < cols; y++) {
            for (z = maxHeight - 1; z >= 0; z--) { 
                //最后的z为找到的更高的沙堆中的最高的沙子的z轴坐标
                if (h[x][y][z] != SAND_EMPTY) {
                    // 东（右）
                    if (y + 1 < cols) {
                        for (e = 0; e < maxHeight; e++) { //最后的i的大小为东边一格沙堆中的最高的沙子的z轴坐标+1
                            if (h[x][y + 1][e] == SAND_EMPTY) {
                                break;
                            }
                        }
                        delta_e = z - e + 1; //delta_e为东边一格沙堆中的最高的沙子的z轴坐标与当前沙子的z轴坐标的差值
                    }
                    // 南（下）
                    if (x + 1 < rows) {
                        for (s = 0; s < maxHeight; s++) {
                            if (h[x + 1][y][s] == SAND_EMPTY) {
                                break;
                            }
                        }
                        delta_s = z - s + 1;
                    }
                    // 西（左）
                    if (y - 1 >= 0) {
                        for (w = 0; w < maxHeight; w++) {
                            if (h[x][y - 1][w] == SAND_EMPTY) {
                                break;
                            }
                        }
                        delta_w = z - w + 1;
                    }
                    // 北（上）
                    if (x - 1 >= 0) {
                        for (n = 0; n < maxHeight; n++) {
                            if (h[x - 1][y][n] == SAND_EMPTY) {
                                break;
                            }
                        }
                        delta_n = z - n + 1;
                    }
                    maxToMin[0]=delta_e;
                    maxToMin[1]=delta_s;
                    maxToMin[2]=delta_w;
                    maxToMin[3]=delta_n;
                    for(i=0;i<4;i++){
                        for(j=0;j<4;j++){
                            if(maxToMin[sort[i]]<maxToMin[sort[j]]){
                                temp=sort[i];
                                sort[i]=sort[j];
                                sort[j]=temp;
                            }
                        }
                    }
                    flag[sort[0]]=1;
                    if(fabs(maxToMin[sort[0]] - maxToMin[sort[1]])<2){
                        flag[sort[1]]=1;
                        if(fabs(maxToMin[sort[0]] - maxToMin[sort[2]])<2){
                            flag[sort[2]]=1;
                            if(fabs(maxToMin[sort[0]] - maxToMin[sort[3]])<2){
                                flag[sort[3]]=1;
                            }
                        }
                    }
                    count=flag[0]+flag[1]+flag[2]+flag[3];
                    deltaSum=maxToMin[sort[0]]*flag[sort[0]]+maxToMin[sort[1]]*flag[sort[1]]+maxToMin[sort[2]]*flag[sort[2]]+maxToMin[sort[3]]*flag[sort[3]];
                    crushCount=deltaSum / count / count / 2;
                    for(int j = 0; j < crushCount + 1 ; j++){
                        if (flag[0]==1 && deltaSum > 0){
                            h[x][y + 1][e - 1 + crushCount - j] = h[x][y][z - j];
                            h[x][y][z - j] = SAND_EMPTY;
                            deltaSum--;
                        }
                        if (flag[1]==1 && deltaSum > 0){
                            h[x + 1][y][s - 1 + crushCount - j] = h[x][y][z - j];
                            h[x][y][z - j] = SAND_EMPTY;
                            deltaSum--;
                        }
                        if (flag[2]==1 && deltaSum > 0){
                            h[x][y - 1][w - 1 + crushCount - j] = h[x][y][z - j];
                            h[x][y][z - j] = SAND_EMPTY;
                            deltaSum--;
                        }
                        if (flag[3]==1 && deltaSum > 0){
                            h[x - 1][y][n - 1 + crushCount - j] = h[x][y][z - j];
                            h[x][y][z - j] = SAND_EMPTY;
                            deltaSum--;
                        }
                                                     
                    }
                    moved = 1;
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
