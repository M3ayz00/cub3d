#include "../cub3d.h"

int	get_texel(t_image weapon, int x, int y)
{
	char *pixel;

	if (x < 0 || x >= weapon.width || y < 0 || y >= weapon.height)
		return (0);

	pixel = weapon.addr + (y * weapon.line_length + x * (weapon.bits_per_pixel
				/ 8));
	return (*(int *)pixel);
}