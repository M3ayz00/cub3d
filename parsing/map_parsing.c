/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:06:49 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/07 17:49:49 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N'
		|| c == 'E' || c == 'W' || c == 'S');
}

int	count_rows(char **map)
{
	int i = 0;
	while (map && map[i])
		i++;
	return (i);
}

t_map2	*parse_map(char *path)
{
	t_map2	*map;

	map = (t_map2 *)malloc(sizeof(t_map2));
	if (!map)
		return (NULL);
	map->map = (char **)malloc(sizeof(char *) * count_rows(path) + 1);
	if (!map)
		return (NULL);
	
}
