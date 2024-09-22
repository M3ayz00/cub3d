/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:03:06 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/22 21:08:56 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_release(int key, t_cub3d *cub3d)
{
	if (key == W_KEY)
		cub3d->keys.forward = 0;
	else if (key == S_KEY)
		cub3d->keys.backward = 0;
	else if (key == A_KEY)
		cub3d->keys.left = 0;
	else if (key == D_KEY)
		cub3d->keys.right = 0;
	else if (key == LEFT_KEY)
		cub3d->keys.rotate_left = 0;
	else if (key == RIGHT_KEY)
		cub3d->keys.rotate_right = 0;
	else if (key == E_KEY)
		cub3d->keys.e = 0;
	return (0);
}
