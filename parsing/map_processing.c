/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:51:55 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/24 18:49:46 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	there_is_space(char *row)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (row[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	change_spaces(char **row)
{
	int		i;
	char	*changed;

	i = 0;
	changed = (char *)ft_calloc(ft_strlen((*row)) + 1, sizeof(char));
	if (!changed)
		return ;
	while ((*row)[i])
	{
		changed[i] = (*row)[i];
		if ((*row)[i] == ' ')
			changed[i] = '1';
		i++;
	}
	free((*row));
	(*row) = changed;
}

void	change_spaces_to_1s(t_lst **rows)
{
	t_lst	*curr;

	curr = *rows;
	while (curr)
	{
		if (there_is_space(curr->row))
			change_spaces(&curr->row);
		curr = curr->next;
	}
}

int	check_zeros(t_lst **rows, int is_bonus)
{
	t_lst	*curr;
	int		i;

	change_spaces_to_1s(rows);
	curr = *rows;
	while (curr)
	{
		i = 0;
		while (curr->row[i])
		{
			if (curr->row[i] == '0')
			{
				if (!is_valid_zero(curr, i, is_bonus))
					return (0);
			}
			i++;
		}
		curr = curr->next;
	}
	return (1);
}

int	check_first_last_rows(t_lst *rows)
{
	if (!rows)
		return (0);
	if (!is_it_all_ones(rows->row)
		|| !is_it_all_ones(ft_lstlast(rows)->row))
		return (0);
	return (1);
}

int	check_sides(char *row)
{
	char	*trimmed;
	int		size;

	trimmed = ft_strtrim(row, "\n\t\f\r\v ");
	if (!trimmed)
		return (0);
	size = ft_strlen(trimmed);
	if (trimmed[0] != '1' || trimmed[size - 1] != '1')
		return (free(trimmed), 0);
	return (free(trimmed), 1);
}

int	check_each_row(t_lst **rows)
{
	t_lst		*curr;
	t_checking	tools;

	tools.count = 0;
	curr = (*rows)->next;
	while (curr)
	{
		tools.prev_len = 0;
		tools.next_len = 0;
		is_there_player(curr->row, &tools.count);
		if (curr->next)
			tools.next_len = ft_strlen(curr->next->row);
		if (curr->prev)
			tools.prev_len = ft_strlen(curr->prev->row);
		if (!check_row(curr->row, tools.prev_len, tools.next_len))
			return (0);
		curr = curr->next;
		tools.rowc++;
	}
	if (tools.count != 1)
		return (0);
	return (1);
}

int	check_row(char *row, int prev_len, int next_len)
{
	int	curr_len;
	int	i;

	i = 0;
	curr_len = ft_strlen(row);
	while (row[i] && is_space(row[i]))
		i++;
	while (row[i])
	{
		if (!check_adjacent(curr_len, prev_len, row[i], i))
			return (0);
		if (!check_adjacent(curr_len, next_len, row[i], i))
			return (0);
		i++;
	}
	return (1);
}
