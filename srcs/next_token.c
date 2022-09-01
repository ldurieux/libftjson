/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 23:02:07 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/01 23:02:08 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libftjson_internal.h"

t_bool	skip_whitespace(const char **raw)
{
	while (ft_is_whitespace(**raw))
		(*raw)++;
	return (**raw);
}

char	next_token(const char **raw)
{
	char	token;

	if (!skip_whitespace(raw))
		return (0);
	token = *(*raw)++;
	if (token != BEGIN_OBJECT && token != BEGIN_ARRAY && token != NAME_SEP
		&& token != END_OBJECT && token != END_ARRAY && token != VALUE_SEP
		&& token != '\"')
		return (0);
	return (token);
}
