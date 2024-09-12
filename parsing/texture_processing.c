/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:50:47 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/13 16:27:47 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_textures(t_textures *textures)
{
	if (!textures->ceiling
		|| !textures->floor
		|| !textures->east
		|| !textures->west
		|| !textures->north
		|| !textures->south)
		return (0);
	return (1);
}

int	process_texture(t_textures **textures, char **splitted)
{
	if (!ft_strcmp(splitted[0], "NO"))
	{
		if ((*textures)->north)
			return (0);
		(*textures)->north = ft_strdup(splitted[1]);
	}
	else if (!ft_strcmp(splitted[0], "SO"))
	{
		if ((*textures)->south)
			return (0);
		(*textures)->south = ft_strdup(splitted[1]);
	}
	else if (!ft_strcmp(splitted[0], "EA"))
	{
		if ((*textures)->east)
			return (0);
		(*textures)->east = ft_strdup(splitted[1]);
	}
	else if (!ft_strcmp(splitted[0], "WE"))
	{
		if ((*textures)->west)
			return (0);
		(*textures)->west = ft_strdup(splitted[1]);
	}
	else if (!ft_strcmp(splitted[0], "F"))
	{
		if ((*textures)->floor)
			return (0);
		(*textures)->floor = split_color(splitted);
		if (!(*textures)->floor)
			return (0);
	}
	else if (!ft_strcmp(splitted[0], "C"))
	{
		if ((*textures)->ceiling)
			return (0);
		(*textures)->ceiling = split_color(splitted);
		if (!(*textures)->ceiling)
			return (0);
	}
	else if (ft_strlen(splitted[0]) > 0)
		return (0);
	return (1);
}



int	parse_texture(char **line, t_textures **textures, int *counter)
{
	char	**splitted;
	int		status;

	if (!based_split(*line, &splitted))
		return (0);
	if (!is_count_valid(splitted[0], count_rows(splitted)))
		return (free_strs(splitted), 0);
	status = process_texture(textures, splitted);
	if (status == 1)
		(*counter)++;
	return (free_strs(splitted), status);
}
