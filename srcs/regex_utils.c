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
    t_reg_capt *lst;
    
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

void		ft_regex_print(t_regex *st)
{
    t_reg_capt  *lst;
    t_regex_pr  pr;
    int         i;
    
    ft_bzero(&pr, sizeof(t_regex_pr));
    regex_print_calc(st, &pr);
    lst = st->capt;
    ft_printf("[ PRINT  REXGEX CAPTURATIONS  ]\n\n");
    i = ft_printf("[ %*s ]", pr.name, "name");
    i += ft_printf("[ %*s ]", pr.str, "string");
    i += ft_printf("[ %*s ]", pr.pos, "pos");
    i += ft_printf("[ %*s ]", pr.start, "start");
    i += ft_printf("[ %*s ]\n", pr.end, "end");
    ft_printf("%*@\n", i, "char", '-');
	while (lst != NULL)
    {
        ft_printf("[ %*s ]", pr.name, lst->name);
        ft_printf("[ %*s ]", pr.str, lst->str);
        ft_printf("[  %*d  ]", pr.pos, lst->pos);
        ft_printf("[  %*d  ]", pr.start, lst->start);
        ft_printf("[  %*d  ]\n", pr.end, lst->end);
        lst = lst->next;
    }
}