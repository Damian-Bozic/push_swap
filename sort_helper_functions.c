/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helper_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:05:11 by dbozic            #+#    #+#             */
/*   Updated: 2024/06/06 17:05:22 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_list **stack, int size)
{
	t_list	*current;
	t_list	*next;

	current = *stack;
	if ((ft_lstsize(*stack) != size))
		return (0);
	while (current->next)
	{
		next = current->next;
		if (current->value > next->value)
			return (0);
		current = next;
	}
	return (1);
}

int	is_ordered(t_list *stack_a, int lowest)
{
	int		i;
	t_list	*last;
	t_list	*current;

	current = stack_a;
	while (lowest != 0)
	{
		current = current->next;
		lowest--;
	}
	i = current->index;
	last = ft_lstlast(stack_a);
	last->next = stack_a;
	while (current->next->index != i)
	{
		if (current->value > current->next->value)
		{
			last->next = NULL;
			return (0);
		}
		current = current->next;
	}
	last->next = NULL;
	return (1);
}

int	find_lowest(t_list *stack)
{
	int		rtn;
	int		i;
	int		v;
	t_list	*current;

	i = 0;
	current = stack;
	while (current && current->status == 0)
	{
		i++;
		current = current->next;
	}
	rtn = i;
	if (current)
		v = current->value;
	while (current && current->next)
	{
		i++;
		current = current->next;
		if (current->value < v && (current->status == 1))
			rtn = i;
		if (current->value < v && (current->status == 1))
			v = current->value;
	}
	return (rtn);
}

void	sort_indexes(t_list **stack_a, int size)
{
	t_list	*current;
	int		i;
	int		j;

	j = 0;
	while (j < size)
	{
		current = *stack_a;
		i = find_lowest(*stack_a);
		while (i != 0)
		{
			current = current->next;
			i--;
		}
		current->status = 0;
		current->index = j;
		j++;
	}
	current = *stack_a;
	while (current)
	{
		current->status = 1;
		current = current->next;
	}
}

int	find_largest(t_list *stack)
{
	int		rtn;
	int		i;
	int		v;
	t_list	*current;

	i = 0;
	current = stack;
	while (current && current->status == 0)
	{
		i++;
		current = current->next;
	}
	rtn = i;
	if (current)
		v = current->value;
	while (current && current->next)
	{
		i++;
		current = current->next;
		if (current->value > v && (current->status == 1))
			rtn = i;
		if (current->value > v && (current->status == 1))
			v = current->value;
	}
	return (rtn);
}
