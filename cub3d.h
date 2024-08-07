/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:30:47 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/07 17:58:26 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "minilibx-linux/mlx.h"
#include "parsing/gnl/get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FOV (M_PI / 3) // Field of View (60 degrees)

#define WIDTH 1080
#define HEIGHT 720
#define NUM_ROWS 6
#define NUM_COLS 10
#define TILE_SIZE 64

#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
	int	t;
}	t_color;

typedef struct s_ray
{
    double angle;
    double hitX;
    double hitY;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double deltaDistX;
    double deltaDistY;
    double sideDistX;
    double sideDistY;
    int side;
    int hit;
    int stepX;
    int stepY;

    int is_vertical;
    double hit_distance;
} t_ray;

typedef struct s_player
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    double angle;
} t_player;

typedef struct s_map
{
    int mapWidth;
    int mapHeight;
    int map[10][10];
} t_map;

typedef struct s_flr_cln
{
	t_color	floor;
	t_color ceiling;
}	t_flr_cln;

typedef struct	s_map2
{
	char	**map;


}	t_map2;

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
    t_player *player;
	t_map2	*map;
	t_flr_cln	floor_ceil;
} t_data;

#endif
