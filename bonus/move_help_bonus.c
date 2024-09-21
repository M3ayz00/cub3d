/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_help_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:21:22 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/21 23:32:33 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_xy_collision(t_cub3d *cub3d, double newpos_x, double newpos_y)
{
	if (!is_collide_wall_at_x(cub3d, newpos_x) && !is_collide_door_at_x(cub3d,
			newpos_x))
		cub3d->player->pos_x = newpos_x;
	if (!is_collide_wall_at_y(cub3d, newpos_y) && !is_collide_door_at_y(cub3d,
			newpos_y))
		cub3d->player->pos_y = newpos_y;
}

int	is_collision(t_cub3d *cub3d, double newpos_x, double newpos_y)
{
	return (is_collide_wall_at_x(cub3d, newpos_x) || is_collide_wall_at_y(cub3d,
			newpos_y) || is_collide_door_at_x(cub3d, newpos_x)
		|| is_collide_door_at_y(cub3d, newpos_y));
}

void	check_wall_collision(t_cub3d *cub3d, double newpos_x, double newpos_y)
{
	if (!is_collision(cub3d, newpos_x, newpos_y))
	{
		cub3d->player->pos_x = newpos_x;
		cub3d->player->pos_y = newpos_y;
	}
	else
		check_xy_collision(cub3d, newpos_x, newpos_y);
}

void	release_mouse(t_cub3d *cub3d)
{
	if (cub3d->keys.rotate_left == 2 || cub3d->keys.rotate_right == 2)
		cub3d->keys.rotate_left = 0;
	cub3d->keys.rotate_right = 0;
	cub3d->keys.delta_x = 0;
}

void	handle_movement(t_cub3d *cub3d)
{
	double	newpos_x;
	double	newpos_y;

	newpos_x = cub3d->player->pos_x;
	newpos_y = cub3d->player->pos_y;
	if (cub3d->keys.forward)
		ft_move(cub3d, &newpos_x, &newpos_y, FORWARD);
	if (cub3d->keys.backward)
		ft_move(cub3d, &newpos_x, &newpos_y, BACKWARD);
	if (cub3d->keys.left)
		strafing(cub3d, &newpos_x, &newpos_y, LEFT);
	if (cub3d->keys.right)
		strafing(cub3d, &newpos_x, &newpos_y, RIGHT);
	if (cub3d->keys.rotate_left == 1)
		cub3d->player->angle -= ROT_SPEED;
	if (cub3d->keys.rotate_left == 2)
		cub3d->player->angle -= abs(cub3d->keys.delta_x) * SENSITIVITY;
	if (cub3d->keys.rotate_right == 1)
		cub3d->player->angle += ROT_SPEED;
	if (cub3d->keys.rotate_right == 2)
		cub3d->player->angle += abs(cub3d->keys.delta_x) * SENSITIVITY;
	check_wall_collision(cub3d, newpos_x, newpos_y);
	release_mouse(cub3d);
}
