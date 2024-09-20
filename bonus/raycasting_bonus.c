/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 06:59:02 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/20 21:23:53 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	dda(t_cub3d *data)
{
	int	is_open;
	data->ray->hit_door = 0;
	while (1)
	{
		if (data->ray->side_dist_x < data->ray->side_dist_y)
		{
			data->ray->side_dist_x += data->ray->delta_dist_x;
			data->map2->map_x += data->ray->step_x;
			data->ray->side = 0;
		}
		else
		{
			data->ray->side_dist_y += data->ray->delta_dist_y;
			data->map2->map_y += data->ray->step_y;
			data->ray->side = 1;
		}
		if (data->bonus == 1
			&& (data->map2->map[data->map2->map_y][data->map2->map_x] == 'D'))
		{
			is_open = get_door_is_open_at(data->map2->map_x, data->map2->map_y, data);
			if (is_open == 0)
			{
				data->ray->hit_door = 1;
				break ;
			}
		}
		if (data->map2->map[data->map2->map_y][data->map2->map_x] == '1')
			break ;
	}
}


void	get_delta_distance(t_cub3d *data, double ray_dir_x, double ray_dir_y)
{
	data->ray->delta_dist_x = fabs(1 / ray_dir_x);
	data->ray->delta_dist_y = fabs(1 / ray_dir_y);
	get_delta_distance_x(data, ray_dir_x);
	get_delta_distance_y(data, ray_dir_y);
}

void	cast_ray(t_cub3d *data, double ray_angle)
{
	double	ray_dir_x;
	double	ray_dir_y;

	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	data->map2->map_x = (int)data->player->pos_x;
	data->map2->map_y = (int)data->player->pos_y;
	get_delta_distance(data, ray_dir_x, ray_dir_y);
	dda(data);
	if (data->ray->side == 0)
		data->ray->hit_distance = (data->ray->side_dist_x
				- data->ray->delta_dist_x);
	else
		data->ray->hit_distance = (data->ray->side_dist_y
				- data->ray->delta_dist_y);
	data->ray->hit_x = data->player->pos_x + data->ray->hit_distance
		* ray_dir_x;
	data->ray->hit_y = data->player->pos_y + data->ray->hit_distance
		* ray_dir_y;
	data->ray->is_vertical = (data->ray->side == 0);
}

void	cast_all_rays(t_cub3d *data)
{
	int			i;
	int			j;
	t_casting	wall;

	wall.angle_step = data->fov / WIDTH;
	i = 0;
	while (i < WIDTH - 1)
	{
		wall.ray_angle = data->player->angle - (data->fov / 2) + (i
				* wall.angle_step);
		cast_ray(data, wall.ray_angle);
		wall.start = (HEIGHT / 2) - (calc_height((data->ray->hit_distance
						* cos(wall.ray_angle - data->player->angle)), HEIGHT)
				/ 2);
		wall.end = (HEIGHT / 2) + (calc_height((data->ray->hit_distance
						* cos(wall.ray_angle - data->player->angle)), HEIGHT)
				/ 2);
		render_ceil_bonus(data, i, wall.start);
		if (data->ray->hit_door)
			render_door(data, i, wall.start, wall.end);
		else
			render_walls(data, i, wall.start, wall.end);
		render_floor(data, i, wall.end, HEIGHT);
		i++;
	}
}
