#include "../cub3d.h"

int get_texel(t_image weapon, int x, int y)
{
    if (x < 0 || x >= weapon.width || y < 0 || y >= weapon.height)
        return 0;

    char *pixel = weapon.addr + (y * weapon.line_length + x * (weapon.bits_per_pixel / 8));
    return *(int *)pixel;
}

void weapon_puts(t_cub3d *data, int up, int current_frame)
{
    int x, y;
    int color;

    // Screen dimensions
    int screen_width = WIDTH;
    int screen_height = HEIGHT;

    // Original image dimensions
    int image_width = data->frames[current_frame].width;
    int image_height = data->frames[current_frame].height;

    // Scale factor calculation based on window size
    float scale_x = (float)screen_width / 1.5/ image_width;   // Scale image to 1/4 of screen width
    float scale_y = (float)screen_height / 1.5 / image_height; // Scale image to 1/4 of screen height

    // Calculate the position to center the scaled image horizontally and vertically
    int start_x = (screen_width - (int)(image_width * scale_x)) / 2;
    int start_y = screen_height - (int)(image_height * scale_y) - up;

    // Draw the scaled image
    for (y = 0; y < (int)(image_height * scale_y); y++)
    {
        for (x = 0; x < (int)(image_width * scale_x); x++)
        {
            // Calculate the corresponding source pixel from the original image
            int original_x = (int)(x / scale_x);
            int original_y = (int)(y / scale_y);

            // Get the texel color from the original image
            color = get_texel(data->frames[current_frame], original_x, original_y);

            // If the color is not transparent, draw the pixel on the screen
            if (color != 0 && color != -16777216) // Assuming 0 and -16777216 are transparent colors
            {
                my_mlx_pixel_put2(data->image, start_x + x, start_y + y, color);
            }
        }
    }
}

void render_weapon(t_cub3d *data, int current_frame)
{
    // Calculate the position to place the weapon frame at the bottom of the screen
    int up_offset = 10; // You can adjust this value for how far up you want the weapon to be placed
    weapon_puts(data, up_offset, current_frame);

    // Optionally update the window with the new frame of the weapon
    mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
}

void load_weapon_frames(t_cub3d *data)
{
    int width, height;


    char *filenames[FRAME_COUNT] = {
        "bonus/textures/idle/tile000.xpm",
        "bonus/textures/idle/tile001.xpm",
        "bonus/textures/idle/tile002.xpm",
        "bonus/textures/idle/tile003.xpm",
        "bonus/textures/idle/tile004.xpm",
        "bonus/textures/idle/tile005.xpm",
        "bonus/textures/idle/tile006.xpm",
        "bonus/textures/idle/tile007.xpm",
        "bonus/textures/idle/tile008.xpm",
        "bonus/textures/idle/tile009.xpm",
        "bonus/textures/idle/tile010.xpm",
        "bonus/textures/idle/tile011.xpm",
        "bonus/textures/idle/tile012.xpm",
        "bonus/textures/idle/tile013.xpm",
        "bonus/textures/idle/tile014.xpm",
        "bonus/textures/idle/tile015.xpm",
        "bonus/textures/idle/tile016.xpm",
        "bonus/textures/idle/tile017.xpm",
        "bonus/textures/idle/tile018.xpm",
        "bonus/textures/idle/tile019.xpm",
        "bonus/textures/idle/tile020.xpm",
        "bonus/textures/idle/tile021.xpm",
        "bonus/textures/idle/tile022.xpm",

    };

    data->frames->img = malloc(sizeof(t_image) * FRAME_COUNT); // Allocate memory for frames
    if (!data->frames->img)
    {
        write(2, "error allocating frames\n", 24);
        exit(1);
    }

    for (int i = 0; i < FRAME_COUNT; i++)
    {
        data->frames[i].img = mlx_xpm_file_to_image(data->mlx, filenames[i], &width, &height);
        if (!data->frames[i].img)
        {
            write(2, "error loading frame\n", 20);
            exit(1);
        }
        data->frames[i].width = width;
        data->frames[i].height = height;
        data->frames[i].addr = mlx_get_data_addr(data->frames[i].img, &data->frames[i].bits_per_pixel, &data->frames[i].line_length, &data->frames[i].endian);
    }
}

