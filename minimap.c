#include "cub3d.h"

int map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        mlx_pixel_put(data->mlx, data->win, x0, y0, color);
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

void draw_direction_line(t_data *data, int x, int y, double angle, int length, int color)
{
    int end_x = x + cos(angle) * length;
    int end_y = y + sin(angle) * length;
    draw_line(data, x, y, end_x, end_y, color);
}

void draw_horizontal_line(t_data *data, int x_start, int x_end, int y, int color)
{
    for (int x = x_start; x <= x_end; x++)
    {
        mlx_pixel_put(data->mlx, data->win, x, y, color);
    }
}

void draw_player(t_data *data, int xc, int yc, int radius, int color)
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

void draw_cub(t_data *data, int x, int y, int size_h, int size_w, int color)
{
    for (int i = 0; i < size_h; i++)
    {
        for (int j = 0; j < size_w; j++)
        {
            mlx_pixel_put(data->mlx, data->win, j + x, i + y, color);
        }
    }
}

void cast_ray(t_data *data, double ray_angle)
{
    data->ray->angle = ray_angle;
    double step_size = 0.1;

    double ray_x = data->player->posX;
    double ray_y = data->player->posY;

    while (1)
    {
        ray_x += cos(ray_angle) * step_size;
        ray_y += sin(ray_angle) * step_size;

        if (map[(int)ray_y][(int)ray_x] == 1)
        {
            data->ray->hitX = ray_x;
            data->ray->hitY = ray_y;
            data->ray->distance = sqrt(pow(ray_x - data->player->posX, 2) + pow(ray_y - data->player->posY, 2));
            break;
        }
    }
}

void cast_all_rays(t_data *data)
{
    int num_rays = WIDTH / 10;

    double angle_step = FOV / num_rays;

    for (int i = 0; i < num_rays; i++)
    {
      
        double ray_angle = data->player->angle - (FOV / 2) + (i * angle_step);
        cast_ray(data, ray_angle);

        // draw_ray
        int player_x = data->player->posX * TILE_SIZE;
        int player_y = data->player->posY * TILE_SIZE;
        int ray_x = data->ray->hitX * TILE_SIZE;
        int ray_y = data->ray->hitY * TILE_SIZE;
        draw_line(data,player_x,player_y,ray_x,ray_y,0xf0ff0f);
    }
}
void render(t_data *data)
{
    int i = 0;
    int cub_size_width = WIDTH / 10;
    int cub_size_height = HEIGHT / 10;
    while (i < 10)
    {
        int j = 0;
        while (j < 10)
        {
            if (map[i][j] == 1)
                draw_cub(data, j * cub_size_width, i * cub_size_height, cub_size_height, cub_size_width, 0xf0f0ff);
            else
                draw_cub(data, j * cub_size_width, i * cub_size_height, cub_size_height, cub_size_width, 0x0f00ff);

            j++;
        }
        i++;
    }
    draw_player(data, data->player->posX * cub_size_width, data->player->posY * cub_size_height, 15, 0x00ffff);
    // draw_direction_line(data, data->player->posX * cub_size_width, data->player->posY * cub_size_height, data->player->angle, 30, 0xff00ff);
    cast_all_rays(data);
}

void get_player_pos(t_data *data)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (map[i][j] == 2)
            {
                data->player->posX = j;
                data->player->posY = i;
                data->player->angle = 0.0;
            }
        }
    }
}

int key_press(int key, t_data *data)
{
    double newPosX = data->player->posX;
    double newPosY = data->player->posY;

    if (key == W_KEY)
    {
        newPosX += cos(data->player->angle) * 0.2;
        newPosY += sin(data->player->angle) * 0.2;
    }
    else if (key == S_KEY)
    {
        newPosX -= cos(data->player->angle) * 0.2;
        newPosY -= sin(data->player->angle) * 0.2;
    }
    else if (key == A_KEY)
    {
        data->player->angle -= 0.1;
    }
    else if (key == D_KEY)
    {
        data->player->angle += 0.1;
    }
    if (newPosX >= 0 && newPosX < 10 && newPosY >= 0 && newPosY < 10 && map[(int)floor(newPosY)][(int)floor(newPosX)] != 1)
    {
        data->player->posX = newPosX;
        data->player->posY = newPosY;
    }
    mlx_clear_window(data->mlx, data->win);
    render(data);
    return (0);
}

int main()
{
    t_data *data;

    data = malloc(sizeof(t_data));
    data->player = malloc(sizeof(t_player));
    data->map = malloc(sizeof(t_map));
    data->image = malloc(sizeof(t_image));
    data->ray = malloc(sizeof(t_ray));
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    get_player_pos(data);
    render(data);
    mlx_hook(data->win, 2, 1L << 0, key_press, data);
    mlx_loop(data->mlx);
    return (0);
}