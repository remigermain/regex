/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_quantifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/24 20:14:42 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "regex.h"

t_bool	char_quantifier(t_regex *st, char c, char *s1, char *reg)
{
	t_reg_quan quan;

	reg += get_quantifier(&quan, reg);
	print_quan(&quan);
	return (TRUE);
}

t_bool          regex_quantifier(t_regex *st, char c, char *s1, char *reg)
{
    t_reg_quan    quan;
    int             i;

    i = 0;
    reg += get_quantifier(&quan, reg);
    while (*s1 && (*s1 == c || is_delimiter(st, reg, '.')) && (++i))
        s1++;
    if (verif_quantifier(&quan, i))
        return (regex_parse(st, s1, reg));
    return (FALSE);
}