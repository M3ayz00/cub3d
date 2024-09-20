/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 07:05:49 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/20 07:05:55 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_ceil_bonus(t_cub3d *data, int i, int end)
{
	int			j;
	int			texture_x;
	int			texture_y;
	t_image		*ceiling_texture;
	uint32_t	color;

	j = 0;
	ceiling_texture = &data->textures->ceil_tex;
	while (j < end)
	{
		texture_x = (i * ceiling_texture->width) / WIDTH;
		texture_y = (j * ceiling_texture->height) / HEIGHT;
		color = get_texture_color(ceiling_texture, texture_x, texture_y);
		my_mlx_pixel_put(data->image, i, j, color);
		j++;
	}
}

void	init_ceiling_texture(t_cub3d *data)
{
	data->textures->ceil_tex.img = mlx_xpm_file_to_image(data->mlx,
			"textures/sky_dark.xpm", &data->textures->ceil_tex.width,
			&data->textures->ceil_tex.height);
	if (!data->textures->ceil_tex.img)
	{
		write(2, "error loading sky texture\n", 26);
		ft_exit(data);
	}
	data->textures->ceil_tex.addr = \
	mlx_get_data_addr(data->textures->ceil_tex.img,
			&data->textures->ceil_tex.bits_per_pixel,
			&data->textures->ceil_tex.line_length,
			&data->textures->ceil_tex.endian);
}
