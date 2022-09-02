/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:31:42 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/01 22:31:44 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libftjson.h"
#include "libftjson_internal.h"

static inline t_json_value	*ft_json_parse_criterr(int *ptr_err, int err,
												t_json_value *res)
{
	ft_json_free(res);
	if (ptr_err)
		*ptr_err = err;
	return (NULL);
}

t_json_value	*ft_json_parse(const char *raw, int *err, const char **end_ptr)
{
	char			chr;
	t_json_value	*res;
	int				res_err;

	res = NULL;
	if (!raw)
		return (ft_json_parse_criterr(err, input_null, res));
	res_err = no_error;
	chr = next_token(&raw);
	if (chr == BEGIN_OBJECT)
		res = parse_object(&raw, &res_err);
	else if (chr == BEGIN_ARRAY)
		res = parse_array(&raw, &res_err);
	else
		return (ft_json_parse_criterr(err, illegal_value, res));
	skip_whitespace(&raw);
	if (end_ptr)
		*end_ptr = raw;
	if (res_err != no_error)
		return (ft_json_parse_criterr(err, res_err, res));
	if (*raw != '\0')
		return (ft_json_parse_criterr(err, garbage_at_end, res));
	if (err)
		*err = no_error;
	return (res);
}
