/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 15:48:43 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/27 20:52:22 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "regex.h"


/*
**------------------------------------------------
**		regex  ^ 
**------------------------------------------------
*/

void		find_string(t_regex	*reg, char *pat, char *s1)
{
	char	*tmp;
	int		len;
	int		mlen;
	int		pat_len;

	len = 0;
	mlen = ft_strlen(s1);
	pat_len = ft_strlen(pat);
	while ((tmp = ft_strstr(s1 + len, pat)))
	{
		len = mlen - (ft_strlen(tmp) - pat_len);
		add_match(&(reg->match), len - pat_len, len);
		if (match(tmp + pat_len, reg->regex + reg->end))
			return ;
	}
}

void		find_char(t_regex *reg, char pat, char *s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == pat)
			add_match(&(reg->match), i, i + 1);
		i++;
	}
}

int			find_noregex(t_regex *reg, char *s1, int start)
{
	char	*tmp;
	int		end;

	end = start;
	while (reg->regex[end] && is_noregex(reg->regex[end]))
		end++;
	ft_printf("end = %d\n", end);
	if (start == end)
		return (end);
	if (!(tmp = ft_strsub(reg->regex, start, end)))
		error_regex();
	reg->end = end;
	find_string(reg, tmp, s1);
	ft_memdel((void**)&tmp);
	return (end);
}

t_bool	match(char *s1, char *regex)
{
	t_regex	reg;
	int	i;

	ft_bzero(&reg, sizeof(t_regex));
	reg.regex = regex;
	i = 0;
	if (is_noregex(regex[i]))
		find_noregex(&reg, s1, i);
	if (regex[i] == R_CLASS_O)
		find_class(&reg, s1, i + 1);
	print_match(reg.match , s1);
//	find_char(&reg, 'c', s1);
	return (FALSE);
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("./prog < string > < regex string >\n");
		exit(0);
	}
	ft_printf("match = %s\n", (match(argv[1], argv[2]) ?  "\033[38;5;326mTRUE" : "\033[1;31mFALSE"));
	return (0);
}
