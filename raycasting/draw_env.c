/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:29:27 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/21 16:00:28 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_ceil(t_cub3d *cub3d, int i, int end)
{
	int			l;
	uint32_t	color;

	l = 0;
	color = get_rgb(255, cub3d->textures->ceiling->r, cub3d->textures->ceiling->g,
			cub3d->textures->ceiling->b);
	while (l < end)
	{
		my_mlx_pixel_put(cub3d->image, i, l, color);
		l++;
	}
}

t_image	*get_texture_index(t_cub3d *cub3d)
{
	if (cub3d->ray->is_vertical)
	{
		if (cub3d->ray->step_x > 0)
			return (&cub3d->wall_t[2]);
		else
			return (&cub3d->wall_t[3]);
	}
	else
	{
		if (cub3d->ray->step_y > 0)
			return (&cub3d->wall_t[0]);
		else
			return (&cub3d->wall_t[1]);
	}
	return (NULL);
}

void	render_walls(t_cub3d *cub3d, int i, int start, int end)
{
	t_image		*texture;
	t_render	wall;
	int			y;

	texture = get_texture_index(cub3d);
	get_wall_x(cub3d, &wall);
	wall.column = (int)(wall.x * texture->width);
	if (wall.column >= texture->width)
		wall.column = texture->width - 1;
	wall.slice_height = (end - start);
	wall.scale = (float)texture->height / wall.slice_height;
	y = start;
	while (y++ < end)
	{
		wall.y = (int)((y - start) * wall.scale);
		if (wall.y >= texture->height)
			wall.y = texture->height - 1;
		wall.color = get_texture_color(texture, wall.column, wall.y);
		my_mlx_pixel_put(cub3d->image, i, y, wall.color);
	}
}

void	render_floor(t_cub3d *cub3d, int i, int start, int end)
{
	uint32_t	color;

	color = get_rgb(255, cub3d->textures->floor->r, cub3d->textures->floor->g,
			cub3d->textures->floor->b);
	while (start < end)
	{
		my_mlx_pixel_put(cub3d->image, i, start, color);
		start++;
	}
}
