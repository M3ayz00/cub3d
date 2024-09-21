/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:03:17 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/21 14:59:21 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_delta_distance_y(t_cub3d *cub3d, double ray_dir_y)
{
	if (ray_dir_y < 0)
	{
		cub3d->ray->step_y = -1;
		cub3d->ray->side_dist_y = (cub3d->player->pos_y - cub3d->map2->map_y)
			* cub3d->ray->delta_dist_y;
	}
	else
	{
		cub3d->ray->step_y = 1;
		cub3d->ray->side_dist_y = (cub3d->map2->map_y + 1.0 - cub3d->player->pos_y)
			* cub3d->ray->delta_dist_y;
	}
}

void	get_delta_distance_x(t_cub3d *cub3d, double ray_dir_x)
{
	if (ray_dir_x < 0)
	{
		cub3d->ray->step_x = -1;
		cub3d->ray->side_dist_x = (cub3d->player->pos_x - cub3d->map2->map_x)
			* cub3d->ray->delta_dist_x;
	}
	else
	{
		cub3d->ray->step_x = 1;
		cub3d->ray->side_dist_x = (cub3d->map2->map_x + 1.0 - cub3d->player->pos_x)
			* cub3d->ray->delta_dist_x;
	}
}
