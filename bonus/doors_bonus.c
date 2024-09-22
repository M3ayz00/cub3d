/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:43:31 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/21 15:51:39 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_door(t_cub3d *cub3d, int i, int start, int end)
{
	t_image		*door;
	t_render	tools;

	if (cub3d->doors->is_open[cub3d->map->map_y][cub3d->map->map_x] == 1)
		return ;
	door = cub3d->doors->door_frame;
	tools.x = cub3d->ray->hit_x - floor(cub3d->ray->hit_x);
	if (cub3d->ray->is_vertical)
		tools.x = cub3d->ray->hit_y - floor(cub3d->ray->hit_y);
	tools.column = (int)(tools.x * door->width);
	if (tools.column >= door->width)
		tools.column = door->width - 1;
	tools.slice_height = end - start;
	tools.scale = (float)door->height / tools.slice_height;
	tools.i = start;
	while (tools.i < end)
	{
		tools.y = (int)((tools.i - start) * tools.scale);
		if (tools.y >= door->height)
			tools.y = door->height - 1;
		tools.color = get_texture_color(door, tools.column, tools.y);
		if (tools.color != -16777216)
			my_mlx_pixel_put(cub3d->image, i, tools.i, tools.color);
		tools.i++;
	}
}

void	load_door_frames(t_cub3d *cub3d)
{
	t_image	*door_frame;

	door_frame = malloc(sizeof(t_image));
	if (!door_frame)
	{
		write(2, "door frames allocation error\n", 29);
		exit(1);
	}
	door_frame->img = mlx_xpm_file_to_image(cub3d->mlx,
			"bonus/textures/door/wolfenstein_door.xpm", &door_frame->width,
			&door_frame->height);
	if (!door_frame->img)
	{
		write(2, "door frames loading error\n", 28);
		exit(1);
	}
	door_frame->addr = mlx_get_data_addr(door_frame->img,
			&door_frame->bits_per_pixel, &door_frame->line_length,
			&door_frame->endian);
	cub3d->doors->door_frame = door_frame;
}

void	toggle_door(t_cub3d *cub3d, int door_x, int door_y)
{
	if (cub3d->doors->is_open[door_y][door_x] == 0)
	{
		cub3d->doors->is_open[door_y][door_x] = 1;
		cub3d->doors->timer[door_y][door_x] = 0;
	}
	else if (cub3d->doors->is_open[door_y][door_x] == 1)
		cub3d->doors->is_open[door_y][door_x] = 0;
}

void	close_doors(t_cub3d *cub3d)
{
	int	close_threshold;
	int	y;
	int	x;

	y = 0;
	close_threshold = 100;
	while (y < cub3d->map->height)
	{
		x = 0;
		while (x < cub3d->map->width)
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
	int	door_x;
	int	door_y;

	door_x = (int)cub3d->player->pos_x;
	door_y = (int)cub3d->player->pos_y;
	if (is_near_door(cub3d))
	{
		put_message(cub3d);
		if (cub3d->keys.e == 1)
		{
			if (cub3d->map->map[door_y + 1][door_x] == 'D')
				toggle_door(cub3d, door_x, door_y + 1);
			else if (cub3d->map->map[door_y][door_x + 1] == 'D')
				toggle_door(cub3d, door_x + 1, door_y);
			else if (cub3d->map->map[door_y - 1][door_x] == 'D')
				toggle_door(cub3d, door_x, door_y - 1);
			else if (cub3d->map->map[door_y][door_x - 1] == 'D')
				toggle_door(cub3d, door_x - 1, door_y);
			cub3d->keys.e = 0;
		}
	}
}
