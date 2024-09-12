/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:47:37 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/13 16:04:41 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_textures(t_textures **textures)
{
	(*textures)->floor = NULL;
	(*textures)->ceiling = NULL;
	(*textures)->north = NULL;
	(*textures)->south = NULL;
	(*textures)->east = NULL;
	(*textures)->west = NULL;
}

void	init_map(t_map2 **map)
{
	(*map)->rows = NULL;
	(*map)->width = -1;
	(*map)->height = -1;
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
	{
		free(strs[i]);
		i++;
	}
	strs = NULL;
	free(strs);
}

void	free_textures(t_textures **textures)
{
	if ((*textures)->ceiling)
	{
		(*textures)->ceiling = NULL;
		free((*textures)->ceiling);
	}
	if ((*textures)->floor)
	{
		(*textures)->floor = NULL;
		free((*textures)->floor);
	}
	if ((*textures)->north)
	{
		(*textures)->north = NULL;
		free((*textures)->north);
	}
	if ((*textures)->south)
	{
		(*textures)->south = NULL;
		free((*textures)->south);
	}
	if ((*textures)->west)
	{
		(*textures)->west = NULL;
		free((*textures)->west);
	}
	if ((*textures)->east)
	{
		(*textures)->east = NULL;
		free((*textures)->east);
	}
	(*textures) = NULL;
	free((*textures));
}

void	free_map(t_map2 **map)
{
	if ((*map)->rows)
		ft_lstclear(&(*map)->rows);
	free((*map));
}
