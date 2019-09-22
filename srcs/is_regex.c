/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_regex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/22 17:26:42 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

t_bool      is_metachar(t_regex *st, char *reg)
{
    int i;

    i = 0;
    while (reg - i - 1 >= st->reg && *(reg - i - 1) == '\\')
        i++;
    if (i % 2)
        return (FALSE);
    return (TRUE);
}

t_bool      is_enclose(t_regex *st, char *reg)
{
	if (*reg && ft_strchr(ENCLOSE, *reg) && is_metachar(st, reg))
		return (TRUE);
    return (FALSE);    
}

t_bool      is_quantifier(t_regex *st, char *reg)
{
	ft_printf("auqnti = %c\n", *reg);
    if (*reg && ft_strchr(QUANTIFIER, *reg) && is_metachar(st, reg))
        return (TRUE);
    return (FALSE);
}

t_bool      is_delimiter(t_regex *st, char *reg, char delimiter)
{
	if (*reg && delimiter == *reg && is_metachar(st, reg))
		return (TRUE);
    return (FALSE);
}
