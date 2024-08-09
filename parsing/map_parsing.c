/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:06:49 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/09 18:38:25 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void	*new;

    new = malloc(new_size);
    if (!new)
        return (NULL);
    if (ptr)
    {
        ft_memcpy(new, ptr, old_size);
        free(ptr);
    }
    return (new);
}

int	is_color(char *element)
{
	return (!ft_strcmp(element, "F")
		|| !ft_strcmp(element, "C"));
}

int	is_texture(char *element)
{
	return  (!ft_strcmp(element, "NO")
		|| !ft_strcmp(element, "SO")
		|| !ft_strcmp(element, "EA")
		|| !ft_strcmp(element, "WE"));
}

int	is_identifier(char *line)
{
	char	**splitted;

	splitted = ft_split(line, "\n\t\v\r ");
	if (!splitted)
		return (0);
	if (is_color(splitted[0])
		|| is_texture(splitted[0]))
		return (free_strs(splitted), 1);
	else if (ft_strlen(splitted[0]) > 0)
		return (free_strs(splitted), -1);
	return (free_strs(splitted), 0);
}

char	*ft_strdup(char *str)
{
	char	*new_str;

	new_str = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str, ft_strlen(str));
	return (new_str);
}

void   full_realloc(char **map, char *element, int *len)
{
    map = (char **)ft_realloc(map, sizeof(char *) * (*len) ,sizeof(char *) * (*len) + 2);
	if (!map)
		return ;
	map[(*len)++] = ft_strdup(element);
    map[(*len)] = NULL;
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
		result = (result * 10)+ str[i] - '0';
		i++;
		if (result > 255)
			return (-1);
	}
	if (str[i] && !(is_digit(str[i]) || is_space(str[i])))
		return (-1);
	return (result);
}

t_color	*split_color(char **color)
{
	char 	**colors;
	char	*trimmed1;
	char	*trimmed2;
	char	*trimmed3;
	t_color	*actual_col;

	actual_col = (t_color *)malloc(sizeof(t_color));
	if (!actual_col)
		return (NULL);
	if(count_rows(color) == 2)
	{
		colors = ft_split(color[1], ",");
		if (!colors)
			return (NULL);
		if (count_rows(colors) != 3)
			return (free_strs(colors), NULL);
		actual_col->r = ft_atoi(colors[0]);
		actual_col->g = ft_atoi(colors[1]);
		actual_col->b = ft_atoi(colors[2]);
		if (actual_col->r == -1
			|| actual_col->g == -1
			|| actual_col->b == -1)
			return (free_strs(colors), free(actual_col), NULL);
	}
	else if (count_rows(color) == 4)
	{
		trimmed1 = ft_strtrim(color[1], ", \t\n\r\v");
		if (!trimmed1)
			return (free(actual_col), NULL);
		trimmed2 = ft_strtrim(color[2], ", \t\n\r\v");
		if (!trimmed1)
			return (free(trimmed1), free(actual_col), NULL);
		trimmed3 = ft_strtrim(color[3], ", \t\n\r\v");
			return (free(trimmed1), free(trimmed2), free(actual_col), NULL);
		actual_col->r = ft_atoi(trimmed1);
		actual_col->g = ft_atoi(trimmed2);
		actual_col->b = ft_atoi(trimmed3);
		free(trimmed1);
		free(trimmed2);
		free(trimmed3);
		if (actual_col->r == -1
			|| actual_col->g == -1
			|| actual_col->b == -1)
			return (free_strs(colors), free(actual_col), NULL);
	}
	return (free_strs(colors), actual_col);
}

int	process_texture(t_textures **textures, char **splitted)
{
	if (!ft_strcmp(splitted[0], "NO"))
	{
		if ((*textures)->north)
			return (0);
		(*textures)->north = splitted[1];
	}
	else if (!ft_strcmp(splitted[0], "SO"))
	{
		if ((*textures)->south)
			return (0);
		(*textures)->south = splitted[1];
	}
	else if (!ft_strcmp(splitted[0], "EA"))
	{
		if ((*textures)->east)
			return (0);
		(*textures)->east = splitted[1];
	}
	else if (!ft_strcmp(splitted[0], "WE"))
	{
		if ((*textures)->west)
			return (0);
		(*textures)->west = splitted[1];
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

int	is_count_valid(char *identifier, int rows)
{
	if (is_texture(identifier))
		return (rows == 2);
	if (is_color(identifier))
		return (rows == 2 || rows == 4);
	return (0);
}

int	parse_texture(char **line, t_textures **textures, int *counter)
{
	char	**splitted;
	int		status;

	splitted = ft_split(*line, "\t\v\r\n ");
	printf("%s, %s\n", splitted[0], splitted[1]);
	if (!is_count_valid(splitted[0], count_rows(splitted)))
	{
		free(*line);
		free_strs(splitted);
		return (0);
	}
	status = process_texture(textures, splitted);
	if (status == 1)
		(*counter)++;
	return (free(*line), free_strs(splitted), status);
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
	// printf("HELLO : %s\n", trimmed);
	if (trimmed[0] == '1')
		full_realloc((*map)->map, trimmed, i);
	else
		free(trimmed);
	free(*line);
}

int	parse_map(char ***map)
{
	//map_parsing
}
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

void	free_textures(t_textures *textures)
{
	if (textures->ceiling)
	{
		textures->ceiling = NULL;
		free(textures->ceiling);
	}
	if (textures->floor)
	{
		textures->floor = NULL;
		free(textures->floor);
	}
	if (textures->north)
	{
		textures->north = NULL;
		free(textures->north);
	}
	if (textures->south)
	{
		textures->south = NULL;
		free(textures->south);
	}
	if (textures->west)
	{
		textures->west = NULL;
		free(textures->west);
	}
	if (textures->east)
	{
		textures->east = NULL;
		free(textures->east);
	}
	textures = NULL;
	free(textures);
}

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
	(*map)->map = NULL;
	(*map)->width = -1;
	(*map)->height = -1;
}
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
		return (free_textures(textures), 0);
	init_map(&map);
	line = get_next_line(fd);
	while (line && i < 6)
	{
		if (is_identifier(line) == 1)
		{
			if (!parse_texture(&line, &textures, &i))
				return (free(map), free_textures(textures), 0);
		}
		else if (is_identifier(line) == -1)
			return (free(map), free_textures(textures), 0);
		else
			free(line);
		line = get_next_line(fd);
	}
	if (!check_textures(textures))
		return (free(map) ,free_textures(textures), 0);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		fill_map(&map, &line, &i);
		line = get_next_line(fd);
	}
	// parse_map(&map->map);
	cub3d->textures = textures;
	cub3d->map2 = map;
	return (1);
}



int	parse_data(t_cub3d *cub3d ,char *path)
{
	int		fd;

	fd = open_file(path);
	if (fd == -1)
		return (0);
	if (process_map_and_textures(fd, cub3d))
		return (close(fd), 1);
	return (close(fd), 0);
}
int main(int ac, char **av)
{
	t_cub3d	cub3d;

	if (ac == 2)
	{
		if (!parse_data(&cub3d, av[1]))
			write(2, "error\n", 6);

	}
}
