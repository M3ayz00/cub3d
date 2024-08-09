/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:59:04 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/09 15:55:46 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while ((s1 && s2) && (s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

int	is_file_valid(char *path)
{
	if (path)
	{
		path += (ft_strlen(path) - 4);
		if (!ft_strcmp(path, ".cub"))
			return (1);
	}
	return (0);
}

int	open_file(char *path)
{
	int	fd;

	fd = -1;
	if(!is_file_valid(path))
		return(fd);
	fd = open(path, O_RDONLY, 0644);
	return (fd);
}
