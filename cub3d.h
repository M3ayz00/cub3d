#ifndef CUB3D_H
#define CUB3D_H

#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_ROWS 6
#define NUM_COLS 10
#define TILE_SIZE 120

typedef struct s_player
{
    int x ;
    int y;
    double turn_dir;
    double walk_dir;
    double rot_angle;
    double move_speed;
    double turn_speed;

} t_player;

typedef struct s_data
{
    void *mlx;
    void *win;
    char *addr;
    void *img;
    int bits_per_pixel;
    int line_length;
    int endian;
    t_player *player;
} t_data;


#endif