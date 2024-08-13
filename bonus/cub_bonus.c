#include "../cub3d.h"

void render(t_cub3d *data)
{
    cast_all_rays(data);
    render_map(data);
    mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
}
void init(t_cub3d *data)
{
    data->player = malloc(sizeof(t_player));
    data->ray = malloc(sizeof(t_ray));
    data->image = malloc(sizeof(t_image));
    data->minimap = malloc(sizeof(t_image));
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
        render(&data);
        mlx_hook(data.win, 2, 1L << 0, key_press, &data);
        mlx_hook(data.win, 17, 1L << 17, &ft_exit, NULL);
        mlx_loop(data.mlx);
    }
    else
        write(1, "USAGE ./cube3d [map]\n", 22);
    return (0);
}
