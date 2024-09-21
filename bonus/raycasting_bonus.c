/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 06:59:02 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/21 15:58:27 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_door_hit(t_cub3d *cub3d)
{
	int	is_open;

	if (cub3d->bonus == 1
		&& (cub3d->map2->map[cub3d->map2->map_y][cub3d->map2->map_x] == 'D'))
	{
		is_open = get_door_is_open_at(cub3d->map2->map_x, cub3d->map2->map_y,
				cub3d);
		if (is_open == 0)
		{
			cub3d->ray->hit_door = 1;
			return (1);
		}
	}
	return (0);
}

void	dda(t_cub3d *cub3d)
{
	cub3d->ray->hit_door = 0;
	while (1)
	{
		if (cub3d->ray->side_dist_x < cub3d->ray->side_dist_y)
		{
			cub3d->ray->side_dist_x += cub3d->ray->delta_dist_x;
			cub3d->map2->map_x += cub3d->ray->step_x;
			cub3d->ray->side = 0;
		}
		else
		{
			cub3d->ray->side_dist_y += cub3d->ray->delta_dist_y;
			cub3d->map2->map_y += cub3d->ray->step_y;
			cub3d->ray->side = 1;
		}
		if (check_door_hit(cub3d)
			|| cub3d->map2->map[cub3d->map2->map_y][cub3d->map2->map_x] == '1')
			break ;
	}
}

void	get_delta_distance(t_cub3d *cub3d, double ray_dir_x, double ray_dir_y)
{
	cub3d->ray->delta_dist_x = fabs(1 / ray_dir_x);
	cub3d->ray->delta_dist_y = fabs(1 / ray_dir_y);
	get_delta_distance_x(cub3d, ray_dir_x);
	get_delta_distance_y(cub3d, ray_dir_y);
}

void	cast_ray(t_cub3d *cub3d, double ray_angle)
{
	double	ray_dir_x;
	double	ray_dir_y;

	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	cub3d->map2->map_x = (int)cub3d->player->pos_x;
	cub3d->map2->map_y = (int)cub3d->player->pos_y;
	get_delta_distance(cub3d, ray_dir_x, ray_dir_y);
	dda(cub3d);
	if (cub3d->ray->side == 0)
		cub3d->ray->hit_distance = (cub3d->ray->side_dist_x
				- cub3d->ray->delta_dist_x);
	else
		cub3d->ray->hit_distance = (cub3d->ray->side_dist_y
				- cub3d->ray->delta_dist_y);
	cub3d->ray->hit_x = cub3d->player->pos_x + cub3d->ray->hit_distance
		* ray_dir_x;
	cub3d->ray->hit_y = cub3d->player->pos_y + cub3d->ray->hit_distance
		* ray_dir_y;
	cub3d->ray->is_vertical = (cub3d->ray->side == 0);
}

void	cast_all_rays(t_cub3d *cub3d)
{
	int			i;
	t_casting	wall;

	wall.angle_step = cub3d->fov / WIDTH;
	i = 0;
	while (i < WIDTH - 1)
	{
		wall.ray_angle = cub3d->player->angle - (cub3d->fov / 2) + (i
				* wall.angle_step);
		cast_ray(cub3d, wall.ray_angle);
		wall.start = (HEIGHT / 2) - (calc_height((cub3d->ray->hit_distance
						* cos(wall.ray_angle - cub3d->player->angle)), HEIGHT)
				/ 2);
		wall.end = (HEIGHT / 2) + (calc_height((cub3d->ray->hit_distance
						* cos(wall.ray_angle - cub3d->player->angle)), HEIGHT)
				/ 2);
		render_ceil_bonus(cub3d, i, wall.start);
		if (cub3d->ray->hit_door)
			render_door(cub3d, i, wall.start, wall.end);
		else
			render_walls(cub3d, i, wall.start, wall.end);
		render_floor(cub3d, i, wall.end, HEIGHT);
		i++;
	}
}
