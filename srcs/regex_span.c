/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_span.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/29 19:29:16 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

int     regex_span_quantifier(t_regex *st, char *reg)
{
    int i;

    i = 0;
    if (is_quantifier(st, reg))
    {
        if (ft_strchr("*?+", *reg))
            i++;
        else
        {
            i += ft_spantype(reg + i + 1, ft_isdigit) + 1;
            if (*(reg + i) == ',')
                i += ft_spantype(reg + i, ft_isdigit) + 1;
            i++;
        }
        if (*(reg + i) == '?')
            i++;
    }
    return (i);
}