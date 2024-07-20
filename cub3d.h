#ifndef CUB3D_H
#define CUB3D_H

#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WIDTH 640
#define HEIGHT 480
#define NUM_ROWS 6
#define NUM_COLS 10
#define TILE_SIZE 120


typedef struct s_ray
{
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    int stepX;
    int stepY;
    int side;
    int hit;
} t_ray;


typedef struct s_player
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
} t_player;

typedef struct s_map
{
    int mapWidth;
    int mapHeight;
    int map[10][10];
} t_map;

typedef struct s_image
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_image;

typedef struct s_data
{
    void *mlx;
    void *win;
    t_image *image;
    t_map *map;
    t_player *player;
} t_data;


#endif