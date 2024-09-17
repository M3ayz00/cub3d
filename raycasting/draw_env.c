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
	uint32_t	color;

	color = get_rgb(255,data->textures->ceiling->r,data->textures->ceiling->g,data->textures->ceiling->b);
    while (l < end)
    {
        my_mlx_pixel_put(data->image, i, l, color);
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
	uint32_t	color;

	color = get_rgb(255, data->textures->floor->r, data->textures->floor->g, data->textures->floor->b);
    while (l < end)
    {
        my_mlx_pixel_put(data->image, i, l, color);
        l++;
    }
}


int get_background_color(t_cub3d *data, double start_x, double start_y, double angle)
{
    double ray_x = start_x;
    double ray_y = start_y;
    double step_size = 0.1; // Adjust based on desired ray resolution
    int background_color;
    int color;

    while (1)
    {
        // Move the ray forward
        ray_x += cos(angle) * step_size;
        ray_y += sin(angle) * step_size;
        // Ensure (ray_x, ray_y) is within bounds
        if (ray_x < 0 || ray_x >= WIDTH || ray_y < 0 || ray_y >= HEIGHT)
            return get_rgb(0, 0, 0, 0); // Return default color if out of bounds
        // Fetch the color from the scene
        background_color = get_texture_color(data->image, (int)ray_x, (int)ray_y);

        // Check if the color is non-transparent (not black in this case)
        if (background_color != -16777216) // Assume black is transparent
            return background_color;

        // Optionally, break if the ray exceeds a maximum length
        // Adjust max_length as needed
        double max_length = 1000.0;
        double current_length = sqrt(pow(ray_x - start_x, 2) + pow(ray_y - start_y, 2));
        if (current_length > max_length)
            return get_rgb(0, 0, 0, 0); // Return default color if max length exceeded
    }
}


void	render_door(t_cub3d *data, int i, int start, int end)
{
	t_image		*door;
	t_render	tools;
	int			y;
	int			frame_index;

	door = &data->doors->door_frames[0];
    if (data->ray->hit_door)
    {
        frame_index = (int)(data->doors->timer[data->map2->mapY][data->map2->mapX] * (DOOR_FRAMES - 1));
        door = &data->doors->door_frames[frame_index];
    }
	tools.x = data->ray->hitX - floor(data->ray->hitX);
	if (data->ray->is_vertical)
		tools.x = data->ray->hitY - floor(data->ray->hitY);
	tools.column = (int)(tools.x * door->width);
	if (tools.column >= door->width)
		tools.column = door->width - 1;
	tools.slice_height = end - start;
	tools.scale = (float)door->height / tools.slice_height;
	for (y = start; y < end; y++) {
		tools.y = (int)((y - start) * tools.scale);
		if (tools.y >= door->height)
			tools.y = door->height - 1;
		tools.color = get_texture_color(door, tools.column, tools.y);
		if (tools.color == -16777216)
		{
			 // Continue raycasting beyond the door
            double ray_angle = (data->player->angle - (FOV / 2) + (i * (FOV / (WIDTH / 50))));
            double distance = sqrt(pow(data->ray->hitX - data->player->posX, 2) + pow(data->ray->hitY - data->player->posY, 2));
            double offset_distance = distance + 1; // Adding some offset to avoid clipping at edge
            int background_color = get_background_color(data, data->player->posX, data->player->posY, ray_angle);
            my_mlx_pixel_put(data->image, i, y, background_color);
		}
		else if (tools.color !=  -16777216)
			my_mlx_pixel_put(data->image, i, y, tools.color);
	}
}
