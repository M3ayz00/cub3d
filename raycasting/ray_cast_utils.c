/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:03:17 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/20 00:03:19 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_delta_distance_y(t_cub3d *data, double ray_dir_y)
{
	if (ray_dir_y < 0)
	{
		data->ray->step_y = -1;
		data->ray->side_dist_y = (data->player->pos_y - data->map2->map_y)
			* data->ray->delta_dist_y;
	}
	else
	{
		data->ray->step_y = 1;
		data->ray->side_dist_y = (data->map2->map_y + 1.0 - data->player->pos_y)
			* data->ray->delta_dist_y;
	}
}

void	get_delta_distance_x(t_cub3d *data, double ray_dir_x)
{
	if (ray_dir_x < 0)
	{
		data->ray->step_x = -1;
		data->ray->side_dist_x = (data->player->pos_x - data->map2->map_x)
			* data->ray->delta_dist_x;
	}
	else
	{
		data->ray->step_x = 1;
		data->ray->side_dist_x = (data->map2->map_x + 1.0 - data->player->pos_x)
			* data->ray->delta_dist_x;
	}
}
