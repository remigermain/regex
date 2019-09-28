/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:52:11 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/28 09:34:20 by rgermain         ###   ########.fr       */
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

t_bool regex_return(t_regex *st, t_bool ret)
{
    if (ret)
        st->match++;
    return (ret);
}

int ft_spanchar_reg(t_regex *st, char *reg, char *str)
{
	int i;

	i = 0;
	while (reg[i] && (!is_metachar(st, reg + i) || !ft_strchr(str, reg[i]) || ft_isspace(reg[i])))
		i++;
	return (i);
}

int regex_span_class_type(t_regex *st, char *reg)
{
	int func;
	int i;

	func = 0;
	i = -1;
	while (reg[++i] && func != 2)
		if (reg[i] == ':')
			func++;
	return (i);
}

static t_bool	explode_metachar(const char *reg, const char *mem)
{
	int i;

	i = 0;
	while (reg - i - 1 >= mem && *(reg - i - 1) == '\\')
		i++;
	if (i % 2)
		return (FALSE);
	return (TRUE);
}

int span_explode_metachar(const char *reg, char *meta)
{
	const char *mem;

	mem = reg;
	while (*reg)
	{
		if (explode_metachar(reg, mem) && ft_strchr(meta, *reg))
		{
			reg++;
			break ;
		}
		reg++;
	}
	return (reg - mem);
}

int		regex_span_enclose(char *reg, char *meta)
{
	char *mem;
	int len;

	len = 0;
	mem = reg;
	while (*reg)
	{
		if (explode_metachar(reg, mem))
		{
			if (*reg == '(')
				reg += regex_span_enclose(reg + 1, ")") + 1;
			else
			{
				if (ft_strchr(meta, *reg))
				{
					reg++;
					break ;
				}
				reg++;
			}
		}
		else
			reg++;
	}
	return (reg - mem);
}

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
