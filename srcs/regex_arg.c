/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/01 19:16:02 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

void        regex_put_arg(t_regex *st, char *base, char *match)
{
    static t_reg_capt   *mem = NULL;
    static int          position = 0;
    t_reg_capt          *list;
    int                 len;
    
    len = ft_strlen(base) - ft_strlen(match);
    if (!(list = (t_reg_capt*)ft_memalloc(sizeof(t_reg_capt))))
        regex_error(st);
    if (!(list->str = ft_strsub(base, 0, len)))
        regex_error(st);
    list->pos = position++;
    list->start = ft_strlen(st->s1) - ft_strlen(base);
    list->end = ft_strlen(st->s1) - ft_strlen(match);
    if (st->capt == NULL)
    {
        st->capt = list;
        mem = list;
    }
    else
    {
        mem->next = list;
        mem = list;
    }
}