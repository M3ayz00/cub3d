/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:58:39 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/20 21:53:53 by msaadidi         ###   ########.fr       */
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

int	ft_exit(t_cub3d *cub3d)
{
	free_map(&cub3d->map2);
	free_textures(&cub3d->textures);
	exit(0);
	return (0);
}
