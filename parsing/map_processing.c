/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:51:55 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/19 19:41:17 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_zeros(t_lst **rows)
{
	t_lst	*curr;
	int		i;

	curr = *rows;
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

int	check_first_last_rows(t_lst *rows)
{
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
	while (curr->next)
	{
		tools.prev_len = 0;
		tools.next_len = 0;
		is_there_player(curr->row, &tools.count);
		if (curr->next)
			tools.next_len = ft_strlen(curr->next->row);
		if (curr->prev)
			tools.prev_len = ft_strlen(curr->prev->row);
		if (!check_row(curr->row, tools.prev_len, tools.next_len))
			return (printf("ici ? \n"), 0);
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
