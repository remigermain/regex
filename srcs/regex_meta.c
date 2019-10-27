/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/11 19:40:39 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

/*
**-------------------------------------------------------
**		verifie que le character n'est pas antislasher
**		le st->reg est la valeur l'adress original de la regex
**		nous decrementon reg pour retrouver si il n'est pas antislaher
**		ex :  bonj\our\\ca va  represente bonjour\ca va
**			on veut savoir si le c de ca va n'est pas antislaher
**			dans ce ca on decremente reg de i + 1
**			avant le c il y a un slash on continue
**			il y a encore un slash on continue puis il n'y en a plus
**			on n'est arriver au r de bonj\our, i vaut 2
**			dans ce cas , vue qu'il n'est pas impaire
**			le c n'est pas antislaher.
**-------------------------------------------------------
*/

t_bool	is_metachar(t_regex *st, const char *reg)
{
	int i;

	i = 0;
	while (reg - i - 1 >= st->reg && *(reg - i - 1) == '\\')
		i++;
	if (i % 2)
		return (FALSE);
	return (TRUE);
}

/*
**-------------------------------------------------------
**		regarde que le permier charactere de *reg
**		n'est pas antislasher avec is_netachar et
**		que le character est la la chaine *delimiter
**-------------------------------------------------------
*/

t_bool	is_delimiter(t_regex *st, const char *reg, char *delimiter)
{
	if (*reg && ft_strchr(delimiter, *reg) && is_metachar(st, reg))
		return (TRUE);
	return (FALSE);
}
