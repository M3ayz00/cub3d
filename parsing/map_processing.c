/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:51:55 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/13 16:21:19 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int	check_zeros(t_lst **rows)
{
	t_lst	*curr;
	int i;

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
	char *trimmed;

	trimmed = ft_strtrim(row, "\n\t\f\r\v ");
	if (!trimmed)
		return (0);
	int size = ft_strlen(trimmed);
	if (trimmed[0] != '1' || trimmed[size - 1] != '1')
		return (free(trimmed), 0);
	return (free(trimmed), 1);
}

int	check_each_row(t_lst **rows)
{
	t_lst	*curr;
	int		prev_len;
	int		next_len;
	int		count;

	count = 0;
	curr = (*rows)->next;
	while (curr->next)
	{
		prev_len = 0;
		next_len = 0;
		is_there_player(curr->row, &count);
		if (curr->next)
			next_len = ft_strlen(curr->next->row);
		if (curr->prev)
			prev_len = ft_strlen(curr->prev->row);
		if (!check_row(curr->row, prev_len, next_len))
			return (0);
		curr = curr->next;
	}
	if (count != 1)
		return (0);
	return (1);
}

int	check_row(char *row, int prev_len, int next_len)
{
	int	curr_len;
	int i;

	i = 0;
	curr_len = ft_strlen(row);
	while (row[i] && is_space(row[i]))
		i++;
	while (row[i])
	{
		if (curr_len > prev_len - 2 && i > prev_len - 2)
		{
			if (!is_space(row[i]))
			{
				if (row[i] != '1')
					return (0);
			}
		}
		if (curr_len > next_len - 2 && i > next_len - 2)
		{
			if (!is_space(row[i]))
			{
				if (row[i] != '1')
					return (0);
			}
		}
		i++;
	}
	return (1);
}
