/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:47:37 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/22 16:27:40 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_map(t_map **map)
{
	if ((*map)->rows)
		ft_lstclear(&(*map)->rows);
	free((*map));
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
	free(strs);
	strs = NULL;
}

void	free_textures2(t_textures **textures)
{
	if ((*textures)->ceiling)
	{
		free((*textures)->ceiling);
		(*textures)->ceiling = NULL;
	}
	if ((*textures)->floor)
	{
		free((*textures)->floor);
		(*textures)->floor = NULL;
	}
	if ((*textures)->north)
	{
		free((*textures)->north);
		(*textures)->north = NULL;
	}
	if ((*textures)->south)
	{
		free((*textures)->south);
		(*textures)->south = NULL;
	}
}

void	free_textures(t_textures **textures)
{
	free_textures2(textures);
	if ((*textures)->west)
	{
		free((*textures)->west);
		(*textures)->west = NULL;
	}
	if ((*textures)->east)
	{
		free((*textures)->east);
		(*textures)->east = NULL;
	}
	if ((*textures)->door)
	{
		free((*textures)->door);
		(*textures)->door = NULL;
	}
	free((*textures));
	(*textures) = NULL;
}
