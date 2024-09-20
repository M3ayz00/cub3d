/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:44:14 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/19 21:25:47 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'W' || c == 'S' || c == 'E');
}

int	is_plane(char c, int is_bonus)
{
	return (c == '0' || c == '1' || (is_bonus == 1 && c == 'D'));
}

int	is_valid_char(char c, int is_bonus)
{
	return (is_plane(c, is_bonus) || is_player(c) || is_space(c));
}

int	is_valid_elem(char *element, int is_bonus)
{
	int	i;

	i = 0;
	if (!element)
		return (0);
	while (element[i] && element[i] != '\n')
	{
		if (!is_valid_char(element[i], is_bonus))
			return (0);
		i++;
	}
	return (1);
}
