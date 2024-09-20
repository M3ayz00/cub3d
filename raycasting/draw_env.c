/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:29:27 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/19 22:29:33 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_ceil(t_cub3d *data, int i, int end)
{
	int			l;
	uint32_t	color;

	l = 0;
	color = get_rgb(255, data->textures->ceiling->r, data->textures->ceiling->g,
			data->textures->ceiling->b);
	while (l < end)
	{
		my_mlx_pixel_put(data->image, i, l, color);
		l++;
	}
}

t_image	*get_texture_index(t_cub3d *data)
{
	if (data->ray->is_vertical)
	{
		if (data->ray->step_x > 0)
			return (&data->wall_t[2]);
		else
			return (&data->wall_t[3]);
	}
	else
	{
		if (data->ray->step_y > 0)
			return (&data->wall_t[0]);
		else
			return (&data->wall_t[1]);
	}
	return (&data->wall_t[2]);
}

void	render_walls(t_cub3d *data, int i, int start, int end)
{
	t_image		*texture;
	uint32_t	color;
	int			y;
	t_render	*wall;

	wall = malloc(sizeof(t_render));
	texture = get_texture_index(data);
	get_wall_x(data, wall);
	wall->column = (int)(wall->x * texture->width);
	if (wall->column >= texture->width)
		wall->column = texture->width - 1;
	wall->slice_height = (end - start);
	wall->scale = (float)texture->height / wall->slice_height;
	y = start;
	while (y++ < end)
	{
		wall->y = (int)((y - start) * wall->scale);
		if (wall->y >= texture->height)
			wall->y = texture->height - 1;
		wall->color = get_texture_color(texture, wall->column, wall->y);
		my_mlx_pixel_put(data->image, i, y, wall->color);
	}
	free(wall);
}

void	render_floor(t_cub3d *data, int i, int start, int end)
{
	int			l;
	uint32_t	color;

	l = start;
	color = get_rgb(255, data->textures->floor->r, data->textures->floor->g,
			data->textures->floor->b);
	while (l < end)
	{
		my_mlx_pixel_put(data->image, i, l, color);
		l++;
	}
}
