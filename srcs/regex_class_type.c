/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 15:48:43 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 20:35:56 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"

t_bool  regex_class_type(const char *s1, const char *reg)
{
    if (!ft_strncmp(reg, ":alnum:", 8))
        return (ft_isalnum(*s1));
    else if (!ft_strncmp(reg, ":alpha:", 8))
        return (ft_isalpha(*s1));
    else if (!ft_strncmp(reg, ":ascii:", 8))
        return (ft_isascii(*s1));
    else if (!ft_strncmp(reg, ":blank:", 8))
        return (ft_isblank(*s1));
    else if (!ft_strncmp(reg, ":cntrl:", 8))
        return (ft_iscntrl(*s1));
    else if (!ft_strncmp(reg, ":digit:", 8))
        return (ft_isdigit(*s1));
    else if (!ft_strncmp(reg, ":graph:", 8))
        return (ft_isgraph(*s1));
    else if (!ft_strncmp(reg, ":lower:", 8))
        return (ft_islowercase(*s1));
    else if (!ft_strncmp(reg, ":print:", 8))
        return (ft_isprint(*s1));
    else if (!ft_strncmp(reg, ":space:", 8))
        return (ft_isspace(*s1));
    else if (!ft_strncmp(reg, ":upper:", 8))
        return (ft_isuppercase(*s1));
    else if (!ft_strncmp(reg, ":xdigit:", 9))
        return (ft_isxdigit(*s1));
    return (FALSE);
//    else if (!ft_strncmp(reg, ":punct:", 9))
//        return (ft_ispunct(*s1));
}