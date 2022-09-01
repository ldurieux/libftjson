/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 23:15:27 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/01 23:15:28 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_free(t_list **list)
{
	t_list	*cur;
	t_list	*next;

	if (!list)
		return ;
	cur = *list;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	*list = NULL;
}
