/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:31:06 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/20 00:31:07 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(void *cub)
{
	t_cub3d	*data;

	data = (t_cub3d *)cub;
	handle_movement(data);
	cast_all_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
	return (0);
}

void	init(t_cub3d *data)
{
	data->player = malloc(sizeof(t_player));
	data->ray = malloc(sizeof(t_ray));
	data->image = malloc(sizeof(t_image));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	data->image->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image->img)
		ft_exit(data);
	data->image->addr = mlx_get_data_addr(data->image->img,
			&data->image->bits_per_pixel, &data->image->line_length,
			&data->image->endian);
	data->fov = deg_to_rad(60.0);
}

void	load_images(t_cub3d *data)
{
	int		i;
	char	*textures[4];

	i = 0;
	textures[0] = data->textures->north;
	textures[1] = data->textures->south;
	textures[2] = data->textures->east;
	textures[3] = data->textures->west;
	while (i < 4)
	{
		data->wall_t[i].img = mlx_xpm_file_to_image(data->mlx, textures[i],
				&data->wall_t[i].width, &data->wall_t[i].height);
		if (!data->wall_t[i].img)
			ft_exit(data);
		data->wall_t[i].addr = mlx_get_data_addr(data->wall_t[i].img,
				&data->wall_t[i].bits_per_pixel, &data->wall_t[i].line_length,
				&data->wall_t[i].endian);
		if (!data->wall_t[i].addr)
			ft_exit(data);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_cub3d	data;

	if (ac == 2)
	{
		data.bonus = 0;
		if (!parse_data(&data, av[1], data.bonus))
		{
			write(2, "error\n", 6);
			exit(1);
		}
		init(&data);
		get_player_pos(&data);
		init_key_state(&data.keys);
		load_images(&data);
		mlx_hook(data.win, 2, 1L << 0, key_press, &data);
		mlx_hook(data.win, 3, 1L << 1, key_release, &data);
		mlx_hook(data.win, 17, 1L << 17, &ft_exit, NULL);
		mlx_loop_hook(data.mlx, render, &data);
		mlx_loop(data.mlx);
	}
	else
		write(1, "USAGE ./cube3d [map]\n", 22);
	return (0);
}
