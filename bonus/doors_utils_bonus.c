/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:50:26 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/21 16:01:19 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	put_rect(t_cub3d *cub3d)
{
	int	y;
	int	x;
	int	end_y;
	int	end_x;

	y = HEIGHT - 188;
	end_x = WIDTH / 2 + 68;
	end_y = HEIGHT - 170;
	while (y < end_y)
	{
		x = WIDTH / 2 - 65;
		while (x < end_x)
		{
			my_mlx_pixel_put(cub3d->image, x, y, get_rgb(0, 0, 0, 0));
			x++;
		}
		y++;
	}
}

void	put_message(t_cub3d *cub3d)
{
	put_rect(cub3d);
	mlx_string_put(cub3d->mlx, cub3d->win, WIDTH / 2 - 60, HEIGHT - 175,
		get_rgb(0, 255, 255, 255), "Press [E] to interact");
}

int	is_near_door(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = (int)cub3d->player->pos_x;
	y = (int)cub3d->player->pos_y;
	return (cub3d->map2->map[y + 1][x] == 'D'
		|| cub3d->map2->map[y][x + 1] == 'D'
		|| cub3d->map2->map[y - 1][x] == 'D'
		|| cub3d->map2->map[y][x - 1] == 'D');
}
