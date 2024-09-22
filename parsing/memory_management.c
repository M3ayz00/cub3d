/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:40:24 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/20 14:09:12 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	new = malloc(new_size);
	if (!new)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new, ptr, old_size);
		free(ptr);
	}
	return (new);
}

char	*ft_strdup(char *str)
{
	char	*new_str;

	new_str = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str, ft_strlen(str));
	return (new_str);
}

int	add_map_line(t_map **map, char *element, int is_bonus)
{
	if (!is_valid_elem(element, is_bonus))
		return (0);
	ft_lstadd_back(&(*map)->rows, lst_new(element));
	return (1);
}

int	add_map_lines(char **line, t_cub3d **cub3d, int fd, int is_bonus)
{
	while (*line)
	{
		if (!add_map_line(&(*cub3d)->map, *line, is_bonus))
			return (free(*line),
				free_textures(&(*cub3d)->textures),
				free_map(&(*cub3d)->map), 0);
		free(*line);
		*line = get_next_line(fd);
	}
	return (1);
}
