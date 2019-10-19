/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 18:11:21 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/11 19:32:26 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "regex.h"

static t_bool	regex_same_char(t_regex *st, const char *s1, const char *reg)
{
	char	alpha[128];

	if (*s1)
	{
		ft_bzero(alpha, sizeof(char) * 128);
		regex_is_metatype(alpha, reg);
		if ((is_delimiter(st, reg, ".") || alpha[(int)(*s1)] == 1))
			return (regex_parse(st, ++s1, ++reg));
	}
	return (FALSE);
}

t_bool			regex_parse(t_regex *st, const char *s1, const char *reg)
{
	st->last_s1 = s1;
	if (is_delimiter(st, reg, "\\"))
		reg++;
	if (*reg == '\0' && (++st->match))
		return (TRUE);
	if (is_delimiter(st, reg, "|"))
		return (TRUE);
	if (is_delimiter(st, reg, ")"))
		return (TRUE);
	if (is_delimiter(st, reg, "["))
		return (regex_class(st, s1, ++reg));
	if (is_delimiter(st, reg, "("))
		return (regex_enclosed(st, s1, ++reg));
	if (is_delimiter(st, reg + 1, QUANTIFIER))
		return (regex_quantifier(st, s1, reg));
	if (is_delimiter(st, reg, REG_END) && *(reg + 1) == '\0')
	{
		if (*s1 == '\0' && (++st->match))
			return (TRUE);
		return (FALSE);
	}
	return (regex_same_char(st, s1, reg));
}

/*
**-------------------------------------------------------
**
**		ft_regex by rgermain
**
**	-------------
**		QUANTIFIER
**	-------------
**
**		{n,m} ? * +
**
**		{5,9}	match upper than 5, and lower than 9
**		{0,}	match upper than 0 same as *
**		{1,}	match upper than 1 same as +
**		{,1}	match lower than 1 same as ?
**
**		?		lazy quantifier
**		{5,9}?	match upper than 5, and lower than 9
**
**	-------------
**		CLASS	
**	-------------
**
**	[^a-zA-Z\d[:isdigit].\\]fg]
**		*^				for not matching
**		*a-z			whole char in a to z
**		*\d				whole char is digit same as 0-9
**		[:isdigit:]		whole char is digit same as 0-9
**		*.				for point char
**		*fg				match with f or g
**
**	-------------
**		META	
**	-------------
**
**	\d \D \s \S \w \W \n \e \t
**	{}()[]?*+^$.					metachar need to be esapced
**
**	-------------
**		ENCLOSE
**	-------------
**
**
**	(?!<name>regex)
**
**		*?		for capture en memory
**		*!		for Not matching
**		<name>	for named where you capture (do nothing if ? is not set)
**
**
**	-------------
**		EXEMPLE
**	-------------
**
**	"^(?<alone>[\\p])*\\|(\\s*(?<flags>[\\p])+\\s*(\\((\\s*(?<type>[a-zA-Z*])+
**	\\s*(\\{\\s*(?<min>[\\d])*\\s*,\\s*(?<max>[\\d])*\\s*(,(?<pattern>[^}])*)?
**	\\}\\s*,\\s*)?)*\\))?\\s*;\\s*(?<set>[\\p])*\\s*;\\s*(?<unset>[\\p])*
**	\\s*\\|)*$"
**
**-------------------------------------------------------
*/
int				ft_regex_exec(t_regex *st, const char *s1, const char *reg)
{
	int i;

	ft_bzero(st, sizeof(*st));
	st->s1 = s1;
	while (*reg)
	{
		st->reg = reg;
		if (is_delimiter(st, reg, REG_START))
			regex_parse(st, s1, reg + 1);
		else
		{
			i = 0;
			while (*(s1 + i))
				regex_parse(st, s1 + i++, reg);
		}
		reg += regex_span_or(st, reg);
	}
	return (st->error | st->match);
}
