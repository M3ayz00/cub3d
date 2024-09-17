/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:47:18 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/17 21:30:40 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_lst	*ft_lst_before(t_lst *lst, t_lst *curr)
{
	t_lst	*head;

	if (!lst || !curr)
		return (NULL);
	head = lst;
	while (head->next && head->next != curr)
		head = head->next;
	return (head);
}

void	ft_lst_remove(t_lst	**lst, t_lst *to_rem)
{
	t_lst	*curr;
	t_lst	*prev;

	if (!lst || !(*lst) || !to_rem)
		return ;
	if (*lst == to_rem)
	{
		*lst = (*lst)->next;
		(*lst)->prev = NULL;
		to_rem->next = NULL;
		free(to_rem->row);
		free(to_rem);
		return ;
	}
	curr = *lst;
	prev = NULL;
	while (curr)
	{
		if (curr == to_rem)
		{
			if (prev)
				prev->next = curr->next;
			free(to_rem->row);
			free(to_rem);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

t_lst	*ft_lstlast(t_lst *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_lst	*lst_new(char *row)
{
	t_lst	*lst;

	lst = malloc(sizeof(t_lst));
	if (!lst)
		return (NULL);
	lst->row = ft_strdup(row);
	lst->row_len = ft_strlen(row);
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
}

int	ft_lstsize(t_lst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_lstclear(t_lst **lst)
{
	t_lst	*curr;
	t_lst	*next;

	if (!lst || !(*lst))
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr->row);
		free(curr);
		curr = next;
	}
	*lst = NULL;
}
