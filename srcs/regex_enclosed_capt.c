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
    t_reg_capt *list;
    t_reg_capt *tmp;

    list = st->capt;
    while (list)
    {
        tmp = list;
        list = list->next;
        ft_memdel((void **)&(tmp->str));
        if (tmp->name)
            ft_memdel((void **)&(tmp->name));
        ft_memdel((void **)&tmp);
    }
}

static void     regex_put_capt(t_regex *st, t_reg_capt *new)
{
    t_reg_capt *lst;
    t_reg_capt *mem;

    lst = st->capt;
    mem = NULL;
    while (lst && lst->start < new->start)
    {
        mem = lst;
        lst = lst->next;
    }
    new->next = lst;
    if (mem)
        mem->next = new;
    else
        st->capt = new;
}

static t_bool   exist_capt(t_regex *st, int start, int end)
{
    t_reg_capt *lst;

    lst = st->capt;
    while (lst)
    {
        if (lst->start == start && lst->end == end)
            return (TRUE);
        lst = lst->next;
    }
    return (FALSE);
}

void            regex_put_arg(t_regex *st, const char *s1, int len, char *name)
{
    t_reg_capt *list;

    if (len <= 0)
        return;
    if (!(list = (t_reg_capt *)ft_memalloc(sizeof(t_reg_capt))) ||
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