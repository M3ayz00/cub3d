/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:11:32 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/21 14:59:21 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_put2(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + ((y + 10) * image->line_length + (x + 10)
			* (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

uint32_t	get_texture_color(t_image *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(uint32_t *)pixel);
}

void	get_wall_x(t_cub3d *cub3d, t_render *wall)
{
	if (cub3d->ray->is_vertical)
		wall->x = cub3d->ray->hit_y - floor(cub3d->ray->hit_y);
	else
		wall->x = cub3d->ray->hit_x - floor(cub3d->ray->hit_x);
}
