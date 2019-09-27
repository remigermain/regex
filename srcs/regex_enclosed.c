/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_enclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/27 21:27:16 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

t_bool		regex_enclose_do(t_regex *st, char **tab, char *s1, char *reg)
{
    t_regex base;
	int     i;

	i = -1;
	while (tab && tab[++i])
	{
		if (ft_regex_cmp(st, s1, tab[i]))
            return (TRUE);
    }
    return (regex_parse(st, s1, reg));
}


t_bool  regex_enclosed(t_regex *st, char *s1, char *reg)
{
    t_reg_quan  quantifier;
    char        **tab;

    tab = NULL;
    ft_printf("[ ENCLSOSE ] reg = %s\n", reg);
    ft_bzero(&quantifier, sizeof(t_reg_quan));
    return (regex_enclose_do(st, tab, s1, reg));
}