#include "../cub3d.h"

void	check_x_collision(t_cub3d *data, double newpos_x)
{
	if (data->map2->map[(int)floor(data->player->pos_y
			- MARGIN)][(int)floor(newpos_x - MARGIN)] != '1'
		&& data->map2->map[(int)floor(data->player->pos_y
			+ MARGIN)][(int)floor(newpos_x - MARGIN)] != '1'
		&& data->map2->map[(int)floor(data->player->pos_y
			- MARGIN)][(int)floor(newpos_x + MARGIN)] != '1'
		&& data->map2->map[(int)floor(data->player->pos_y
			+ MARGIN)][(int)floor(newpos_x + MARGIN)] != '1')
	{
		// No collision in X direction, allow X movement
		data->player->pos_x = newpos_x;
	}
}
void	check_y_collision(t_cub3d *data, double newpos_y)
{
	if (data->map2->map[(int)floor(newpos_y
			- MARGIN)][(int)floor(data->player->pos_x - MARGIN)] != '1'
		&& data->map2->map[(int)floor(newpos_y
			+ MARGIN)][(int)floor(data->player->pos_x - MARGIN)] != '1'
		&& data->map2->map[(int)floor(newpos_y
			- MARGIN)][(int)floor(data->player->pos_x + MARGIN)] != '1'
		&& data->map2->map[(int)floor(newpos_y
			+ MARGIN)][(int)floor(data->player->pos_x + MARGIN)] != '1')
	{
		// No collision in Y direction, allow Y movement
		data->player->pos_y = newpos_y;
	}
}

int	is_collision(t_cub3d *data, double newpos_x, double newpos_y)
{
	// Check surrounding tiles for collisions
	return (data->map2->map[(int)floor(newpos_y - MARGIN)][(int)floor(newpos_x
			- MARGIN)] == '1' || data->map2->map[(int)floor(newpos_y
			- MARGIN)][(int)floor(newpos_x + MARGIN)] == '1'
		|| data->map2->map[(int)floor(newpos_y + MARGIN)][(int)floor(newpos_x
			- MARGIN)] == '1' || data->map2->map[(int)floor(newpos_y
			+ MARGIN)][(int)floor(newpos_x + MARGIN)] == '1');
}

void	check_wall_collision(t_cub3d *data, double newpos_x, double newpos_y)
{
	if (!is_collision(data, newpos_x, newpos_y))
	{
		// No collisions, update both X and Y positions
		data->player->pos_x = newpos_x;
		data->player->pos_y = newpos_y;
	}
	else
	{
		// Check movement in X direction
		check_x_collision(data, newpos_x);
		// Check movement in Y direction
		check_y_collision(data, newpos_y);
	}
}

void	handle_movement(t_cub3d *data)
{
	double newpos_x;
	double newpos_y;
	float sensitivity;

	newpos_x = data->player->pos_x;
	newpos_y = data->player->pos_y;
	sensitivity = 0.5;
	if (data->keys.forward)
		ft_move(data, &newpos_x, &newpos_y, FORWARD);
	if (data->keys.backward)
		ft_move(data, &newpos_x, &newpos_y, BACKWARD);
	if (data->keys.left)
		strafing(data, &newpos_x, &newpos_y, LEFT);
	if (data->keys.right)
		strafing(data, &newpos_x, &newpos_y, RIGHT);
	if (data->keys.rotate_left == 1)
		data->player->angle -= ROT_SPEED;
	if (data->keys.rotate_left == 2)
		data->player->angle -= abs(data->keys.delta_x) * SENSITIVITY;
	if (data->keys.rotate_right == 1)
		data->player->angle += ROT_SPEED;
	if (data->keys.rotate_right == 2)
		data->player->angle += abs(data->keys.delta_x) * SENSITIVITY;
	check_wall_collision(data, newpos_x, newpos_y);
	data->keys.rotate_left = 0;
	data->keys.rotate_right = 0;
	data->keys.delta_x = 0;
	if (data->keys.rotate_left == 2 || data->keys.rotate_right == 2)
		data->keys.rotate_left = 0, data->keys.rotate_right = 0,
			data->keys.delta_x = 0;
}
