/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:32:12 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/01 20:32:13 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

size_t	ft_list_size(t_list *list)
{
	size_t	res;

	res = 0;
	while (list)
	{
		list = list->next;
		res++;
	}
	return (res);
}
