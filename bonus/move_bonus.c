/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 07:04:30 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/21 14:59:21 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_key_state(t_key_state *keys)
{
	keys->forward = 0;
	keys->backward = 0;
	keys->left = 0;
	keys->right = 0;
	keys->rotate_left = 0;
	keys->rotate_right = 0;
}

void	ft_move(t_cub3d *cub3d, double *newpos_x, double *newpos_y,
		t_direction move)
{
	if (move == FORWARD)
	{
		*newpos_x += cos(cub3d->player->angle) * MOVE_SPEED;
		*newpos_y += sin(cub3d->player->angle) * MOVE_SPEED;
	}
	else
	{
		*newpos_x -= cos(cub3d->player->angle) * MOVE_SPEED;
		*newpos_y -= sin(cub3d->player->angle) * MOVE_SPEED;
	}
}

void	strafing(t_cub3d *cub3d, double *newpos_x, double *newpos_y,
		t_direction dir)
{
	if (dir == LEFT)
	{
		*newpos_x += sin(cub3d->player->angle) * MOVE_SPEED;
		*newpos_y -= cos(cub3d->player->angle) * MOVE_SPEED;
	}
	else
	{
		*newpos_x -= sin(cub3d->player->angle) * MOVE_SPEED;
		*newpos_y += cos(cub3d->player->angle) * MOVE_SPEED;
	}
}

int	mouse_move(int x, int y, t_cub3d *cub3d)
{
	static int	last_x = -1;
	int			window_center_x;
	int			widow_center_y;

	window_center_x = WIDTH / 2;
	widow_center_y = HEIGHT / 2;
	if (last_x != -1)
	{
		cub3d->keys.delta_x = (x - window_center_x);
		if (cub3d->keys.delta_x != 0)
		{
			if (cub3d->keys.delta_x > 0)
				cub3d->keys.rotate_right = 2;
			else if (cub3d->keys.delta_x < 0)
				cub3d->keys.rotate_left = 2;
		}
		if (x != window_center_x || y != widow_center_y)
			mlx_mouse_move(cub3d->mlx, cub3d->win, window_center_x,
				widow_center_y);
	}
	last_x = x;
	return (0);
}
