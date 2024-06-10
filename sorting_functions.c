/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:12:08 by dbozic            #+#    #+#             */
/*   Updated: 2024/06/06 17:12:55 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// <= 3
void	sort_tiny(t_list **stack_a, t_list **stack_b, int lowest)
{
	if (is_sorted(stack_a, ft_lstsize(*stack_a)) == 1)
		return ;
	else if (is_ordered(*stack_a, lowest))
	{
		if (lowest == 1)
			exec_command(stack_a, stack_b, "ra");
		else
			exec_command(stack_a, stack_b, "rra");
	}
	else
	{
		if (lowest == 0)
			exec_command(stack_a, stack_b, "ra");
		else if (lowest == 1)
			exec_command(stack_a, stack_b, "rra");
		exec_command(stack_a, stack_b, "sa");
		exec_command(stack_a, stack_b, "rra");
	}
}

static void	sort_small_unordered(t_list **stack_a, t_list **stack_b, int size)
{
	while (ft_lstsize(*stack_a) > 3)
	{
		if (find_lowest(*stack_a) > (ft_lstsize(*stack_a) / 2))
			while (find_lowest(*stack_a) != 0)
				exec_command(stack_a, stack_b, "rra");
		else
			while (find_lowest(*stack_a) != 0)
				exec_command(stack_a, stack_b, "ra");
		if (is_sorted(stack_a, ft_lstsize(*stack_a)))
			break ;
		exec_command(stack_a, stack_b, "pb");
	}
	if (!(is_sorted(stack_a, ft_lstsize(*stack_a))))
		sort_tiny(stack_a, stack_b, find_lowest(*stack_a));
	while (ft_lstsize(*stack_a) != size)
		exec_command(stack_a, stack_b, "pa");
}

// > 3 && <= 7
void	sort_small(t_list **stack_a, t_list **stack_b, int lowest)
{
	if (is_sorted(stack_a, ft_lstsize(*stack_a)) == 1)
		return ;
	if (!is_ordered(*stack_a, lowest))
	{
		sort_small_unordered(stack_a, stack_b, ft_lstsize(*stack_a));
		return ;
	}
	if (find_lowest(*stack_a) >= (ft_lstsize(*stack_a) / 2))
		while (!(is_sorted(stack_a, ft_lstsize(*stack_a)) == 1))
			exec_command(stack_a, stack_b, "rra");
	else
		while (!(is_sorted(stack_a, ft_lstsize(*stack_a)) == 1))
			exec_command(stack_a, stack_b, "ra");
}

static void	sort_big2(t_list **s_a, t_list **s_b)
{
	t_list	*a;
	t_list	*b;

	a = *s_a;
	b = *s_b;
	if (ft_lstsize(a) <= 3)
		sort_tiny(s_a, s_b, find_lowest(*s_a));
	else
		sort_small(s_a, s_b, find_lowest(*s_a));
	while (*s_b)
	{
		if (find_largest(*s_b) > (ft_lstsize(*s_b) / 2))
			while (find_largest(*s_b) != 0)
				exec_command(s_a, s_b, "rrb");
		else
			while (find_largest(*s_b) != 0)
				exec_command(s_a, s_b, "rb");
		exec_command(s_a, s_b, "pa");
	}
}

// > 7
void	sort_big(t_list **s_a, t_list **s_b, t_list *a, t_list *b)
{
	while (ft_lstsize(*s_a) > 3 && (!is_ordered(*s_a, find_lowest(*s_a))))
	{
		a = *s_a;
		b = *s_b;
		sort_indexes(s_a, ft_lstsize(*s_a));
		if (a->index < (ft_lstsize(*s_a) * 0.095))
		{
			if (b && b->next && a->value < b->value)
				exec_command(s_a, s_b, "rb");
			exec_command(s_a, s_b, "pb");
		}
		else if (a->next->index < (ft_lstsize(*s_a) * 0.095))
		{
			if (b && b->next && a->next->value < b->value)
				exec_command(s_a, s_b, "rr");
			else
				exec_command(s_a, s_b, "ra");
			exec_command(s_a, s_b, "pb");
		}
		else
			exec_command(s_a, s_b, "ra");
	}
	sort_big2(s_a, s_b);
}
