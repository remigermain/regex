/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_enclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/11 19:40:31 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

void            ft_regex_free(t_regex *st)
{
    //t_reg_capt *list;
    //t_reg_capt *tmp;
//
    //list = st->capt;
    //while (list)
    //{
    //    tmp = list;
    //    list = list->next;
    //    ft_memdel((void **)&(tmp->str));
    //    if (tmp->name)
    //        ft_memdel((void **)&(tmp->name));
    //    ft_memdel((void **)&tmp);
    //}
}

static void     regex_put_capt(t_regex *st, t_reg_list *lst)
{
 //   st->inst = ft_realloc(st->inst, st->inst->children + 1);
 ft_printf("[ %s ]", lst->name);
 ft_printf("[ %s ]", lst->str);
 ft_printf("[  %d  ]", lst->pos);
 ft_printf("[  %d  ]", lst->start);
 ft_printf("[  %d  ]\n", lst->end);
}

void            regex_put_arg(t_regex *st, const char *s1, int len, char *name)
{
    t_reg_list *list;

    if (!(list = (t_reg_list *)ft_memalloc(sizeof(t_reg_list))) ||
        (!(list->str = ft_strsub(s1, 0, len))))
    {
        st->error = ERROR_REGEX;
        return;
    }
    list->name = name;
    list->start = ft_strlen(st->s1) - ft_strlen(s1);
    list->end = list->start + len;
    regex_put_capt(st, list);
}