/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:35:46 by dbozic            #+#    #+#             */
/*   Updated: 2024/05/08 14:59:23 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "Libft/libft.h"

typedef struct s_list
{
	int				value;
	int				index;
	int				status;
	struct s_list	*next;
}		t_list;

t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	exec_command(t_list **stack_a, t_list **stack_b, char *cmd);
t_list	*swap_nodes(t_list *first_node);
t_list	*push_node(t_list *sender, t_list **id_reciever);
t_list	*rotate_list(t_list *list, int rotation);
int		check_lst_for_dup(t_list *lst);
int		ft_atoimod(const char *nptr, int *rtn);
int		checkfilters(char **array);
char	**arraydup(char **array);
int		freearray(char **array);
t_list	*strarray_to_intlist(char **array);
void	ft_lstclearmod(t_list **lst);
void	ft_lstadd_rear(t_list **lst, t_list *new_node);
t_list	*ft_intlstnew(int integer, int index, int status);
int		find_largest(t_list *stack);
void	sort_indexes(t_list **stack_a, int size);
int		find_lowest(t_list *stack);
int		is_ordered(t_list *stack_a, int lowest);
int		is_sorted(t_list **stack, int size);
void	sort_tiny(t_list **stack_a, t_list **stack_b, int lowest);
void	sort_small(t_list **stack_a, t_list **stack_b, int lowest);
void	sort_big(t_list **s_a, t_list **s_b, t_list *a, t_list *b);

#endif
