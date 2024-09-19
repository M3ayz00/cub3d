/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:50:47 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/19 16:57:55 by msaadidi         ###   ########.fr       */
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
		|| !textures->south
		|| !textures->door)
		return (0);
	return (1);
}

int	texture_processing(char **splitted, char **texture, char *test)
{
	if (!ft_strcmp(splitted[0], test))
	{
		if ((*texture))
			return (0);
		if (!check_texture_file(splitted[1], texture))
			return (0);
	}
	return (1);
}

int	color_processing(char **splitted, t_color **color, char *test)
{
	if (!ft_strcmp(splitted[0], test))
	{
		if (*color)
			return (0);
		*color = split_color(splitted);
		if (!*color)
			return (0);
	}
	return (1);
}

int	process_texture(t_textures **textures, char **splitted)
{
	if (!texture_processing(splitted, &(*textures)->north, "NO"))
		return (0);
	else if (!texture_processing(splitted, &(*textures)->south, "SO"))
		return (0);
	else if (!texture_processing(splitted, &(*textures)->east, "EA"))
		return (0);
	else if (!texture_processing(splitted, &(*textures)->west, "WE"))
		return (0);
	else if (!texture_processing(splitted, &(*textures)->door, "D"))
		return (0);
	else if (!color_processing(splitted, &(*textures)->floor, "F"))
		return (0);
	else if (!color_processing(splitted, &(*textures)->ceiling, "C"))
		return (0);
	else if (ft_strlen(splitted[0]) > 0)
		return (0);
	return (1);
}

int	parse_texture(char **line, t_textures **textures, int *counter)
{
	char	**splitted;
	int		status;

	if (!based_split(*line, &splitted))
		return (free(*line), free_strs(splitted), 0);
	if (!is_count_valid(splitted[0], count_rows(splitted)))
		return (free(*line), free_strs(splitted), 0);
	status = process_texture(textures, splitted);
	if (status == 1)
		(*counter)++;
	return (free(*line), free_strs(splitted), status);
}
