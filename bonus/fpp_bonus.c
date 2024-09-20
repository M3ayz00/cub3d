/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpp_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 06:19:36 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/20 06:19:38 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calc_scale_and_position(t_cub3d *data, t_weapon_vars *vars,
		int current_frame)
{
	vars->screen_width = WIDTH;
	vars->screen_height = HEIGHT;
	vars->image_width = data->frames[current_frame].width;
	vars->image_height = data->frames[current_frame].height;
	vars->scale_x = (float)vars->screen_width / 1.5 / vars->image_width;
	vars->scale_y = (float)vars->screen_height / 1.5 / vars->image_height;
	vars->start_x = (vars->screen_width - (int)(vars->image_width
				* vars->scale_x)) / 2;
	vars->start_y = vars->screen_height - (int)(vars->image_height
			* vars->scale_y) - 10;
}

void	draw_weapon_img(t_cub3d *data, t_weapon_vars *vars, int current_frame)
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
			color = get_texel(data->frames[current_frame], original_x,
					original_y);
			if (color != 0 && color != -16777216)
				my_mlx_pixel_put2(data->image, vars->start_x + vars->x,
					vars->start_y + vars->y, color);
			vars->x++;
		}
		vars->y++;
	}
}

void	render_weapon(t_cub3d *data, int current_frame)
{
	t_weapon_vars	vars;

	calc_scale_and_position(data, &vars, current_frame);
	draw_weapon_img(data, &vars, current_frame);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
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

void	load_weapon_frames(t_cub3d *data)
{
	int		width;
	int		height;
	int		i;
	char	*filenames[FRAME_COUNT];

	i = 0;
	initialize_filenames(filenames);
	while (i < FRAME_COUNT)
	{
		data->frames[i].img = mlx_xpm_file_to_image(data->mlx, filenames[i],
				&width, &height);
		if (!data->frames[i].img)
		{
			write(2, "error loading frame\n", 20);
			exit(1);
		}
		data->frames[i].width = width;
		data->frames[i].height = height;
		data->frames[i].addr = mlx_get_data_addr(data->frames[i].img,
				&data->frames[i].bits_per_pixel, &data->frames[i].line_length,
				&data->frames[i].endian);
		i++;
	}
}
