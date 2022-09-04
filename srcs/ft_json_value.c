/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:19:15 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/04 20:19:16 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libftjson.h"

t_json_value	*ft_json_value(t_json_value *obj, const char *key)
{
	t_list			*list;
	t_json_member	*member;

	if (!obj || obj->type != J_Object)
		return (NULL);
	list = obj->obj;
	while (list)
	{
		member = list->value;
		if (ft_strcmp(member->key, key) == 0)
			return (member->value);
		list = list->next;
	}
	return (NULL);
}

t_json_value	*ft_json_value_at(t_json_value *cont, size_t index)
{
	t_list	*list;

	if (!cont || (cont->type != J_Object && cont->type != J_Array))
		return (NULL);
	if (cont->type == J_Array)
		return (cont->arr[index]);
	list = cont->obj;
	while (list && index--)
		list = list->next;
	if (!list)
		return (NULL);
	return (list->value);
}
