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
			free(member);
		}
		obj = obj->next;
	}
	ft_list_free(&obj_copy);
}

//NOLINTNEXTLINE(misc-no-recursion)
static inline void	ft_json_free_arr(t_json_value **arr)
{
	size_t	idx;

	if (!arr)
		return ;
	idx = -1;
	while (arr[++idx])
		ft_json_free(arr[idx]);
	free(arr);
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
		ft_json_free_obj(json->obj);
	else if (type == J_Array)
		ft_json_free_arr(json->arr);
	free(json);
}
