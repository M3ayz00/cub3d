/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:06:49 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/17 21:43:06 by msaadidi         ###   ########.fr       */
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
		|| !ft_strcmp(element, "WE")
		|| !ft_strcmp(element, "D"));
}

int	is_identifier(char *line)
{
	char	**splitted;

	splitted = ft_split(line, "\f\n\t\v\r ");
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
	return (c == 'N' || c == 'W' || c == 'S'
		|| c == 'E');
}

int	is_plane(char c)
{
		return (c == '0' || c == '1' || c == 'D');
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
int   add_map_line(t_map2 **map, char *element)
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

int	check_texture_file(char *file, char **texture)
{
	if (ft_strcmp(file + ft_strlen(file) - 4, ".xpm"))
		return (0);
	(*texture) = ft_strdup(file);
	return (1);
}

int	process_texture(t_textures **textures, char **splitted)
{
	if (!ft_strcmp(splitted[0], "NO"))
	{
		if ((*textures)->north)
			return (0);
		if (!check_texture_file(splitted[1], &(*textures)->north))
			return (0);
	}
	else if (!ft_strcmp(splitted[0], "SO"))
	{
		if ((*textures)->south)
			return (0);
		if (!check_texture_file(splitted[1], &(*textures)->south))
			return (0);
	}
	else if (!ft_strcmp(splitted[0], "EA"))
	{
		if ((*textures)->east)
			return (0);
		if (!check_texture_file(splitted[1], &(*textures)->east))
			return (0);
	}
	else if (!ft_strcmp(splitted[0], "WE"))
	{
		if ((*textures)->west)
			return (0);
		if (!check_texture_file(splitted[1], &(*textures)->west))
			return (0);
	}
	else if (!ft_strcmp(splitted[0], "D"))
	{
		if ((*textures)->door)
			return (0);
		if (!check_texture_file(splitted[1], &(*textures)->door))
			return (0);
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
	(*splitted) = ft_split(line, "\f\t\v\r\n ");
	if (is_color((*splitted)[0]))
	{
		if (count_commas(line) != 2)
			return (0);
		free_strs(*splitted);
		*splitted = ft_split(line, "\f\t\v\r\n ,");
	}
	return (1);
}
int	parse_texture(char **line, t_textures **textures, int *counter)
{
	char	**splitted;
	int		status;

	if (!based_split(*line, &splitted))
		return (free(*line), free_strs(splitted),0);
	if (!is_count_valid(splitted[0], count_rows(splitted)))
		return (free(*line), free_strs(splitted), 0);
	status = process_texture(textures, splitted);
	if (status == 1)
		(*counter)++;
	return (free(*line), free_strs(splitted), status);
}

int	is_plane_or_player(char c)
{
	return (is_plane(c) || is_player(c));
}

int	is_valid_zero(t_lst *row, int i)
{
	if ((i > 0 && !is_plane_or_player(row->row[i - 1]))
		|| (row->row[i + 1] && !is_plane_or_player(row->row[i + 1])))
		return (0);
	if (row->prev)
	{
		if ((row->prev->row[i] && !is_plane_or_player(row->prev->row[i])))
			return (0);
	}
	if (row->next)
	{
		if ((row->next->row[i] && !is_plane_or_player(row->next->row[i])))
			return (0);
	}
	return (1);
}

int	check_zeros(t_lst **rows)
{
	t_lst	*curr = *rows;
	int i;

	while (curr)
	{
		i = 0;
		while (curr->row[i])
		{
			if (curr->row[i] == '0')
			{
				if (!is_valid_zero(curr, i))
					return (0);
			}
			i++;
		}
		curr = curr->next;
	}
	return (1);
}

void	is_there_player(char *row, int *count)
{
	int i = 0;
	while (row[i])
	{
		if (is_player(row[i]))
			(*count)++;
		i++;
	}
}

int	is_it_all_spaces(char *row)
{
	int i = 0;

	while (row[i] && is_space(row[i]))
		i++;
	if (!row[i])
		return (1);
	return (0);
}



int	is_it_all_ones(char *row)
{
	int i = 0;
	int	ones_count = 0;

	while (row && row[i])
	{
		if (!is_space(row[i]))
		{
			if (row[i] == '1')
				ones_count++;
			else
				return (0);
		}
		i++;
	}
	if (!ones_count)
		return (0);
	return (1);
}

int	check_first_last_rows(t_lst *rows)
{
	if (!is_it_all_ones(rows->row)
		|| !is_it_all_ones(ft_lstlast(rows)->row))
		return (0);
	return (1);
}

int	check_sides(char *row)
{
	char *trimmed = ft_strtrim(row, "\n\t\f\r\v ");
	if (!trimmed)
		return (0);
	int size = ft_strlen(trimmed);
	if (trimmed[0] != '1' || trimmed[size - 1] != '1')
		return (free(trimmed), 0);
	return (free(trimmed), 1);
}

int	is_map_valid(t_lst **rows)
{
	t_lst	*curr;
	t_lst	*checkpoint;
	curr = *rows;
	while (curr)
	{
		if (!is_it_all_spaces(curr->row))
			break ;
		else
		{
			ft_lst_remove(rows, curr);
			curr = *rows;
		}
	}
	while (curr)
	{
		if (!check_sides(curr->row) || is_it_all_spaces(curr->row))
			break ;
		curr = curr->next;
	}
	checkpoint = ft_lst_before(*rows, curr);
	while (curr)
	{
		if (!is_it_all_spaces(curr->row))
			return (0);
		else
		{
			ft_lst_remove(rows, curr);
			curr = checkpoint->next;
		}
	}
	return (1);
}

int	is_space2(char c)
{
	return (c == ' ' || c == '\t' || c == '\f'
		|| c == '\r' || c == '\v');
}

int	check_row(char *row, int prev_len, int next_len)
{
	int	curr_len = ft_strlen(row);
	int i = 0;
	while (row[i] && is_space(row[i]))
		i++;
	while (row[i])
	{
		if (curr_len > prev_len - 2 && i > prev_len - 2)
		{
			if (!is_space(row[i]))
			{
				if (row[i] != '1')
				{
					printf("PREV\n");
					printf("ROW[%d] : %c\n", i, row[i]);
					return (0);
				}
			}
		}
		if (curr_len > next_len - 2 && i > next_len - 2)
		{
			if (!is_space(row[i]))
			{
				if (row[i] != '1')
				{
					printf("NEXT\n");
					printf("ROW[%d] : %c\n", i, row[i]);
					return (0);
				}
			}
		}
		i++;
	}
	return (1);
}

int	check_each_row(t_lst **rows)
{
	t_lst	*curr = (*rows)->next;
	int		prev_len;
	int		next_len;
	int		count = 0;
	int		rowc = 0;

	while (curr->next)
	{
		prev_len = 0;
		next_len = 0;
		is_there_player(curr->row, &count);
		if (curr->next)
			next_len = ft_strlen(curr->next->row);
		if (curr->prev)
			prev_len = ft_strlen(curr->prev->row);
		printf("ROW NUMBER : %d\n", rowc);
		if (!check_row(curr->row, prev_len, next_len))
			return (0);
		curr = curr->next;
		rowc++;
	}
	if (count != 1)
		return (0);
	return (1);
}

int	get_longest_line(t_lst *rows)
{
	int max_size = ft_strlen(rows->row);
	while (rows)
	{
		if (ft_strlen(rows->row) > max_size)
			max_size = ft_strlen(rows->row);
		rows = rows->next;
	}
	return (max_size);
}

int	parse_map(t_lst **rows, t_cub3d *cub3d)
{
	int		count = 0;
	int		before = 0;
	t_lst	*curr = *rows;

	if (!is_map_valid(rows))
		return (0);
	if (!check_first_last_rows(*rows))
		return (0);
	if (!check_each_row(rows))
		return (0);
	if (!check_zeros(rows))
		return (0);
	// cub3d->map2->height = ft_lstsize(*rows);
	// cub3d->map2->width = get_longest_line(*rows);
	return (1);

}
int	check_textures(t_textures *textures)
{
	if ((!textures->ceiling
		|| !textures->floor
		|| !textures->east
		|| !textures->west
		|| !textures->north
		|| !textures->south))
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
	if ((*textures)->door)
	{
		(*textures)->door = NULL;
		free((*textures)->door);
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
	(*textures)->door = NULL;
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
	printf("-------------UNPARSED MAP----------\n");
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
	if (nb_textures == 7 && !check_door_texture(&line, &textures, &i, fd))
		return (free_map(&map), free_textures(&textures), 0);
	if (!check_textures(textures))
		return (free_map(&map) ,free_textures(&textures), 0);
	// print_textures(textures);
	// line = get_next_line(fd);
	while (line)
	{
		if (!add_map_line(&map, line))
			return (free(line), free_textures(&textures), free_map(&map), 0);
		// printf("OOOF : %s\n", map->rows->row);
		free(line);
		line = get_next_line(fd);
	}
	// print_map(map->rows);
	if (!parse_map(&map->rows, cub3d))
		return (free_map(&map), free_textures(&textures), 0);
	// print_map(map->rows);
	cub3d->textures = textures;
	cub3d->map2 = map;
	return (1);
}



int	parse_data(t_cub3d *cub3d ,char *path, int nb_textures)
{
	int		fd;

	fd = open_file(path);
	if (fd == -1)
		return (0);
	if (process_map_and_textures(fd, cub3d, nb_textures))
		return (close(fd), 1);
	return (close(fd), 0);
}
