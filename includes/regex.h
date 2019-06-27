/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   regex.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 15:47:12 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/27 16:12:20 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef	REGEX_H
# define REGEX_H
# include "libft.h"

enum	e_regex_op
{
	R_NOT = '^',
	R_OR = '|',
	R_RANGE = '-',
	R_STAR = '*',
	R_COMMA= ',',
	R_QUAN_O = '{',
	R_QUAN_C = '}',
	R_CLASS_O = '[',
	R_CLASS_C = ']',
	START_STRING = '^',
	END_STRING = '$',
};

typedef	struct	s_reg_word
{
	char			*name;
	struct	s_class	*next;
}				t_reg_word;

typedef	struct	s_reg_class
{
	t_reg_word	*word;
	int			range1;
	int			range2;
	int			stop;
	int			flags;
}				t_reg_class;

typedef	struct	s_match
{
	int		start;
	int		end;
	struct	s_regex	*next;
}				t_match;

typedef struct	s_regex
{
	t_match		*match;
	char		*regex;
	char		*s1;
}				t_regex;

void	print_match(t_regex	*reg, char	*s1);
int		count_match(t_regex	*reg);
t_regex	*add_list(int start, int end);
void	add_match(t_regex **reg, int start, int end);
t_bool	regex_start_string(char *s1, char *regex);
t_bool	match_regex(char *s1, char *regex);
t_bool	match(char *s1, char *regex);
#endif
