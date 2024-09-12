/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:44:14 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/13 16:02:40 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_player(char c)
{
	return (c == 'N' || c == 'W'
		|| c == 'S' || c == 'E');
}

int is_plane(char c)
{
	return (c == '0' || c == '1');
}

int is_valid_char(char c)
{
	return (is_plane(c)
		|| is_player(c)
		|| is_space(c));
}

int is_valid_elem(char *element)
{
	int	i;

	i = 0;
	if (!element)
		return (0);
	while (element[i] && element[i] != '\n')
	{
		if (!is_valid_char(element[i]))
			return (0);
		i++;
	}
	return (1);
}

int is_one_or_player(char c)
{
	return (c == '1' || c == '0'
		|| is_player(c));
}
