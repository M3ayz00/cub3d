/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:47:47 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/24 19:08:06 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_plane_or_player(char c, int is_bonus)
{
	return (is_plane(c, is_bonus) || is_player(c));
}

int	is_space2(char c)
{
	return (c == ' ' || c == '\t' || c == '\f' || c == '\r' || c == '\v');
}

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
			changed[i] = '0';
		i++;
	}
	free((*row));
	(*row) = changed;
}

void	change_spaces_to_0s(t_lst **rows)
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
