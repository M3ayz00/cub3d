#include "../cub3d.h"

int calc_height(double distance, int screen_height)
{
    if (distance <= 0)
        return screen_height;
    return (int)(screen_height / distance);
}

char **get_arr(t_lst *lst)
{
    t_lst *tmp;
    int size;
    int i = 0;
    char **arr;

    tmp = lst;
    size = ft_lstsize(lst);
    arr = malloc(sizeof(char *) * (size + 1));
    if (!arr) // Always good to check for malloc failure
        return (NULL);

    while (i < size)
    {
        arr[i] = ft_strdup(tmp->row);
        if (!arr[i]) // Check for strdup failure
        {
            while (i-- > 0)
                free(arr[i]);
            free(arr);
            return (NULL);
        }
        i++;
        tmp = tmp->next;
    }
    arr[i] = NULL;
    return (arr);
}


int get_rgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

int ft_exit(t_cub3d *cub3d)
{
	free_map(&cub3d->map2);
	free_textures(&cub3d->textures);
    exit(0);
    return (0);
}
