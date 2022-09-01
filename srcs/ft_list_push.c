/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:32:11 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/01 20:32:11 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_list_pushback(t_list **list, void *value)
{
	t_list	*res;

	res = malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	res->value = value;
	if (!*list)
	{
		*list = res;
		return (res);
	}
	ft_list_back(*list)->next = res;
	return (res);
}

t_list	*ft_list_pushfront(t_list **list, void *value)
{
	t_list	*res;

	res = malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	res->value = value;
	res->next = *list;
	*list = res;
	return (res);
}
