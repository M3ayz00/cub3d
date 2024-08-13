/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:30:09 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/08 17:53:49 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_c_in_str(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

static char	*word(char *s, char *set, int j)
{
	char	*word;
	int		i;

	i = 0;
	word = NULL;
	while (s[j] && !is_c_in_str(s[j], set))
	{
		i++;
		j++;
	}
	word = (char *)ft_calloc(i + 1, sizeof(char));
	if (!word)
		return (NULL);
	j -= i;
	i = 0;
	while (!is_c_in_str(s[j], set) && s[j])
		word[i++] = s[j++];
	return (word);
}

static size_t	count_words(char *s, char *set)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (is_c_in_str(*s, set))
			s++;
		if (*s)
			count++;
		while (*s && !is_c_in_str(*s, set))
			s++;
	}
	return (count);
}

static void	free_all(char **strs, int i)
{
	while (i >= 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
}

char	**ft_split(char *s, char *set)
{
	char	**strings;
	int		i;
	int		j;
	int		count;

	if (!s)
		return (NULL);
	count = count_words(s, set);
	if (count == 0)
		return (NULL);
	strings = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!strings)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (is_c_in_str(s[i], set) && s[i++])
			continue ;
		strings[j] = word(s, set, i);
		if (strings[j] == NULL)
			return (free_all(strings, j), NULL);
		i += ft_strlen(strings[j++]);
	}
	strings[j] = NULL;
	return (strings);
}
