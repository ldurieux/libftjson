/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftjson.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:32:15 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/01 20:32:20 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTJSON_H
# define LIBFTJSON_H

# include "libft.h"
# include "ft_list.h"

typedef enum e_json_type
{
	J_Null,
	J_Number,
	J_Bool,
	J_String,
	J_Object,
	J_Array,
}	t_json_type;

typedef struct s_json_value
{
	t_json_type	type;
	union
	{
		char	*str;
		double	num;
		t_bool	bool;
		t_list	*cont;
	};
}	t_json_value;

typedef struct s_json_member
{
	char			*key;
	t_json_value	*value;
}	t_json_member;

t_json_value	*ft_json_parse(const char *raw, int *err,
					const char **end_ptr);
void			ft_json_free(t_json_value *json);
char			*ft_json_strerror(int err);

#endif // LIBFTJSON_H
