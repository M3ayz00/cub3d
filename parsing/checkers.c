/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:43:20 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/13 16:35:54 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_space(char c)
{
	return ((c >= 9 && c <= 13)
		|| c == 32);
}

int is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int is_color(char *element)
{
	return (!ft_strcmp(element, "F")
		|| !ft_strcmp(element, "C"));
}

int is_texture(char *element)
{
	return (!ft_strcmp(element, "NO")
		|| !ft_strcmp(element, "SO")
		|| !ft_strcmp(element, "EA")
		|| !ft_strcmp(element, "WE"));
}

int is_identifier(char *line)
{
	char	**splitted;

	splitted = ft_split(line, "\f\n\t\v\r ");
	if (!splitted)
		return (0);
	printf("IS IT ? \n");
	if (is_color(splitted[0]) || is_texture(splitted[0]))
		return (free_strs(splitted), 1);
	else if (ft_strlen(splitted[0]) > 0)
		return (free_strs(splitted), -1);
	return (free_strs(splitted), 0);
}
