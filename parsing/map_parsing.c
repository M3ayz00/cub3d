/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:06:49 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/08 21:03:40 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new;

    new = (void *)malloc(new_size);
    if (!new)
        return (NULL);
    if (ptr)
    {
        ft_memcpy(new, ptr, old_size);
        free(ptr);
    }
    return (new);
}

void   full_realloc(char **map, char *element, int *len)
{
    map = ft_realloc(map, sizeof(char *) * (*len) + 2);
	if (!map)
		return ;
    map[(*len)++] = element;
    map[(*len)] = NULL;
	(*len)++;
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

int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N'
		|| c == 'E' || c == 'W' || c == 'S');
}

int	count_rows(char **map)
{
	int i = 0;
	while (map && map[i])
		i++;
	return (i);
}

int	is_space(char c)
{
	return (c >= 9 && c <= 13);
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *str)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	if (!str)
		return (-1);
	while (is_space(str[i]))
		i++;
	if (str[i] && !is_digit(str[i]))
		return (-1);
	while (str[i] && is_digit(str[i]))
	{
		if (result > 255)
			return (-1);
		result = (result * 10)+ str[i] - '0';
		i++;
		if (str[i] && !is_digit(str[i]))
			return (-1);
	}
	return (result);
}

t_color	split_color(char *color)
{
	char 	**colors;
	t_color	actual_col;

	colors = ft_split(color, ",");
	if (count_rows(colors) != 3)
		return (free_strs(colors), 0);
	actual_col.r = ft_atoi(colors[0]);
	actual_col.g = ft_atoi(colors[1]);
	actual_col.b = ft_atoi(colors[2]);
	if (actual_col.r == -1
		|| actual_col.g == -1
		|| actual_col.b == -1)
		return (free_strs(colors), 0);
	return (free_strs(colors), actual_col);
}

int	process_texture(t_textures **textures, char **splitted)
{
	if (ft_strcmp(splitted[0], "NO"))
		(*textures)->north = splitted[1];
	else if (ft_strcmp(splitted[0], "SO"))
		(*textures)->south = splitted[1];
	else if (ft_strcmp(splitted[0], "EA"))
		(*textures)->east = splitted[1];
	else if (ft_strcmp(splitted[0], "WE"))
		(*textures)->west = splitted[1];
	else if (ft_strcmp(splitted[0], "F"))
	{
		(*textures)->floor = split_color(splitted[1]);
		if (!(*textures)->floor)
			return (0);
	}
	else if (ft_strcmp(splitted[0], "C"))
	{
		(*textures)->ceiling = split_color(splitted[1]);
		if (!(*textures)->ceiling)
			return (0);
	}
	else if (ft_strlen(splitted[0]) > 0)
		return (-1);
	return (1);
}

int	parse_texture(char **line, t_textures **textures, int *counter)
{
	char	**splitted;
	int		process;

	splitted = ft_split(*line, "\t\v\r\n ");
	if (!splitted)
	{
		free(*line);
		return (1);
	}
	process = process_texture(textures, splitted);
	if (process == 1)
	{
		free(*line);
		free_strs(splitted);
		(*counter)++;
		return (1);
	}
	else if (process == -1)
	{
		free(*line);
		free_strs(splitted);
		return (0);
	}
}

void	fill_map(t_map2 **map, char **line, int *i)
{
	char	*trimmed;

	trimmed = ft_strtrim(*line, " \n\t\v\r");
	if (!trimmed)
	{
		free(*line);
		return ;
	}
	full_realloc(map->map, trimmed, i);
	free(*line);
}

int	parse_map(char ***map)
{
	//map_parsing
}

void	process_map_and_textures(int fd, t_cub3d *cub3d)
{
	t_textures	*textures;
	t_map2		*map;
	int			i;
	char		*line;

	i = 0;
	textures = malloc(sizeof(t_textures));
	map = malloc(sizeof(t_map2));
	if (!textures || !map)
		return (NULL);
	while (i < 6)
	{
		line = get_next_line(fd);
		if (!parse_texture(&line, &textures, &i))
			return (free(map), free(textures), NULL);
	}
	if (i != 6)
		return (free(map), free(textures), NULL);
	i = 0;
	while (line)
	{
		line = get_next_line(fd);
		fill_map(&map, &line, &i);
	}
	parse_map(&map);
	cub3d->textures = textures;
	cub3d->map2 = map;
	return (textures);
}



int	parse_data(t_cub3d *cub3d ,char *path)
{
	int		fd;

	fd = open_file(path);
	if (fd == -1)
		return (0);
	if (fillup_data(cub3d, path, fd))
		return (close(fd), 1);
	return (close(fd), 0);
}

