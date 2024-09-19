/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:30:09 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/19 16:43:43 by msaadidi         ###   ########.fr       */
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
	t_split	tools;

	if (!s)
		return (NULL);
	tools.count = count_words(s, set);
	if (tools.count == 0)
		return (NULL);
	tools.strings = (char **)ft_calloc(tools.count + 1, sizeof(char *));
	if (!tools.strings)
		return (NULL);
	tools.i = 0;
	tools.j = 0;
	while (s[tools.i])
	{
		if (is_c_in_str(s[tools.i], set) && s[tools.i++])
			continue ;
		tools.strings[tools.j] = word(s, set, tools.i);
		if (tools.strings[tools.j] == NULL)
			return (free_all(tools.strings, tools.j), NULL);
		tools.i += ft_strlen(tools.strings[tools.j++]);
	}
	tools.strings[tools.j] = NULL;
	return (tools.strings);
}
