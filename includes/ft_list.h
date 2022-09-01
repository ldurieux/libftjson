/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:32:14 by ldurieux          #+#    #+#             */
/*   Updated: 2022/09/01 20:32:14 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

# include <stdlib.h>

typedef struct s_list
{
	struct s_list	*next;
	void			*value;
}	t_list;

size_t	ft_list_size(t_list *list);
t_list	*ft_list_back(t_list *list);
t_list	*ft_list_at(t_list *list, size_t index);
t_list	*ft_list_pushback(t_list **list, void *value);
t_list	*ft_list_pushfront(t_list **list, void *value);
void	*ft_list_popback(t_list **list);
void	*ft_list_popfront(t_list **list);

#endif // FT_LIST_H
