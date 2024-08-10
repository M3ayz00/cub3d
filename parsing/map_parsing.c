/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:06:49 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/10 18:15:48 by msaadidi         ###   ########.fr       */
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


int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
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

int	is_player(char c)
{
	return (c == 'N' || c == 'W' || c == 'N'
		|| c == 'E');
}

int	is_plane(char c)
{
	return (c == '0' || c == '1');
}


int	is_valid_char(char c)
{
	return (is_plane(c) || is_player(c) || is_space(c));
}

int	is_valid_elem(char *element)
{
	int i = 0;
	if (!element)
		return (0);
	while (element[i] && element[i] != '\n')
	{
		if (!is_valid_char(element[i]))
			return (0);
		i++;
	}
	return (1);
}
int   full_realloc(t_map2 **map, char *element)
{
	if (!is_valid_elem(element))
		return (0);
	ft_lstadd_back(&(*map)->rows, lst_new(element));
	return (1);
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


int	count_rows(char **map)
{
	int i = 0;
	while (map && map[i])
		i++;
	return (i);
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

t_color	*get_color(t_color **actual_color, char ***colors, char *color)
{
	(*actual_color)->r = ft_atoi((*colors)[1]);
	(*actual_color)->g = ft_atoi((*colors)[2]);
	(*actual_color)->b = ft_atoi((*colors)[3]);
	if ((*actual_color)->r == -1
		|| (*actual_color)->g == -1
		|| (*actual_color)->b == -1)
		return (free((*actual_color)), NULL);
	return ((*actual_color));
}

t_color	*split_color(char **color)
{
	char 	**colors;
	int		size;
	t_color	*actual_col;

	size = count_rows(color);
	actual_col = (t_color *)malloc(sizeof(t_color));
	if (!actual_col)
		return (NULL);
	if(size == 4)
		return (get_color(&actual_col, &color, color[1]));
	return (actual_col);
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

int	is_count_valid(char *identifier, int rows)
{
	if (is_texture(identifier))
		return (rows == 2);
	if (is_color(identifier))
		return (rows == 2 || rows == 4);
	return (0);
}

int	count_commas(char *str)
{
	int i = 0;
	int count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}
int	based_split(char *line, char ***splitted)
{
	(*splitted) = ft_split(line, "\t\v\r\n ");
	if (is_color((*splitted)[0]))
	{
		if (count_commas(line) != 2)
			return (free_strs(*splitted), 0);
		free_strs(*splitted);
		*splitted = ft_split(line, "\t\v\r\n ,");
	}
	return (1);
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

int	check_row(char *row, int *count)
{
	char	*trimmed;
	int		size;

	trimmed = ft_strtrim(row, " \t\n\v\r");
	if (!trimmed)
		return (1);
	size = ft_strlen(row);
	if (trimmed[0] != '1' && trimmed[size - 1] != '1')
		return (0);
	// int i = 0;
	// while (row[i] && is_space(row[i]))
	// 	i++;
	// if (row[i] && row[i] != '1')
	// 	return (0);
	// // printf("ROW : %s\n", row);
	// while (row[i])
	// {
	// 	if (row[i] && is_player(row[i]))
	// 		*count++;
	// 	i++;
	// }
	// if (!is_space(row[i - 1]) && row[i - 1] != '1')
	// 	return (0);
	return (1);
}

int	parse_map(t_lst *rows)
{
	int	count = 0;
	t_lst	*curr = rows;
	while (curr)
	{
		if (!check_row(curr->row, &count))
			return (0);
		curr = curr->next;
	}
	return (1);
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

void	print_textures(t_textures *textures)
{
	printf("C => R : %d, G : %d, B : %d\n", textures->ceiling->r, textures->ceiling->g, textures->ceiling->b);
	printf("F => R : %d, G : %d, B : %d\n", textures->floor->r, textures->floor->g, textures->floor->b);
	printf("NO => %s\n", textures->north);
	printf("SO => %s\n", textures->south);
	printf("EA => %s\n", textures->east);
	printf("WE => %s\n", textures->west);
}

void	print_map(t_lst *lst)
{
	printf("\n-------------UNPARSED MAP----------\n");
	t_lst	*current = lst;
	while (current)
	{
		printf("%s", current->row);
		current = current->next;
	}
	printf("\n-------------UNPARSED MAP----------\n");
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
		return (free_textures(&textures), 0);
	init_map(&map);
	line = get_next_line(fd);
	while (line && i < 6)
	{
		if (is_identifier(line) == 1)
		{
			if (!parse_texture(&line, &textures, &i))
				return (free_map(&map), free_textures(&textures), 0);
		}
		else if (is_identifier(line) == -1)
			return (free_map(&map), free_textures(&textures), 0);
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
		if (!full_realloc(&map, line))
			return (free(line), free_textures(&textures), free_map(&map), 0);
		free(line);
		line = get_next_line(fd);
	}
	print_map(map->rows);
	if (!parse_map(map->rows))
		return (free_map(&map), free_textures(&textures), 0);
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
