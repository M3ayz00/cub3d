/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:31:55 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/21 14:59:21 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_player_pos(t_player *player, int i, int j, char direction)
{
	player->pos_x = j + 0.3;
	player->pos_y = i + 0.3;
	if (direction == 'N')
		player->angle = 3 * M_PI / 2;
	else if (direction == 'S')
		player->angle = M_PI / 2;
	else if (direction == 'W')
		player->angle = M_PI;
	else if (direction == 'E')
		player->angle = 0.0;
}

void	get_player_pos(t_cub3d *cub3d)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = get_arr(cub3d->map->rows);
	cub3d->map->map = map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
				set_player_pos(cub3d->player, i, j, map[i][j]);
			j++;
		}
		i++;
	}
}
