/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:18:40 by dbozic            #+#    #+#             */
/*   Updated: 2024/05/08 14:18:41 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Functions for Demonstration
/* void	printlist(t_list *lst)
{
	t_list	*current;
	int		i;

	i = 0;
	current = lst;
	if (!lst)
	{
		ft_printf("List %p contents:\nNULL\n", lst);
		return ;
	}
	ft_printf("List %p contents:\n", lst);
	while (current)
	{
		ft_printf("Node: %d,	Index: %d,	Value: %d,	Status: %d\n",
			i, current->index, current->value, current->status);
		current = current->next;
		i++;
	}
}

// made for ranges -500 to 500
void	printlist2(t_list *lst)
{
	t_list	*current;
	int		i;
	int		j;


	i = 0;
	j = 0;
	current = lst;
	if (!lst)
	{
		ft_printf("List %p contents:\nNULL\n", lst);
		return ;
	}
	ft_printf("List %p contents:\n", lst);
	while (current)
	{
		ft_printf("%d = ", j);
		i = current->value;
		i += 500;
		while (i > 0)
		{
			ft_printf("O");
			i -= 10;
		}
		ft_printf("\n");
		current = current->next;
		j++;
	}
} */

void	sort_stack(t_list *stack_a, t_list *stack_b, int size)
{
	if (size <= 3)
		sort_tiny(&stack_a, &stack_b, find_lowest(stack_a));
	else if (size <= 7)
		sort_small(&stack_a, &stack_b, find_lowest(stack_a));
	else
		sort_big(&stack_a, &stack_b, NULL, NULL);
	ft_lstclearmod(&stack_a);
	ft_lstclearmod(&stack_b);
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	char	**array;

	array = NULL;
	if (argc == 2)
		array = ft_split(argv[1], ' ');
	else if (argc > 2)
		array = arraydup(&argv[1]);
	if (!array || argc < 2)
		return (0);
	if (checkfilters(array) == 0)
		return (0);
	stack_a = strarray_to_intlist(array);
	freearray(array);
	if (!stack_a)
		return (0);
	if (!check_lst_for_dup(stack_a))
		return (0);
	sort_stack(stack_a, NULL, ft_lstsize(stack_a));
	return (1);
}
// <= 3 values gets sorted by hard coded solution,		max moves 2-3
// > 3 - <= 7 gets sorted by insertion sort algorithm,	max moves 11
// > 7 - <= 100 gets sorted by case sort,				avg moves ~700	max 1131
// 500 elements gets sorted by case sort,				avg moves ~5700	max 6492

//  	Code Cemetary

/* t_list	*empty_intlst(int size)
{
	t_list	*lst;
	t_list	*new_node;
	int		i;

	if (size <= 0)
		return (NULL);
	i = 0;
	lst = NULL;
	new_node = lst;
	while (size > 0)
	{
		new_node = ft_intlstnew(0, i, 0);
		ft_lstadd_rear(&lst, new_node);
		new_node = NULL;
		size--;
		i++;
	}
	return (lst);
} */

/* int find_lowest(t_list *stack)
{
	int		rtn;
	int		i;
	int		v;
	t_list	*current;

	i = 0;
	rtn = 0;
	if (!stack)
		return (-1);
	current = stack;
	v = current->value;
	while (current->next)
	{
		i++;
		current = current->next;
		if (current->value < v)
		{
			v = current->value;
			rtn = i;
		}
	}
	return (rtn);
} */

/* int	find_closest_low(t_list **stack_a, int size)
{
	int	i;
	int	a;
	int b;
	t_list *half;	

	i = 0;
	a = -1;
	half = *stack_a;
	while (i < (size / 2))
	{
		if (a == -1 && half->index < (ft_lstsize(*stack_a) * 0.1))
			a = i;
		half = half->next;
		i++;
	}
	while (half)
	{
		if (half->index < (ft_lstsize(*stack_a) * 0.1))
			b = i;
		half = half->next;
		i--;
	}
	if (a == -1 || b < a)
		return (0);
	return (1);	
} */

/* int	find_average(t_list *stack)
{
	t_list	*current;
	long long	average;
	int		size;

	size = ft_lstsize(stack);
	current = stack;
	average = current->value;
	current = current->next;
	while (current)
	{
		average = (average + current->value);
		current = current->next;
	}
	average = average / size;
	return (average);
} */