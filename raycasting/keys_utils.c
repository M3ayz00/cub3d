/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:03:06 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/20 00:03:08 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int key, t_cub3d *data)
{
	if (key == ESC_KEY)
		exit(0);
	else if (key == W_KEY)
		data->keys.forward = 1;
	else if (key == S_KEY)
		data->keys.backward = 1;
	else if (key == A_KEY)
		data->keys.left = 1;
	else if (key == D_KEY)
		data->keys.right = 1;
	else if (key == LEFT_KEY)
		data->keys.rotate_left = 1;
	else if (key == RIGHT_KEY)
		data->keys.rotate_right = 1;
	return (0);
}

int	key_release(int key, t_cub3d *data)
{
	if (key == W_KEY)
		data->keys.forward = 0;
	else if (key == S_KEY)
		data->keys.backward = 0;
	else if (key == A_KEY)
		data->keys.left = 0;
	else if (key == D_KEY)
		data->keys.right = 0;
	else if (key == LEFT_KEY)
		data->keys.rotate_left = 0;
	else if (key == RIGHT_KEY)
		data->keys.rotate_right = 0;
	return (0);
}
