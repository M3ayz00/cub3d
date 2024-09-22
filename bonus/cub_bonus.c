/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 06:13:25 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/22 20:06:24 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	render(void *cub)
{
	t_cub3d		*cub3d;
	static int	current_frame;
	static int	frame_count;
	int			animation_speed;

	cub3d = (t_cub3d *)cub;
	animation_speed = 1;
	handle_movement(cub3d);
	cast_all_rays(cub3d);
	render_map(cub3d);
	if (frame_count++ >= animation_speed)
	{
		current_frame = (current_frame + 1) % FRAME_COUNT;
		frame_count = 0;
	}
	render_weapon(cub3d, current_frame);
	if (!get_door_is_open_at((int)floor(cub3d->player->pos_x),
			(int)floor(cub3d->player->pos_y), cub3d))
		close_doors(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->image->img, 0, 0);
	door_interaction(cub3d);
	return (0);
}

void	load_images(t_cub3d *cub3d)
{
	int		i;
	char	*textures[4];

	i = 0;
	textures[0] = cub3d->textures->north;
	textures[1] = cub3d->textures->south;
	textures[2] = cub3d->textures->east;
	textures[3] = cub3d->textures->west;
	while (i < 4)
	{
		cub3d->wall_t[i].img = mlx_xpm_file_to_image(cub3d->mlx, textures[i],
				&cub3d->wall_t[i].width, &cub3d->wall_t[i].height);
		if (!cub3d->wall_t[i].img)
			ft_exit_bonus(cub3d);
		cub3d->wall_t[i].addr = mlx_get_data_addr(cub3d->wall_t[i].img,
				&cub3d->wall_t[i].bits_per_pixel, &cub3d->wall_t[i].line_length,
				&cub3d->wall_t[i].endian);
		if (!cub3d->wall_t[i].addr)
			ft_exit_bonus(cub3d);
		i++;
	}
	init_ceiling_texture(cub3d);
}

void	init(t_cub3d *cub3d)
{
	cub3d->player = malloc(sizeof(t_player));
	cub3d->ray = malloc(sizeof(t_ray));
	cub3d->image = malloc(sizeof(t_image));
	cub3d->minimap = malloc(sizeof(t_image));
	cub3d->weapon = malloc(sizeof(t_image));
	cub3d->doors = malloc(sizeof(t_door));
	if (!cub3d->player || !cub3d->ray || !cub3d->image || !cub3d->minimap
		|| !cub3d->weapon || !cub3d->doors)
	{
		write(2, "error allocating memory\n", 25);
		ft_exit_bonus(cub3d);
	}
	init_doors(&cub3d->doors, cub3d);
	cub3d->mlx = mlx_init();
	cub3d->fov = deg_to_rad(60.0);
	load_images(cub3d);
	load_door_frames(cub3d);
	load_weapon_frames(cub3d);
	cub3d->win = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "cub3d");
	cub3d->image->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	cub3d->image->addr = mlx_get_data_addr(cub3d->image->img,
			&cub3d->image->bits_per_pixel, &cub3d->image->line_length,
			&cub3d->image->endian);
}

int	main(int ac, char **av)
{
	t_cub3d	cub3d;

	if (ac == 2)
	{
		cub3d.bonus = 1;
		if (!parse_cub3d(&cub3d, av[1], cub3d.bonus))
		{
			write(2, "error\n", 6);
			exit(1);
		}
		init(&cub3d);
		get_player_pos(&cub3d);
		init_key_state(&cub3d.keys);
		mlx_mouse_hide(cub3d.mlx, cub3d.win);
		mlx_hook(cub3d.win, 2, 1L << 0, key_press_bonus, &cub3d);
		mlx_hook(cub3d.win, 3, 1L << 1, key_release, &cub3d);
		mlx_hook(cub3d.win, 6, 1L << 6, mouse_move, &cub3d);
		mlx_hook(cub3d.win, 17, 1L << 17, &ft_exit_bonus, NULL);
		mlx_loop_hook(cub3d.mlx, render, &cub3d);
		mlx_loop(cub3d.mlx);
	}
	else
		write(1, "USAGE: ./cub3d_bonus [map]\n", 28);
	return (0);
}