void	load_door_frames(t_cub3d *data)
{
	char *filenames[DOOR_FRAMES] = {
		"bonus/textures/door/door_frame_1.xpm",
		"bonus/textures/door/door_frame_2.xpm",
		"bonus/textures/door/door_frame_3.xpm",
		"bonus/textures/door/door_frame_4.xpm",
		"bonus/textures/door/door_frame_5.xpm",
		"bonus/textures/door/door_frame_6.xpm",
		"bonus/textures/door/door_frame_7.xpm",
		"bonus/textures/door/door_frame_8.xpm",
		"bonus/textures/door/door_frame_9.xpm",
	};
	data->doors->door_frames = malloc(sizeof(t_image) * DOOR_FRAMES);
	if (!data->doors->door_frames)
	{
		write(2, "door frames allocation error\n", 29);
		exit(1);
	}
	for (int i = 0; i < DOOR_FRAMES; i++)
	{
		data->doors->door_frames[i].img = mlx_xpm_file_to_image(data->mlx,
			filenames[i], &data->doors->door_frames[i].width,
			&data->doors->door_frames[i].height);
		if (!data->doors->door_frames[i].img)
		{
			write(2, "door frames loading error\n", 28);
			exit(1);
		}
		data->doors->door_frames[i].addr = mlx_get_data_addr(data->doors->door_frames[i].img,
			&data->doors->door_frames[i].bits_per_pixel,
			&data->doors->door_frames[i].line_length,
			&data->doors->door_frames[i].endian);
	}
}

void	update_doors(t_cub3d *cub3d)
{
	int y = 0;
	double delta_time = 1.0 / 60.0;
	while (y < HEIGHT)
	{
		int x = 0;
		while (x < WIDTH)
		{
			if (cub3d->doors->state[y][x] == 1) //opening
			{
				cub3d->doors->timer[y][x] += delta_time * 2;
				if (cub3d->doors->timer[y][x] >= 1.0)
				{
					cub3d->doors->timer[y][x] = 1.0;
					cub3d->doors->state[y][x] = 2; // open
				}
			}
			else if (cub3d->doors->state[y][x] == 3) // closing
			{
				cub3d->doors->timer[y][x] -= delta_time * 2;
				if (cub3d->doors->timer[y][x] <= 0.0)
				{
					cub3d->doors->timer[y][x] = 0.0;
					cub3d->doors->state[y][x] = 0; // open
				}
			}
			x++;
		}
		y++;
	}
}

int render(void *cub)
{
    t_cub3d *data = (t_cub3d *)cub;
    handle_movement(data);
    cast_all_rays(data);
    render_map(data);
	update_doors(data);
	door_interaction(data);


    static int current_frame = 0;
    static int frame_count = 0;
    int animation_speed = 1;

    if (frame_count++ >= animation_speed)
    {
        current_frame = (current_frame + 1) % FRAME_COUNT;
        frame_count = 0;
    }

    render_weapon(data, current_frame);
    mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
    return 0;
}

void	init_doors(t_door **doors)
{
	int y;
	int x;

	y = 0;
	(*doors)->state = malloc(sizeof(int *) * HEIGHT);
	(*doors)->timer = malloc(sizeof(double *) * HEIGHT);
	while (y < HEIGHT)
	{
		(*doors)->state[y] = malloc(sizeof(int) * WIDTH);
		(*doors)->timer[y] = malloc(sizeof(double) * WIDTH);
		x = 0;
		while (x < WIDTH)
		{
			(*doors)->state[y][x] = 0;
			(*doors)->timer[y][x] = 0.0;
			x++;
		}
		y++;
	}
}

