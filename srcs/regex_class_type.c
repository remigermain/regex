/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_class_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:47:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/24 20:10:46 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "regex.h"

t_bool  regex_class_type(t_regex *st, char *s1, char *reg)
{
    if (!ft_strncmp(reg, ":alnum:", 7))
        return (ft_isalnum(*s1));
    else if (!ft_strncmp(reg, ":alpha:", 7))
        return (ft_isalpha(*s1));
    else if (!ft_strncmp(reg, ":ascii:", 7))
        return (ft_isascii(*s1));
    else if (!ft_strncmp(reg, ":blank:", 7))
        return (ft_isblank(*s1));
    else if (!ft_strncmp(reg, ":cntrl:", 7))
        return (ft_iscntrl(*s1));
    else if (!ft_strncmp(reg, ":digit:", 7))
        return (ft_isdigit(*s1));
    else if (!ft_strncmp(reg, ":graph:", 7))
        return (ft_isgraph(*s1));
    else if (!ft_strncmp(reg, ":lower:", 7))
        return (ft_islowercase(*s1));
    else if (!ft_strncmp(reg, ":print:", 7))
        return (ft_isprint(*s1));
    else if (!ft_strncmp(reg, ":space:", 7))
        return (ft_isspace(*s1));
    else if (!ft_strncmp(reg, ":upper:", 7))
        return (ft_isuppercase(*s1));
    else if (!ft_strncmp(reg, ":xdigit:", 8))
        return (ft_isxdigit(*s1));
    return (FALSE);
//    else if (!ft_strncmp(reg, ":punct:", 9))
//        return (ft_ispunct(*s1));
}