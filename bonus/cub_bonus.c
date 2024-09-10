#include "../cub3d.h"

int get_texel(t_image weapon, int x, int y)
{
    // Ensure coordinates are within the texture bounds
    if (x < 0 || x >= weapon.width || y < 0 || y >= weapon.height)
    {
        return 0; // Return black or transparent color for out-of-bounds
    }
    // Calculate the address of the pixel in the texture's data
    char *pixel = weapon.addr + (y * weapon.line_length + x * (weapon.bits_per_pixel / 8));

    // Return the color of the pixel as an int
    return *(int *)pixel;
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
    data->weapon->img = mlx_xpm_file_to_image(data->mlx, "bonus/textures/knife2.xpm", &width, &height);
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
    handle_movement(data);

    cast_all_rays(data);
    render_map(data);
    render_weapon(data);
    mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
    return (0);
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
void load_images(t_cub3d *data)
{
    int i = 0;
    char *textures[4] = {data->textures->north, data->textures->west, data->textures->east, data->textures->south};
    while (i < 4)
    {
        data->wall_textures[i].img = mlx_xpm_file_to_image(data->mlx, textures[i], &data->wall_textures[i].width, &data->wall_textures[i].height);
        data->wall_textures[i].addr = mlx_get_data_addr(data->wall_textures[i].img, &data->wall_textures[i].bits_per_pixel, &data->wall_textures[i].line_length, &data->wall_textures[i].endian);
        i++;
    }

    data->textures->ceil_tex.img = mlx_xpm_file_to_image(data->mlx, "textures/sky_dark.xpm", &data->textures->ceil_tex.width, &data->textures->ceil_tex.height);
    // if (!data->textures->ceil_tex->img)
    // {
    //     printf("failed \n");
    // return;
    // }
    data->textures->ceil_tex.addr = mlx_get_data_addr(data->textures->ceil_tex.img, &data->textures->ceil_tex.bits_per_pixel, &data->textures->ceil_tex.line_length, &data->textures->ceil_tex.endian);
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
        load_images(&data);
                mlx_mouse_hide(data.mlx,data.win);

        // Hook the key press and release events
        mlx_hook(data.win, 2, 1L << 0, key_press, &data);   // Key press
        mlx_hook(data.win, 3, 1L << 1, key_release, &data); // Key release
        mlx_hook(data.win, 6, 1L << 6, mouse_move, &data);  // Mouse movement
        mlx_hook(data.win, 17, 1L << 17, &ft_exit, NULL);

        // Set up the main loop to handle movement and rendering
        mlx_loop_hook(data.mlx, render, &data);

        mlx_loop(data.mlx);
        // show_cursor(display, (Window)data.win);
    }
    else
        write(1, "USAGE ./cube3d [map]\n", 22);
    return (0);
}
