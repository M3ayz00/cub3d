/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texture_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:54:48 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/19 20:08:16 by msaadidi         ###   ########.fr       */
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
	(*textures)->door = NULL;
}

void	init_map(t_map2 **map)
{
	(*map)->rows = NULL;
	(*map)->width = -1;
	(*map)->height = -1;
}

int	init_map_and_textures(t_textures **textures, t_map2 **map)
{
	(*textures) = (t_textures *)malloc(sizeof(t_textures));
	if (!(*textures))
		return (0);
	init_textures(textures);
	(*map) = (t_map2 *)malloc(sizeof(t_map2));
	if (!(*map))
		return (free_textures(textures), 0);
	init_map(map);
	return (1);
}

int	check_door_texture(char **line, t_textures **textures, int *i, int fd)
{
	while (*line)
	{
		if (is_identifier((*line)) == 1)
		{
			if (!parse_texture(&(*line), textures, i))
				return (0);
		}
		else if (!is_identifier((*line)))
			free((*line));
		else
			return (1);
		(*line) = get_next_line(fd);
	}
	return (0);
}

int	process_map_and_textures(int fd, t_cub3d *cub3d, int nb_textures)
{
	int			i;
	char		*line;

	i = 0;
	if (!init_map_and_textures(&cub3d->textures, &cub3d->map2))
		return (0);
	line = get_next_line(fd);
	while (line && i < 6)
	{
		if (!check_line(&line, &cub3d->textures, &cub3d->map2, &i))
			return (0);
		line = get_next_line(fd);
	}
	if (nb_textures == 7
		&& !check_door_texture(&line, &cub3d->textures, &i, fd))
		return (free_map(&cub3d->map2), free_textures(&cub3d->textures), 0);
	if (!check_textures(cub3d->textures, nb_textures))
		return (free_map(&cub3d->map2), free_textures(&cub3d->textures), 0);
	if (!add_map_lines(&line, &cub3d->textures, &cub3d->map2, fd))
		return (0);
	if (!parse_map(&cub3d->map2->rows, cub3d))
		return (free_map(&cub3d->map2), free_textures(&cub3d->textures), 0);
	return (1);
}
