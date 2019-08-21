/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   class.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 20:32:03 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 20:35:03 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"

t_bool  verif_class()
{
    
    return (FALSE);
}

int     parse_class(t_regex_quan *quan, const char *reg, const char *s1, int j)
{
    t_regex_class   class;
    char            *tmp;
    int             number_match;

    number_match = 0;
    if (*reg == '^')
        class.isset |= CLASS_NOT;
    tmp = (char*)reg + class.isset;
    ft_bzero(&class, sizeof(t_regex_class));
    while (*tmp && *tmp != ']')
    {
        class.range_min = *tmp++;
        if (*tmp != '-' && class.range_min != ']' && *s1 == class.range_min)
        {
            s1++;
            tmp = (char*)reg + class.isset;;
            if (verif_quantifier(quan, ++number_match) && regex_cmp(s1, reg + j))
                return (TRUE);
        }
        else if (*tmp == '-' && *tmp != ']')
        {
            tmp++;
            class.range_max = *tmp++;
            if (*s1 >= class.range_min && *s1 <= class.range_max)
            {
                s1++;
                tmp = (char*)reg + class.isset;;
                if (verif_quantifier(quan, ++number_match) && regex_cmp(s1, reg + j))
                    return (TRUE);
            }
        }
    }
    return (FALSE);
}   

t_bool  regex_class(const char *s1, const char *reg)
{
    t_regex_quan    quan;
    int i;
    int j;

    j = 0;
    ft_bzero(&quan, sizeof(t_regex_quan));
    i = ft_spanchar((char*)reg, "]") + 1;
    if (*(reg + i) == '{')
        j = get_quantifier(&quan, reg + i + 1) + 1;
    return (parse_class(&quan, reg, s1, i + j));
}