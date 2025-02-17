#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"
#define MAX_IMAGES 10
#define MAX_FILTERS 10
#define kP 100
typedef struct {
int ***data;
int N;
int M;
} Image;
typedef struct {
float **data;
int size;
} Filter;
void free_imagine(Image *imagine) {
for (int i = 0; i < imagine->N; i++) {
for (int j = 0; j < imagine->M; j++) {
free(imagine->data[i][j]);
}
free(imagine->data[i]);
}
free(imagine->data);
}
void free_filtre(Filter *filtre, int filtru_count) {
for (int i = 0; i < filtru_count; i++) {
free(filtre[i].data[0]);
free(filtre[i].data);
}
}
float **create_filtru(int size) {
float **filtru = (float **)malloc(size * sizeof(float *));
for (int i = 0; i < size; i++) {
filtru[i] = (float *)malloc(size * sizeof(float));
for (int j = 0; j < size; j++) {
filtru[i][j] = 1.0f / (float)(size * size);
}
}
return filtru;
}
void free_imagini(Image *imagini, int imagine_count) {
for (int i = 0; i < imagine_count; i++) {
free_imagine(&imagini[i]);
}
}
int main() {
Image imagini[MAX_IMAGES];
Filter filtre[MAX_FILTERS];
int imagine_count = 0;
int filtru_count = 0;
while (1) {
char alege[3];
scanf("%s", alege);
if (strcmp(alege, "e") == 0) {
break;
} else if (strcmp(alege, "l") == 0) {
char path[kP];
scanf("%d %d %s", &imagini[imagine_count].N, &imagini[imagine_count].M, path);
imagini[imagine_count].data = (int ***)malloc(imagini[imagine_count].N * sizeof(int **));
for (int i = 0; i < imagini[imagine_count].N; i++) {
imagini[imagine_count].data[i] = (int **)malloc(imagini[imagine_count].M * sizeof(int *));
for (int j = 0; j < imagini[imagine_count].M; j++) {
imagini[imagine_count].data[i][j] = (int *)malloc(3 * sizeof(int));
}
}
read_from_bmp(imagini[imagine_count].data, imagini[imagine_count].N, imagini[imagine_count].M, path);
imagine_count++;
} else if (strcmp(alege, "s") == 0) {
int index = 0;
char path[kP];
scanf("%d %s", &index, path);
write_to_bmp(imagini[index].data, imagini[index].N, imagini[index].M, path);
} else if (strcmp(alege, "ah") == 0) {
int index = 0;
scanf("%d", &index);
imagini[index].data = flip_horizontal(imagini[index].data, imagini[index].N, imagini[index].M);
} else if (strcmp(alege, "ar") == 0) {
int index = 0;
scanf("%d", &index);
imagini[index].data = rotate_left(imagini[index].data, imagini[index].N, imagini[index].M);
int aux = imagini[index].N;
imagini[index].N = imagini[index].M;
imagini[index].M = aux;
} else if (strcmp(alege, "ac") == 0) {
int index = 0, x = 0, y = 0, w = 0, h = 0;
scanf("%d %d %d %d %d", &index, &x, &y, &w, &h);
imagini[index].data = crop(imagini[index].data, imagini[index].N, imagini[index].M, x, y, w, h);
imagini[index].N = h;
imagini[index].M = w;
} else if (strcmp(alege, "ae") == 0) {
int index = 0, rows = 0, cols = 0, R = 0, G = 0, B = 0;
scanf("%d %d %d %d %d %d", &index, &rows, &cols, &R, &G, &B);
imagini[index].data = extend(imagini[index].data, imagini[index].N, imagini[index].M, rows, cols, R, G, B);
imagini[index].N += 2 * rows;
imagini[index].M += 2 * cols;
} else if (strcmp(alege, "ap") == 0) {
int index_dst = 0, index_src = 0, x = 0, y = 0;
scanf("%d %d %d %d", &index_dst, &index_src, &x, &y);
imagini[index_dst].data = paste(imagini[index_dst].data, imagini[index_dst].N, imagini[index_dst].M,
imagini[index_src].data, imagini[index_src].N, imagini[index_src].M, x, y);
} else if (strcmp(alege, "cf") == 0) {
int size = 0;
scanf("%d", &size);
filtre[filtru_count].data = create_filtru(size);
filtre[filtru_count].size = size;
filtru_count++;
} else if (strcmp(alege, "af") == 0) {
int index_img = 0, index_filtru = 0;
scanf("%d %d", &index_img, &index_filtru);
imagini[index_img].data = apply_filter(imagini[index_img].data, imagini[index_img].N, imagini[index_img].M,
filtre[index_filtru].data, filtre[index_filtru].size);
} else if (strcmp(alege, "df") == 0) {
int index_filtru = 0;
scanf("%d", &index_filtru);
free(filtre[index_filtru].data[0]);
free(filtre[index_filtru].data);
for (int i = index_filtru; i < filtru_count - 1; i++) {
filtre[i] = filtre[i + 1];
}
filtru_count--;
} else if (strcmp(alege, "di") == 0) {
int index_img = 0;
scanf("%d", &index_img);
free_imagine(&imagini[index_img]);
for (int i = index_img; i < imagine_count - 1; i++) {
imagini[i] = imagini[i + 1];
}
imagine_count--;
}
}
free_imagini(imagini, imagine_count);
free_filtre(filtre, filtru_count);
return 0;
}
