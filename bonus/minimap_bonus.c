#include "../cub3d.h"

void draw_line(t_cub3d *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        my_mlx_pixel_put2(data->image, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
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

void draw_direction_line(t_cub3d *data, int x, int y, double angle, int length, int color)
{
    int end_x = x + cos(angle) * length;
    int end_y = y + sin(angle) * length;
    draw_line(data, x, y, end_x, end_y, color);
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
            my_mlx_pixel_put2(data->image,j+x,i+y,color);
        }
    }
}

void cast_map_rays(t_cub3d *data)
{
    int num_rays = WIDTH / 50;
    int i = 0;
    double angle_step = FOV / num_rays;

    while (i < num_rays)
    {
        double ray_angle = data->player->angle - (FOV / 2) + (i * angle_step);
        cast_ray(data, ray_angle);
        int player_x = data->player->posX * TILE_SIZE;
        int player_y = data->player->posY * TILE_SIZE;
        int ray_x = data->ray->hitX * TILE_SIZE;
        int ray_y = data->ray->hitY * TILE_SIZE;
        draw_line(data, player_x, player_y, ray_x, ray_y, get_rgb(255,150,200,65));
        i++;
    }
}

void render_map(t_cub3d *data)
{
    int i = 0;
    int size = ft_lstsize(data->map2->rows);
    int cub_size_width = TILE_SIZE;
    int cub_size_height = TILE_SIZE;
    char **map = get_arr(data->map2->rows);
    while (data->map2->map[i] != NULL)
    {
        int j = 0;
        while (data->map2->map[i][j])
        {
            if (data->map2->map[i][j] == '1')
                draw_cub(data, j * cub_size_width, i * cub_size_height, cub_size_height, cub_size_width, get_rgb(100,44,16,16));
            else if (data->map2->map[i][j] == '0' || data->map2->map[i][j] == 'S' || data->map2->map[i][j] == 'N' || data->map2->map[i][j] == 'E' || data->map2->map[i][j] == 'W')
                draw_cub(data, j * cub_size_width, i * cub_size_height, cub_size_height, cub_size_width, get_rgb(100,118,115,165));
			else if (data->map2->map[i][j] == 'D')
				draw_cub(data, j * cub_size_width, i * cub_size_height, cub_size_height, cub_size_width, get_rgb(100,255,255,16));
            j++;
        }
        i++;
    }
    draw_player(data, data->player->posX * cub_size_width, data->player->posY * cub_size_height, 2, get_rgb(100,255,229,204));
    // // draw_direction_line(data, data->player->posX * cub_size_width, data->player->posY * cub_size_height, data->player->angle, 30, 0xff00ff);
    cast_map_rays(data);
}
