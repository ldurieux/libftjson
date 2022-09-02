/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftjson_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:31:45 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/01 22:31:46 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTJSON_INTERNAL_H
# define LIBFTJSON_INTERNAL_H

# include "libft.h"

# define ERR_OK				"no error occurred"
# define ERR_INPUT_NULL		"raw input is null"
# define ERR_FAIL_MALOC		"memory allocation failed"
# define ERR_UNTERM_OBJ		"unterminated object"
# define ERR_MISS_NSEP		"missing name separator"
# define ERR_UNTERM_ARR		"unterminated array"
# define ERR_MISS_VSEP		"missing value separator"
# define ERR_ILLEGAL_VAL	"illegal value"
# define ERR_END_OF_NUM		"invalid termination by number"
# define ERR_ILLEGAL_NUM	"illegal number"
# define ERR_STR_ESC_SEQ	"invalid escape sequence"
# define ERR_STR_UTF8		"invalid UTF8 string"
# define ERR_UNTERM_STR		"unterminated string"
# define ERR_MISS_OBJ		"object is missing after a comma"
# define ERR_DEEP_NEST		"too deeply nested document"
# define ERR_DOC_LARGE		"too large document"
# define ERR_GARBAGEEND		"garbage at the end of the document"

# define BEGIN_OBJECT	'{'
# define END_OBJECT		'}'
# define BEGIN_ARRAY	'['
# define END_ARRAY		']'
# define NAME_SEP		':'
# define VALUE_SEP		','

typedef struct s_json_value		t_json_value;
typedef struct s_json_member	t_json_member;

typedef enum e_err
{
	no_error,
	input_null,
	failed_malloc,
	unterminated_object,
	missing_name_separator,
	unterminated_array,
	missing_val_sep,
	illegal_value,
	termination_by_number,
	illegal_number,
	illegal_escape_sequence,
	illegal_utf8string,
	unterminated_string,
	missing_object,
	deep_nesting,
	document_too_large,
	garbage_at_end,
}	t_err;

/* return false if there is no more characters */
t_bool			skip_whitespace(const char **raw);
char			next_token(const char **raw);

t_json_value	*parse_object(const char **raw, int *err);
t_json_value	*parse_array(const char **raw, int *err);
t_json_member	*parse_member(const char **raw, int *err);
char			*parse_string(const char **raw, int *err);

#endif // LIBFTJSON_INTERNAL_H
