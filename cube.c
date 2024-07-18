#include "cub3d.h"


int map[6][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,1,1,0,1},
    {1,0,0,0,0,0,1,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}

};



int	get_rgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void    my_mlx_pixel_put(void *data,void *win, int x, int y, int color)
{
    mlx_pixel_put(data,win , x, y, color);
}

void    draw_circle(void *data,void *win, int center_x, int center_y, int radius, int color)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
          for (int i = center_x - x; i <= center_x + x; i++)
        {
            my_mlx_pixel_put(data, win, i, center_y + y, color);
            my_mlx_pixel_put(data, win, i, center_y - y, color);
        }
        for (int i = center_x - y; i <= center_x + y; i++)
        {
            my_mlx_pixel_put(data, win, i, center_y + x, color);
            my_mlx_pixel_put(data, win, i, center_y - x, color);
        }

        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void draw_scene(t_data *data) {

    int i = 0;
    int j;
    while(i < NUM_ROWS)
    {
        j = 0;
        while(j < NUM_COLS)
        {
            int tile_x = j * TILE_SIZE;
            int tile_y = i * TILE_SIZE;
            int tile_x_g = j * (TILE_SIZE + 1);
            int tile_y_g = i * (TILE_SIZE + 1);
            int tile_color = map[i][j] == 1 ? get_rgb(200,180,77,80) : get_rgb(255,100,5,80);
            int k = 0;
            int l = 0;

            while(k < TILE_SIZE)
            {
                l = 0;
                while(l < TILE_SIZE)
                {
                
                mlx_pixel_put(data->mlx,data->win, tile_x_g+k, tile_y_g+l, tile_color);
                    l++;
                }
                k++;
            }
                if (tile_x == data->player->x && tile_y == data->player->y)
                {
                    int player_center_x = tile_x + TILE_SIZE / 2;
                    int player_center_y = tile_y + TILE_SIZE / 2;
                    draw_circle(data->mlx,data->win, player_center_x+5, player_center_y+5, TILE_SIZE / 4, get_rgb(255, 187, 98, 0));
                }
            j++;
        }
        i++;
    }
 
}

int key_press(int keycode, t_data *data)
{
    if (keycode == 65307) // Escape key
        exit(0);
    if (keycode == 119) // W key
    {
            printf("w pressed\n");

        if (map[data->player->y / TILE_SIZE][data->player->x] == 1)
        {
            printf("wall in front\n");
        }
    }
    if (keycode == 115) // S key
    {

    }
    if (keycode == 97) // A key
    {
    
    }
    if (keycode == 100) // D key
    {
 
    }
    // mlx_clear_window(data->mlx, data->win);
    // draw_scene(data);
    return (0);
}

int main()
{
    t_data *data;
    data = malloc(sizeof(t_data));
    if (!data)
        return (1);
    memset(data,0,sizeof(t_data));
    // data->mlx = mlx_init();
    // data->win = mlx_new_window(data->mlx, NUM_COLS * (TILE_SIZE + 1), NUM_ROWS * (TILE_SIZE + 1), "Cub3D");

    t_player player;

    player.x = NUM_COLS * TILE_SIZE / 2;
    player.y = NUM_ROWS * TILE_SIZE / 2;
    player.turn_dir = 0;
    player.walk_dir = 0;
    player.rot_angle = M_PI / 2;
    player.move_speed = 3.2;
    player.turn_speed = 3 * (M_PI / 180);

    data->player = &player;


            printf("%i",map[0][0]);

    // map[5][5] = 2;
    // int i = 0;
    // int j = 0;
    // while(i < NUM_ROWS)
    // {
    //     j=0;
    //     while(j < NUM_COLS)
    //     {
    //         printf("%d",map[j][j]);
    //         j++;
    //     }
    //     i++;
    // }
    
    // draw_scene(data);
    // mlx_hook(data->win, 2, 1L << 0, key_press, &data);
    
    // mlx_loop(data->mlx);
    
    return 0;
}