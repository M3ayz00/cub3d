#include "../cub3d.h"

void	check_x_collision(t_cub3d *cub3d, double newpos_x)
{
	if (cub3d->map2->map[(int)floor(cub3d->player->pos_y
			- MARGIN)][(int)floor(newpos_x - MARGIN)] != '1'
		&& cub3d->map2->map[(int)floor(cub3d->player->pos_y
			+ MARGIN)][(int)floor(newpos_x - MARGIN)] != '1'
		&& cub3d->map2->map[(int)floor(cub3d->player->pos_y
			- MARGIN)][(int)floor(newpos_x + MARGIN)] != '1'
		&& cub3d->map2->map[(int)floor(cub3d->player->pos_y
			+ MARGIN)][(int)floor(newpos_x + MARGIN)] != '1')
	{
		// No collision in X direction, allow X movement
		cub3d->player->pos_x = newpos_x;
	}
}
void	check_y_collision(t_cub3d *cub3d, double newpos_y)
{
	if (cub3d->map2->map[(int)floor(newpos_y
			- MARGIN)][(int)floor(cub3d->player->pos_x - MARGIN)] != '1'
		&& cub3d->map2->map[(int)floor(newpos_y
			+ MARGIN)][(int)floor(cub3d->player->pos_x - MARGIN)] != '1'
		&& cub3d->map2->map[(int)floor(newpos_y
			- MARGIN)][(int)floor(cub3d->player->pos_x + MARGIN)] != '1'
		&& cub3d->map2->map[(int)floor(newpos_y
			+ MARGIN)][(int)floor(cub3d->player->pos_x + MARGIN)] != '1')
	{
		// No collision in Y direction, allow Y movement

		cub3d->player->pos_y = newpos_y;
	}
}

int	is_collision(t_cub3d *cub3d, double newpos_x, double newpos_y)
{
	// Check surrounding tiles for collisions
	return (cub3d->map2->map[(int)floor(newpos_y - MARGIN)][(int)floor(newpos_x
			- MARGIN)] == '1' || cub3d->map2->map[(int)floor(newpos_y
			- MARGIN)][(int)floor(newpos_x + MARGIN)] == '1'
		|| cub3d->map2->map[(int)floor(newpos_y + MARGIN)][(int)floor(newpos_x
			- MARGIN)] == '1' || cub3d->map2->map[(int)floor(newpos_y
			+ MARGIN)][(int)floor(newpos_x + MARGIN)] == '1');
}

void	check_wall_collision(t_cub3d *cub3d, double newpos_x, double newpos_y)
{
	if (!is_collision(cub3d, newpos_x, newpos_y))
	{
		// No collisions, update both X and Y positions
		cub3d->player->pos_x = newpos_x;
		cub3d->player->pos_y = newpos_y;
	}
	else
	{
		// Check movement in X direction
		check_x_collision(cub3d, newpos_x);
		// Check movement in Y direction
		check_y_collision(cub3d, newpos_y);
	}
}

void	handle_movement(t_cub3d *cub3d)
{
	double newpos_x;
	double newpos_y;
	float sensitivity;

	newpos_x = cub3d->player->pos_x;
	newpos_y = cub3d->player->pos_y;
	sensitivity = 0.5;
	if (cub3d->keys.forward)
		ft_move(cub3d, &newpos_x, &newpos_y, FORWARD);
	if (cub3d->keys.backward)
		ft_move(cub3d, &newpos_x, &newpos_y, BACKWARD);
	if (cub3d->keys.left)
		strafing(cub3d, &newpos_x, &newpos_y, LEFT);
	if (cub3d->keys.right)
		strafing(cub3d, &newpos_x, &newpos_y, RIGHT);
	if (cub3d->keys.rotate_left == 1)
		cub3d->player->angle -= ROT_SPEED;
	if (cub3d->keys.rotate_left == 2)
		cub3d->player->angle -= abs(cub3d->keys.delta_x) * SENSITIVITY;
	if (cub3d->keys.rotate_right == 1)
		cub3d->player->angle += ROT_SPEED;
	if (cub3d->keys.rotate_right == 2)
		cub3d->player->angle += abs(cub3d->keys.delta_x) * SENSITIVITY;
	check_wall_collision(cub3d, newpos_x, newpos_y);
	cub3d->keys.rotate_left = 0;
	cub3d->keys.rotate_right = 0;
	cub3d->keys.delta_x = 0;
	if (cub3d->keys.rotate_left == 2 || cub3d->keys.rotate_right == 2)
		cub3d->keys.rotate_left = 0, cub3d->keys.rotate_right = 0,
			cub3d->keys.delta_x = 0;
}
