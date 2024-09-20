#include "../cub3d.h"

void render_door(t_cub3d *data, int i, int start, int end)
{
    t_image *door;
    t_render tools;
    int y;
    int frame_index;

    door = &data->doors->door_frames[0];
    if (data->ray->hit_door)
    {
        frame_index = (int)(data->doors->timer[data->map2->map_y][data->map2->map_x] * (DOOR_FRAMES - 1));
        door = &data->doors->door_frames[frame_index];
    }
    tools.x = data->ray->hit_x - floor(data->ray->hit_x);
    if (data->ray->is_vertical)
        tools.x = data->ray->hit_y - floor(data->ray->hit_y);
    tools.column = (int)(tools.x * door->width);
    if (tools.column >= door->width)
        tools.column = door->width - 1;
    tools.slice_height = end - start;
    tools.scale = (float)door->height / tools.slice_height;
    for (y = start; y < end; y++)
    {
        tools.y = (int)((y - start) * tools.scale);
        if (tools.y >= door->height)
            tools.y = door->height - 1;
        tools.color = get_texture_color(door, tools.column, tools.y);
        if (tools.color != -16777216)
            my_mlx_pixel_put(data->image, i, y, tools.color);
    }
}

void render_ceil_bonus(t_cub3d *data, int i, int end)
{
    int j;
    int texture_x;
    int texture_y;
    t_image *ceiling_texture;
    uint32_t color;

    j = 0;
    ceiling_texture = &data->textures->ceil_tex;
    while (j < end)
    {
        texture_x = (i * ceiling_texture->width) / WIDTH;
        texture_y = (j * ceiling_texture->height) / HEIGHT;
        color = get_texture_color(ceiling_texture, texture_x, texture_y);
        my_mlx_pixel_put(data->image, i, j, color);
        j++;
    }
}