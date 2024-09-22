/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpp_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 06:19:36 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/22 21:21:36 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calc_scale_and_position(t_cub3d *cub3d, t_weapon_vars *vars,
		int current_frame)
{
	vars->screen_width = WIDTH;
	vars->screen_height = HEIGHT;
	vars->image_width = cub3d->frames[current_frame].width;
	vars->image_height = cub3d->frames[current_frame].height;
	vars->scale_x = (float)vars->screen_width / 1.5 / vars->image_width;
	vars->scale_y = (float)vars->screen_height / 1.5 / vars->image_height;
	vars->start_x = (vars->screen_width - (int)(vars->image_width
				* vars->scale_x)) / 2;
	vars->start_y = vars->screen_height - (int)(vars->image_height
			* vars->scale_y) - 10;
}

void	draw_weapon_img(t_cub3d *cub3d, t_weapon_vars *vars, int current_frame)
{
	int	color;
	int	original_x;
	int	original_y;

	vars->y = 0;
	while (vars->y < (int)(vars->image_height * vars->scale_y))
	{
		vars->x = 0;
		while (vars->x < (int)(vars->image_width * vars->scale_x))
		{
			original_x = (int)(vars->x / vars->scale_x);
			original_y = (int)(vars->y / vars->scale_y);
			color = get_texel(cub3d->frames[current_frame], original_x,
					original_y);
			if (color != 0 && color != -16777216)
				my_mlx_pixel_put2(cub3d->image, vars->start_x + vars->x,
					vars->start_y + vars->y, color);
			vars->x++;
		}
		vars->y++;
	}
}

void	render_weapon(t_cub3d *cub3d, int current_frame)
{
	t_weapon_vars	vars;

	calc_scale_and_position(cub3d, &vars, current_frame);
	draw_weapon_img(cub3d, &vars, current_frame);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->image->img, 0, 0);
}

void	initialize_filenames(char *filenames[])
{
	filenames[0] = "bonus/textures/idle/tile000.xpm";
	filenames[1] = "bonus/textures/idle/tile001.xpm";
	filenames[2] = "bonus/textures/idle/tile002.xpm";
	filenames[3] = "bonus/textures/idle/tile003.xpm";
	filenames[4] = "bonus/textures/idle/tile004.xpm";
	filenames[5] = "bonus/textures/idle/tile005.xpm";
	filenames[6] = "bonus/textures/idle/tile006.xpm";
	filenames[7] = "bonus/textures/idle/tile007.xpm";
	filenames[8] = "bonus/textures/idle/tile008.xpm";
	filenames[9] = "bonus/textures/idle/tile009.xpm";
	filenames[10] = "bonus/textures/idle/tile010.xpm";
	filenames[11] = "bonus/textures/idle/tile011.xpm";
	filenames[12] = "bonus/textures/idle/tile012.xpm";
	filenames[13] = "bonus/textures/idle/tile013.xpm";
	filenames[14] = "bonus/textures/idle/tile014.xpm";
	filenames[15] = "bonus/textures/idle/tile015.xpm";
	filenames[16] = "bonus/textures/idle/tile016.xpm";
	filenames[17] = "bonus/textures/idle/tile017.xpm";
	filenames[18] = "bonus/textures/idle/tile018.xpm";
	filenames[19] = "bonus/textures/idle/tile019.xpm";
	filenames[20] = "bonus/textures/idle/tile020.xpm";
	filenames[21] = "bonus/textures/idle/tile021.xpm";
	filenames[22] = "bonus/textures/idle/tile022.xpm";
}

int	check_filenames(char *filenames[])
{
	int i = 0;
	while (i < FRAME_COUNT)
	{
		if (!check_file(filenames[i]))
			return (0);
		i++;
	}
	return (1);
}

void	load_weapon_frames(t_cub3d *cub3d)
{
	int		width;
	int		height;
	int		i;
	char	*filenames[FRAME_COUNT];

	i = 0;
	initialize_filenames(filenames);
	if (!check_filenames(filenames))
		ft_exit_bonus(cub3d, 0);
	while (i < FRAME_COUNT)
	{
		cub3d->frames[i].img = mlx_xpm_file_to_image(cub3d->mlx, filenames[i],
				&width, &height);
		if (!cub3d->frames[i].img)
		{
			write(2, "error loading frame\n", 20);
			ft_exit_bonus(cub3d, 1);
		}
		cub3d->frames[i].width = width;
		cub3d->frames[i].height = height;
		cub3d->frames[i].addr = mlx_get_data_addr(cub3d->frames[i].img,
				&cub3d->frames[i].bits_per_pixel, &cub3d->frames[i].line_length,
				&cub3d->frames[i].endian);
		i++;
	}
}
