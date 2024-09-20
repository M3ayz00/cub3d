#include "../cub3d.h"

int is_near_door(t_cub3d *cub3d)
{
	int x = (int)cub3d->player->pos_x;
	int y = (int)cub3d->player->pos_y;
	return ( cub3d->map2->map[y + 1][x] == 'D'
		|| cub3d->map2->map[y][x + 1] == 'D'
		|| cub3d->map2->map[y - 1][x] == 'D'
		|| cub3d->map2->map[y][x - 1] == 'D');
}

void	door_interaction(t_cub3d *cub3d)
{
	int y = 0;
	while (cub3d->map2->map[y])
	{
		int x = 0;
		while (cub3d->map2->map[y][x])
		{
			if (cub3d->map2->map[y][x] == 'D')
			{
				if (is_near_door(cub3d))
					mlx_string_put(cub3d->mlx, cub3d->win, WIDTH / 2, HEIGHT / 2, get_rgb(0, 255, 255, 255), "Press [E] to interact");
			}
			x++;
		}
		y++;
	}
}

void init_key_state(t_key_state *keys)
{
    keys->forward = 0;
    keys->backward = 0;
    keys->left = 0;
    keys->right = 0;
    keys->rotate_left = 0;
    keys->rotate_right = 0;
}

void ft_move(t_cub3d *data, double *newpos_x, double *newpos_y, t_direction move)
{
    if (move == FORWARD)
    {
        *newpos_x += cos(data->player->angle) * MOVE_SPEED;
        *newpos_y += sin(data->player->angle) * MOVE_SPEED;
    }
    else
    {
        *newpos_x -= cos(data->player->angle) * MOVE_SPEED;
        *newpos_y -= sin(data->player->angle) * MOVE_SPEED;
    }
}

void strafing(t_cub3d *data, double *newpos_x, double *newpos_y, t_direction dir)
{
    if (dir == LEFT)
    {
        *newpos_x += sin(data->player->angle) * MOVE_SPEED;
        *newpos_y -= cos(data->player->angle) * MOVE_SPEED;
    }
    else
    {
        *newpos_x -= sin(data->player->angle) * MOVE_SPEED;
        *newpos_y += cos(data->player->angle) * MOVE_SPEED;
    }
}

void check_wall_colision(t_cub3d *data, double newpos_x, double newpos_y)
{
   if (data->map2->map[(int)floor(newpos_y - MARGIN)][(int)floor(newpos_x - MARGIN)] != '1' &&
    data->map2->map[(int)floor(newpos_y - MARGIN)][(int)floor(newpos_x + MARGIN)] != '1' &&
    data->map2->map[(int)floor(newpos_y + MARGIN)][(int)floor(newpos_x - MARGIN)] != '1' &&
    data->map2->map[(int)floor(newpos_y + MARGIN)][(int)floor(newpos_x + MARGIN)] != '1')
{
    // No collisions, update both X and Y positions
    data->player->pos_x = newpos_x;
    data->player->pos_y = newpos_y;
}
else
{
    // Check X direction only
    if (data->map2->map[(int)floor(data->player->pos_y - MARGIN)][(int)floor(newpos_x - MARGIN)] != '1' &&
        data->map2->map[(int)floor(data->player->pos_y + MARGIN)][(int)floor(newpos_x - MARGIN)] != '1' &&
        data->map2->map[(int)floor(data->player->pos_y - MARGIN)][(int)floor(newpos_x + MARGIN)] != '1' &&
        data->map2->map[(int)floor(data->player->pos_y + MARGIN)][(int)floor(newpos_x + MARGIN)] != '1')
    {
        // No collision in X direction, allow X movement
        data->player->pos_x = newpos_x;
    }

    // Check Y direction only
    if (data->map2->map[(int)floor(newpos_y - MARGIN)][(int)floor(data->player->pos_x - MARGIN)] != '1' &&
        data->map2->map[(int)floor(newpos_y + MARGIN)][(int)floor(data->player->pos_x - MARGIN)] != '1' &&
        data->map2->map[(int)floor(newpos_y - MARGIN)][(int)floor(data->player->pos_x + MARGIN)] != '1' &&
        data->map2->map[(int)floor(newpos_y + MARGIN)][(int)floor(data->player->pos_x + MARGIN)] != '1')
    {
        // No collision in Y direction, allow Y movement
        data->player->pos_y = newpos_y;
    }
}

}

void handle_movement(t_cub3d *data)
{
    double newpos_x = data->player->pos_x;
    double newpos_y = data->player->pos_y;

    float sensitivity = 0.5;
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
    check_wall_colision(data, newpos_x, newpos_y);

    data->keys.rotate_left = 0;
    data->keys.rotate_right = 0;
    data->keys.delta_x = 0;
    if (data->keys.rotate_left == 2 || data->keys.rotate_right == 2)
        data->keys.rotate_left = 0, data->keys.rotate_right = 0, data->keys.delta_x = 0;
}

int mouse_move(int x, int y, t_cub3d *data)
{
    static int last_x = -1;
    int window_center_x = WIDTH / 2;
    int widow_center_y = HEIGHT / 2;

    if (last_x != -1)
    {
        data->keys.delta_x = (x - window_center_x);

        if (data->keys.delta_x != 0)
        {
            if (data->keys.delta_x > 0)
                data->keys.rotate_right = 2;
            else if (data->keys.delta_x < 0)
                data->keys.rotate_left = 2;
        }
        if (x != window_center_x || y != widow_center_y)
            mlx_mouse_move(data->mlx, data->win, window_center_x, widow_center_y);
    }
    last_x = x;
    return (0);
}

void toggle_door(t_cub3d *data, int door_x, int door_y)
{
    if (data->doors->state[door_y][door_x] == 0)
        data->doors->state[door_y][door_x] = 1;
    else if (data->doors->state[door_y][door_x] == 2)
        data->doors->state[door_y][door_x] = 3;
}



