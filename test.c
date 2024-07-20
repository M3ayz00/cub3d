#include "./minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480

typedef struct s_data
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    int mapWidth;
    int mapHeight;
    int map[10][10];
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
} t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int get_rgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

int draw(t_data *data)
{
    for (int x = 0; x < WIDTH; x++)
    {
        // Calculate ray position and direction
        double cameraX = 2 * x / (double)WIDTH - 1;
        double rayDirX = data->dirX + data->planeX * cameraX;
        double rayDirY = data->dirY + data->planeY * cameraX;

        // Which box of the map we're in
        int mapX = (int)data->posX;
        int mapY = (int)data->posY;

        // Length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        // Length of ray from one x or y-side to next x or y-side
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        // What direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; // was there a wall hit?
        int side;    // was a NS or a EW wall hit?

        // Calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (data->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (data->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
        }

        // Perform DDA
        while (hit == 0)
        {
            // Jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY)
            {
                mapX += stepX;
                sideDistX += deltaDistX;
                side = 0; // Horizontal intersection
            }
            else
            {
                mapY += stepY;
                sideDistY += deltaDistY;
                side = 1; // Vertical intersection
            }

            // Check if ray has hit a wall
            if (data->map[mapX][mapY] > 0)
                hit = 1;
        }

        // Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)

        if (side == 0)
            perpWallDist = (mapX - data->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - data->posY + (1 - stepY) / 2) / rayDirY;

        // Calculate height of line to draw on screen
        int lineHeight = (int)(HEIGHT / perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT)
            drawEnd = HEIGHT - 1;

        // Choose wall color
        int color;
        switch (data->map[mapX][mapY])
        {
        case 1:
            color = get_rgb(200, 180, 77, 80);
            break; // Red
        // You can add more cases for different wall types
        default:
            color = get_rgb(255, 100, 5, 80);
            break; // White
        }

        // Give x and y sides different brightness
        if (side == 1)
        {
            color = color / 2;
        }

        // Draw the vertical stripe
        for (int y = drawStart; y < drawEnd; y++)
        {
            my_mlx_pixel_put(data, x, y, color);
        }

        // Draw the sky
        for (int y = 0; y < drawStart; y++)
        {
            my_mlx_pixel_put(data, x, y, get_rgb(240,111, 199, 242)); // Light blue color for the sky
        }

        // Draw the floor
        for (int y = drawEnd; y < HEIGHT; y++)
        {
            // Calculate floor color (could be more complex based on ray position, but we'll use a solid color here)
            int floorColor = get_rgb(255,133, 138, 128); // Dark gray color for the floor
            my_mlx_pixel_put(data, x, y, floorColor);
        }
    }
    return (0);
}

int key_press(int keycode, t_data *data)
{
    if (keycode == 65307) // Escape key
        exit(0);
    if (keycode == 119) // W key
    {
        if (data->map[(int)(data->posX + data->dirX * 0.1)][(int)(data->posY)] == 0)
            data->posX += data->dirX * 0.1;
        if (data->map[(int)(data->posX)][(int)(data->posY + data->dirY * 0.1)] == 0)
            data->posY += data->dirY * 0.1;
    }
    if (keycode == 115) // S key
    {
        if (data->map[(int)(data->posX - data->dirX * 0.1)][(int)(data->posY)] == 0)
            data->posX -= data->dirX * 0.1;
        if (data->map[(int)(data->posX)][(int)(data->posY - data->dirY * 0.1)] == 0)
            data->posY -= data->dirY * 0.1;
    }
    if (keycode == 97) // A key
    {
        double oldDirX = data->dirX;
        data->dirX = data->dirX * cos(0.1) - data->dirY * sin(0.1);
        data->dirY = oldDirX * sin(0.1) + data->dirY * cos(0.1);
        double oldPlaneX = data->planeX;
        data->planeX = data->planeX * cos(0.1) - data->planeY * sin(0.1);
        data->planeY = oldPlaneX * sin(0.1) + data->planeY * cos(0.1);
    }
    if (keycode == 100) // D key
    {
        double oldDirX = data->dirX;
        data->dirX = data->dirX * cos(-0.1) - data->dirY * sin(-0.1);
        data->dirY = oldDirX * sin(-0.1) + data->dirY * cos(-0.1);
        double oldPlaneX = data->planeX;
        data->planeX = data->planeX * cos(-0.1) - data->planeY * sin(-0.1);
        data->planeY = oldPlaneX * sin(-0.1) + data->planeY * cos(-0.1);
    }
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    draw(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}

int main(void)
{
    t_data data;
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Raycaster");

    // Create an image

    data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

    data.mapWidth = 10;
    data.mapHeight = 10;
    // Initialize your map, player position, direction and plane
    // Example map (10x10 grid, 1 represents walls)
    int map[10][10] =
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    // Copy the map to the struct
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            data.map[i][j] = map[i][j];
    // Player position and direction
    data.posX = 2.0;
    data.posY = 2.0;
    data.dirX = -1.0;
    data.dirY = 0.0;
    data.planeX = 0.0;
    data.planeY = 0.66;

    // Draw the initial frame
    draw(&data);
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_hook(data.win, 2, 1L << 0, key_press, &data);
    mlx_loop(data.mlx);
    return (0);
}
