/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 06:13:25 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/20 21:55:13 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	render(void *cub)
{
	t_cub3d		*data;
	static int	current_frame;
	static int	frame_count;
	int			animation_speed;

	data = (t_cub3d *)cub;
	animation_speed = 1;
	handle_movement(data);
	cast_all_rays(data);
	render_map(data);
	door_interaction(data);
	close_doors(data);
	if (frame_count++ >= animation_speed)
	{
		current_frame = (current_frame + 1) % FRAME_COUNT;
		frame_count = 0;
	}
	render_weapon(data, current_frame);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
	return (0);
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
	init_ceiling_texture(data);
}

void	init(t_cub3d *data)
{
	data->player = malloc(sizeof(t_player));
	data->ray = malloc(sizeof(t_ray));
	data->image = malloc(sizeof(t_image));
	data->minimap = malloc(sizeof(t_image));
	data->weapon = malloc(sizeof(t_image));
	data->doors = malloc(sizeof(t_door));
	if (!data->player || !data->ray || !data->image || !data->minimap
		|| !data->weapon || !data->doors)
	{
		write(2, "error allocating memory\n", 25);
		ft_exit(data);
	}
	init_doors(&data->doors, data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	data->image->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->image->addr = mlx_get_data_addr(data->image->img,
			&data->image->bits_per_pixel, &data->image->line_length,
			&data->image->endian);
	data->fov = deg_to_rad(60.0);
	load_images(data);
	load_door_frames(data);
	load_weapon_frames(data);
}

int	main(int ac, char **av)
{
	t_cub3d	data;

	if (ac == 2)
	{
		data.bonus = 1;
		if (!parse_data(&data, av[1], data.bonus))
		{
			write(2, "error\n", 6);
			exit(1);
		}
		init(&data);
		get_player_pos(&data);
		init_key_state(&data.keys);
		mlx_mouse_hide(data.mlx, data.win);
		mlx_hook(data.win, 2, 1L << 0, key_press, &data);
		mlx_hook(data.win, 3, 1L << 1, key_release, &data);
		mlx_hook(data.win, 6, 1L << 6, mouse_move, &data);
		mlx_hook(data.win, 17, 1L << 17, &ft_exit, NULL);
		mlx_loop_hook(data.mlx, render, &data);
		mlx_loop(data.mlx);
	}
	else
		write(1, "USAGE: ./cub3d_bonus [map]\n", 28);
	return (0);
}
