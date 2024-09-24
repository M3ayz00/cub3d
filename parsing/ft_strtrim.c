/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:30:41 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/24 21:34:38 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_rows(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

static int	ft_start(char *set, char *s)
{
	int	i;

	i = 0;
	while (s[i] && (ft_strchr(set, s[i])))
		i++;
	return (i);
}

static int	ft_end(char *set, char *s)
{
	int	j;

	j = ft_strlen(s) - 1;
	while (j > 0 && (ft_strchr(set, s[j])))
		j--;
	return (j);
}

char	*ft_strtrim(char *s, char *set)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	if (!s || !set)
		return (NULL);
	i = ft_start(set, s);
	j = ft_end(set, s);
	j++;
	if (i < j)
	{
		tmp = ft_calloc(j - i + 1, sizeof(char));
		if (!tmp)
			return (NULL);
		ft_memcpy(tmp, s + i, j - i);
		tmp[j - i] = '\0';
	}
	else
		return (NULL);
	return (tmp);
}
