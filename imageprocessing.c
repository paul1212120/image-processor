#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "imageprocessing.h"
#define max 255
#define min 0
int ***flip_horizontal(int ***image, int N, int M) {
int i = 0, j = 0, k = 0;
int ***t1 = (int ***)malloc(N * sizeof(int **));
for(i = 0; i < N; i++) {
t1[i] = (int **)malloc(M * sizeof(int*));
for(j = 0; j < M; j++)
t1[i][j] = (int *)malloc(3 * sizeof(int));
}
for(i = 0; i < N; i++) {
for(j = 0; j < M; j++) {
for(k = 0; k < 3; k++)
t1[i][j][k] = image[i][M-j-1][k];
}
}
return t1;
}
int ***rotate_left(int ***image, int N, int M) {
int i = 0, j = 0, k = 0;
int ***t2 = (int ***)malloc(M * sizeof(int **));
for(i = 0; i < M; i++) {
t2[i] = (int **)malloc(N * sizeof(int*));
for(j = 0; j < N; j++)
t2[i][j] = (int *)malloc(3 * sizeof(int));
}
for(i = 0; i < N; i++) {
for(j = 0; j < M; j++) {
for(k = 0; k < 3; k++)
t2[M-j-1][i][k] = image[i][j][k];
}
}
return t2;
}
int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
int i = 0, j = 0, k = 0;
int ***t3 = (int ***)malloc(h * sizeof(int **));
for(i = 0; i < h; i++) {
t3[i] = (int **)malloc(w * sizeof(int*));
for(j = 0; j < w; j++)
t3[i][j] = (int *)malloc(3 * sizeof(int));
}
for(i = 0; i < h; i++) {
for(j = 0; j < w; j++) {
for(k = 0; k < 3; k++)
t3[i][j][k] = image[i+y][j+x][k];
}
}
return t3;
}
int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
int i = 0, j = 0, k = 0;
int ***t4 = (int ***)malloc((N + 2 * rows) * sizeof(int **));
for(i = 0; i < N + 2 * rows; i++) {
t4[i] = (int **)malloc((M + 2 * cols) * sizeof(int*));
for(j = 0; j < M + 2 * cols; j++)
t4[i][j] = (int *)malloc(3 * sizeof(int));
}
for(i = 0; i < N + 2 * rows; i++) {
for(j = 0; j < M + 2 * cols; j++) {
if (i < rows || i >= N + rows || j < cols || j >= M + cols) {
t4[i][j][0] = new_R;
t4[i][j][1] = new_G;
t4[i][j][2] = new_B;
} else {
for(k = 0; k < 3; k++)
t4[i][j][k] = image[i-rows][j-cols][k];
}
}
}
return t4;
}
int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y) {
int i = 0, j = 0, k = 0, u = 0, w = 0;
for(i = y; i < N_dst && u < N_src; i++) {
for(j = x; j < M_dst && w < M_src; j++) {
for(k = 0; k < 3; k++) {
image_dst[i][j][k] = image_src[u][w][k];
}
w++;
}
u++; w = 0;
}
return image_dst;
}
int ver(int val) {
if (val < min) {
return min;
} else if (val > max) {
return max;
} else {
return val;
}
}
int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
int ***t6 = (int ***)malloc(N * sizeof(int **));
for(int i = 0; i < N; ++i) {
t6[i] = (int **)malloc(M * sizeof(int *));
for (int j = 0; j < M; ++j) {
t6[i][j] = (int *)malloc(3 * sizeof(int));
float newR = 0, newG = 0, newB = 0;
for (int fi = 0; fi < filter_size; ++fi) {
for (int fj = 0; fj < filter_size; ++fj) {
int ni = i + fi - filter_size / 2;
int nj = j + fj - filter_size / 2;
if (ni < 0 || ni >= N || nj < 0 || nj >= M) {
newR += 0;
newG += 0;
newB += 0;
} else {
newR += (float)image[ni][nj][0] * filter[fi][fj];
newG += (float)image[ni][nj][1] * filter[fi][fj];
newB += (float)image[ni][nj][2] * filter[fi][fj];
}
}
}
t6[i][j][0] = ver((int)newR);
t6[i][j][1] = ver((int)newG);
t6[i][j][2] = ver((int)newB);
}
}
return t6;
}
