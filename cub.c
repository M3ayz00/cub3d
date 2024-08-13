#include "cub3d.h"

int map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int get_rgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

void my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    char *dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_line(t_image *image, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        my_mlx_pixel_put(image, x0, y0, color);
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

void draw_player(t_image *image, int xc, int yc, int radius, int color)
{
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (y >= x)
    {
        my_mlx_pixel_put(image, xc + x, yc + y, color);
        my_mlx_pixel_put(image, xc - x, yc + y, color);
        my_mlx_pixel_put(image, xc + x, yc - y, color);
        my_mlx_pixel_put(image, xc - x, yc - y, color);
        my_mlx_pixel_put(image, xc + y, yc + x, color);
        my_mlx_pixel_put(image, xc - y, yc + x, color);
        my_mlx_pixel_put(image, xc + y, yc - x, color);
        my_mlx_pixel_put(image, xc - y, yc - x, color);
        if (d < 0)
            d = d + 4 * x + 6;
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void cast_ray(t_data *data, double ray_angle)
{
    int mapX, mapY;
    double sideDistX, sideDistY;
    double deltaDistX, deltaDistY;
    double perpDistWall;
    int stepX, stepY;
    int hit = 0;
    int side;

    mapX = (int)data->player->posX;
    mapY = (int)data->player->posY;

    double rayDirX = cos(ray_angle);
    double rayDirY = sin(ray_angle);

    deltaDistX = fabs(1 / rayDirX);
    deltaDistY = fabs(1 / rayDirY);

    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (data->player->posX - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - data->player->posX) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (data->player->posY - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - data->player->posY) * deltaDistY;
    }

    while (hit == 0)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        if (map[mapY][mapX] > 0)
            hit = 1;
    }

    if (side == 0)
        perpDistWall = (sideDistX - deltaDistX);
    else
        perpDistWall = (sideDistY - deltaDistY);

    data->ray->hitX = data->player->posX + perpDistWall * rayDirX;
    data->ray->hitY = data->player->posY + perpDistWall * rayDirY;
    data->ray->hit_distance = perpDistWall;
    data->ray->is_vertical = (side == 0);
}

int calc_height(double distance, int screen_height)
{
    if (distance <= 0)
        return screen_height;
    return (int)(screen_height / distance);
}

void cast_all_rays(t_data *data)
{
    int num_rays = WIDTH;
    double angle_step = FOV / num_rays;

    int i, j, k, l;
    i = 0;
    while (i < num_rays - 1)
    {

        double ray_angle = data->player->angle - (FOV / 2) + (i * angle_step);
        cast_ray(data, ray_angle);

        int wall_height = calc_height((data->ray->hit_distance * cos(ray_angle - data->player->angle)), HEIGHT);
        int wall_start = (HEIGHT / 2) - (wall_height / 2);
        int wall_end = (HEIGHT / 2) + (wall_height / 2);
        j = 0;
        while (j < wall_start)
        {
            my_mlx_pixel_put(data->image, i, j, get_rgb(255, 135, 206, 235));
            j++;
        }
        k = wall_start;
        while (k < wall_end)
        {
            int wall_color = data->ray->is_vertical ? get_rgb(255, 210, 180, 140) : get_rgb(255, 128, 128, 128);
            my_mlx_pixel_put(data->image, i, k, wall_color);
            k++;
        }
        l = wall_end;
        while (l < HEIGHT)
        {
            my_mlx_pixel_put(data->image, i, l, get_rgb(255, 54, 69, 79));
            l++;
        }
        i++;
    }
}

void render(t_data *data)
{
    cast_all_rays(data);
    mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
}

void get_player_pos(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (i < 10)
    {
        j = 0;
        while (j < 10)
        {
            if (map[i][j] == 2)
            {
                data->player->posX = j;
                data->player->posY = i;
                data->player->angle = 0.5;
                return;
            }
            j++;
        }
        i++;
    }
}

int key_press(int key, t_data *data)
{
    double move_speed = 0.09;
    double rot_speed = 0.09;
    double newPosX = data->player->posX;
    double newPosY = data->player->posY;
    double margin = 0.05; // Margin value

    if (key == W_KEY)
    {
        newPosX += cos(data->player->angle) * move_speed;
        newPosY += sin(data->player->angle) * move_speed;
    }
    else if (key == S_KEY)
    {
        newPosX -= cos(data->player->angle) * move_speed;
        newPosY -= sin(data->player->angle) * move_speed;
    }

    else if (key == A_KEY) // Move left (strafe left)
    {
        newPosX += sin(data->player->angle) * move_speed;
        newPosY -= cos(data->player->angle) * move_speed;
    }
    else if (key == D_KEY) // Move right (strafe right)
    {
        newPosX -= sin(data->player->angle) * move_speed;
        newPosY += cos(data->player->angle) * move_speed;
    }
    else if (key == LEFT_KEY)
    {
        data->player->angle -= rot_speed;
    }
    else if (key == RIGHT_KEY)
    {
        data->player->angle += rot_speed;
    }
    if (newPosX >= margin && newPosX <= 10 &&
        newPosY >= margin && newPosY <= 10)
    {
        printf("newPosX: %d, newPosY: %d\n", (int)floor(newPosX), (int)floor(newPosY));
        // Check for collisions with walls, considering the margin
        if (map[(int)floor(newPosY - margin)][(int)floor(newPosX - margin)] != 1 &&
            map[(int)floor(newPosY + margin)][(int)floor(newPosX + margin)] != 1 &&
            map[(int)floor(newPosY - margin)][(int)floor(newPosX + margin)] != 1 &&
            map[(int)floor(newPosY + margin)][(int)floor(newPosX - margin)] != 1)
        {
            data->player->posX = newPosX;
            data->player->posY = newPosY;
            render(data);
        }
    }
    return (0);
}
int ft_exit()
{
    exit(0);
    return (0);
}

int main()
{
    t_data data;

    data.player = malloc(sizeof(t_player));
    data.ray = malloc(sizeof(t_ray));
    data.image = malloc(sizeof(t_image));
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "cub3d");
    data.image->img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    data.image->addr = mlx_get_cub3d_addr(data.image->img, &data.image->bits_per_pixel, &data.image->line_length, &data.image->endian);
    get_player_pos(&data);
    data.tex_width = 64;
    data.tex_height = 64;
    render(&data);
    mlx_hook(data.win, 2, 1L << 0, key_press, &data);
    mlx_hook(data.win, 17, 1L << 17, &ft_exit, NULL);
    mlx_loop(data.mlx);
    return (0);
}
