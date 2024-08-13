#include "../cub3d.h"

void my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void my_mlx_pixel_put2(t_image *image, int x, int y, int color)
{
    char *dst;

    dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}


void render_ceil(t_cub3d *data, int i, int end)
{
    int j;

    j = 0;
    while (j < end)
    {
        my_mlx_pixel_put(data->image, i, j, get_rgb(255, 135, 206, 235));
        j++;
    }
}

void render_walls(t_cub3d *data, int i, int start, int end)
{
    int color;

    while (start < end)
    {
        if (data->ray->is_vertical)
            color = get_rgb(255, 210, 180, 140);
        else
            color = get_rgb(255, 128, 128, 128);
        // color = data->ray->is_vertical ? get_rgb(255, 210, 180, 140) : get_rgb(255, 128, 128, 128);
        my_mlx_pixel_put(data->image, i, start, color);
        start++;
    }
}

void render_floor(t_cub3d *data, int i, int start, int end)
{
    int l = start;
    while (l < end)
    {
        my_mlx_pixel_put(data->image, i, l, get_rgb(255, 54, 69, 79));
        l++;
    }
}
