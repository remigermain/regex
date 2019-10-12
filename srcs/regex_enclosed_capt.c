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

void            regex_put_arg(t_regex *st, const char *base,
                                        const char *match, char *name)
{
    t_reg_capt *list;
    int len;

    len = ft_strlen(base);
    len -= ft_strlen(match);
    if (len <= 0 || exist_capt(st, ft_strlen(st->s1) - ft_strlen(base),
                               ft_strlen(st->s1) - ft_strlen(match)))
        return;
    if (!(list = (t_reg_capt *)ft_memalloc(sizeof(t_reg_capt))) ||
        (!(list->str = ft_strsub(base, 0, len))))
    {
        st->error = ERROR_REGEX;
        return;
    }
    if (name && !(list->name = ft_strdup(name)))
        st->error = ERROR_REGEX;
    list->start = ft_strlen(st->s1) - ft_strlen(base);
    list->end = ft_strlen(st->s1) - ft_strlen(match);
    regex_put_capt(st, list);
}