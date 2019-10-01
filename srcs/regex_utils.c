/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:52:11 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/01 19:18:51 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

void    regex_error_line(t_regex *st, char *reg, char c)
{
    if (st)
        error_line((char*)st->reg);
    ft_dprintf(2, "in %s, end char is normaly is %c\n", reg, c);
    exit(0);
}

void	regex_error(t_regex *st)
{
	(void)st;
	ft_dprintf(2, "error malloc\n");
	exit(0);
}

t_bool regex_return(t_regex *st, t_bool ret)
{
    if (ret)
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
