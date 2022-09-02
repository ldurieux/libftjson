/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 00:33:21 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/02 00:33:23 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libftjson.h"
#include "libftjson_internal.h"

static inline t_json_value	*parse_object_criterr(int *ptr_err, int err,
									t_json_value *res, t_list *obj)
{
	if (res)
		res->cont = obj;
	*ptr_err = err;
	return (res);
}

static inline t_list	*list_push_guard(t_list **list, void *value)
{
	t_list	*res;

	res = ft_list_pushfront(list, value);
	if (!res)
		free(value);
	return (res);
}

/* ft_list_pushfront is a hack we should use
 * ft_list_pushback but it is slower and
 * element order is not important in a json
 * object
*/
static inline t_json_value	*parse_object_loop(const char **raw, int *err,
											t_json_value *res)
{
	t_list			*obj;
	char			token;

	obj = NULL;
	token = next_token(raw);
	while (token == '\"')
	{
		if (!list_push_guard(&obj, parse_member(raw, err)))
			return (parse_object_criterr(err, failed_malloc, res, obj));
		if (*err)
			return (parse_object_criterr(err, *err, res, obj));
		token = next_token(raw);
		if (token != VALUE_SEP)
			break ;
		token = next_token(raw);
		if (token == END_OBJECT)
			return (parse_object_criterr(err, missing_object, res, obj));
	}
	res->cont = obj;
	*err = (token != END_OBJECT) * unterminated_object;
	return (res);
}

t_json_value	*parse_object(const char **raw, int *err)
{
	t_json_value	*res;

	res = malloc(sizeof(t_json_value));
	if (!res)
		return (parse_object_criterr(err, failed_malloc, NULL, NULL));
	res->type = J_Object;
	return (parse_object_loop(raw, err, res));
}
