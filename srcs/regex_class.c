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

int     parse_class_not(t_regex_quan *quan, const char *reg, const char *s1, int j)
{
    t_regex_class   class;
    char            *tmp;

    tmp = (char*)reg;
    ft_bzero(&class, sizeof(t_regex_class));
    while (!verif_quantifier(quan, ++class.match))
    {
        class.range_min = *tmp++;
        while (*tmp && *tmp != ']')
        {
            class.range_min = *tmp++;
            if (*tmp != '-' && class.range_min != ']')
                if (*s1 == class.range_min)
                    return (FALSE);
            else if (*tmp == '-' && *tmp != ']' && (++tmp))
                if (*s1 >= class.range_min && *s1 <= class.range_max)
                    return (FALSE);
        }
        s1++;
    }
    return (regex_cmp(s1, reg + j));
}

int     parse_class(t_regex_quan *quan, const char *reg, const char *s1, int j)
{
    t_regex_class   class;
    char            *tmp;

    tmp = (char*)reg;
    ft_bzero(&class, sizeof(t_regex_class));
    while (*tmp && *tmp != ']')
    {
        class.range_min = *tmp++;
        if (*tmp != '-' && class.range_min != ']' &&
                    *s1 == class.range_min && (tmp = (char*)reg))
            if ((++s1) && verif_quantifier(quan, ++class.match)
                    && regex_cmp(s1, reg + j))
                return (TRUE);
        else if (*tmp == '-' && *tmp != ']' && (++tmp))
        {
            class.range_max = *tmp++;
            if (*s1 >= class.range_min && *s1 <= class.range_max && (tmp = (char*)reg))
                if ((++s1) && verif_quantifier(quan, ++class.match) && regex_cmp(s1, reg + j))
                    return (TRUE);
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
    if (*reg == '^')
        return (parse_class_not(&quan, reg + 1, s1, i + j - 1));
    return (parse_class(&quan, reg, s1, i + j));
}