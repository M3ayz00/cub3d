/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:30:35 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/24 21:20:07 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_adjacent(int curr_len, int adj_len, char c, int i)
{
	if (curr_len > adj_len && i > adj_len)
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
			{
				(*prev)->next = (*curr)->next;
				if ((*curr)->next)
					(*curr)->next->prev = (*prev);
			}
			else
			{
				(*curr) = (*curr)->next;
				(*curr)->prev = NULL;
			}
			free((*to_rem)->row);
			free((*to_rem));
			return ;
		}
		(*prev) = (*curr);
		(*curr) = (*curr)->next;
	}
}

int	colors_processing(char **splitted, t_textures **textures)
{
	if (!ft_strcmp(splitted[0], "F"))
	{
		if (!color_processing(splitted, &(*textures)->floor))
			return (0);
		else
			return (1);
	}
	else if (!ft_strcmp(splitted[0], "C"))
	{
		if (!color_processing(splitted, &(*textures)->ceiling))
			return (0);
		else
			return (1);
	}
	return (0);
}

int	process_texture(t_textures **textures, char **splitted)
{
	if (ft_strlen(splitted[0]) > 0)
	{
		if (textures_processing(splitted, textures) == 1)
			return (1);
		else if (colors_processing(splitted, textures) == 1)
			return (1);
		else
			return (0);
	}
	return (-1);
}
