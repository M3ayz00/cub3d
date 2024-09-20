/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:53:49 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/20 20:27:25 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	check_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY, 0644);
	if (fd == -1)
		return (0);
	return (close(fd), 1);
}

int	check_files(t_cub3d *cub3d)
{
	if (!check_file(cub3d->textures->north)
		|| !check_file(cub3d->textures->south)
		|| !check_file(cub3d->textures->east)
		|| !check_file(cub3d->textures->west))
		return (0);
	return (1);
}

void	set_width_and_height(t_lst **rows, t_cub3d *cub3d)
{
	t_lst	*curr;
	int		width;
	int		height;

	curr = *rows;
	height = 0;
	width = ft_strlen(curr->row);
	while (curr)
	{
		if (curr->next &&  width <= ft_strlen(curr->next->row))
			width = ft_strlen(curr->next->row);
		curr = curr->next;
		height++;
	}
	cub3d->map2->height = height;
	cub3d->map2->width = width;
	printf("WIDTH : %d, HEIGHT : %d\n", width, height);
}
