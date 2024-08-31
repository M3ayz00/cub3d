#include "../cub3d.h"

void my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void my_mlx_pixel_put2(t_image *image, int x, int y, int color)
{
    char *dst;

    dst = image->addr + ((y+10) * image->line_length + (x+10) * (image->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

// Function to get the color from a texture at a specific coordinate
uint32_t get_texture_color(t_image *texture, int x, int y) {
    // Ensure coordinates are within bounds
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height) {
        return 0; // Return black or transparent color for out-of-bounds
    }

    // Calculate the address offset for the pixel
    char *pixel = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
    return *(uint32_t *)pixel;
}
void render_ceil(t_cub3d *data, int i, int end)
{
     int l = 0;
    while (l < end)
    {
        my_mlx_pixel_put(data->image, i, l, get_rgb(255,data->textures->ceiling->r,data->textures->ceiling->g,data->textures->ceiling->b));
        l++;
    }
}
 


void render_ceil_bonus(t_cub3d *data, int i, int end)
{
        int j;
        int texture_x, texture_y;
        t_image *ceiling_texture = &data->textures->ceil_tex;

        j = 0;
        while (j < end)
        {
            // Calculate texture coordinates
            // Example: Simple mapping based on screen coordinates
            texture_x = (i * ceiling_texture->width) / WIDTH;
            texture_y = (j * ceiling_texture->height) / HEIGHT;

            // Get the color from the ceiling texture
            uint32_t color = get_texture_color(ceiling_texture, texture_x, texture_y);

            // Draw the pixel with the texture color
            my_mlx_pixel_put(data->image, i, j, color);

            j++;
        }
}




// Function to render walls with full texture mapping
void render_walls(t_cub3d *data, int i, int start, int end) {
    // Determine the texture to use based on the ray direction
    int texture_index;
    if (data->ray->is_vertical) {
        texture_index = (data->ray->stepX > 0) ? 2 : 3; // East or West
    } else {
        texture_index = (data->ray->stepY > 0) ? 0 : 1; // North or South
    }

    // Access the texture
    t_image *texture = &data->wall_textures[texture_index];

    // Calculate the texture column based on the wall hit position
    double wall_x;
    if (data->ray->is_vertical) {
        wall_x = data->ray->hitY - floor(data->ray->hitY); // Fractional part of the hit position
    } else {
        wall_x = data->ray->hitX - floor(data->ray->hitX); // Fractional part of the hit position
    }
    int texture_column = (int)(wall_x * texture->width);
    if (texture_column >= texture->width) {
        texture_column = texture->width - 1;
    }

    // Calculate the height of the wall slice
    int wall_slice_height = end - start;

    // Adjust for perspective correction
    float texture_scale = (float)texture->height / wall_slice_height;

    // Render the wall slice with the texture
    for (int y = start; y < end; y++) {
        // Calculate the Y coordinate in the texture based on the wall slice height
        int texture_y = (int)((y - start) * texture_scale);
        if (texture_y >= texture->height) {
            texture_y = texture->height - 1;
        }

        // Fetch the color from the texture bitmap
        uint32_t color = get_texture_color(texture, texture_column, texture_y);

        // Draw the pixel with the texture color
        my_mlx_pixel_put(data->image, i, y, color);
    }
}



void render_floor(t_cub3d *data, int i, int start, int end)
{
    int l = start;
    while (l < end)
    {
        my_mlx_pixel_put(data->image, i, l, get_rgb(255,data->textures->floor->r,data->textures->floor->g,data->textures->floor->b));
        l++;
    }
}
