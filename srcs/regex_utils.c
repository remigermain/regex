/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:52:11 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/03 18:54:03 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

void	regex_error(t_regex *st)
{
	ft_regex_free(st);
	st->error += ERROR_REGEX;
}

t_bool regex_return(t_regex *st, t_bool ret)
{
	if (ret == TRUE)
    	st->match++;
    return (ret);
}

void	ft_regex_free(t_regex *st)
{
	t_reg_capt	*list;
	t_reg_capt	*tmp;

	list = st->capt;
	while (list)
	{
		tmp = list;
		list = list->next;
		ft_memdel((void**)&(tmp->str));
		ft_memdel((void**)&tmp);
	}
}
