#include "../cub3d.h"

int is_near_door(t_cub3d *cub3d)
{
	int x = (int)cub3d->player->posX;
	int y = (int)cub3d->player->posY;
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

void ft_move(t_cub3d *data, double *newPosX, double *newPosY, t_direction move)
{
    if (move == FORWARD)
    {
        *newPosX += cos(data->player->angle) * MOVE_SPEED;
        *newPosY += sin(data->player->angle) * MOVE_SPEED;
    }
    else
    {
        *newPosX -= cos(data->player->angle) * MOVE_SPEED;
        *newPosY -= sin(data->player->angle) * MOVE_SPEED;
    }
}

void strafing(t_cub3d *data, double *newPosX, double *newPosY, t_direction dir)
{
    if (dir == LEFT)
    {
        *newPosX += sin(data->player->angle) * MOVE_SPEED;
        *newPosY -= cos(data->player->angle) * MOVE_SPEED;
    }
    else
    {
        *newPosX -= sin(data->player->angle) * MOVE_SPEED;
        *newPosY += cos(data->player->angle) * MOVE_SPEED;
    }
}

void check_wall_colision(t_cub3d *data, double newPosX, double newPosY)
{	
	if (data->map2->map[(int)floor(newPosY - MARGIN)][(int)floor(newPosX - MARGIN)] != '1'// top-left corner
		&&  data->map2->map[(int)floor(newPosY - MARGIN)][(int)floor(newPosX + MARGIN)] != '1' // top-right corner
		&& data->map2->map[(int)floor(newPosY + MARGIN)][(int)floor(newPosX - MARGIN)] != '1' // bottom-left corner
		&& data->map2->map[(int)floor(newPosY + MARGIN)][(int)floor(newPosX + MARGIN)] != '1')    // bottom-right corner
	{
		// If no collisions, update the player's position
		data->player->posX = newPosX;
		data->player->posY = newPosY;
	}
}

void handle_movement(t_cub3d *data)
{
    double newPosX = data->player->posX;
    double newPosY = data->player->posY;

    float sensitivity = 0.5;
	if (data->keys.forward)
		ft_move(data, &newPosX, &newPosY, FORWARD);
	if (data->keys.backward)
		ft_move(data, &newPosX, &newPosY, BACKWARD);
	if (data->keys.left)
		strafing(data, &newPosX, &newPosY, LEFT);
	if (data->keys.right)
		strafing(data, &newPosX, &newPosY, RIGHT);

    if (data->keys.rotate_left == 1)
        data->player->angle -= ROT_SPEED;
    if (data->keys.rotate_left == 2)
        data->player->angle -= abs(data->keys.delta_x) * SENSITIVITY;

    if (data->keys.rotate_right == 1)
        data->player->angle += ROT_SPEED;
    if (data->keys.rotate_right == 2)
        data->player->angle += abs(data->keys.delta_x) * SENSITIVITY;
    check_wall_colision(data, newPosX, newPosY);

    data->keys.rotate_left = 0;
    data->keys.rotate_right = 0;
    data->keys.delta_x = 0;
    if (data->keys.rotate_left == 2 || data->keys.rotate_right == 2)
        data->keys.rotate_left = 0,data->keys.rotate_right = 0,data->keys.delta_x = 0;
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


int key_press(int key, t_cub3d *data)
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
	else if (key == E_KEY)
	{
		int x = (int)data->player->posX;
        int y = (int)data->player->posY;
		if (data->map2->map[y + 1][x] == 'D')
			toggle_door(data, x, y + 1);
		if (data->map2->map[y][x + 1] == 'D')
			toggle_door(data, x + 1, y);
		if (data->map2->map[y - 1][x] == 'D')
			toggle_door(data, x, y - 1);
		if (data->map2->map[y][x - 1] == 'D')
			toggle_door(data, x - 1, y);
	}
    return (0);
}

int key_release(int key, t_cub3d *data)
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
