/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:48:10 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/24 15:15:48 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_line(t_cub3d *cub3d, t_line *line)
{
	t_draw_tool	tool;

	tool.dx = abs(line->x1 - line->x0);
	tool.dy = abs(line->y1 - line->y0);
	tool.err = tool.dx - tool.dy;
	define_sx(&tool, line);
	while (1)
	{
		my_mlx_pixel_put2(cub3d->image, line->x0, line->y0, line->color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		tool.e2 = 2 * tool.err;
		if (tool.e2 > -tool.dy)
		{
			tool.err -= tool.dy;
			line->x0 += tool.sx;
		}
		if (tool.e2 < tool.dx)
		{
			tool.err += tool.dx;
			line->y0 += tool.sy;
		}
	}
}

void	draw_player_icon(t_cub3d *cub3d, t_render infos, double angle,
	int color)
{
	t_draw_tool	tool;
	t_line		line;
	t_line		line2;
	t_line		line3;

	tool.x_tip = infos.map_x + cos(angle) * infos.size;
	tool.y_tip = infos.map_y + sin(angle) * infos.size;
	tool.x_left = infos.map_x + cos(angle + M_PI_2) * (infos.size / 2);
	tool.y_left = infos.map_y + sin(angle + M_PI_2) * (infos.size / 2);
	tool.x_right = infos.map_x + cos(angle - M_PI_2) * (infos.size / 2);
	tool.y_right = infos.map_y + sin(angle - M_PI_2) * (infos.size / 2);
	line = (t_line){tool.x_tip, tool.y_tip, tool.x_left, tool.y_left, color};
	draw_line(cub3d, &line);
	line2 = (t_line){tool.x_left, tool.y_left, tool.x_right,
		tool.y_right, color};
	draw_line(cub3d, &line2);
	line3 = (t_line){tool.x_right, tool.y_right, tool.x_tip, tool.y_tip, color};
	draw_line(cub3d, &line3);
}

void	draw_cub(t_cub3d *cub3d, t_render tools)
{
	int	i;
	int	j;

	i = 0;
	while (i < tools.tile_size)
	{
		j = 0;
		while (j < tools.tile_size)
		{
			my_mlx_pixel_put2(cub3d->image, j + tools.map_x,
				i + tools.map_y, tools.color);
			j++;
		}
		i++;
	}
}

void	map_rendering(t_cub3d *cub3d, t_render *tools, int i, int j)
{
	tools->map_x = MAP_X + (j * tools->tile_size
			- cub3d->player->pos_x * tools->tile_size);
	tools->map_y = MAP_Y + (i * tools->tile_size
			- cub3d->player->pos_y * tools->tile_size);
	if (is_inside_circle(tools->map_x, tools->map_y))
	{
		if (cub3d->map->map[i][j] == '1')
		{
			tools->color = get_rgb(100, 44, 16, 16);
			draw_cub(cub3d, *tools);
		}
		else if (is_plane_or_player(cub3d->map->map[i][j], 0))
		{
			tools->color = get_rgb(100, 118, 115, 165);
			draw_cub(cub3d, *tools);
		}
		else if (cub3d->map->map[i][j] == 'D')
		{
			tools->color = get_rgb(100, 255, 255, 16);
		}
	}
}

void	render_map(t_cub3d *cub3d)
{
	t_render	tools;
	int			i;
	int			j;

	i = 0;
	tools.tile_size = TILE_SIZE;
	fill_circle(cub3d, get_rgb(20, 0, 0, 0));
	while (cub3d->map->map[i])
	{
		j = 0;
		while (cub3d->map->map[i][j])
		{
			map_rendering(cub3d, &tools, i, j);
			j++;
		}
		i++;
	}
	tools.map_x = MAP_X;
	tools.map_y = MAP_Y;
	tools.size = 7;
	draw_player_icon(cub3d, tools, cub3d->player->angle,
		get_rgb(255, 255, 255, 255));
}
