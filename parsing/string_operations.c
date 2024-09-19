/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:53:49 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/19 17:20:29 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// char	*ft_strdup(char *str)
// {
// 	char	*new_str;

// 	new_str = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
// 	if (!new_str)
// 		return (NULL);
// 	ft_memcpy(new_str, str, ft_strlen(str));
// 	return (new_str);
// }

// int	add_map_line(t_map2 **map, char *element, int nb_textures)
// {
// 	if (!is_valid_elem(element))
// 		return (0);
// 	ft_lstadd_back(&(*map)->rows, lst_new(element));
// 	return (1);
// }

int	ft_atoi(char *str)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	if (!str)
		return (-1);
	while (is_space(str[i]))
		i++;
	if (str[i] && !is_digit(str[i]))
		return (-1);
	while (str[i] && is_digit(str[i]))
	{
		result = (result * 10) + str[i] - '0';
		i++;
		if (result > 255)
			return (-1);
	}
	if (str[i] && !(is_digit(str[i]) || is_space(str[i])))
		return (-1);
	return (result);
}
