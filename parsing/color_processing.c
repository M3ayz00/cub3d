/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:48:50 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/22 20:28:07 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_rows(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

int	count_commas(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
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
		free_strs(*splitted);
		if (count_commas(line) != 2)
			return (0);
		*splitted = ft_split(line, "\f\t\v\r\n ,");
		if (count_rows(*splitted) != 4)
			return (free_strs(*splitted), 0);
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
	return (actual_col);
}
