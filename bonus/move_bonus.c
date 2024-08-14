#include "../cub3d.h"

double get_delta_time()
{
    static struct timeval last_time;
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    double delta_time = (current_time.tv_sec - last_time.tv_sec) +
                        (current_time.tv_usec - last_time.tv_usec) * 1e-6;
    last_time = current_time;

    return delta_time;
}

double delta_time;

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
    if (data->map2->map[(int)floor(newPosY - MARGIN)][(int)floor(newPosX - MARGIN)] != '1' &&
        data->map2->map[(int)floor(newPosY - MARGIN)][(int)floor(newPosX + MARGIN)] != '1' &&
        data->map2->map[(int)floor(newPosY + MARGIN)][(int)floor(newPosX - MARGIN)] != '1')
    {
        data->player->posX = newPosX;
        data->player->posY = newPosY;
        render(data);
    }
}

int key_press(int key, t_cub3d *data)
{
    delta_time = get_delta_time();
    double newPosX;
    double newPosY;

    newPosX = data->player->posX;
    newPosY = data->player->posY;
    if (key == ESC_KEY)
        exit(0);
    else if (key == W_KEY)
        ft_move(data, &newPosX, &newPosY, FORWARD);
    else if (key == S_KEY)
        ft_move(data, &newPosX, &newPosY, BACKWARD);
    else if (key == A_KEY)
        strafing(data, &newPosX, &newPosY, LEFT);
    else if (key == D_KEY)
        strafing(data, &newPosX, &newPosY, RIGHT);
    else if (key == LEFT_KEY)
        data->player->angle -= ROT_SPEED;
    else if (key == RIGHT_KEY)
        data->player->angle += ROT_SPEED;
    check_wall_colision(data, newPosX, newPosY);

    return (0);
}
