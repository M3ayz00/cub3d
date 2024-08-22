/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:30:47 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/12 15:43:29 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "minilibx-linux/mlx.h"
#include "parsing/gnl/get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#define FOV (M_PI / 3) // Field of View (60 degrees)

#define WIDTH 900
#define HEIGHT 650
#define TILE_SIZE 12

#define MOVE_SPEED 0.004
#define ROT_SPEED 0.005
#define MARGIN 0.02

#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100
#define LEFT_KEY 65361
#define RIGHT_KEY 65363
#define ESC_KEY 65307

typedef enum t_dir
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
} t_direction;

typedef struct s_key_state {
    int forward;
    int backward;
    int left;
    int right;
    int rotate_left;
    int rotate_right;
} t_key_state;


typedef struct s_color
{
    int t;
    int r;
    int g;
    int b;
} t_color;

typedef struct s_lst
{
    char *row;
    int row_len;
    struct s_lst *next;
    struct s_lst *prev;
} t_lst;

typedef struct s_textures
{
    t_color *floor;
    t_color *ceiling;
    char *north;
    char *south;
    char *east;
    char *west;
} t_textures;

typedef struct s_ray
{
    double angle;
    double hitX;
    double hitY;
    double deltaDistX;
    double deltaDistY;
    double sideDistX;
    double sideDistY;
    double rayDirX;
    double rayDirY;
    int stepX;
    int stepY;
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

typedef struct s_map2
{
    t_lst *rows;
    char **map;
    int width;
    int height;
    int mapX;
    int mapY;
} t_map2;

typedef struct s_image
{
    int width;
    int height;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_image;

typedef struct s_cub3d
{
    void *mlx;
    void *win;
    t_image *image;
    t_image *minimap;
    t_image *weapon;
    t_ray *ray;
    t_player *player;
    t_map2 *map2;
    t_key_state keys;
    t_textures *textures;
} t_cub3d;

int open_file(char *path);
void free_strs(char **strs);
char **ft_split(char *s, char *set);
char *ft_strtrim(char *s, char *set);
int ft_strcmp(char *s1, char *s2);
int get_rgb(int t, int r, int g, int b);
t_lst *lst_new(char *row);
void ft_lstadd_back(t_lst **lst, t_lst *new);
t_lst *ft_lst_before(t_lst *lst, t_lst *curr);
void ft_lst_remove(t_lst **lst, t_lst *to_rem);
int ft_lstsize(t_lst *lst);
void ft_lstclear(t_lst **lst);
char *ft_strdup(char *str);
t_lst *ft_lstlast(t_lst *lst);
int parse_data(t_cub3d *cub3d, char *path);

// raycasting prototypes
void my_mlx_pixel_put(t_image *image, int x, int y, int color);
void my_mlx_pixel_put2(t_image *image, int x, int y, int color);
void render_ceil(t_cub3d *data, int i, int end);
void render_walls(t_cub3d *data, int i, int start, int end);
void render_floor(t_cub3d *data, int i, int start, int end);
int key_press(int key, t_cub3d *data);
void get_player_pos(t_cub3d *data);
void dda(t_cub3d *data);
void get_delta_distance(t_cub3d *data, double rayDirX, double rayDirY);
void cast_ray(t_cub3d *data, double ray_angle);
void cast_all_rays(t_cub3d *data);
int calc_height(double distance, int screen_height);
char **get_arr(t_lst *lst);
int get_rgb(int t, int r, int g, int b);
int render(void *cub);
int ft_exit();

// bonus
void draw_line(t_cub3d *data, int x0, int y0, int x1, int y1, int color);
void draw_direction_line(t_cub3d *data, int x, int y, double angle, int length, int color);
void draw_player(t_cub3d *data, int xc, int yc, int radius, int color);
void draw_cub(t_cub3d *data, int x, int y, int size_h, int size_w, int color);
void cast_map_rays(t_cub3d *data);
void render_map(t_cub3d *data);
int    get_texel(t_image texture, int x, int y);
void init_key_state(t_key_state *keys) ;
int key_release(int key, t_cub3d *data);
void handle_movement(t_cub3d *data);
void check_wall_colision(t_cub3d *data, double newPosX, double newPosY);
#endif
