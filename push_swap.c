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

static int push_swap(t_list **lst, size_t lst_length)
{
	return (0);
}

static int	check_lst_for_chr(t_list **lst, int chr)
{
	char	*content;
	t_list	*current;
	t_list	*next;

	current = *lst;
	while(current)
	{
		content = current->content;
		if (content[0] == chr)
			return(2);
		next = current->next;
		current = next;
	}
	return (0);
}
void do_nothing(void *str)
{
	return ;
}

int	main(int argv, char **argc)
{
	t_list	*lst;
	t_list	*current;
	int		i;

	i = 1;
	lst = ft_lstnew(argc[0]);
	ft_printf("Argv: %d\n", argv);
	if (argv < 2)
		return (0);
	
	while (argc[i])
	{
		if (!(argc[i][0] >= '0' && argc[i][0] <= '9') || !(argc[i][1] == '\0')
			|| (check_lst_for_chr(&lst, argc[i][0]) == 2))
		{
			ft_putstr_fd("Error\n", 2);
			ft_lstclear(&lst, do_nothing);
			return(2);
		}
		current = ft_lstnew(argc[i]);
		ft_lstadd_back(&lst, current);
		i++;
	}
	push_swap(&lst, argv - 1);	
	return (0);
}

/*
USEFULL CODE THAT DIDNT WORK ORIGINALLY
if (!(argc[i][0] >= '0' && argc[i][0] <= '9') || !(argc[i][1] == '\0'))
{
	ft_putstr_fd("Error\n", 2);
	return(2);
}
*/

// Sorting a list using a limited set of instructions on two rotatable stacks can be quite an interesting challenge! Let’s break it down.

// First, let’s understand the available commands:

// sa: Swap the first two elements at the top of stack A.
// sb: Swap the first two elements at the top of stack B.
// ss: Perform both sa and sb simultaneously.
// pa: Push the first element at the top of B onto A (do nothing if B is empty).
// pb: Push the first element at the top of A onto B (do nothing if A is empty).
// ra: Rotate stack A by moving the first element to the last position.
// rb: Rotate stack B by moving the first element to the last position.
// rr: Perform both ra and rb simultaneously.
// rra: Reverse rotate stack A by moving the last element to the first position.
// rrb: Reverse rotate stack B by moving the last element to the first position.
// rrr: Perform both rra and rrb simultaneously12.
// Now, let’s devise an efficient algorithm to sort the list using these commands. We’ll focus on minimizing the number of instructions rather than the complexity of the algorithm.

// Initial Setup:
// Push all 10 items from list A onto stack A.
// Stack B remains empty.
// Sorting Algorithm:
// While stack A is not sorted:
// Take the first element from stack A (let’s call it x).
// If x is already in the correct position (i.e., at the top of stack A), proceed to the next element.
// Otherwise, follow these steps:
// If x is in the second position, perform sa (swap the first two elements in stack A).
// If x is closer to the top of stack A, perform ra (rotate stack A).
// If x is closer to the bottom of stack A, perform rra (reverse rotate stack A).
// After each operation, check if stack A is sorted.
// If not, push the first element of stack A onto stack B.
// Repeat steps 1-5 until only two elements remain in stack A.
// If the remaining two elements are not in the correct order, perform sa to swap them.
// Push all elements from stack B back onto stack A.
// Result:
// Stack A will be sorted in ascending order.
// Stack B will be empty.
