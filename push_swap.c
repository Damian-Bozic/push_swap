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
	if (nbr > 2147483647)
		ft_putstr_fd("Error\n", 2);
	if (nbr > 2147483647)
		return (0);
	nbr = nbr * sign;
	*rtn = nbr;
	return (1);
}

t_list	*ft_intlstnew(int integer, int index)
{
	t_list	*starting_node;

	starting_node = (t_list *)malloc(sizeof(t_list));
	if (!starting_node)
		return (NULL);
	starting_node->integer = integer;
	starting_node->index = index;
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
			return (NULL);
		temp = ft_intlstnew(nbr, i);
		ft_lstadd_rear(&lst, temp);
		temp = NULL;
		i++;
	}
	return (lst);
}

t_list	*empty_intlst(int size)
{
	t_list	*lst;
	t_list	*new_node;
	int		i;

	if (size <= 0)
		return (NULL);
	i = 0;
	new_node = lst;
	while (size > 0)
	{
		new_node = ft_intlstnew(-2147483648, i);
		ft_lstadd_rear(&lst, new_node);
		size--;
		i++;
	}
	return (lst);
}

void	printlist(t_list *lst)
{
	t_list *current;
	int	i;

	i = 0;
	current = lst;
	if (!lst)
	{
		ft_printf("List %p is NULL\n", lst);
		return ;
	}
	ft_printf("List %p contents:\n", lst);
	while (current)
	{
		ft_printf("Node: %d,	Index: %d,	Value: %d\n", i,
			current->index, current->integer);
		current = current->next;
		i++;
	}
}

void	sort_stack(t_list *stack_a, t_list *stack_b, int size)
{
	int a = ft_lstsize(stack_a);
	int b = ft_lstsize(stack_b);
	printf("stack sizes\n a: %d\n b: %d\n", a, b);
	printlist(stack_a);
	printlist(stack_b);
}

int	main(int argv, char **argc)
{
	t_list	*stack_a;
	char	**array;

	if (argv == 2)
		array = ft_split(argc[1], '\n');
	else if (argv > 2)
		array = arraydup(&argc[1]);
	if (!array || argv < 2)
		return (0);
	if (checkfilters(array) == 0)
		return (0);
	stack_a = strarray_to_intlist(array);
	if (!stack_a)
		return (0);
	sort_stack(stack_a, empty_intlst(ft_lstsize(stack_a)), ft_lstsize(stack_a));
	printf("Successful Run\n");
	freearray(array);
	ft_lstclearmod(&stack_a);
	return (1);
}

// CHANGE ' ' TO '\n' AFTER TESTING!!!
// double check that all printfs are ft_printfs