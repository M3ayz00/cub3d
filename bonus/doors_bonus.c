#include "../cub3d.h"

void	init_doors(t_door **doors, t_cub3d *cub3d)
{
	int	y;
	int	x;

	y = 0;
	(*doors)->is_open = malloc(sizeof(int *) * cub3d->map2->height);
	(*doors)->timer = malloc(sizeof(int *) * cub3d->map2->height);
	while (y < cub3d->map2->height)
	{
		(*doors)->is_open[y] = malloc(sizeof(int) * cub3d->map2->width);
		(*doors)->timer[y] = malloc(sizeof(int) * cub3d->map2->width);
		x = 0;
		while (x < cub3d->map2->width)
		{
			(*doors)->is_open[y][x] = 0;
			(*doors)->is_open[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	render_door(t_cub3d *data, int i, int start, int end)
{
	t_image		*door;
	t_render	tools;

	if (data->doors->is_open[data->map2->map_y][data->map2->map_x] == 1)
        return ;
	door = data->doors->door_frame;
	tools.x = data->ray->hit_x - floor(data->ray->hit_x);
	if (data->ray->is_vertical)
		tools.x = data->ray->hit_y - floor(data->ray->hit_y);
	tools.column = (int)(tools.x * door->width);
	if (tools.column >= door->width)
		tools.column = door->width - 1;
	tools.slice_height = end - start;
	tools.scale = (float)door->height / tools.slice_height;
	for (tools.i = start; tools.i < end; tools.i++)
	{
		tools.y = (int)((tools.i - start) * tools.scale);
		if (tools.y >= door->height)
			tools.y = door->height - 1;
		tools.color = get_texture_color(door, tools.column, tools.y);
		if (tools.color != -16777216)
			my_mlx_pixel_put(data->image, i, tools.i, tools.color);
	}
}

void	load_door_frames(t_cub3d *data)
{
	data->doors->door_frame = malloc(sizeof(t_image));
	if (!data->doors->door_frame)
	{
		write(2, "door frames allocation error\n", 29);
		exit(1);
	}
	data->doors->door_frame->img = mlx_xpm_file_to_image(data->mlx,
			"bonus/textures/door/wolfenstein_door.xpm", &data->doors->door_frame->width,
			&data->doors->door_frame->height);
	if (!data->doors->door_frame->img)
	{
		write(2, "door frames loading error\n", 28);
		exit(1);
	}
	data->doors->door_frame->addr = mlx_get_data_addr(data->doors->door_frame->img,
			&data->doors->door_frame->bits_per_pixel,
			&data->doors->door_frame->line_length,
			&data->doors->door_frame->endian);
}

int	is_near_door(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = (int)cub3d->player->pos_x;
	y = (int)cub3d->player->pos_y;
	return (cub3d->map2->map[y + 1][x] == 'D' || cub3d->map2->map[y][x + 1] == 'D'
		|| cub3d->map2->map[y - 1][x] == 'D' || cub3d->map2->map[y][x - 1] == 'D');
}

void	toggle_door(t_cub3d *data, int door_x, int door_y)
{
	if (data->doors->is_open[door_y][door_x] == 0)
	{
		data->doors->is_open[door_y][door_x] = 1;
		data->doors->timer[door_y][door_x] = 0;
	}
	else if (data->doors->is_open[door_y][door_x] == 1)
		data->doors->is_open[door_y][door_x] = 0;
}

void	close_doors(t_cub3d *cub3d)
{
	int	close_threshold = 100;
	int	y = 0;
	while (y < cub3d->map2->height)
	{
		int x = 0;
		while (x < cub3d->map2->width)
		{
			if (cub3d->doors->is_open[y][x])
				cub3d->doors->timer[y][x]++;
			if (cub3d->doors->timer[y][x] >= close_threshold)
				cub3d->doors->is_open[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	door_interaction(t_cub3d *cub3d)
{
	int door_x;
	int door_y;

	door_x = (int)cub3d->player->pos_x;
	door_y = (int)cub3d->player->pos_y;
	if (is_near_door(cub3d))
	{
		mlx_string_put(cub3d->mlx, cub3d->win, WIDTH / 2, HEIGHT / 2,
			get_rgb(0, 255, 255, 255), "Press [E] to interact");
		if (cub3d->keys.e == 1)
		{
			if (cub3d->map2->map[door_y + 1][door_x] == 'D')
				toggle_door(cub3d, door_x, door_y + 1);
			else if (cub3d->map2->map[door_y][door_x + 1] == 'D')
				toggle_door(cub3d, door_x + 1, door_y);
			else if (cub3d->map2->map[door_y - 1][door_x] == 'D')
				toggle_door(cub3d, door_x, door_y - 1);
			else if (cub3d->map2->map[door_y][door_x - 1] == 'D')
				toggle_door(cub3d, door_x - 1, door_y);
			cub3d->keys.e = 0;
		}
	}
}
