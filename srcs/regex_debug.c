/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:52:11 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/30 17:05:26 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

void print_quan(t_reg_quan *st)
{
    ft_printf("[ quantifier debug ]\n\n");
    ft_printf("numer_1 = %d\n", st->number_1);
    ft_printf("numer_2 = %d\n", st->number_2);
    ft_printf("%b\n", st->isset);
    if (st->isset & QUAN_EX)
        ft_printf("only number %d \n", st->number_1);
    if (st->isset & QUAN_MIN)
        ft_printf("min number %d \n", st->number_1);
    if (st->isset & QUAN_MAX)
        ft_printf("max number %d \n", st->number_2);

    ft_printf("{");
    if (st->isset & QUAN_EX)
        ft_printf("%d", st->number_1);
    if (st->isset & QUAN_MIN)
        ft_printf("%d", st->number_1);
    if (st->isset & QUAN_MIN || st->isset & QUAN_MAX)
        ft_printf(",");
    if (st->isset & QUAN_MAX)
        ft_printf("%d", st->number_2);
    ft_printf("}\n");
    if (st->isset & QUAN_LAZY)
        ft_printf("Lazy quantifier\n");
    ft_printf("\n[ quantifier END debug ]\n");
}
