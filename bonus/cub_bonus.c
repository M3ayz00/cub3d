#include "../cub3d.h"

int get_texel(t_image texture, int x, int y)
{
    char *pixel;

    if (x < 0 || y < 0 || x >= texture.width || y >= texture.height)
        return (0);
    pixel = texture.addr + (y * texture.line_length + x *
                                                          (texture.bits_per_pixel / 8));
    return (*(unsigned int *)pixel);
}

void weapon_puts(t_cub3d *data, int up)
{
    int i;
    int x;
    int color;
    int screen_width = WIDTH;
    int screen_height = HEIGHT;
    int image_width = data->weapon->width;
    int image_height = data->weapon->height;

    // Calculate the position to center the image horizontally
    int start_x = (screen_width - image_width) / 2;
    int start_y = screen_height - image_height - up;

    i = 0;
    while (i < image_height)
    {
        x = 0;
        while (x < image_width)
        {
            color = get_texel(*(data->weapon), x, i);
            if (color != 0 && color != -16777216) // Assuming 0 and -16777216 are transparent colors
            {
                my_mlx_pixel_put2(data->image, start_x + x, start_y + i, color);
            }
            x++;
        }
        i++;
    }
}

void render_weapon(t_cub3d *data)
{
    int width;
    int height;
    data->weapon->img = mlx_xpm_file_to_image(data->mlx, "bonus/textures/hk53_idle1.xpm", &width, &height);
    data->weapon->width = width;
    data->weapon->height = height;
    if (!data->weapon->img)
    {
        write(2, "error\n", 6);
        exit(1);
    }
    data->weapon->addr = mlx_get_data_addr(data->weapon->img, &data->weapon->bits_per_pixel, &data->weapon->line_length, &data->weapon->endian);
    weapon_puts(data, 80);
    mlx_destroy_image(data->mlx, data->weapon->img);
}

int render(void *cub)
{
    t_cub3d *data = (t_cub3d *)cub;
    cast_all_rays(data);
    render_map(data);
    render_weapon(data);
    mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
}
void init(t_cub3d *data)
{
    data->player = malloc(sizeof(t_player));
    data->ray = malloc(sizeof(t_ray));
    data->image = malloc(sizeof(t_image));
    data->minimap = malloc(sizeof(t_image));
    data->weapon = malloc(sizeof(t_image));
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    data->image->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->image->addr = mlx_get_data_addr(data->image->img, &data->image->bits_per_pixel, &data->image->line_length, &data->image->endian);
}

int main(int ac, char **av)
{
    t_cub3d data;

    if (ac == 2)
    {
        if (!parse_data(&data, av[1]))
        {
            write(2, "error\n", 6);
            exit(1);
        }
        init(&data);
        get_player_pos(&data);
         init_key_state(&data.keys);

        // Hook the key press and release events
        mlx_hook(data.win, 2, 1L << 0, key_press, &data);
        mlx_hook(data.win, 3, 1L << 1, key_release, &data);
        mlx_hook(data.win, 17, 1L << 17, &ft_exit, NULL);

        // Set up the main loop to handle movement and rendering
        mlx_loop_hook(data.mlx, render, &data);

        mlx_loop(data.mlx);
    }
    else
        write(1, "USAGE ./cube3d [map]\n", 22);
    return (0);
}
