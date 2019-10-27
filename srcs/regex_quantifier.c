/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_quantifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/11 19:40:48 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

/*
**-------------------------------------------------------
**		verifi le nombre de match (i) et les donner du quantifier
**		QUAN_EX n doit etre egal a i
**		QUAN_MIN n doit superieur ou egale a i
**		QUAN_MAX m doit etre inferieur ou egale a i
**		QUAN_OR i doit etre egale a n ou m
**		si le quantifier est vide , i doit etre de 1
**-------------------------------------------------------
*/

t_bool		verif_quantifier(t_reg_quan *quan, int i)
{
	if ((quan->isset & QUAN_EX) && quan->n != i)
		return (FALSE);
	else if ((quan->isset & QUAN_MIN) && quan->n > i)
		return (FALSE);
	else if ((quan->isset & QUAN_MAX) && quan->m < i)
		return (FALSE);
	else if ((quan->isset & QUAN_OR) && quan->n != i && quan->m != i)
		return (FALSE);
	else if (quan->isset == 0 && i != 1)
		return (FALSE);
	return (TRUE);
}

/*
**-------------------------------------------------------
**		verifie qu'il ne depasse pas le nombre
**		maximuin de fois qu'il peut matcher
**-------------------------------------------------------
*/

t_bool verif_quantifier_max(t_reg_quan *quan, int i)
{
	if ((quan->isset & QUAN_EX) && quan->n >= i)
		return (FALSE);
	else if ((quan->isset & QUAN_MAX) && quan->m >= i)
		return (FALSE);
	else if ((quan->isset & QUAN_OR) && quan->n >= i && quan->m >= i)
		return (FALSE);
	else if (quan->isset == 0 && i >= 1)
		return (FALSE);
	return (TRUE);
}

/*
**-------------------------------------------------------
**		LAZY
**		si le quantifier est LAZY on commence a 0 puis
**		on l'incremente jusqu'au nombre de fois qu'il a match 
**										(quan->match)
**		GREDIE
**		si le quantifier est GREDIE on commence au 
**		nombre de fois qu'il a match (quan->match)
**		on le decremente jusqu'a zero
**
**		si la valeur du quantifier a valide , on apelle regex_parse
**		si celle si nous renvoie TRUE
**		on s'arrete et on revoie cette valeur , sinon on continue
**		si rien a matcher , en retourne FALSE
**-------------------------------------------------------
*/

t_bool		regex_quantifier_do(t_regex *st, t_reg_quan *quan,
											const char *s1, const char *reg)
{
	int i;

	i = 0;
	while ((quan->isset & QUAN_LAZY) && i <= quan->match)
	{
		if (verif_quantifier(quan, i) && regex_parse(st, s1 + i, reg))
			return (TRUE);
		i++;
	}
	while (!(quan->isset & QUAN_LAZY) && quan->match >= 0)
	{
		if (verif_quantifier(quan, quan->match) &&
			regex_parse(st, s1 + quan->match, reg))
			return (TRUE);
		quan->match--;
	}
	return (FALSE);
}

/*
**-------------------------------------------------------
**		fonction pour le cas d'un character seul avec un quantifier
**		ex :   bonjou+r 	 u+
**			   bonj*?our	 j*?
**			   bon{5,99}?jour	 n{5,99}?
**
**		le alpha[128] represente un chaine de 1 et de 0
**		le 1 represente le character set
**		ex :	bonjou+r
**		u = 117 en valeur ascii
**		alpha[117] vaudra 1 tendis que alpha[110] vaudre 0
**
**		il fonctionnera aussi avec les metachar \d \w \D \W ...
**		ex :	bonjour\d+
**		\d = tout les digits donc de 0 a 9
**		apha[48] a alpha[57] vaudra 1 
**		car 0 = 48 et 9 = 57 , on va set tout les char de 0 a 9 
**-------------------------------------------------------
*/

t_bool		regex_quantifier(t_regex *st, const char *s1, const char *reg)
{
	t_reg_quan	quan;
	char		alpha[128];
	t_bool		is_any;

	if (REGEX_DEBUG)
		ft_dprintf(2, "[regex_quantifier]\n[s1][%s]\n[reg][%s]\n", s1, reg);
	ft_bzero(alpha, sizeof(char) * 128);
	regex_is_metatype(st, alpha, reg);
	if (REGEX_DEBUG)
		regex_alpha_debug("regex_quantifier", alpha);
	is_any = is_delimiter(st, reg, ".") ? TRUE : FALSE;
	reg += regex_get_quantifier(&quan, reg + 1) + 1;
	while (*(s1 + quan.match) && (is_any || alpha[(int)(*(s1 + quan.match))]))
		quan.match++;
	return (regex_quantifier_do(st, &quan, s1, reg));
}
