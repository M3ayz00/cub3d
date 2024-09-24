/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 07:05:49 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/24 19:23:39 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_ceil_bonus(t_cub3d *cub3d, int i, int end)
{
	int			j;
	int			texture_x;
	int			texture_y;
	t_image		*ceiling_texture;
	uint32_t	color;

	j = 0;
	ceiling_texture = &cub3d->textures->ceil_tex;
	while (j < end)
	{
		texture_x = (i * ceiling_texture->width) / WIDTH;
		texture_y = (j * ceiling_texture->height) / HEIGHT;
		color = get_texture_color(ceiling_texture, texture_x, texture_y);
		my_mlx_pixel_put(cub3d->image, i, j, color);
		j++;
	}
}

void	init_ceiling_texture(t_cub3d *cub3d)
{
	cub3d->textures->ceil_tex.img = mlx_xpm_file_to_image(cub3d->mlx,
			"textures/sky_dark.xpm", &cub3d->textures->ceil_tex.width,
			&cub3d->textures->ceil_tex.height);
	if (!cub3d->textures->ceil_tex.img)
	{
		write(2, "error loading sky texture\n", 26);
		ft_exit_bonus(cub3d, 1);
	}
	cub3d->textures->ceil_tex.addr = \
	mlx_get_data_addr(cub3d->textures->ceil_tex.img,
			&cub3d->textures->ceil_tex.bits_per_pixel,
			&cub3d->textures->ceil_tex.line_length,
			&cub3d->textures->ceil_tex.endian);
}

void	init_frames(t_cub3d *cub3d, t_image *image, char *filename)
{
	int	height;
	int	width;

	image->img = mlx_xpm_file_to_image(cub3d->mlx, filename,
			&width, &height);
	if (!image->img)
	{
		write(2, "error loading frame\n", 20);
		ft_exit_bonus(cub3d, 1);
	}
	image->width = width;
	image->height = height;
	image->addr = mlx_get_data_addr(image->img,
			&image->bits_per_pixel, &image->line_length,
			&image->endian);
}
