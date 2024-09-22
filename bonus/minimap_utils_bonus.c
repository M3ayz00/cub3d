/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:54:23 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/21 18:55:42 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_max(int v1, int v2)
{
	if (v1 > v2)
		return (v1);
	return (v2);
}

double	get_scale(t_cub3d *cub3d)
{
	int		map_width;
	int		map_height;
	int		max_map_size;
	double	max_screen_size;

	map_width = ft_strlen(cub3d->map->map[0]);
	map_height = ft_lstsize(cub3d->map->rows);
	max_map_size = get_max(map_height, map_width);
	max_screen_size = WIDTH * 0.20;
	return (max_screen_size / (max_map_size * TILE_SIZE));
}

void	define_sx(t_draw_tool *tool, t_line *line)
{
	tool->sx = -1;
	if (line->x0 < line->x1)
		tool->sx = 1;
	tool->sy = -1;
	if (line->y0 < line->y1)
		tool->sy = 1;
}

void	init_render(t_cub3d *cub3d, t_render *tools)
{
	tools->offset = 10;
	tools->scale = get_scale(cub3d);
	tools->tile_size = TILE_SIZE * tools->scale;
}
