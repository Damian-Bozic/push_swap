/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:55:41 by dbozic            #+#    #+#             */
/*   Updated: 2024/06/06 16:59:49 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static void	exec_command2(t_list **stack_a, t_list **stack_b, char *cmd)
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
