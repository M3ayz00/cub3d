/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:30:47 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/21 19:14:20 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "parsing/gnl/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define FRAME_COUNT 23
# define DOOR_FRAMES 9

# define WIDTH 1280
# define HEIGHT 900
# define TILE_SIZE 12
# define SENSITIVITY 0.0005
# define MOVE_SPEED 0.09
# define ROT_SPEED 0.05
# define MARGIN 0.1

# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ESC_KEY 65307
# define E_KEY 101

typedef enum t_dir
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
}	t_direction;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	color;
}	t_line;

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
	int		width;
	int		height;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_door
{
	int		**is_open;
	int		**timer;
	t_image	*door_frame;
}	t_door;

typedef struct s_rendering_tools
{
	double	x;
	int		y;
	int		i;
	int		column;
	int		slice_height;
	float	scale;
	int		offset;
	int		tile_size;
	int32_t	color;
	int		door_is_open;
	double	door_timer;
	int		m;
	int		n;
	int		size;
	int		map_x;
	int		map_y;
}	t_render;

typedef struct s_drawing_tools
{
	int	x_tip;
	int	y_tip;
	int	x_left;
	int	y_left;
	int	x_right;
	int	y_right;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_draw_tool;

typedef struct s_weapon_vars
{
	int		screen_width;
	int		screen_height;
	int		image_width;
	int		image_height;
	float	scale_x;
	float	scale_y;
	int		start_x;
	int		start_y;
	int		x;
	int		y;
}	t_weapon_vars;

typedef struct s_key_state
{
	int	delta_x;
	int	forward;
	int	backward;
	int	left;
	int	right;
	int	rotate_left;
	int	rotate_right;
	int	e;
}	t_key_state;

typedef struct s_color
{
	int	t;
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_lst
{
	char			*row;
	int				row_len;
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_lst;

typedef struct s_ray
{
	double	angle;
	double	hit_x;
	double	hit_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	raydir_x;
	double	raydir_y;
	int		step_x;
	int		step_y;
	int		side;
	int		is_vertical;
	int		hit_door;
	double	hit_distance;
}	t_ray;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	angle;
}	t_player;

typedef struct s_map2
{
	t_lst	*rows;
	char	**map;
	int		width;
	int		height;
	int		map_x;
	int		map_y;
}	t_map2;

typedef struct s_textures
{
	t_color	*floor;
	t_color	*ceiling;
	t_image	ceil_tex;
	t_image	*floor_tex;
	t_image	door_tex;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*door;
}	t_textures;

typedef struct s_cast
{
	int		height;
	int		start;
	int		end;
	double	ray_angle;
	double	angle_step;
}	t_casting;

typedef struct s_cub3d
{
	int			bonus;
	void		*mlx;
	void		*win;
	t_image		*image;
	t_image		*minimap;
	t_image		*weapon;
	t_ray		*ray;
	t_player	*player;
	t_map2		*map2;
	t_key_state	keys;
	t_door		*doors;
	t_textures	*textures;
	t_image		wall_t[4];
	double		fov;
	t_image		frames[FRAME_COUNT];
}	t_cub3d;

int			open_file(char *path);
void		free_strs(char **strs);
char		**ft_split(char *s, char *set);
char		*ft_strtrim(char *s, char *set);
int			ft_strcmp(char *s1, char *s2);
int			get_rgb(int t, int r, int g, int b);
t_lst		*lst_new(char *row);
void		ft_lstadd_back(t_lst **lst, t_lst *new);
t_lst		*ft_lst_before(t_lst *lst, t_lst *curr);
void		ft_lst_remove(t_lst **lst, t_lst *to_rem);
int			ft_lstsize(t_lst *lst);
void		ft_lstclear(t_lst **lst);
char		*ft_strdup(char *str);
t_lst		*ft_lstlast(t_lst *lst);
int			parse_cub3d(t_cub3d *cub3d, char *path, int is_bonus);
void		free_textures(t_textures **textures);
void		free_map(t_map2 **map);
void		render_door(t_cub3d *cub3d, int i, int start, int end);
uint32_t	get_texture_color(t_image *texture, int x, int y);
void		init_textures(t_textures **textures);
void		init_map(t_map2 **map);
int			init_map_and_textures(t_textures **textures, t_map2 **map);
int			is_identifier(char *line);
int			parse_texture(char **line, t_textures **textures,
				int *counter);
int			add_map_line(t_map2 **map, char *element, int is_bonus);
int			check_door_texture(char **line, t_textures **textures,
				int *i, int fd);
int			check_textures(t_textures *textures, char **line);
t_color		*split_color(char **color);
int			based_split(char *line, char ***splitted);
int			is_count_valid(char *identifier, int rows);
int			count_rows(char **map);
int			check_texture_file(char *file, char **texture);
void		set_width_and_height(t_lst **rows, t_cub3d *cub3d);
int			parse_map(t_lst **rows, t_cub3d *cub3d, int is_bonus);
int			process_map_and_textures(int fd, t_cub3d *cub3d,
				int is_bonus);
int			process_texture(t_textures **textures, char **splitted);
int			color_processing(char **splitted, t_color **color);
int			textures_processing(char **splitted, t_textures **textures);
int			colors_processing(char **splitted, t_textures **textures);
double		deg_to_rad(double degrees);
int			validating_and_cleaning(t_lst **rows, t_lst *curr);
int			is_map_valid(t_lst **rows);
int			check_each_row(t_lst **rows);
int			is_space(char c);
int			is_texture(char *element);
int			is_color(char *element);
int			is_plane_or_player(char c, int is_bonus);
int			is_player(char c);
int			is_plane(char c, int is_bonus);
int			is_it_all_ones(char *row);
int			is_it_all_spaces(char *row);
int			is_digit(char c);
int			is_valid_elem(char *element, int is_bonus);
void		is_there_player(char *row, int *count);
int			is_valid_zero(t_lst *row, int i, int is_bonus);
int			ft_atoi(char *str);
int			check_files(t_cub3d *cub3d);
int			check_adjacent(int curr_len, int adj_len, char c, int i);
int			check_zeros(t_lst **rows, int is_bonus);
int			check_first_last_rows(t_lst *rows);
int			check_sides(char *row);
int			check_line(char **line, t_textures **textures, t_map2 **map,
				int *i);
int			add_map_lines(char **line, t_cub3d **cub3d, int fd,
				int is_bonus);
int			check_row(char *row, int prev_len, int next_len);
void		remove_x_node(t_lst **curr, t_lst **prev, t_lst **to_rem);

// raycasting prototypes
void		my_mlx_pixel_put(t_image *image, int x, int y, int color);
void		my_mlx_pixel_put2(t_image *image, int x, int y, int color);
void		render_ceil(t_cub3d *cub3d, int i, int end);
void		render_walls(t_cub3d *cub3d, int i, int start, int end);
void		render_floor(t_cub3d *cub3d, int i, int start, int end);
int			key_press(int key, t_cub3d *cub3d);
void		get_player_pos(t_cub3d *cub3d);
void		dda(t_cub3d *cub3d);
void		get_delta_distance(t_cub3d *cub3d, double ray_dir_x,
				double ray_dir_y);
void		cast_ray(t_cub3d *cub3d, double ray_angle);
void		cast_all_rays(t_cub3d *cub3d);
int			calc_height(double distance, int screen_height);
char		**get_arr(t_lst *lst);
int			get_rgb(int t, int r, int g, int b);
int			render(void *cub);
int			ft_exit(t_cub3d *cub3d);
void		get_wall_x(t_cub3d *cub3d, t_render *wall);
void		get_delta_distance_y(t_cub3d *cub3d, double ray_dir_y);
void		get_delta_distance_x(t_cub3d *cub3d, double ray_dir_x);

// bonus
void		draw_line(t_cub3d *cub3d, t_line *line);
void		draw_cub(t_cub3d *cub3d, t_render tools);
void		render_map(t_cub3d *cub3d);
void		door_interaction(t_cub3d *cub3d);
void		init_render(t_cub3d *cub3d, t_render *tools);
void		render_ceil_bonus(t_cub3d *cub3d, int i, int end);
int			get_texel(t_image texture, int x, int y);
void		init_key_state(t_key_state *keys);
int			key_release(int key, t_cub3d *cub3d);
void		handle_movement(t_cub3d *cub3d);
void		put_rect(t_cub3d *cub3d);
void		put_message(t_cub3d *cub3d);
int			is_near_door(t_cub3d *cub3d);
int			get_max(int v1, int v2);
double		get_scale(t_cub3d *cub3d);
void		define_sx(t_draw_tool *tool, t_line *line);
void		check_wall_colision(t_cub3d *cub3d, double newpos_x,
				double newpos_y);
int			get_door_is_open_at(int map_x, int map_y, t_cub3d *cub3d);
void		render_ceil_bonus(t_cub3d *cub3d, int i, int end);
int			mouse_move(int x, int y, t_cub3d *cub3d);
int			get_texel(t_image weapon, int x, int y);
void		calc_scale_and_position(t_cub3d *cub3d,
				t_weapon_vars *vars, int current_frame);
void		draw_weapon_img(t_cub3d *cub3d,
				t_weapon_vars *vars, int current_frame);
void		render_weapon(t_cub3d *cub3d, int current_frame);
void		initialize_filenames(char *filenames[]);
void		load_weapon_frames(t_cub3d *cub3d);
void		init_doors(t_door **doors, t_cub3d *cub3d);
void		load_door_frames(t_cub3d *cub3d);
void		close_doors(t_cub3d *cub3d);
void		init_ceiling_texture(t_cub3d *cub3d);
int			is_near_door(t_cub3d *cub3d);
void		toggle_door(t_cub3d *cub3d, int door_x, int door_y);
void		handle_movement(t_cub3d *cub3d);
void		check_wall_collision(t_cub3d *cub3d,
				double newpos_x, double newpos_y);
void		ft_move(t_cub3d *cub3d, double *newpos_x, double *newpos_y,
				t_direction move);
void		strafing(t_cub3d *cub3d, double *newpos_x, double *newpos_y,
				t_direction dir);

#endif
