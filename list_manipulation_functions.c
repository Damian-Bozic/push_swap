/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:01:49 by dbozic            #+#    #+#             */
/*   Updated: 2024/06/06 17:03:27 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*ft_intlstnew(int integer, int index, int status)
{
	t_list	*starting_node;

	starting_node = (t_list *)malloc(sizeof(t_list));
	if (!starting_node)
		return (NULL);
	starting_node->value = integer;
	starting_node->index = index;
	starting_node->status = status;
	starting_node->next = (NULL);
	return (starting_node);
}

void	ft_lstadd_rear(t_list **lst, t_list *new_node)
{
	t_list	*current;

	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	ft_lstclearmod(t_list **lst)
{
	t_list	*current;
	t_list	*next;

	if (!*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

t_list	*strarray_to_intlist(char **array)
{
	int		i;
	int		nbr;
	t_list	*lst;
	t_list	*temp;

	i = 0;
	nbr = 0;
	lst = NULL;
	while (array[i])
	{
		if (!ft_atoimod(array[i], &nbr))
		{
			ft_lstclearmod(&lst);
			return (NULL);
		}
		temp = ft_intlstnew(nbr, i, 1);
		ft_lstadd_rear(&lst, temp);
		temp = NULL;
		i++;
	}
	return (lst);
}
