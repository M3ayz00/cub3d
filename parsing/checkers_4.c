/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:47:47 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/19 21:26:39 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_plane_or_player(char c, int is_bonus)
{
	return (is_plane(c, is_bonus) || is_player(c));
}

int	check_texture_file(char *file, char **texture)
{
	if (ft_strcmp(file + ft_strlen(file) - 4, ".xpm"))
		return (0);
	(*texture) = ft_strdup(file);
	return (1);
}

int	is_space2(char c)
{
	return (c == ' ' || c == '\t' || c == '\f' || c == '\r' || c == '\v');
}
