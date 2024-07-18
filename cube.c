#include "cub3d.h"

int map[6][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

};

int get_rgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_circle(void *data, int center_x, int center_y, int radius, int color)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        for (int i = center_x - x; i <= center_x + x; i++)
        {
            my_mlx_pixel_put(data, i, center_y + y, color);
            my_mlx_pixel_put(data, i, center_y - y, color);
        }
        for (int i = center_x - y; i <= center_x + y; i++)
        {
            my_mlx_pixel_put(data, i, center_y + x, color);
            my_mlx_pixel_put(data, i, center_y - x, color);
        }

        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(data, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
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

int has_wall_at(int x, int y)
{
    if (x < 0 || x > NUM_COLS * TILE_SIZE || y < 0 || y > NUM_ROWS * TILE_SIZE)
        return (1);
    int map_index_x = floor(x / TILE_SIZE);
    int map_index_y = floor(y / TILE_SIZE);
      
    return map[map_index_y][map_index_x] != 0;
}

void update(t_data *data, int angle)
{
    if (angle)
        data->player->rot_angle += data->player->turn_dir * data->player->turn_speed;
    else
    {
        double move_step = data->player->walk_dir * data->player->move_speed;
        int new_px = data->player->x + cos(data->player->rot_angle) * move_step;
        int new_py = data->player->y + sin(data->player->rot_angle) * move_step;

        if (!has_wall_at(new_px, new_py))
        {
            data->player->x = new_px;
            data->player->y = new_py;
        }
    }
}

void draw_scene(t_data *data)
{

    int i = 0;
    int j;
    while (i < NUM_ROWS)
    {
        j = 0;
        while (j < NUM_COLS)
        {
            int tile_x = j * TILE_SIZE;
            int tile_y = i * TILE_SIZE;
            int tile_x_g = j * (TILE_SIZE);
            int tile_y_g = i * (TILE_SIZE);
            int tile_color = map[i][j] == 1 ? get_rgb(200, 180, 77, 80) : get_rgb(255, 100, 5, 80);
            int k = 0;
            int l = 0;

            while (k < TILE_SIZE)
            {
                l = 0;
                while (l < TILE_SIZE)
                {

                    my_mlx_pixel_put(data, tile_x_g + k, tile_y_g + l, tile_color);
                    l++;
                }
                k++;
            }

            j++;
        }
        i++;
    }
    int player_center_x = data->player->x + TILE_SIZE / 2;
    int player_center_y = data->player->y + TILE_SIZE / 2;
    draw_circle(data, player_center_x, player_center_y, TILE_SIZE / 4, get_rgb(255, 187, 98, 255));
    int cord_x = player_center_x + cos(data->player->rot_angle) * TILE_SIZE / 2;
    int cord_y = player_center_y + sin(data->player->rot_angle) * TILE_SIZE / 2;
    draw_line(data, player_center_x, player_center_y, cord_x, cord_y, get_rgb(255, 187, 98, 255));
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int key_press(int keycode, t_data *data)
{
    int flag = 0;
    if (keycode == 65307) // Escape key
        exit(0);
    if (keycode == 119) // W key
    {

        data->player->walk_dir = +1;
        update(data, 0);
    }
    if (keycode == 115) // S key
    {
        data->player->walk_dir = -1;
        update(data, 0);
    }
    if (keycode == 97) // A key
    {
        data->player->turn_dir = -1;
        update(data, 1);
    }
    if (keycode == 100) // D key
    {
        data->player->turn_dir = +1;
        update(data, 1);
    }
    mlx_clear_window(data->mlx, data->win);

    draw_scene(data);
    return (0);
}

int main()
{
    t_data *data;
    data = malloc(sizeof(t_data));
    if (!data)
        return (1);
    memset(data, 0, sizeof(t_data));
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, NUM_COLS * TILE_SIZE, NUM_ROWS * (TILE_SIZE), "Cub3D");
    data->img = mlx_new_image(data->mlx, NUM_COLS * TILE_SIZE, NUM_ROWS * (TILE_SIZE));
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    data->player = malloc(sizeof(t_player));
    if (!data->player)
        return (1);

    data->player->x = NUM_COLS * TILE_SIZE / 2;
    data->player->y = NUM_ROWS * TILE_SIZE / 2;
    data->player->turn_dir = 0;
    data->player->walk_dir = 0;
    data->player->rot_angle = M_PI / 2;
    data->player->move_speed = 5.0;
    data->player->turn_speed = 3 * (M_PI / 180);

    draw_scene(data);
    mlx_hook(data->win, 2, 1L << 0, key_press, data);

    mlx_loop(data->mlx);

    return 0;
}