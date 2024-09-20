#include "../cub3d.h"

void	init_doors(t_door **doors)
{
	int	y;
	int	x;

	y = 0;
	(*doors)->state = malloc(sizeof(int *) * HEIGHT);
	(*doors)->timer = malloc(sizeof(double *) * HEIGHT);
	while (y < HEIGHT)
	{
		(*doors)->state[y] = malloc(sizeof(int) * WIDTH);
		(*doors)->timer[y] = malloc(sizeof(double) * WIDTH);
		x = 0;
		while (x < WIDTH)
		{
			(*doors)->state[y][x] = 0;
			(*doors)->timer[y][x] = 0.0;
			x++;
		}
		y++;
	}
}

void	render_door(t_cub3d *data, int i, int start, int end)
{
	t_image		*door;
	t_render	tools;
	int			y;
	int			frame_index;

	door = &data->doors->door_frames[0];
	if (data->ray->hit_door)
	{
		frame_index = (int)(data->doors->timer[data->map2->map_y][data->map2->map_x]
				* (DOOR_FRAMES - 1));
		door = &data->doors->door_frames[frame_index];
	}
	tools.x = data->ray->hit_x - floor(data->ray->hit_x);
	if (data->ray->is_vertical)
		tools.x = data->ray->hit_y - floor(data->ray->hit_y);
	tools.column = (int)(tools.x * door->width);
	if (tools.column >= door->width)
		tools.column = door->width - 1;
	tools.slice_height = end - start;
	tools.scale = (float)door->height / tools.slice_height;
	for (y = start; y < end; y++)
	{
		tools.y = (int)((y - start) * tools.scale);
		if (tools.y >= door->height)
			tools.y = door->height - 1;
		tools.color = get_texture_color(door, tools.column, tools.y);
		if (tools.color != -16777216)
			my_mlx_pixel_put(data->image, i, y, tools.color);
	}
}

void	load_door_frames(t_cub3d *data)
{
	char *filenames[DOOR_FRAMES] = {
		"bonus/textures/door/door_frame_1.xpm",
		"bonus/textures/door/door_frame_2.xpm",
		"bonus/textures/door/door_frame_3.xpm",
		"bonus/textures/door/door_frame_4.xpm",
		"bonus/textures/door/door_frame_5.xpm",
		"bonus/textures/door/door_frame_6.xpm",
		"bonus/textures/door/door_frame_7.xpm",
		"bonus/textures/door/door_frame_8.xpm",
		"bonus/textures/door/door_frame_9.xpm",
	};
	data->doors->door_frames = malloc(sizeof(t_image) * DOOR_FRAMES);
	if (!data->doors->door_frames)
	{
		write(2, "door frames allocation error\n", 29);
		exit(1);
	}
	for (int i = 0; i < DOOR_FRAMES; i++)
	{
		data->doors->door_frames[i].img = mlx_xpm_file_to_image(data->mlx,
				filenames[i], &data->doors->door_frames[i].width,
				&data->doors->door_frames[i].height);
		if (!data->doors->door_frames[i].img)
		{
			write(2, "door frames loading error\n", 28);
			exit(1);
		}
		data->doors->door_frames[i].addr = mlx_get_data_addr(data->doors->door_frames[i].img,
				&data->doors->door_frames[i].bits_per_pixel,
				&data->doors->door_frames[i].line_length,
				&data->doors->door_frames[i].endian);
	}
}

void	update_doors(t_cub3d *cub3d)
{
	int		y;
	double	delta_time;
	int		x;

	y = 0;
	delta_time = 1.0 / 60.0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (cub3d->doors->state[y][x] == 1) // opening
			{
				cub3d->doors->timer[y][x] += delta_time * 2;
				if (cub3d->doors->timer[y][x] >= 1.0)
				{
					cub3d->doors->timer[y][x] = 1.0;
					cub3d->doors->state[y][x] = 2; // open
				}
			}
			else if (cub3d->doors->state[y][x] == 3) // closing
			{
				cub3d->doors->timer[y][x] -= delta_time * 2;
				if (cub3d->doors->timer[y][x] <= 0.0)
				{
					cub3d->doors->timer[y][x] = 0.0;
					cub3d->doors->state[y][x] = 0; // open
				}
			}
			x++;
		}
		y++;
	}
}

void	init_door_texture(t_cub3d *data)
{
	if (data->textures->door)
	{
		data->textures->door_tex.img = mlx_xpm_file_to_image(data->mlx,
				data->textures->door, &data->textures->door_tex.width,
				&data->textures->door_tex.height);
		if (!data->textures->door_tex.img)
		{
			write(2, "error loading door texture\n", 26);
			ft_exit(data);
		}
		data->textures->door_tex.addr = mlx_get_data_addr(data->textures->door_tex.img,
				&data->textures->door_tex.bits_per_pixel,
				&data->textures->door_tex.line_length,
				&data->textures->door_tex.endian);
	}
}

int	is_near_door(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = (int)cub3d->player->pos_x;
	y = (int)cub3d->player->pos_y;
	return (cub3d->map2->map[y + 1][x] == 'D' || cub3d->map2->map[y][x
		+ 1] == 'D' || cub3d->map2->map[y - 1][x] == 'D'
		|| cub3d->map2->map[y][x - 1] == 'D');
}

void	toggle_door(t_cub3d *data, int door_x, int door_y)
{
	if (data->doors->state[door_y][door_x] == 0)
		data->doors->state[door_y][door_x] = 1;
	else if (data->doors->state[door_y][door_x] == 2)
		data->doors->state[door_y][door_x] = 3;
}

void	door_interaction(t_cub3d *cub3d)
{
	int y;
	int x;

	y = 0;
	while (cub3d->map2->map[y])
	{
		x = 0;
		while (cub3d->map2->map[y][x])
		{
			if (cub3d->map2->map[y][x] == 'D')
			{
				if (is_near_door(cub3d))
					mlx_string_put(cub3d->mlx, cub3d->win, WIDTH / 2, HEIGHT
						/ 2, get_rgb(0, 255, 255, 255),
						"Press [E] to interact");
			}
			x++;
		}
		y++;
	}
}