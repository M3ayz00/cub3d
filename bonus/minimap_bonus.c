#include "../cub3d.h"

void draw_line(t_cub3d *data, t_line *line)
{
    int dx = abs(line->x1 - line->x0);
    int dy = abs(line->y1 - line->y0);
    int sx = (line->x0 < line->x1) ? 1 : -1;
    int sy = (line->y0 < line->y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        my_mlx_pixel_put2(data->image, line->x0, line->y0, line->color);
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

void draw_horizontal_line(t_cub3d *data, int x_start, int x_end, int y, int color)
{
    for (int x = x_start; x <= x_end; x++)
    {
        my_mlx_pixel_put2(data->image, x, y, color);
    }
}

void draw_player_icon(t_cub3d *data, int xc, int yc, int size, double angle, int color)
{
    int x1 = xc + cos(angle) * size;
    int y1 = yc + sin(angle) * size;
    int x2 = xc + cos(angle + M_PI_2) * (size / 2);
    int y2 = yc + sin(angle + M_PI_2) * (size / 2);
    int x3 = xc + cos(angle - M_PI_2) * (size / 2);
    int y3 = yc + sin(angle - M_PI_2) * (size / 2);
    t_line line = {x1, y1, x2, y2, color};
    draw_line(data, &line);
    t_line line2 = {x2, y2, x3, y3, color};
    draw_line(data, &line2);
    t_line line3 = {x3, y3, x1, y1, color};
    draw_line(data, &line3);
}

void draw_direction_line(t_cub3d *data, int x, int y, double angle, int length, int color)
{
    int end_x = x + cos(angle) * length;
    int end_y = y + sin(angle) * length;

    t_line line = { x, y, end_x, end_y, color};
    draw_line(data,&line);
}

void draw_player(t_cub3d *data, int xc, int yc, int radius, int color)
{
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (y >= x)
    {
        // Draw horizontal lines between symmetrical points
        draw_horizontal_line(data, xc - x, xc + x, yc + y, color);
        draw_horizontal_line(data, xc - x, xc + x, yc - y, color);
        draw_horizontal_line(data, xc - y, xc + y, yc + x, color);
        draw_horizontal_line(data, xc - y, xc + y, yc - x, color);

        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }
    }
}

void draw_cub(t_cub3d *data, int x, int y, int size_h, int size_w, int color)
{
    for (int i = 0; i < size_h; i++)
    {
        for (int j = 0; j < size_w; j++)
        {
            my_mlx_pixel_put2(data->image, j + x, i + y, color);
        }
    }
}

void cast_map_rays(t_cub3d *data, int offset, double scale)
{
    int num_rays = WIDTH / 50;
    int i = 0;
    double angle_step = data->fov / num_rays;

    int player_x = data->player->pos_x * TILE_SIZE * scale + offset;
    int player_y = data->player->pos_y * TILE_SIZE * scale + offset;
    while (i < num_rays)
    {
        double ray_angle = (data->player->angle - (data->fov / 2) + (i * angle_step));
        cast_ray(data, ray_angle);
        int ray_x = data->ray->hit_x * TILE_SIZE * scale + offset;
        int ray_y = data->ray->hit_y * TILE_SIZE * scale + offset;
        t_line line = {player_x, player_y, ray_x, ray_y, get_rgb(255, 150, 200, 65)};
        draw_line(data, &line);
        ray_angle += angle_step;
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
    int map_width = ft_strlen(cub3d->map2->map[0]);
    int map_height = ft_lstsize(cub3d->map2->rows);
    int max_map_size = get_max(map_height, map_width);
    double max_screen_size = WIDTH * 0.20;
    return (max_screen_size / (max_map_size * TILE_SIZE));
}

void render_map(t_cub3d *data)
{
    int i = 0;
    int offset = 10;
    int size = ft_lstsize(data->map2->rows);
    double scale = get_scale(data);
    int cub_size_width = TILE_SIZE * scale;
    int cub_size_height = TILE_SIZE * scale;
    char **map = get_arr(data->map2->rows);
    while (data->map2->map[i] != NULL)
    {
        int j = 0;
        while (data->map2->map[i][j])
        {
            if (data->map2->map[i][j] == '1')
                draw_cub(data, j * cub_size_width + offset, i * cub_size_height + offset, cub_size_height, cub_size_width, get_rgb(100, 44, 16, 16));
            else if (data->map2->map[i][j] == '0' || data->map2->map[i][j] == 'S' || data->map2->map[i][j] == 'N' || data->map2->map[i][j] == 'E' || data->map2->map[i][j] == 'W')
                draw_cub(data, j * cub_size_width + offset, i * cub_size_height + offset, cub_size_height, cub_size_width, get_rgb(100, 118, 115, 165));
            else if (data->map2->map[i][j] == 'D')
                draw_cub(data, j * cub_size_width + offset, i * cub_size_height + offset, cub_size_height, cub_size_width, get_rgb(100, 255, 255, 16));
            j++;
        }
        i++;
    }
    // draw_player(data, data->player->pos_x * cub_size_width + offset, data->player->pos_y * cub_size_height + offset, scale, get_rgb(100,255,229,204));
    // cast_map_rays(data, offset, scale);
    draw_player_icon(data, data->player->pos_x * cub_size_width + offset, data->player->pos_y * cub_size_height + offset, 5 * scale, data->player->angle, get_rgb(255, 255, 255, 255)); // Triangle player icon
    // draw_direction_line(data, data->player->pos_x * cub_size_width + offset, data->player->pos_y * cub_size_height + offset, data->player->angle, 10, 0xff00ff);
}
