/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   regex_class.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <rgermain@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 20:32:03 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 18:12:23 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"

/*
**-------------------------------------------------------
**		function pour parser la class
**		si il y a un delimiteur [ cela veut dire que c'est un
**		posix type ex : [:isdigit:] ou [:isalnum:] ...ect
**		on apelle le meta_istype pour set la class->alpha
**
**		si ce n'est pas un metachar (il est antislasher)
**		et qu'il est dans REGEX_TYPE ex : \d \D \w ...ect
**		on apelle le meta_type pour set la class->alpha
**
**		sinon c'est un character classic
**		on set le class->aplha du code assci de ce character
**		si il y a - apres , cela veut dire que cela doit etre
**		entre le charactere precedent et celui apres le -
**		donc on boucle pour set le alpha a 1
**
**		on retourne le nombre de charactere pass par la class
**-------------------------------------------------------
*/

static int		regex_class_parse(t_regex *st, t_reg_class *class,
															const char *reg)
{
	const char	*mem;
	int			i;

	mem = reg;
	while (*reg && !is_delimiter(st, reg, "]"))
	{
		if (is_delimiter(st, reg, "\\"))
			reg++;
		i = *reg;
		if (is_delimiter(st, reg, "[") && (i = -1))
			reg += regex_is_type(class->alpha, reg + 1) + 2;
		else if (!is_metachar(st, reg) && ft_strchr(REGEX_TYPE, i))
			reg += regex_is_metatype(st, class->alpha, reg);
		else
		{
			class->alpha[((int)*reg++)] = 1;
			if (*reg == '-' && (++reg))
				while (i <= *reg)
					class->alpha[i++] = 1;
		}
	}
	return (regex_span_class(st, mem));
}

/*
**-------------------------------------------------------
**		function pour les class  [0-9a-zR]
**		si il y a le delimiter  ^  au debut de la class
**		on set le is_not a TRUE, cela veut dire que
**		tout les character dans la class ne doit pas etre cela
**		on parse la class, puis on regarde si il y a un quantifier
**
**		puis on boucle sur s1
**		si class.alpha nous retourne TRUE et que is not est sur FALSE
**		alors on incremente le quantifier.match
**		si class.alpha nous retourne FALSE et que is not est sur TRUE
**		alors on incremente le quantifier.match
**-------------------------------------------------------
*/

t_bool			regex_class(t_regex *st, const char *s1, const char *reg)
{
	t_reg_class	class;
	int			i;

	i = -1;
	if (REGEX_DEBUG)
		ft_dprintf(2, "[regex_class]\n[s1][%s]\n[reg][%s]\n", s1, reg);
	ft_bzero(&class, sizeof(t_reg_class));
	if (is_delimiter(st, reg, "^"))
	{
		reg++;
		class.is_not = TRUE;
	}
	reg += regex_class_parse(st, &class, reg);
	if (REGEX_DEBUG)
		regex_alpha_debug("regex_class", class.alpha);
	if (is_delimiter(st, reg, QUANTIFIER))
		reg += regex_get_quantifier(&(class.quantifier), reg);
	while (s1[++i] && class.alpha[(int)s1[i]] != class.is_not)
		class.quantifier.match++;
	return (regex_quantifier_do(st, &(class.quantifier), s1, reg));
}
