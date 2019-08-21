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

t_bool          regex_quantifier(t_regex *st, char c, const char *s1, const char *reg)
{
    t_reg_quan    quan;
    int             i;

    i = 0;
    reg += get_quantifier(&quan, (char*)reg);
    while (*s1 && (*s1 == c || delimiter(st, (char*)reg, '.')) && (++i))
        s1++;
    if (verif_quantifier(&quan, i))
        return (regex_parse(st, s1, reg));
    return (FALSE);
}