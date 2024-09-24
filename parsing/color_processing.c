/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:48:50 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/24 21:34:13 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_there_digit(char *mapline)
{
	int	i;

	i = 0;
	while (mapline[i])
	{
		if (is_digit(mapline[i]))
			return (1);
		i++;
	}
	return (0);
}

int	are_numbers_valid(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (is_there_digit(strs[i]))
			i++;
		else
			return (0);
	}
	if (i != 3)
		return (0);
	return (1);
}

int	based_split(char *line, char ***splitted)
{
	char	*trimmed;

	(*splitted) = ft_split(line, "\f\t\v\r\n ");
	if (is_color((*splitted)[0]))
	{
		free_strs(*splitted);
		trimmed = ft_strtrim(line, "FC");
		*splitted = ft_split(trimmed, ",");
		free(trimmed);
		if (!are_numbers_valid(*splitted))
			return (free_strs(*splitted), 0);
		free_strs(*splitted);
		(*splitted) = ft_split(line, "\f\t\v\r\n, ");
	}
	return (1);
}

t_color	*get_color(t_color **actual_color, char ***colors)
{
	(*actual_color)->r = ft_atoi((*colors)[1]);
	(*actual_color)->g = ft_atoi((*colors)[2]);
	(*actual_color)->b = ft_atoi((*colors)[3]);
	if ((*actual_color)->r == -1 || (*actual_color)->g == -1
		|| (*actual_color)->b == -1)
		return (free((*actual_color)), NULL);
	return ((*actual_color));
}

t_color	*split_color(char **color)
{
	int		size;
	t_color	*actual_col;

	size = count_rows(color);
	actual_col = (t_color *)malloc(sizeof(t_color));
	if (!actual_col)
		return (NULL);
	if (size == 4)
		return (get_color(&actual_col, &color));
	return (free(actual_col), NULL);
}
