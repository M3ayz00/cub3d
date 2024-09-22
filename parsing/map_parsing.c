/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:06:49 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/22 18:25:59 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_longest_line(t_lst *rows)
{
	int	max_size;

	max_size = ft_strlen(rows->row);
	while (rows)
	{
		if (ft_strlen(rows->row) > max_size)
			max_size = ft_strlen(rows->row);
		rows = rows->next;
	}
	return (max_size);
}

int	parse_map(t_lst **rows, t_cub3d *cub3d, int is_bonus)
{
	int		count;
	int		before;
	t_lst	*curr;

	curr = *rows;
	before = 0;
	count = 0;
	if (!is_map_valid(rows))
		return (0);
	if (!check_first_last_rows(*rows))
		return (0);
	if (!check_each_row(rows))
		return (0);
	if (!check_zeros(rows, is_bonus))
		return (0);
	set_width_and_height(rows, cub3d);
	return (1);
}

int	is_map_valid(t_lst **rows)
{
	t_lst	*curr;

	curr = *rows;
	while (curr)
	{
		if (is_it_all_spaces(curr->row))
		{
			ft_lst_remove(rows, curr);
			curr = *rows;
		}
		else
			break ;
	}
	while (curr)
	{
		if (!check_sides(curr->row) || is_it_all_spaces(curr->row))
			break ;
		curr = curr->next;
	}
	validating_and_cleaning(rows, curr);
	return (1);
}

int	check_line(char **line, t_cub3d *cub3d, int *i)
{
	if (is_identifier(*line) == 1)
	{
		if (!parse_texture(line, &cub3d->textures, i))
			return (free(*line), free(cub3d->container), free_map(&cub3d->map), free_textures(&cub3d->textures), 0);
	}
	else if (is_identifier(*line) == -1)
		return (free(cub3d->container), free(*line), free_map(&cub3d->map), free_textures(&cub3d->textures), 0);
	else
		free(*line);
	return (1);
}

int	parse_cub3d(t_cub3d *cub3d, char *path, int is_bonus)
{
	int	fd;

	fd = open_file(path);
	if (fd == -1)
		return (0);
	if (!process_map_and_textures(fd, cub3d, is_bonus))
		return (close(fd), 0);
	if (!check_files(cub3d))
		return (close(fd), free_map(&cub3d->map), free_textures(&cub3d->textures), 0);
	return (close(fd), 1);
}
