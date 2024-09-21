/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:18:19 by aes-sarg          #+#    #+#             */
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

void	ft_move(t_cub3d *cub3d, double *new_pos_x, double *new_pos_y,
		t_direction move)
{
	if (move == FORWARD)
	{
		*new_pos_x += cos(cub3d->player->angle) * MOVE_SPEED;
		*new_pos_y += sin(cub3d->player->angle) * MOVE_SPEED;
	}
	else
	{
		*new_pos_x -= cos(cub3d->player->angle) * MOVE_SPEED;
		*new_pos_y -= sin(cub3d->player->angle) * MOVE_SPEED;
	}
}

void	strafing(t_cub3d *cub3d, double *new_pos_x, double *new_pos_y,
		t_direction dir)
{
	if (dir == LEFT)
	{
		*new_pos_x += sin(cub3d->player->angle) * MOVE_SPEED;
		*new_pos_y -= cos(cub3d->player->angle) * MOVE_SPEED;
	}
	else
	{
		*new_pos_x -= sin(cub3d->player->angle) * MOVE_SPEED;
		*new_pos_y += cos(cub3d->player->angle) * MOVE_SPEED;
	}
}

void	check_wall_colision(t_cub3d *cub3d, double new_pos_x, double new_pos_y)
{
	if (cub3d->map2->map[(int)floor(new_pos_y - MARGIN)][(int)floor(new_pos_x
			- MARGIN)] != '1' && cub3d->map2->map[(int)floor(new_pos_y
			- MARGIN)][(int)floor(new_pos_x + MARGIN)] != '1'
		&& cub3d->map2->map[(int)floor(new_pos_y + MARGIN)][(int)floor(new_pos_x
			- MARGIN)] != '1' && cub3d->map2->map[(int)floor(new_pos_y
			+ MARGIN)][(int)floor(new_pos_x + MARGIN)] != '1')
	{
		cub3d->player->pos_x = new_pos_x;
		cub3d->player->pos_y = new_pos_y;
	}
}

void	handle_movement(t_cub3d *cub3d)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = cub3d->player->pos_x;
	new_pos_y = cub3d->player->pos_y;
	if (cub3d->keys.forward)
		ft_move(cub3d, &new_pos_x, &new_pos_y, FORWARD);
	if (cub3d->keys.backward)
		ft_move(cub3d, &new_pos_x, &new_pos_y, BACKWARD);
	if (cub3d->keys.left)
		strafing(cub3d, &new_pos_x, &new_pos_y, LEFT);
	if (cub3d->keys.right)
		strafing(cub3d, &new_pos_x, &new_pos_y, RIGHT);
	if (cub3d->keys.rotate_left)
		cub3d->player->angle -= ROT_SPEED;
	if (cub3d->keys.rotate_right)
		cub3d->player->angle += ROT_SPEED;
	check_wall_colision(cub3d, new_pos_x, new_pos_y);
}
