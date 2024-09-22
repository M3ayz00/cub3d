/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:50:47 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/22 14:17:15 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_textures(t_textures *textures, char **line)
{
	if (!textures->ceiling
		|| !textures->floor
		|| !textures->east
		|| !textures->west
		|| !textures->north
		|| !textures->south)
		return (free(*line), 0);
	return (1);
}

int	texture_processing(char **splitted, char **texture)
{
	if ((*texture))
		return (0);
	if (!check_texture_file(splitted[1], texture))
		return (0);
	return (1);
}

int	color_processing(char **splitted, t_color **color)
{
	if (*color)
		return (0);
	*color = split_color(splitted);
	if (!*color)
		return (0);
	return (1);
}

int	textures_processing(char **splitted, t_textures **textures)
{
	if (!ft_strcmp(splitted[0], "NO"))
		return (texture_processing(splitted, &(*textures)->north));
	else if (!ft_strcmp(splitted[0], "SO"))
		return (texture_processing(splitted, &(*textures)->south));
	else if (!ft_strcmp(splitted[0], "EA"))
		return (texture_processing(splitted, &(*textures)->east));
	else if (!ft_strcmp(splitted[0], "WE"))
		return (texture_processing(splitted, &(*textures)->west));
	return (-1);
}

int	parse_texture(char **line, t_textures **textures, int *counter)
{
	char	**splitted;
	int		status;

	if (!based_split(*line, &splitted))
		return (free(*line), 0);
	if (!is_count_valid(splitted[0], count_rows(splitted)))
		return (free(*line), free_strs(splitted), 0);
	status = process_texture(textures, splitted);
	if (status == 1)
		(*counter)++;
	return (free(*line), free_strs(splitted), status);
}
