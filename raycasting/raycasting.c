#include "../cub3d.h"

void dda(t_cub3d *data)
{
    int hit = 0;

    while (hit == 0)
    {
        if (data->ray->sideDistX < data->ray->sideDistY)
        {
            data->ray->sideDistX += data->ray->deltaDistX;
            data->map2->mapX += data->ray->stepX;
            data->ray->side = 0;
        }
        else
        {
            data->ray->sideDistY += data->ray->deltaDistY;
            data->map2->mapY += data->ray->stepY;
            data->ray->side = 1;
        }
        if (data->map2->map[data->map2->mapY][data->map2->mapX] == '1')
            hit = 1;
    }
    if (data->ray->side == 0)
        data->ray->hit_distance = (data->ray->sideDistX - data->ray->deltaDistX);
    else
        data->ray->hit_distance = (data->ray->sideDistY - data->ray->deltaDistY);
}

void get_delta_distance(t_cub3d *data, double rayDirX, double rayDirY)
{
    data->ray->deltaDistX = fabs(1 / rayDirX);
    data->ray->deltaDistY = fabs(1 / rayDirY);

    if (rayDirX < 0)
    {
        data->ray->stepX = -1;
        data->ray->sideDistX = (data->player->posX - data->map2->mapX) * data->ray->deltaDistX;
    }
    else
    {
        data->ray->stepX = 1;
        data->ray->sideDistX = (data->map2->mapX + 1.0 - data->player->posX) * data->ray->deltaDistX;
    }
    if (rayDirY < 0)
    {
        data->ray->stepY = -1;
        data->ray->sideDistY = (data->player->posY - data->map2->mapY) * data->ray->deltaDistY;
    }
    else
    {
        data->ray->stepY = 1;
        data->ray->sideDistY = (data->map2->mapY + 1.0 - data->player->posY) * data->ray->deltaDistY;
    }
}

void cast_ray(t_cub3d *data, double ray_angle)
{
    data->map2->mapX = (int)data->player->posX;
    data->map2->mapY = (int)data->player->posY;

    double rayDirX = cos(ray_angle);
    double rayDirY = sin(ray_angle);
    // get delta distance
    get_delta_distance(data, rayDirX, rayDirY);
    dda(data);

    data->ray->hitX = data->player->posX + data->ray->hit_distance * rayDirX;
    data->ray->hitY = data->player->posY + data->ray->hit_distance * rayDirY;
    data->ray->is_vertical = (data->ray->side == 0);
}

void cast_all_rays(t_cub3d *data)
{
    double angle_step;
    int i;
    int j;
    int wall_height;
    int wall_start;
    int wall_end;

    angle_step = FOV / WIDTH;
    i = 0;
    while (i < WIDTH - 1)
    {
        double ray_angle = data->player->angle - (FOV / 2) + (i * angle_step);
        cast_ray(data, ray_angle);
        wall_start = (HEIGHT / 2) - (calc_height((data->ray->hit_distance * cos(ray_angle - data->player->angle)), HEIGHT) / 2);
        wall_end = (HEIGHT / 2) + (calc_height((data->ray->hit_distance * cos(ray_angle - data->player->angle)), HEIGHT) / 2);
        data->wall_height = wall_end - wall_start;
        render_ceil_bonus(data, i, wall_start);
        render_walls(data, i, wall_start, wall_end);
        render_floor(data, i, wall_end, HEIGHT);
        i++;
    }
}
