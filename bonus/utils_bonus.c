/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:56:35 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/22 23:30:05 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_door_is_open_at(int map_x, int map_y, t_cub3d *cub3d)
{
	return (cub3d->doors->is_open[map_y][map_x]);
}

int	get_texel(t_image weapon, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= weapon.width || y < 0 || y >= weapon.height)
		return (0);
	pixel = weapon.addr + (y * weapon.line_length + x * (weapon.bits_per_pixel
				/ 8));
	return (*(int *)pixel);
}

int	ft_exit_bonus(t_cub3d *cub3d)
{
	free_weapon_frames(cub3d);
	free_strs(cub3d->map->map);
	free_doors(cub3d);
	free_map(&cub3d->map);
	if (cub3d->textures->ceil_tex.img)
	{
		mlx_destroy_image(cub3d->mlx, cub3d->textures->ceil_tex.img);
		cub3d->textures->ceil_tex.img = NULL;
	}
	free_textures(&cub3d->textures);
	free_struct_bonus(cub3d);
	if (cub3d->image->img)
		mlx_destroy_image(cub3d->mlx, cub3d->image->img);
	if (cub3d->image)
		free(cub3d->image);
	if (cub3d->win)
		mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	if (cub3d->mlx)
		free(cub3d->mlx);
	exit(0);
	return (0);
}

int	key_press_bonus(int key, t_cub3d *cub3d)
{
	if (key == ESC_KEY)
		ft_exit_bonus(cub3d);
	else if (key == W_KEY)
		cub3d->keys.forward = 1;
	else if (key == S_KEY)
		cub3d->keys.backward = 1;
	else if (key == A_KEY)
		cub3d->keys.left = 1;
	else if (key == D_KEY)
		cub3d->keys.right = 1;
	else if (key == LEFT_KEY)
		cub3d->keys.rotate_left = 1;
	else if (key == RIGHT_KEY)
		cub3d->keys.rotate_right = 1;
	else if (key == E_KEY)
		cub3d->keys.e = 1;
	return (0);
}

int	check_filenames(char *filenames[])
{
	int	i;

	i = 0;
	while (i < FRAME_COUNT)
	{
		if (!check_file(filenames[i]))
			return (write(2, "error\n", 7), 0);
		i++;
	}
	return (1);
}
