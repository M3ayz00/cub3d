/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:30:35 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/19 21:07:38 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_adjacent(int curr_len, int adj_len, char c, int i)
{
	if (curr_len > adj_len - 2 && i > adj_len - 2)
	{
		if (!is_space(c))
		{
			if (c != '1')
				return (0);
		}
	}
	return (1);
}

void	remove_x_node(t_lst **curr, t_lst **prev, t_lst **to_rem)
{
	while ((*curr))
	{
		if ((*curr) == (*to_rem))
		{
			if ((*prev))
				(*prev)->next = (*curr)->next;
			free((*to_rem)->row);
			free((*to_rem));
			return ;
		}
		(*prev) = (*curr);
		(*curr) = (*curr)->next;
	}
}

int	validating_and_cleaning(t_lst **rows, t_lst *curr)
{
	t_lst	*checkpoint;

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
