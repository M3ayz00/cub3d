#include "../cub3d.h"

int	get_door_state_at(int map_x, int map_y, t_cub3d *data)
{
	if (map_x < 0 || map_x >= data->map2->width || map_y < 0 || map_y >= data->map2->height)
		return (-1);
	if (data->map2->map[map_y][map_x] == 'D')
		return (data->doors->state[map_y][map_x]);
	return (-1);
}

double	get_door_timer_at(int map_x, int map_y, t_cub3d *data)
{
	if (map_x < 0 || map_x >= data->map2->width || map_y < 0 || map_y >= data->map2->height)
		return (-1);
	if (data->map2->map[map_y][map_x] == 'D')
		return (data->doors->timer[map_y][map_x]);
	return (-1);
}

int	get_texel(t_image weapon, int x, int y)
{
	char *pixel;

	if (x < 0 || x >= weapon.width || y < 0 || y >= weapon.height)
		return (0);

	pixel = weapon.addr + (y * weapon.line_length + x * (weapon.bits_per_pixel
				/ 8));
	return (*(int *)pixel);
}
