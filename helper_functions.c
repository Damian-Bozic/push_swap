/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:09:06 by dbozic            #+#    #+#             */
/*   Updated: 2024/06/06 17:09:38 by dbozic           ###   ########.fr       */
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
	if ((nbr > 2147483647 && sign == 1) || (nbr > 2147483648 && sign == -1))
		ft_putstr_fd("Error\n", 2);
	if ((nbr > 2147483647 && sign == 1) || (nbr > 2147483648 && sign == -1))
		return (0);
	nbr = nbr * sign;
	*rtn = nbr;
	return (1);
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
