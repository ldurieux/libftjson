/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 20:37:29 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/02 20:37:30 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libftjson.h"
#include "libftjson_internal.h"

static inline t_json_value	*parse_value_criterr(int *ptr_err, int err,
									t_json_value *res)
{
	*ptr_err = err;
	return (res);
}

static inline t_json_value	*parse_value_bool(const char **raw, int *err,
											t_bool val, t_json_value *res)
{
	res->type = J_Bool;
	res->bool = val;
	if ((val && ft_strncmp(*raw, "rue", 3))
		|| (!val && ft_strncmp(*raw, "alse", 4)))
		return (parse_value_criterr(err, illegal_value, res));
	(*raw) += 3 + (val == 0);
	return (res);
}

static inline t_json_value	*parse_value_null(const char **raw, int *err,
											t_json_value *res)
{
	res->type = J_Null;
	if (ft_strncmp(*raw, "ull", 3))
		return (parse_value_criterr(err, illegal_value, res));
	(*raw) += 3;
	return (res);
}

static inline t_json_value	*parse_value_string(const char **raw, int *err,
												t_json_value *res)
{
	res->type = J_String;
	res->str = parse_string(raw, err);
	return (res);
}

/* for the love of god, let me use a switch
*/
t_json_value	*parse_value(const char **raw, int *err)
{
	t_json_value	*res;
	char			token;

	token = *(*raw)++;
	if (token == BEGIN_ARRAY)
		return (parse_array(raw, err));
	if (token == BEGIN_OBJECT)
		return (parse_object(raw, err));
	if (token == END_ARRAY || token == END_OBJECT)
		return (parse_value_criterr(err, missing_object, NULL));
	res = malloc(sizeof(t_json_value));
	if (!res)
		return (parse_value_criterr(err, failed_malloc, NULL));
	if (token == 'n')
		return (parse_value_null(raw, err, res));
	if (token == 't')
		return (parse_value_bool(raw, err, 1, res));
	if (token == 'f')
		return (parse_value_bool(raw, err, 0, res));
	if (token == '\"')
		return (parse_value_string(raw, err, res));
	(*raw)--;
	return (parse_number(res, raw, err));
}
