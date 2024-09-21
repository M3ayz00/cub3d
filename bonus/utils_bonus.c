/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:56:35 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/21 18:56:45 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_door_is_open_at(int map_x, int map_y, t_cub3d *cub3d)
{
	return (cub3d->doors->is_open[map_y][map_x]);
}

int	get_texel(t_image weapon, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= weapon.width || y < 0 || y >= weapon.height)
		return (0);
	pixel = weapon.addr + (y * weapon.line_length + x * (weapon.bits_per_pixel
				/ 8));
	return (*(int *)pixel);
}
