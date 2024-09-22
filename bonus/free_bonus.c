/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:57:04 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/22 21:45:03 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_struct_bonus(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub3d->wall_t[i].img)
		{
			mlx_destroy_image(cub3d->mlx, cub3d->wall_t[i].img);
			cub3d->wall_t[i].img = NULL;
		}
		i++;
	}
	if (cub3d->player)
		free(cub3d->player);
	if (cub3d->ray)
		free(cub3d->ray);
	if (cub3d->weapon)
		free(cub3d->weapon);
	if (cub3d->minimap)
		free(cub3d->minimap);
	if (cub3d->doors)
		free(cub3d->doors);
}

void	free_weapon_frames(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < FRAME_COUNT)
	{
		if (cub3d->frames[i].img)
		{
			mlx_destroy_image(cub3d->mlx, cub3d->frames[i].img);
			cub3d->frames[i].img = NULL;
		}
		i++;
	}
}

void	free_doors(t_door **doors, t_cub3d *cub3d)
{
	int	y;

	if (!doors || !(*doors) || !cub3d->map)
		return ;
	y = 0;
	printf("HELLO : %d\n", (cub3d->doors->door_frame != NULL));
	if (cub3d->doors->door_frame->img)
	{
		mlx_destroy_image(cub3d->mlx, cub3d->doors->door_frame->img);
		cub3d->doors->door_frame->img = NULL;
		free(cub3d->doors->door_frame);
	}
	while (y < cub3d->map->height)
	{
		free((*doors)->is_open[y]);
		free((*doors)->timer[y]);
		y++;
	}
	free((*doors)->is_open);
	free((*doors)->timer);
	free(*doors);
	*doors = NULL;
}
