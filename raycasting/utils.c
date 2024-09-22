/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:58:39 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/22 19:59:45 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	calc_height(double distance, int screen_height)
{
	if (distance <= 0)
		return (screen_height);
	return ((int)(screen_height / distance));
}

char	**get_arr(t_lst *lst)
{
	t_lst	*tmp;
	int		size;
	int		i;
	char	**arr;

	i = 0;
	tmp = lst;
	size = ft_lstsize(lst);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	while (i < size)
	{
		arr[i] = ft_strdup(tmp->row);
		if (!arr[i])
		{
			while (i-- > 0)
				free(arr[i]);
			free(arr);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	return (arr[i] = NULL, arr);
}

int	get_rgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

double	deg_to_rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

void free_struct(t_cub3d *cub3d)
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
	mlx_destroy_window(cub3d->mlx,cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	if (cub3d->mlx)
		free(cub3d->mlx);
	exit(0);
	return (0);
}
