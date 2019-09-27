/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_is_methode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/09/27 20:53:17 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

t_bool	is_enclose(t_regex *st, char *reg)
{
	if (*reg && ft_strchr(ENCLOSE, *reg) && is_metachar(st, reg))
		return (TRUE);
	return (FALSE);    
}

t_bool	is_quantifier(t_regex *st, char *reg)
{
	if (*reg && ft_strchr(QUANTIFIER, *reg) && is_metachar(st, reg))
		return (TRUE);
	return (FALSE);
}

t_bool	is_delimiter(t_regex *st, char *reg, char delimiter)
{
	if (*reg && delimiter == *reg && is_metachar(st, reg))
		return (TRUE);
	return (FALSE);
}