void init(t_cub3d *data)
{
    data->player = malloc(sizeof(t_player));
    data->ray = malloc(sizeof(t_ray));
    data->image = malloc(sizeof(t_image));
    data->minimap = malloc(sizeof(t_image));
    data->weapon = malloc(sizeof(t_image));
	data->doors = malloc(sizeof(t_door));
	//check each on its own for better memory management
    if (!data->player || !data->ray || !data->image || !data->minimap || !data->weapon || !data->doors)
    {
        write(2, "error allocating memory\n", 25);
        exit(1);
    }
	init_doors(&data->doors);
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    data->image->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->image->addr = mlx_get_data_addr(data->image->img, &data->image->bits_per_pixel, &data->image->line_length, &data->image->endian);
    data->fov = deg_to_rad(60.0);
}

void load_images(t_cub3d *data)
{
   int		i;
	char	*textures[4];

	i = 0;
	textures[0] = data->textures->north;
	textures[1] = data->textures->south;
	textures[2] = data->textures->east;
	textures[3] = data->textures->west;
	while (i < 4)
	{
		data->wall_t[i].img = mlx_xpm_file_to_image(data->mlx, textures[i],
				&data->wall_t[i].width, &data->wall_t[i].height);
		if (!data->wall_t[i].img)
			ft_exit(data);
		data->wall_t[i].addr = mlx_get_data_addr(data->wall_t[i].img,
				&data->wall_t[i].bits_per_pixel, &data->wall_t[i].line_length,
				&data->wall_t[i].endian);
		if (!data->wall_t[i].addr)
			ft_exit(data);
		i++;
	}

    data->textures->ceil_tex.img = mlx_xpm_file_to_image(data->mlx, "textures/sky_dark.xpm", &data->textures->ceil_tex.width, &data->textures->ceil_tex.height);
    if (!data->textures->ceil_tex.img)
    {
        write(2, "error loading sky texture\n", 26);
        exit(1);
    }
    data->textures->ceil_tex.addr = mlx_get_data_addr(data->textures->ceil_tex.img, &data->textures->ceil_tex.bits_per_pixel, &data->textures->ceil_tex.line_length, &data->textures->ceil_tex.endian);
	if (data->textures->door)
	{
		printf("DOOR_TEXTURE : %s\n", data->textures->door);
		data->textures->door_tex.img = mlx_xpm_file_to_image(data->mlx, data->textures->door, &data->textures->door_tex.width, &data->textures->door_tex.height);
		if (!data->textures->door_tex.img)

		{
			write(2, "error loading door texture\n", 26);
			exit(1);
		}
		data->textures->door_tex.addr = mlx_get_data_addr(data->textures->door_tex.img, &data->textures->door_tex.bits_per_pixel, &data->textures->door_tex.line_length, &data->textures->door_tex.endian);
	}
}

int main(int ac, char **av)
{
    t_cub3d data;

    if (ac == 2)
    {
		data.bonus = 1;
        if (!parse_data(&data, av[1], data.bonus))
        {
            write(2, "error\n", 6);
            exit(1);
        }

        init(&data);
        get_player_pos(&data);
        init_key_state(&data.keys);
        load_images(&data);
		load_door_frames(&data);
        load_weapon_frames(&data); // Load weapon frames

        mlx_mouse_hide(data.mlx, data.win); // Hide the mouse

        mlx_hook(data.win, 2, 1L << 0, key_press, &data);
        mlx_hook(data.win, 3, 1L << 1, key_release, &data);
        mlx_hook(data.win, 6, 1L << 6, mouse_move, &data);
        mlx_hook(data.win, 17, 1L << 17, &ft_exit, NULL);

        mlx_loop_hook(data.mlx, render, &data);
        mlx_loop(data.mlx);
    }
    else
    {
        write(1, "USAGE: ./cub3d [map]\n", 22);
    }

    return 0;
}
