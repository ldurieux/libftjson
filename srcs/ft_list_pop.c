/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_pop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:32:09 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/01 20:32:10 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	*ft_list_popback(t_list **list)
{
	t_list	*last;
	void	*res;

	last = *list;
	if (!last)
		return (NULL);
	if (!last->next)
	{
		res = last->value;
		free(last);
		*list = NULL;
		return (res);
	}
	while (last->next->next)
		last = last->next;
	res = last->next->value;
	free(last->next);
	last->next = NULL;
	return (res);
}

void	*ft_list_popfront(t_list **list)
{
	t_list	*first;
	void	*res;

	first = *list;
	if (!first)
		return (NULL);
	*list = first->next;
	res = first->value;
	free(first);
	return (res);
}
