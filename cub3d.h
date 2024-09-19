/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:30:47 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/19 17:19:39 by msaadidi         ###   ########.fr       */
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

#define THIN_WALL_THRESHOLD 0.3

#define FRAME_COUNT 23
#define DOOR_FRAMES 9
#define FOV (M_PI / 3) // Field of View (60 degrees)

#define WIDTH 1280
#define HEIGHT 900
#define TILE_SIZE 12
#define SENSITIVITY 0.0005

#define MOVE_SPEED 0.06
#define ROT_SPEED 0.05
#define MARGIN 0.1

#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100
#define LEFT_KEY 65361
#define RIGHT_KEY 65363
#define ESC_KEY 65307
#define E_KEY 101

typedef enum t_dir
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
} t_direction;

typedef struct s_checking_tools
{
	int	prev_len;
	int	next_len;
	int	count;
	int	rowc;
}	t_checking;

typedef struct s_split_tools
{
	char	**strings;
	int		i;
	int		j;
	int		count;
}	t_split;
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

typedef struct s_door
{
	int		**state;
	double	**timer;
	t_image	*door_frames;
} t_door;

typedef struct s_rendering_tools
{
	double		x;
	int			y;
	int			column;
	int			slice_height;
	float		scale;
	uint32_t	color;
}	t_render;
typedef struct s_key_state {
	int delta_x;
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
	int	hit_door;
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


typedef struct s_textures
{
    t_color *floor;
    t_color *ceiling;
    t_image ceil_tex;
    t_image *floor_tex;
	t_image door_tex;
    char *north;
    char *south;
    char *east;
    char *west;
	char	*door;
} t_textures;

typedef struct s_cub3d
{
	int		bonus;
    void *mlx;
    void *win;
    t_image *image;
    t_image *minimap;
    t_image *weapon;
    t_ray *ray;
    t_player *player;
    t_map2 *map2;
    t_key_state keys;
	t_door		*doors;
    t_textures *textures;
    t_image wall_textures[4];
    t_image frames[FRAME_COUNT];
    int wall_height;
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
int parse_data(t_cub3d *cub3d, char *path, int nb_textures);
void	free_textures(t_textures **textures);
void	free_map(t_map2 **map);
void	render_door(t_cub3d *data, int i, int start, int end);
uint32_t get_texture_color(t_image *texture, int x, int y);
void	init_textures(t_textures **textures);
void	init_map(t_map2 **map);
int	init_map_and_textures(t_textures **textures, t_map2 **map);
int	is_identifier(char *line);
int	parse_texture(char **line, t_textures **textures, int *counter);
int   add_map_line(t_map2 **map, char *element);
int	check_door_texture(char **line, t_textures **textures, int *i, int fd);
int	check_textures(t_textures *textures);
t_color	*split_color(char **color);
int	based_split(char *line, char ***splitted);
int	is_count_valid(char *identifier, int rows);
int	count_rows(char **map);
int	check_texture_file(char *file, char **texture);
int	parse_map(t_lst **rows, t_cub3d *cub3d);
int	process_map_and_textures(int fd, t_cub3d *cub3d, int nb_textures);
int	is_space(char c);
int	is_texture(char *element);
int	is_color(char *element);
int	is_one_or_player(char c);
int	is_player(char c);
int	is_plane(char c);
int	is_it_all_ones(char *row);
int	is_it_all_spaces(char *row);
int	is_digit(char c);
int	is_valid_elem(char *element);
void	is_there_player(char *row, int *count);
int	is_valid_zero(t_lst *row, int i);
int	ft_atoi(char *str);
int	check_adjacent(int curr_len, int adj_len, char c, int i);
int	check_zeros(t_lst **rows);
int	check_first_last_rows(t_lst *rows);
int	check_sides(char *row);
int	check_line(char **line, t_textures **textures, t_map2 **map, int *i);
int	add_map_lines(char **line, t_textures **textures, t_map2 **map, int fd);
int	check_row(char *row, int prev_len, int next_len);
void	remove_x_node(t_lst **curr, t_lst **prev, t_lst **to_rem);

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
int ft_exit(t_cub3d *cub3d);

// bonus
void draw_line(t_cub3d *data, int x0, int y0, int x1, int y1, int color);
void draw_direction_line(t_cub3d *data, int x, int y, double angle, int length, int color);
void draw_player(t_cub3d *data, int xc, int yc, int radius, int color);
void draw_cub(t_cub3d *data, int x, int y, int size_h, int size_w, int color);
void cast_map_rays(t_cub3d *data, int offset, double scale);
void render_map(t_cub3d *data);
void	door_interaction(t_cub3d *cub3d);

int    get_texel(t_image texture, int x, int y);
void init_key_state(t_key_state *keys) ;
int key_release(int key, t_cub3d *data);
void handle_movement(t_cub3d *data);
void check_wall_colision(t_cub3d *data, double newPosX, double newPosY);
void render_ceil_bonus(t_cub3d *data, int i, int end);
int mouse_move(int x, int y, t_cub3d *data);

#endif
