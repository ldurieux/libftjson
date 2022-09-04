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

#define START_SIZE	32

static inline t_bool	simple_realloc(void **ptr, size_t *size,
									size_t new_size)
{
	void	*res;
	size_t	copy_size;

	if (!*ptr)
	{
		*ptr = malloc(new_size);
		*size = new_size * (*ptr != NULL);
		return (*ptr != NULL);
	}
	res = malloc(new_size);
	if (!res)
		return (0);
	copy_size = *size;
	if (*size > new_size)
		copy_size = new_size;
	ft_memcpy(res, *ptr, copy_size);
	ft_memset(res + copy_size, 0, new_size - copy_size);
	free(*ptr);
	*ptr = res;
	*size = new_size;
	return (1);
}

static inline t_json_value	*parse_array_criterr(int *ptr_err, int err,
									t_json_value *res, t_json_value **arr)
{
	if (res)
		res->arr = arr;
	*ptr_err = err;
	return (res);
}

static inline t_bool	loop_init(size_t *count, t_json_value ***arr,
								size_t *mem_size, char *token)
{
	*count = 0;
	*arr = NULL;
	*token = '\0';
	return (simple_realloc((void **)arr, mem_size, *mem_size));
}

static inline t_json_value	*parse_array_loop(const char **raw, int *err,
											t_json_value *res,
											size_t mem_size)
{
	t_json_value	**arr;
	size_t			count;
	char			token;

	if (!loop_init(&count, &arr, &mem_size, &token))
		return (parse_array_criterr(err, failed_malloc, res, arr));
	while (token != END_ARRAY)
	{
		if (!skip_whitespace(raw))
			return (parse_array_criterr(err, unterminated_array, res, arr));
		if ((count + 1) * sizeof(t_json_value *) >= mem_size
			&& !simple_realloc((void **)&arr, &mem_size, mem_size * 2))
			return (parse_array_criterr(err, failed_malloc, res, arr));
		arr[count++] = parse_value(raw, err);
		if (*err)
			return (parse_array_criterr(err, *err, res, arr));
		token = next_token(raw);
		if (token != END_ARRAY && token != VALUE_SEP && !skip_whitespace(raw))
			return (parse_array_criterr(err, unterminated_array, res, arr));
		if (token != END_ARRAY && token != VALUE_SEP)
			return (parse_array_criterr(err, missing_val_sep, res, arr));
	}
	arr[count] = NULL;
	res->arr = arr;
	return (res);
}

t_json_value	*parse_array(const char **raw, int *err)
{
	t_json_value	*res;
	size_t			mem_size;

	if (!skip_whitespace(raw))
		return (parse_array_criterr(err, unterminated_array, NULL, NULL));
	res = malloc(sizeof(t_json_value));
	if (!res)
		return (parse_array_criterr(err, failed_malloc, NULL, NULL));
	res->type = J_Array;
	if (**raw == END_ARRAY)
	{
		res->arr = NULL;
		return (res);
	}
	mem_size = sizeof(t_json_value *) * START_SIZE;
	return (parse_array_loop(raw, err, res, mem_size));
}
