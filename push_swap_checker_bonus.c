/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:12:58 by dbozic            #+#    #+#             */
/*   Updated: 2024/06/07 14:13:01 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	exec_command_mod2(t_list **stack_a, t_list **stack_b, char *cmd)
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
	else
		return (0);
	return (1);
}

static int	exec_command_mod(t_list **stack_a, t_list **stack_b, char *cmd)
{
	if (!(ft_strncmp(cmd, "sa\n", 3)))
		*stack_a = swap_nodes(*stack_a);
	else if (!(ft_strncmp(cmd, "sb\n", 3)))
		*stack_b = swap_nodes(*stack_b);
	else if (!(ft_strncmp(cmd, "ss\n", 3)))
	{
		*stack_a = swap_nodes(*stack_a);
		*stack_b = swap_nodes(*stack_b);
	}
	else if (!(ft_strncmp(cmd, "pa\n", 3)))
		*stack_b = push_node(*stack_b, stack_a);
	else if (!(ft_strncmp(cmd, "pb\n", 3)))
		*stack_a = push_node(*stack_a, stack_b);
	else if (!(ft_strncmp(cmd, "ra\n", 3)))
		*stack_a = rotate_list(*stack_a, 1);
	else if (!(ft_strncmp(cmd, "rb\n", 3)))
		*stack_b = rotate_list(*stack_b, 1);
	else if (!(ft_strncmp(cmd, "rr\n", 3)))
	{
		*stack_a = rotate_list(*stack_a, 1);
		*stack_b = rotate_list(*stack_b, 1);
	}
	else
		return (exec_command_mod2(stack_a, stack_b, cmd));
	return (1);
}

//Used for testing
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
} */

static void	push_checker(t_list *stack_a, t_list *stack_b, int size)
{
	char	*command;

	command = NULL;
	while (1)
	{
		command = get_next_line(0);
		if (!command)
			break ;
		if (!(exec_command_mod(&stack_a, &stack_b, command)))
		{
			ft_printf("%d", exec_command_mod(&stack_a, &stack_b, command));
			ft_lstclearmod(&stack_a);
			ft_lstclearmod(&stack_b);
			ft_putstr_fd("Error\n", 2);
			return ;
		}
		free(command);
	}
	if (is_sorted(&stack_a, ft_lstsize(stack_a))
		&& (ft_lstsize(stack_a) == size))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
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
	push_checker(stack_a, NULL, ft_lstsize(stack_a));
	return (1);
}
