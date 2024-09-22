/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 21:49:12 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/21 23:05:03 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_collide_wall_at_x(t_cub3d *cub3d, double newpos_x)
{
	return ((cub3d->map->map[(int)floor(cub3d->player->pos_y
					- MARGIN)][(int)floor(newpos_x - MARGIN)] == '1'
		|| cub3d->map->map[(int)floor(cub3d->player->pos_y
				+ MARGIN)][(int)floor(newpos_x - MARGIN)] == '1'
		|| cub3d->map->map[(int)floor(cub3d->player->pos_y
					- MARGIN)][(int)floor(newpos_x + MARGIN)] == '1'
		|| cub3d->map->map[(int)floor(cub3d->player->pos_y
					+ MARGIN)][(int)floor(newpos_x + MARGIN)] == '1'));
}

int	is_collide_wall_at_y(t_cub3d *cub3d, double newpos_y)
{
	return (cub3d->map->map[(int)floor(newpos_y
				- MARGIN)][(int)floor(cub3d->player->pos_x - MARGIN)] == '1'
		|| cub3d->map->map[(int)floor(newpos_y
			+ MARGIN)][(int)floor(cub3d->player->pos_x - MARGIN)] == '1'
		|| cub3d->map->map[(int)floor(newpos_y
			- MARGIN)][(int)floor(cub3d->player->pos_x + MARGIN)] == '1'
		|| cub3d->map->map[(int)floor(newpos_y
			+ MARGIN)][(int)floor(cub3d->player->pos_x + MARGIN)] == '1');
}

int	is_collide_door_at_x(t_cub3d *cub3d, double newpos_x)
{
	return ((cub3d->map->map[(int)floor(cub3d->player->pos_y
					- MARGIN)][(int)floor(newpos_x - MARGIN)] == 'D'
		&& !get_door_is_open_at((int)floor(newpos_x - MARGIN),
			(int)floor(cub3d->player->pos_y - MARGIN), cub3d))
		|| (cub3d->map->map[(int)floor(cub3d->player->pos_y
			+ MARGIN)][(int)floor(newpos_x - MARGIN)] == 'D'
		&& !get_door_is_open_at((int)floor(newpos_x - MARGIN),
			(int)floor(cub3d->player->pos_y + MARGIN), cub3d))
		|| (cub3d->map->map[(int)floor(cub3d->player->pos_y
			- MARGIN)][(int)floor(newpos_x + MARGIN)] == 'D'
		&& !get_door_is_open_at((int)floor(newpos_x + MARGIN),
			(int)floor(cub3d->player->pos_y - MARGIN), cub3d))
		|| (cub3d->map->map[(int)floor(cub3d->player->pos_y
			+ MARGIN)][(int)floor(newpos_x + MARGIN)] == 'D'
		&& !get_door_is_open_at((int)floor(newpos_x + MARGIN),
			(int)floor(cub3d->player->pos_y + MARGIN), cub3d)));
}

int	is_collide_door_at_y(t_cub3d *cub3d, double newpos_y)
{
	return ((cub3d->map->map[(int)floor(newpos_y
					- MARGIN)][(int)floor(cub3d->player->pos_x - MARGIN)] == 'D'
		&& !get_door_is_open_at((int)floor(cub3d->player->pos_x - MARGIN),
			(int)floor(newpos_y - MARGIN), cub3d))
		|| (cub3d->map->map[(int)floor(newpos_y
			+ MARGIN)][(int)floor(cub3d->player->pos_x - MARGIN)] == 'D'
		&& !get_door_is_open_at((int)floor(cub3d->player->pos_x - MARGIN),
			(int)floor(newpos_y + MARGIN), cub3d))
		|| (cub3d->map->map[(int)floor(newpos_y
			- MARGIN)][(int)floor(cub3d->player->pos_x + MARGIN)] == 'D'
		&& !get_door_is_open_at((int)floor(cub3d->player->pos_x + MARGIN),
			(int)floor(newpos_y - MARGIN), cub3d))
		|| (cub3d->map->map[(int)floor(newpos_y
			+ MARGIN)][(int)floor(cub3d->player->pos_x + MARGIN)] == 'D'
		&& !get_door_is_open_at((int)floor(cub3d->player->pos_x + MARGIN),
			(int)floor(newpos_y + MARGIN), cub3d)));
}
