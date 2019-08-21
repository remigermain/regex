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

t_bool          regex_quantifier(char c, const char *s1, const char *reg)
{
    t_reg_quan    st;
    int             i;

    i = 0;
    reg += get_quantifier(&st, (char*)reg);
    while (*s1 && (*s1 == c || c == '.') && (++i))
        s1++;
    if (verif_quantifier(&st, i))
        return (regex_cmp(s1, reg));
    return (FALSE);
}