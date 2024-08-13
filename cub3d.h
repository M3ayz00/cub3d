#ifndef CUB3D_H
#define CUB3D_H

#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#define FOV (M_PI / 3) // Field of View (60 degrees)

#define WIDTH 1080
#define HEIGHT 720
#define TILE_SIZE 32

#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100

typedef struct s_ray
{
    double angle;
    double hitX;
    double hitY;
    double rayDirX;
    double rayDirY;
    int texture_id;
    int side;
    int is_vertical;
    double hit_distance;
} t_ray;

typedef struct s_player
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double angle;
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
    t_ray *ray;
    void *textures[10];
    int tex_width;
    int tex_height;
    t_player *player;
} t_data;

#endif