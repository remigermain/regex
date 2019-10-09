/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_regex_cmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/24 20:23:19 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

static t_bool   regex_replace_check(t_reg_capt *list, int len, enum e_regex_replace mod)
{
    if ((len == 0 && (mod & REG_FIRST))  ||
    (list->next == NULL && (mod & REG_LAST)) ||
    (mod & REG_ALL) || (mod == 0))
        return (TRUE);
    return (FALSE);
}

int     regex_replace_len(t_regex *st, char *s1, char *src, enum e_regex_replace mod)
{
	t_reg_capt *list;
    int         len;
    int         rem;

    len = 0;
    rem = 0;
    list = st->capt;
    while (list)
    {
        if (regex_replace_check(list, len, mod) && (++len))
            rem += ft_strlen(list->str);
        list = list->next;
    }
    return ((ft_strlen(s1) - rem) + (ft_strlen(src) * len));
}

char    *regex_replace_do(t_regex *st, char *s1, char *rep, enum e_regex_replace mod)
{
	t_reg_capt  *list;
    char        *ptr;
    int         len;
    int         i;

    i = 0;
    list = st->capt;
    len = regex_replace_len(st, s1, rep, mod);
    if (!(ptr = (char*)ft_memalloc(sizeof(char) * (len + 1))))
        return (NULL);
    len = -1;
    while (list && (++len))
    {
        ft_strncat(ptr, s1 + i, list->start - i);
        if (regex_replace_check(list, len, mod))
            ft_strcat(ptr, rep);
        else
            ft_strncat(ptr, s1 + list->start, list->end - list->start);
        i = list->end;
        list = list->next;
    }
    ft_strcat(ptr, s1 + i);
    return (ptr);
}

char	*ft_regex_replace(char *s1, char *reg, char *rep, enum e_regex_replace mod)
{
	t_regex st;

	if (ft_regex_cmp(&st, s1, reg) < 0)
		return (NULL);
	return (regex_replace_do(&st, s1, rep, mod));
}