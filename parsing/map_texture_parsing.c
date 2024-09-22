/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texture_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:54:48 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/22 18:28:08 by msaadidi         ###   ########.fr       */
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

void	init_map(t_map **map)
{
	(*map)->rows = NULL;
	(*map)->width = -1;
	(*map)->height = -1;
}

int	init_map_and_textures(t_textures **textures, t_map **map)
{
	(*textures) = (t_textures *)malloc(sizeof(t_textures));
	if (!(*textures))
		return (0);
	init_textures(textures);
	(*map) = (t_map *)malloc(sizeof(t_map));
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
		(*line) = get_next_line(fd, NULL);
	}
	return (0);
}

char	**read_whole_file(int fd, t_cub3d *cub3d)
{
	char	*line;
	char	*long_line;
	char	**file;

	long_line = NULL;
	line = get_next_line(fd, &cub3d->container);
	while (line)
	{
		long_line = ft_strjoin2(long_line, line);
		free(line);
		line = get_next_line(fd, &cub3d->container);
	}
	file = ft_split(long_line, "\n");
	if (!file)
		return (NULL);
	return (file);
}

int	process_map_and_textures(int fd, t_cub3d *cub3d, int is_bonus)
{
	int			i;
	char		*line;

	i = 0;
	if (!init_map_and_textures(&cub3d->textures, &cub3d->map))
		return (0);
	line = get_next_line(fd, &cub3d->container);
	while (line && i < 6)
	{
		if (!check_line(&line, cub3d, &i))
			return (0);
		line = get_next_line(fd, &cub3d->container);
	}
	if (!check_textures(cub3d->textures, &line))
		return (free(cub3d->container),free_map(&cub3d->map), free_textures(&cub3d->textures), 0);
	printf("HNA\n");
	if (!add_map_lines(&line, &cub3d, fd, is_bonus))
		return (free(cub3d->container),0);
	if (!parse_map(&cub3d->map->rows, cub3d, is_bonus))
		return (free(cub3d->container),free_map(&cub3d->map), free_textures(&cub3d->textures), 0);
	return (1);
}
