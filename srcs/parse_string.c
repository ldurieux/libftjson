/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 01:28:08 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/02 01:28:09 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libftjson_internal.h"

static inline char	*parse_string_criterr(int *ptr_err, int err, char *res)
{
	*ptr_err = err;
	return (res);
}

/* TODO: handle escape sequence:
 * \" \\
 * */
char	*parse_string(const char **raw, int *err)
{
	char	*end;
	char	*res;

	end = (char *)*raw;
	while (*end && *end != '\"')
		end++;
	if (!*end)
		parse_string_criterr(err, unterminated_string, NULL);
	res = ft_strndup(*raw, end - *raw);
	if (!res)
		parse_string_criterr(err, failed_malloc, NULL);
	*raw = end + 1;
	return (res);
}
