/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/11 19:23:29 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

static void	regex_print_calc(t_regex *st, t_regex_pr *pr)
{
    t_reg_list *lst;

    lst = st->capt;
	while (lst != NULL)
    {
        if (lst->name)
            pr->name = MAX(pr->name, ft_strlen(lst->name));
        else
            pr->name = MAX(pr->name, 6);        
        pr->str = MAX(pr->str, ft_strlen(lst->str));
        pr->pos = MAX(pr->pos, (size_t)ft_intlen(lst->pos));
        pr->start = MAX(pr->start, (size_t)ft_intlen(lst->start));
		pr->end = MAX(pr->end, (size_t)ft_intlen(lst->end));
		lst = lst->next;
    }
}

/*
**-------------------------------------------------------
**          affiche tout les resultas sous forme de tabbleau
**-------------------------------------------------------
*/

void		ft_regex_print(t_regex *st)
{
    t_reg_list *lst;
    t_regex_pr  pr;
    int         i;

    ft_bzero(&pr, sizeof(t_regex_pr));
    regex_print_calc(st, &pr);
    lst = st->capt;
    ft_printf("[ PRINT  REXGEX CAPTURATIONS  ]\n\n");
    i = ft_printf("[ %*s ]", pr.name, "name");
    i += ft_printf("[ %*s ]", pr.str, "string");
    i += ft_printf("[ %*s ]", pr.pos + 2, "pos");
    i += ft_printf("[ %*s ]", pr.start, "start");
    i += ft_printf("[ %*s ]\n", pr.end + 2, "end");
    ft_printf("%*@\n", i, "char", '-');
    while (lst != NULL)
    {
        ft_printf("%*@", lst->level, "char", ' ');
        ft_printf("[ %*s ]", pr.name, lst->name);
        ft_printf("[ %*s ]", pr.str, lst->str);
        ft_printf("[  %*d  ]", pr.pos, lst->pos);
        ft_printf("[  %*d  ]", pr.start, lst->start);
        ft_printf("[  %*d  ]\n", pr.end, lst->end);
        lst = lst->next;
    }
}

void	regex_alpha_debug(char *func, char alpha[128])
{
	int i;

	i = -1;
	ft_dprintf(2, "[%s]", func);
	while (++i < 128)
		ft_dprintf(2, "%d", alpha[i]);
	ft_dprintf(2, "\n");
}

void     ft_regex_free(t_regex *st)
{
    t_reg_list *tmp;
    t_reg_list *list;
    
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

void    regex_put_arg(t_regex *st, const char *s1, int len, char *name)
{
    t_reg_list **head;
    t_reg_list *list;

    if (!(list = (t_reg_list *)ft_memalloc(sizeof(t_reg_list))) ||
        (!(list->str = ft_strsub(s1, 0, len))))
    {
        st->error = ERROR_REGEX;
        if (list)
            ft_memdel((void**)&list);
        return;
    }
    list->name = name;
    list->start = st->len_s1 - ft_strlen(s1);
    list->end = list->start + len;
    list->level = st->level;
    list->pos = st->nb_capt++;
    head = &(st->capt);
    while (*head && (*head)->start <= list->start)
        head = &(*head)->next;
    list->next = *head;
    *head = list;
}