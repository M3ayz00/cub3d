#include "cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->image->addr + (y * data->image->line_length + x * (data->image->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int get_rgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

void calculate_ray_direction(t_data *data, int x, t_ray *ray)
{
    double cameraX = 2 * x / (double)WIDTH - 1;
    ray->rayDirX = data->player->dirX + data->player->planeX * cameraX;
    ray->rayDirY = data->player->dirY + data->player->planeY * cameraX;
}

void initialize_step_and_sideDist(t_data *data, t_ray *ray)
{
    ray->mapX = (int)data->player->posX;
    ray->mapY = (int)data->player->posY;
    ray->deltaDistX = fabs(1 / ray->rayDirX);
    ray->deltaDistY = fabs(1 / ray->rayDirY);
    ray->sideDistX = (ray->rayDirX < 0) ? (data->player->posX - ray->mapX) * ray->deltaDistX
                                        : (ray->mapX + 1.0 - data->player->posX) * ray->deltaDistX;
    ray->sideDistY = (ray->rayDirY < 0) ? (data->player->posY - ray->mapY) * ray->deltaDistY
                                        : (ray->mapY + 1.0 - data->player->posY) * ray->deltaDistY;
    ray->stepX = (ray->rayDirX < 0) ? -1 : 1;
    ray->stepY = (ray->rayDirY < 0) ? -1 : 1;
}

void perform_dda(t_data *data, t_ray *ray)
{
    while (ray->hit == 0)
    {
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->mapX += ray->stepX;
            ray->sideDistX += ray->deltaDistX;
            ray->side = 0;
        }
        else
        {
            ray->mapY += ray->stepY;
            ray->sideDistY += ray->deltaDistY;
            ray->side = 1;
        }
        if (data->map->map[ray->mapX][ray->mapY] > 0)
            ray->hit = 1;
    }
}

void calculate_wall_distance(t_data *data, t_ray *ray, double *perpWallDist)
{
    if (ray->side == 0)
        *perpWallDist = (ray->mapX - data->player->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
    else
        *perpWallDist = (ray->mapY - data->player->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
}

void draw_vertical_stripe(t_data *data, int x, int drawStart, int drawEnd, int color)
{
    for (int y = drawStart; y < drawEnd; y++)
        my_mlx_pixel_put(data, x, y, color);
}

int draw(t_data *data)
{
    t_ray ray;
    for (int x = 0; x < WIDTH; x++)
    {
        calculate_ray_direction(data, x, &ray);
        initialize_step_and_sideDist(data, &ray);
        ray.hit = 0;
        perform_dda(data, &ray);

        double perpWallDist;
        calculate_wall_distance(data, &ray, &perpWallDist);

        // Calculate height of line to draw on screen
        int lineHeight = (int)(HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        // Calculate lowest and highest pixel to fill in current stripe
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT)
            drawEnd = HEIGHT - 1;
        // Choose wall color based on the side
        int color = (data->map->map[ray.mapX][ray.mapY] == 1) ? get_rgb(200, 180, 77, 80) : get_rgb(255, 100, 5, 80);
        if (ray.side == 1)
            color /= 2;
        draw_vertical_stripe(data, x, drawStart, drawEnd, color); // Draw the wall

        for (int y = 0; y < drawStart; y++)
            my_mlx_pixel_put(data, x, y, get_rgb(240, 111, 199, 242)); // Sky

        for (int y = drawEnd; y < HEIGHT; y++)
            my_mlx_pixel_put(data, x, y, get_rgb(255, 133, 138, 128)); // Floor
    }
    return (0);
}

int key_press(int keycode, t_data *data)
{
    if (keycode == 65307) // Escape key
        exit(0);
    if (keycode == 119) // W key
    {
        // Move forward
        if (data->map->map[(int)(data->player->posX + data->player->dirX * 0.1)][(int)(data->player->posY)] == 0)
            data->player->posX += data->player->dirX * 0.1;
        if (data->map->map[(int)(data->player->posX)][(int)(data->player->posY + data->player->dirY * 0.1)] == 0)
            data->player->posY += data->player->dirY * 0.1;
    }
    if (keycode == 115) // S key
    {
        // Move backwards
        if (data->map->map[(int)(data->player->posX - data->player->dirX * 0.1)][(int)(data->player->posY)] == 0)
            data->player->posX -= data->player->dirX * 0.1;
        if (data->map->map[(int)(data->player->posX)][(int)(data->player->posY - data->player->dirY * 0.1)] == 0)
            data->player->posY -= data->player->dirY * 0.1;
    }
    if (keycode == 97) // A key
    {
        // Rotate left
        double oldDirX = data->player->dirX;
        data->player->dirX = data->player->dirX * cos(0.1) - data->player->dirY * sin(0.1);
        data->player->dirY = oldDirX * sin(0.1) + data->player->dirY * cos(0.1);
        double oldPlaneX = data->player->planeX;
        data->player->planeX = data->player->planeX * cos(0.1) - data->player->planeY * sin(0.1);
        data->player->planeY = oldPlaneX * sin(0.1) + data->player->planeY * cos(0.1);
    }
    if (keycode == 100) // D key
    {
        //both camera direction and camera plane must be rotated
        double oldDirX = data->player->dirX;
        data->player->dirX = data->player->dirX * cos(-0.1) - data->player->dirY * sin(-0.1);
        data->player->dirY = oldDirX * sin(-0.1) + data->player->dirY * cos(-0.1);
        double oldPlaneX = data->player->planeX;
        data->player->planeX = data->player->planeX * cos(-0.1) - data->player->planeY * sin(-0.1);
        data->player->planeY = oldPlaneX * sin(-0.1) + data->player->planeY * cos(-0.1);
    }
    // Redraw the frame
    if (data->image->img)
        mlx_destroy_image(data->mlx, data->image->img);
    data->image->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->image->addr = mlx_get_data_addr(data->image->img, &data->image->bits_per_pixel, &data->image->line_length, &data->image->endian);
    draw(data);
    mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
    return (0);
}

int main(void)
{
    t_data data;
    t_image image;
    t_map map;
    t_player player;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Raycaster");

    // Create an image
    data.image = &image;
    data.image->img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    data.image->addr = mlx_get_data_addr(data.image->img, &data.image->bits_per_pixel, &data.image->line_length, &data.image->endian);

    // Initialize map
    data.map = &map;
    data.map->mapWidth = 10;
    data.map->mapHeight = 10;
    // Example map (10x10 grid, 1 represents walls)
    int mapArray[10][10] =
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 1, 1, 1, 1 ,1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    // Copy the map to the struct
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            data.map->map[i][j] = mapArray[i][j];

    // Initialize player
    data.player = &player;
    data.player->posX = 2.0;
    data.player->posY = 2.0;
    data.player->dirX = -1.0;
    data.player->dirY = 0.0;
    data.player->planeX = 0.0;
    data.player->planeY = 0.66;

    // Draw the initial frame
    draw(&data);
    mlx_put_image_to_window(data.mlx, data.win, data.image->img, 0, 0);
    mlx_hook(data.win, 2, 1L << 0, key_press, &data);
    mlx_loop(data.mlx);
    return (0);
}
