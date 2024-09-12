/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texture_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:54:48 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/13 16:37:00 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	process_map_and_textures(int fd, t_cub3d *cub3d)
{
	t_textures	*textures;
	t_map2		*map;
	int			i;
	char		*line;

	i = 0;
	textures = (t_textures *)malloc(sizeof(t_textures));
	if (!textures)
		return (0);
	init_textures(&textures);
	map = (t_map2 *)malloc(sizeof(t_map2));
	if (!map)
		return (free_textures(&textures), 0);
	init_map(&map);
	line = get_next_line(fd);
	while (line && i < 6)
	{
		if (is_identifier(line) == 1)
		{
			if (!parse_texture(&line, &textures, &i))
				return (free_map(&map), free_textures(&textures), free(line), 0);
		}
		else if (is_identifier(line) == -1)
			return (free_map(&map), free_textures(&textures), free(line), 0);
		else
			free(line);
		line = get_next_line(fd);
	}
	if (!check_textures(textures))
		return (free_map(&map) ,free_textures(&textures), 0);
	print_textures(textures);
	line = get_next_line(fd);
	while (line)
	{
		if (!add_map_line(&map, line))
			return (free(line), free_textures(&textures), free_map(&map), 0);
		free(line);
		line = get_next_line(fd);
	}
	print_map(map->rows);
	if (!parse_map(&map->rows))
		return (free_map(&map), free_textures(&textures), 0);
	print_map(map->rows);
	free_textures(&textures);
	free_map(&map);
	// cub3d->textures = textures;
	// cub3d->map2 = map;
	return (1);
}
