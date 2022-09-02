/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:45:17 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/02 18:45:20 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libftjson.h"
#include "libftjson_internal.h"

static inline t_json_value	*parse_array_criterr(int *ptr_err, int err,
									t_json_value *res, t_list *arr)
{
	if (res)
		res->cont = arr;
	*ptr_err = err;
	return (res);
}

// TODO
/* when checking for a list failed malloc
 * we do not store the value that was supposed
 * to be in the list anywhere,
 * we should free it
*/
// TODO
/* using a list for a json array is a hack
 * we should definitly use a vector instead
*/
static inline t_json_value	*parse_array_loop(const char **raw, int *err,
											t_json_value *res)
{
	t_list	*arr;
	char	token;

	arr = NULL;
	while (1)
	{
		if (!skip_whitespace(raw))
			return (parse_array_criterr(err, unterminated_array, res, arr));
		if (!ft_list_pushback(&arr, parse_value(raw, err)))
			return (parse_array_criterr(err, failed_malloc, res, arr));
		if (*err)
			return (parse_array_criterr(err, *err, res, arr));
		token = next_token(raw);
		if (token == END_ARRAY)
			break ;
		if (token != VALUE_SEP && !skip_whitespace(raw))
			return (parse_array_criterr(err, unterminated_array, res, arr));
		if (token != VALUE_SEP)
			return (parse_array_criterr(err, missing_val_sep, res, arr));
	}
	res->cont = arr;
	return (res);
}

t_json_value	*parse_array(const char **raw, int *err)
{
	t_json_value	*res;

	if (!skip_whitespace(raw))
		return (parse_array_criterr(err, unterminated_array, NULL, NULL));
	res = malloc(sizeof(t_json_value));
	if (!res)
		return (parse_array_criterr(err, failed_malloc, NULL, NULL));
	res->type = J_Array;
	if (**raw == END_ARRAY)
	{
		res->cont = NULL;
		return (res);
	}
	return (parse_array_loop(raw, err, res));
}
