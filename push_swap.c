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

int	freearray(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (1);
}

char	**arraydup(char **array)
{
	int		i;
	char	**rtn;

	i = 0;
	while (array[i])
		i++;
	rtn = malloc((i + 1) * sizeof(char *));
	if (!rtn)
		return (0);
	i = 0;
	while (array[i])
	{
		rtn[i] = ft_strdup(array[i]);
		if (!rtn[i])
		{
			freearray(rtn);
			return (0);
		}
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}

int	checkfilters(char **array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (array[i])
	{
		while (array[i][j])
		{
			if ((ft_isdigit(array[i][j]) == 0) &&
				(!(array[i][j] == '-' && j == 0)))
			{
				ft_putstr_fd("Error\n", 2);
				freearray(array);
				return (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	ft_atoimod(const char *nptr, int *rtn)
{
	long	nbr;
	int		sign;
	int		i;

	nbr = 0;
	sign = 1;
	i = 0;
	if (!*nptr)
		return (0);
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-')
		nptr++;
	while (ft_isdigit(*nptr) && i++ < 11)
	{
		nbr = nbr * 10 + ((*nptr) - '0');
		nptr++;
	}
	if ((nbr > 2147483647 && sign == 1) || (nbr > 2147483648 && sign == -1))
		ft_putstr_fd("Error\n", 2);
	if ((nbr > 2147483647 && sign == 1) || (nbr > 2147483648 && sign == -1))
		return (0);
	nbr = nbr * sign;
	*rtn = nbr;
	return (1);
}

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

int	check_lst_for_dup(t_list *lst)
{
	t_list	*current;
	t_list	*compare;

	current = lst;
	while (current)
	{
		compare = current->next;
		while (compare)
		{
			if (compare->value == current->value)
			{
				ft_lstclearmod(&lst);
				ft_putstr_fd("Error\n", 2);
				return (0);
			}
			compare = compare->next;
		}
		current = current->next;
	}
	return (1);
}

t_list	*swap_nodes(t_list *first_node)
{
	t_list	*second_node;

	if (!first_node->next)
	{
		ft_printf("Swap Error\n");
		return (NULL);
	}
	second_node = first_node->next;
	first_node->next = second_node->next;
	second_node->next = first_node;
	first_node = second_node;
	return (first_node);
}

t_list	*push_node(t_list *sender, t_list **id_reciever)
{
	t_list	*temp;
	t_list	*reciever;

	temp = sender->next;
	reciever = *id_reciever;
	sender->next = reciever;
	*id_reciever = sender;
	return (temp);
}

t_list	*rotate_list(t_list *list, int rotation)
{
	t_list	*temp;
	t_list	*rtn;

	if (!list || rotation == 0)
		return (NULL);
	if (rotation >= 0)
	{
		rtn = list->next;
		temp = ft_lstlast(list);
		temp->next = list;
		list->next = NULL;
	}
	else
	{
		temp = list;
		rtn = temp->next;
		while (rtn->next)
		{
			temp = temp->next;
			rtn = rtn->next;
		}
		rtn->next = list;
		temp->next = NULL;
	}
	return (rtn);
}

void	exec_command2(t_list **stack_a, t_list **stack_b, char *cmd)
{
	if (!(ft_strncmp(cmd, "rra", 3)))
		*stack_a = rotate_list(*stack_a, -1);
	else if (!(ft_strncmp(cmd, "rrb", 3)))
		*stack_b = rotate_list(*stack_b, -1);
	else if (!(ft_strncmp(cmd, "rrr", 3)))
	{
		*stack_a = rotate_list(*stack_a, -1);
		*stack_b = rotate_list(*stack_b, -1);
	}
}

void	exec_command(t_list **stack_a, t_list **stack_b, char *cmd)
{
	if (!(ft_strncmp(cmd, "sa", 3)))
		*stack_a = swap_nodes(*stack_a);
	else if (!(ft_strncmp(cmd, "sb", 3)))
		*stack_b = swap_nodes(*stack_b);
	else if (!(ft_strncmp(cmd, "ss", 3)))
	{
		*stack_a = swap_nodes(*stack_a);
		*stack_b = swap_nodes(*stack_b);
	}
	else if (!(ft_strncmp(cmd, "pa", 3)))
		*stack_b = push_node(*stack_b, stack_a);
	else if (!(ft_strncmp(cmd, "pb", 3)))
		*stack_a = push_node(*stack_a, stack_b);
	else if (!(ft_strncmp(cmd, "ra", 3)))
		*stack_a = rotate_list(*stack_a, 1);
	else if (!(ft_strncmp(cmd, "rb", 3)))
		*stack_b = rotate_list(*stack_b, 1);
	else if (!(ft_strncmp(cmd, "rr", 3)))
	{
		*stack_a = rotate_list(*stack_a, 1);
		*stack_b = rotate_list(*stack_b, 1);
	}
	else
		exec_command2(stack_a, stack_b, cmd);
	ft_printf("%s\n", cmd);
}

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

void	sort_small_unordered(t_list **stack_a, t_list **stack_b, int size)
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

void	sort_big2(t_list **s_a, t_list **s_b)
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
	// ft_printf("Is sorted: %d\n", is_sorted(&stack_a, size));
	// printlist(stack_a);

int	main(int argv, char **argc)
{
	t_list	*stack_a;
	char	**array;

	array = NULL;
	if (argv == 2)
		array = ft_split(argc[1], '\n');
	else if (argv > 2)
		array = arraydup(&argc[1]);
	if (!array || argv < 2)
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