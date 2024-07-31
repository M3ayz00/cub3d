#include "cub3d.h"



int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

double degreeToRadians(double degree) {
    return degree * M_PI / 180.0;
}

void drawLine(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (1) {
        mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color); // Draw current point
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void casting_rays(t_data *data) {
    double rayAngle = data->player->angle - HFOV;
    int raycount = 0;
    while (raycount < WIDTH) {
        // ray path incrementer
        double rayCos = cos(degreeToRadians(rayAngle)) / data->ray->precision;
        double raySin = sin(degreeToRadians(rayAngle)) / data->ray->precision;
        data->ray->x = data->player->x;
        data->ray->y = data->player->y;
        // wall finder
        int wall = 0;
        while (!wall) {
            data->ray->x += rayCos;
            data->ray->y += raySin;
            wall = map[(int)floor(data->ray->y)][(int)floor(data->ray->x)];
        }

        // pythagoras theorem
        double distance = sqrt(pow(data->player->x - data->ray->x, 2) + pow(data->player->y - data->ray->y, 2));

        // wall height
        double wall_height = HALFH / distance;
        int red = 0xFF0000;
        int green = 0x00FF00;
        int cyan = 0x00FFFF;
        drawLine(data->mlx, data->win, raycount, 0, raycount, HALFH - wall_height, cyan);                  // Draw the ceiling (From screen top to screen half height minus wall height)
        drawLine(data->mlx, data->win, raycount, HALFH - wall_height, raycount, HALFH + wall_height, red); // Draw the wall (From screen half height minus wall height to screen half height plus wall height)
        drawLine(data->mlx, data->win, raycount, HALFH + wall_height, raycount, HEIGHT, green);            // Draw the floor (From screen half height plus wall height to screen bottom)

        rayAngle += data->ray->angle;
        raycount++;
    }
}

int key_press(int keycode, t_data *data) {
    if (keycode == 65307) // Escape key
        exit(0);
    if (keycode == 119) { // W key
        double playerCos = cos(degreeToRadians(data->player->angle)) * data->player->speed->move;
        double playerSin = sin(degreeToRadians(data->player->angle)) * data->player->speed->move;

        double newX = data->player->x + playerCos;
        double newY = data->player->y + playerSin;
        if (map[(int)floor(newY)][(int)floor(newX)] == 0) {
            data->player->x = newX;
            data->player->y = newY;
        }
    }
    if (keycode == 115) { // S key
        double playerCos = cos(degreeToRadians(data->player->angle)) * data->player->speed->move;
        double playerSin = sin(degreeToRadians(data->player->angle)) * data->player->speed->move;
        double newX = data->player->x - playerCos;
        double newY = data->player->y - playerSin;

        if (map[(int)floor(newY)][(int)floor(newX)] == 0) {
            data->player->x = newX;
            data->player->y = newY;
        }
    }
    if (keycode == 97) { // A key
        data->player->angle -= data->player->speed->rotation;
    }
    if (keycode == 100) { // D key
        data->player->angle += data->player->speed->rotation;
    }
    mlx_clear_window(data->mlx, data->win);
    casting_rays(data);
    return 0;
}

int main() {
    t_data *data;

    data = malloc(sizeof(t_data));
    data->player = malloc(sizeof(t_player));
    data->ray = malloc(sizeof(t_ray));
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");

    data->player->x = 2;
    data->player->y = 2;
    data->player->angle = 90;
    data->player->speed = malloc(sizeof(t_speed));
    data->player->speed->move = 0.5;
    data->player->speed->rotation = 5.0;

    data->ray->angle = (double)FOV / WIDTH;
    data->ray->precision = 64;

    casting_rays(data);
    mlx_hook(data->win, 2, 1L << 0, key_press, data);
    mlx_loop(data->mlx);

    free(data->player->speed);
    free(data->player);
    free(data->ray);
    free(data);
    return 0;
}
