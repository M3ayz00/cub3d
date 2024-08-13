#include "../cub3d.h"

void get_player_pos(t_cub3d *data)
{
    char **map = get_arr(data->map2->rows);
    int i = 0;
    int j = 0;
    data->map2->map = map;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N')
            {
                data->player->posX = j;
                data->player->posY = i;
                data->player->angle = 0.0;
            }
            else if (map[i][j] == 'S')
            {
                data->player->posX = j;
                data->player->posY = i;
                data->player->angle = M_PI;
            }
            else if (map[i][j] == 'W')
            {
                data->player->posX = j;
                data->player->posY = i;
                data->player->angle = 3 * M_PI / 2;
            }
            else if (map[i][j] == 'E')
            {
                data->player->posX = j;
                data->player->posY = i;
                data->player->angle = M_PI / 2;
            }
            write(1, &map[i][j], 1);
            j++;
        }
        i++;
    }
}