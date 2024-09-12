/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:45:43 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/13 16:24:08 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_count_valid(char *identifier, int rows)
{
	if (is_texture(identifier))
		return (rows == 2);
	if (is_color(identifier))
		return (rows == 2 || rows == 4);
	return (0);
}

int is_valid_zero(t_lst *row, int i)
{
	if ((i > 0 && !is_one_or_player(row->row[i - 1]))
		|| (row->row[i + 1]
		&& !is_one_or_player(row->row[i + 1])))
		return (0);
	if (row->prev)
	{
		if ((row->prev->row[i]
			&& !is_one_or_player(row->prev->row[i])))
			return (0);
	}
	if (row->next)
	{
		if ((row->next->row[i]
			&& !is_one_or_player(row->next->row[i])))
			return (0);
	}
	return (1);
}

void is_there_player(char *row, int *count)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (is_player(row[i]))
			(*count)++;
		i++;
	}
}

int is_it_all_spaces(char *row)
{
	int	i;

	i = 0;
	while (row[i] && is_space(row[i]))
		i++;
	if (!row[i])
		return (1);
	return (0);
}

int is_it_all_ones(char *row)
{
	int	i;
	int	ones_count;

	i = 0;
	ones_count = 0;
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
