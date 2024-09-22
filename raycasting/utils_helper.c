/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:56:39 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/22 20:56:41 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_struct(t_cub3d *cub3d)
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
}

int	ft_exit(t_cub3d *cub3d)
{
	if (cub3d->map->map)
		free_strs(cub3d->map->map);
	free_map(&cub3d->map);
	free_textures(&cub3d->textures);
	free_struct(cub3d);
	mlx_destroy_image(cub3d->mlx, cub3d->image->img);
	if (cub3d->image)
		free(cub3d->image);
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	if (cub3d->mlx)
		free(cub3d->mlx);
	exit(0);
	return (0);
}
