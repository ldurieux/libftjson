/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:32:06 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/01 20:32:08 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_list_back(t_list *list)
{
	if (!list)
		return (NULL);
	while (list.next)
		list = list->next;
	return (list);
}

t_list	*ft_list_at(t_list *list, size_t index)
{
	size_t	i;

	i = 0;
	while (i++ != index)
	{
		if (!list)
			return (NULL);
		list = list->next;
	}
	return (list);
}
