/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:47:18 by msaadidi          #+#    #+#             */
/*   Updated: 2024/09/22 14:49:14 by msaadidi         ###   ########.fr       */
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
		if (*lst)
			(*lst)->prev = NULL;
		to_rem->next = NULL;
		free(to_rem->row);
		free(to_rem);
		return ;
	}
	curr = *lst;
	prev = NULL;
	remove_x_node(&curr, &prev, &to_rem);
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
