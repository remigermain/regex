/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:52:11 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/30 17:06:02 by rgermain         ###   ########.fr       */
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
