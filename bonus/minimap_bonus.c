/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:48:10 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/21 16:48:11 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_line(t_cub3d *cub3d, t_line *line)
{
    int dx = abs(line->x1 - line->x0);
    int dy = abs(line->y1 - line->y0);
    int sx = (line->x0 < line->x1) ? 1 : -1;
    int sy = (line->y0 < line->y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        my_mlx_pixel_put2(cub3d->image, line->x0, line->y0, line->color);
        if (line->x0 == line->x1 && line->y0 == line->y1)
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            line->x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            line->y0 += sy;
        }
    }
}

void draw_player_icon(t_cub3d *cub3d, int xc, int yc, int size, double angle, int color)
{
    int x1 = xc + cos(angle) * size;
    int y1 = yc + sin(angle) * size;
    int x2 = xc + cos(angle + M_PI_2) * (size / 2);
    int y2 = yc + sin(angle + M_PI_2) * (size / 2);
    int x3 = xc + cos(angle - M_PI_2) * (size / 2);
    int y3 = yc + sin(angle - M_PI_2) * (size / 2);
    t_line line = {x1, y1, x2, y2, color};
    draw_line(cub3d, &line);
    t_line line2 = {x2, y2, x3, y3, color};
    draw_line(cub3d, &line2);
    t_line line3 = {x3, y3, x1, y1, color};
    draw_line(cub3d, &line3);
}

void draw_cub(t_cub3d *cub3d, t_render tools)
{
	int	i;
	int	j;

	i = 0;
	while(i < tools.tile_size)
	{
		j = 0;
		while (j < tools.tile_size)
		{
			my_mlx_pixel_put2(cub3d->image, j + tools.map_x, i + tools.map_y, tools.color);
			j++;
		}
		i++;
	}
}

int get_max(int v1, int v2)
{
    if (v1 > v2)
        return (v1);
    return (v2);
}

double get_scale(t_cub3d *cub3d)
{
    int map_width;
    int map_height;
    int max_map_size;
    double max_screen_size;

	map_width = ft_strlen(cub3d->map2->map[0]);
	map_height = ft_lstsize(cub3d->map2->rows);
	max_map_size = get_max(map_height, map_width);
	max_screen_size = WIDTH * 0.20;
    return (max_screen_size / (max_map_size * TILE_SIZE));
}

void	init_render(t_cub3d *cub3d,t_render *tools)
{
	tools->offset = 10;
	tools->scale = get_scale(cub3d);
	tools->tile_size = TILE_SIZE * tools->scale;
}

void	map_rendering(t_cub3d *cub3d, t_render *tools, int i, int j)
{
	tools->map_x = j * tools->tile_size + tools->offset;
	tools->map_y = i * tools->tile_size + tools->offset;
	if (cub3d->map2->map[i][j] == '1')
		tools->color = get_rgb(100, 44, 16, 16);
	else if (is_plane_or_player(cub3d->map2->map[i][j], 0))
		tools->color = get_rgb(100, 118, 115, 165);
	else if (cub3d->map2->map[i][j] == 'D')
		tools->color = get_rgb(100, 255, 255, 16);
	if (is_plane_or_player(cub3d->map2->map[i][j], 1))
		draw_cub(cub3d, *tools);
}

void render_map(t_cub3d *cub3d)
{
	t_render	tools;
	int			i;
	int			j;

	i = 0;
	init_render(cub3d, &tools);
	while (cub3d->map2->map[i])
	{
		j = 0;
		while (cub3d->map2->map[i][j])
		{
			map_rendering(cub3d, &tools, i, j);
			j++;
		}
		i++;
	}
	draw_player_icon(cub3d,
		cub3d->player->pos_x * tools.tile_size + tools.offset,
		cub3d->player->pos_y * tools.tile_size + tools.offset,
		5 * tools.scale, cub3d->player->angle,
		get_rgb(255, 255, 255, 255));
}
