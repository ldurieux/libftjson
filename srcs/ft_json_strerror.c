/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_strerror.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:46:42 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/01 22:46:43 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libftjson.h"
#include "libftjson_internal.h"

static inline char	*ft_json_strerror2(int err);

/* can't use switch ? fun times
 *
 * switch (err)
 * {
 * case input_null:		return (ERR_INPUT_NULL);
 * case failed_malloc:	return (ERR_FAIL_MALOC);
 * ...
 * default:				return (ERR_OK);
 * }
*/
char	*ft_json_strerror(int err)
{
	if (err == input_null)
		return (ERR_INPUT_NULL);
	if (err == failed_malloc)
		return (ERR_FAIL_MALOC);
	if (err == unterminated_object)
		return (ERR_UNTERM_OBJ);
	if (err == missing_name_separator)
		return (ERR_MISS_NSEP);
	if (err == unterminated_array)
		return (ERR_UNTERM_ARR);
	if (err == missing_val_sep)
		return (ERR_MISS_VSEP);
	if (err == illegal_value)
		return (ERR_ILLEGAL_VAL);
	if (err == termination_by_number)
		return (ERR_END_OF_NUM);
	if (err == illegal_number)
		return (ERR_ILLEGAL_NUM);
	if (err == illegal_escape_sequence)
		return (ERR_STR_ESC_SEQ);
	if (err == illegal_utf8string)
		return (ERR_STR_UTF8);
	if (err == unterminated_string)
		return (ERR_UNTERM_STR);
	return (ft_json_strerror2(err));
}

static inline char	*ft_json_strerror2(int err)
{
	if (err == missing_object)
		return (ERR_MISS_OBJ);
	if (err == deep_nesting)
		return (ERR_DEEP_NEST);
	if (err == document_too_large)
		return (ERR_DOC_LARGE);
	if (err == garbage_at_end)
		return (ERR_GARBAGEEND);
	return (ERR_OK);
}
