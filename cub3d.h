#ifndef CUB3D_H
#define CUB3D_H

#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define MAP_SIZE 20
#define TILE_SIZE 64
#define WIDTH 1000
#define HEIGHT 800

typedef struct {
    double x;
    double y;
    double dir;
} Player;




#endif