/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:18:19 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/19 23:18:21 by aes-sarg         ###   ########.fr       */
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

void	ft_move(t_cub3d *data, double *new_pos_x, double *new_pos_y,
		t_direction move)
{
	if (move == FORWARD)
	{
		*new_pos_x += cos(data->player->angle) * MOVE_SPEED;
		*new_pos_y += sin(data->player->angle) * MOVE_SPEED;
	}
	else
	{
		*new_pos_x -= cos(data->player->angle) * MOVE_SPEED;
		*new_pos_y -= sin(data->player->angle) * MOVE_SPEED;
	}
}

void	strafing(t_cub3d *data, double *new_pos_x, double *new_pos_y,
		t_direction dir)
{
	if (dir == LEFT)
	{
		*new_pos_x += sin(data->player->angle) * MOVE_SPEED;
		*new_pos_y -= cos(data->player->angle) * MOVE_SPEED;
	}
	else
	{
		*new_pos_x -= sin(data->player->angle) * MOVE_SPEED;
		*new_pos_y += cos(data->player->angle) * MOVE_SPEED;
	}
}

void	check_wall_colision(t_cub3d *data, double new_pos_x, double new_pos_y)
{
	if (data->map2->map[(int)floor(new_pos_y - MARGIN)][(int)floor(new_pos_x
			- MARGIN)] != '1' && data->map2->map[(int)floor(new_pos_y
			- MARGIN)][(int)floor(new_pos_x + MARGIN)] != '1'
		&& data->map2->map[(int)floor(new_pos_y + MARGIN)][(int)floor(new_pos_x
			- MARGIN)] != '1' && data->map2->map[(int)floor(new_pos_y
			+ MARGIN)][(int)floor(new_pos_x + MARGIN)] != '1')
	{
		data->player->pos_x = new_pos_x;
		data->player->pos_y = new_pos_y;
	}
}

void	handle_movement(t_cub3d *data)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = data->player->pos_x;
	new_pos_y = data->player->pos_y;
	if (data->keys.forward)
		ft_move(data, &new_pos_x, &new_pos_y, FORWARD);
	if (data->keys.backward)
		ft_move(data, &new_pos_x, &new_pos_y, BACKWARD);
	if (data->keys.left)
		strafing(data, &new_pos_x, &new_pos_y, LEFT);
	if (data->keys.right)
		strafing(data, &new_pos_x, &new_pos_y, RIGHT);
	if (data->keys.rotate_left)
		data->player->angle -= ROT_SPEED;
	if (data->keys.rotate_right)
		data->player->angle += ROT_SPEED;
	check_wall_colision(data, new_pos_x, new_pos_y);
}
