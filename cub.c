#include "cub3d.h"



int render(void *cub)
{
    t_cub3d *data = (t_cub3d *)cub;
    handle_movement(data);
    cast_all_rays(data);
    mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
    return (0);
}
void init(t_cub3d *data)
{
    data->player = malloc(sizeof(t_player));
    data->ray = malloc(sizeof(t_ray));
    data->image = malloc(sizeof(t_image));
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    data->image->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->image->addr = mlx_get_data_addr(data->image->img, &data->image->bits_per_pixel, &data->image->line_length, &data->image->endian);
}

void load_images(t_cub3d *data)
{
    int  i = 0;
    char *textures[4] = {data->textures->north,data->textures->west,data->textures->east,data->textures->south};
    while (i < 4)
    {
        data->wall_textures[i].img = mlx_xpm_file_to_image(data->mlx,textures[i],&data->wall_textures[i].width,&data->wall_textures[i].height);
        data->wall_textures[i].addr = mlx_get_data_addr(data->wall_textures[i].img,&data->wall_textures[i].bits_per_pixel,&data->wall_textures[i].line_length,&data->wall_textures[i].endian);
        i++;
    }
    
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

        // Initialize key states
        init_key_state(&data.keys);

        load_images(&data);

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

