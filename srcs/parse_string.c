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
	if (res)
		free(res);
	res = NULL;
	return (res);
}

/* switch anyone ?
*/
static inline char	escape_sequence(char chr)
{
	if (chr == 'b')
		return ('\b');
	if (chr == 'f')
		return ('\f');
	if (chr == 'n')
		return ('\n');
	if (chr == 'r')
		return ('\r');
	if (chr == 't')
		return ('\t');
	if (chr == '\"')
		return ('\"');
	if (chr == '\\')
		return ('\\');
	return ('\0');
}

static inline char	*parse_esc(const char **raw, int *err, size_t len)
{
	char	*end;
	char	*res;
	size_t	idx;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (parse_string_criterr(err, failed_malloc, NULL));
	end = (char *)*raw;
	idx = 0;
	while (idx < len)
	{
		if (*end == '\\')
		{
			res[idx] = escape_sequence(*++end);
			if (!res[idx++])
				return (parse_string_criterr(err, illegal_esc_seq, res));
		}
		else
			res[idx++] = *end;
		end++;
	}
	res[idx] = '\0';
	(*raw) = end + 1;
	return (res);
}

char	*parse_string(const char **raw, int *err)
{
	char	*end;
	char	*res;
	t_bool	has_esc;
	size_t	len;

	has_esc = 0;
	len = 0;
	end = (char *)*raw;
	while (*end && *end != '\"')
	{
		if (*end == '\\')
			has_esc = 1;
		end += 1 + (*end == '\\');
		len++;
	}
	if (!*end)
		return (parse_string_criterr(err, unterminated_string, NULL));
	if (has_esc)
		return (parse_esc(raw, err, len));
	res = ft_strndup(*raw, len);
	if (!res)
		return (parse_string_criterr(err, failed_malloc, NULL));
	*raw = end + 1;
	return (res);
}
