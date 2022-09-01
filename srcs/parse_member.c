/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_member.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 01:12:48 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/02 01:12:49 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libftjson.h"
#include "libftjson_internal.h"

static inline t_json_member	*parse_member_criterr(int *ptr_err, int err,
									t_json_member *res)
{
	*ptr_err = err;
	return (res);
}

t_json_member	*parse_member(const char **raw, int *err)
{
	t_json_member	*member;
	char			token;

	member = malloc(sizeof(t_json_member));
	if (!member)
		return (parse_member_criterr(err, failed_malloc, NULL));
	member->value = NULL;
	member->key = parse_string(raw, err);
	if (*err)
		return (member);
	token = next_token(raw);
	if (token != NAME_SEP)
		return (parse_member_criterr(err, missing_name_separator, member));
	if (!skip_whitespace(raw))
		return (parse_member_criterr(err, unterminated_object, member));
	member->value = parse_value(raw, err);
	return (member);
}
