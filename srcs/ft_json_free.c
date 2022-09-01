/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 23:40:29 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/01 23:40:30 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libftjson.h"

//NOLINTNEXTLINE(misc-no-recursion)
static inline void	ft_json_free_obj(t_list *obj)
{
	t_list			*obj_copy;
	t_json_member	*member;

	if (!obj)
		return ;
	obj_copy = obj;
	while (obj)
	{
		member = obj->value;
		if (member)
		{
			if (member->key)
				free(member->key);
			ft_json_free(member->value);
		}
		obj = obj->next;
	}
	ft_list_free(&obj_copy);
}

//NOLINTNEXTLINE(misc-no-recursion)
static inline void	ft_json_free_arr(t_list *arr)
{
	t_list	*arr_copy;

	if (!arr)
		return ;
	arr_copy = arr;
	while (arr)
	{
		ft_json_free(arr->value);
		arr = arr->next;
	}
	ft_list_free(&arr_copy);
}

//NOLINTNEXTLINE(misc-no-recursion)
void	ft_json_free(t_json_value *json)
{
	t_json_type		type;

	if (!json)
		return ;
	type = json->type;
	if (type == J_String)
		free(json->str);
	else if (type == J_Object)
		ft_json_free_obj(json->cont);
	else if (type == J_Array)
		ft_json_free_arr(json->cont);
	free(json);
}
