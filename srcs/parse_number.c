/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 21:26:54 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/02 21:26:55 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libftjson.h"
#include "libftjson_internal.h"

static inline t_bool	is_integer(const char *raw)
{
	char	chr;

	chr = *raw;
	if (chr == '-')
		chr = *(raw + 1);
	while (chr)
	{
		if (chr == '.' || chr == 'e' || chr == 'E')
			return (0);
		if (chr < '0' || (chr > '9'))
			break ;
		chr = *++raw;
	}
	return (1);
}

#define BASE_10_LEN	10

static inline t_bool	is_digit(char chr)
{
	return (chr >= '0' && chr <= '9');
}

static inline t_int64	parse_integer(const char **raw, int *err)
{
	const char	*str;
	t_int64		res;
	int			sign;
	t_int64		tmp;

	str = *raw;
	res = 0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	str += sign == -1;
	while (is_digit(*str))
	{
		tmp = res * BASE_10_LEN + (*str++ - '0') * (long long)sign;
		if ((sign == 1 && tmp < res) || (sign == -1 && tmp > res))
		{
			*err = number_overflow;
			res = LLONG_MAX * (sign == 1) + LLONG_MIN * (sign == -1);
			break ;
		}
		res = tmp;
	}
	*raw = str;
	return (res);
}

//TODO
static inline double	parse_float(const char **raw, int *err)
{
	(void)raw;
	*err = unimplemented;
	return (0);
}

t_json_value	*parse_number(t_json_value *res, const char **raw, int *err)
{
	if (is_integer(*raw))
	{
		res->type = J_Integer;
		res->i_num = parse_integer(raw, err);
	}
	else
	{
		res->type = J_Float;
		res->f_num = parse_float(raw, err);
	}
	return (res);
}
