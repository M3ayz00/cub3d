#include "cub3d.h"

Player player = {
    .x = MAP_SIZE / 2.0,
    .y = MAP_SIZE / 2.0,
    .dir = 0.0,
};

int map[MAP_SIZE][MAP_SIZE] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}

};

void draw_scene(void *mlx, void *win) {
    for (int x = 0; x <= WIDTH; x = x+50) {
        double ray_dir = player.dir + (x - WIDTH / 2.0) / WIDTH;
        double ray_x = player.x;
        double ray_y = player.y;
        int map_x = (int)ray_x;
        int map_y = (int)ray_y;
        
        // Step through the map until we hit a wall
        // while (map_x >= 0 && map_x < MAP_SIZE && map_y >= 0 && map_y < MAP_SIZE && map[map_x][map_y] == 0) {
          
        // }
          ray_x += cos(ray_dir);
            ray_y += sin(ray_dir);
            map_x = (int)ray_x;
            map_y = (int)ray_y;
        // // Calculate the distance to the wall
        double dist = sqrt((ray_x - player.x) * (ray_x - player.x) + (ray_y - player.y) * (ray_y - player.y));
        
        // // Draw the wall slice
        int height = (int)(HEIGHT / dist);
        int cell_w = 100;
        int cell_h = 100;
        for (int y = 0; y <= HEIGHT ; y = y+50)
        {
        mlx_pixel_put(mlx,win,x,y,255);

        }
        // void *wall = mlx_xpm_file_to_image(mlx,"./image/wall2.xpm",&cell_w,&cell_h);
        // mlx_put_image_to_window(mlx, win,wall, x, HEIGHT / 2 - height);
    }
}

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, WIDTH, HEIGHT, "Cube3D");
    
    draw_scene(mlx, win);
    
    mlx_loop(mlx);
    
    return 0;
}