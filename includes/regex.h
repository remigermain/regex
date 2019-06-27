/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   regex.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 15:47:12 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/27 20:43:54 by rgermain    ###    #+. /#+    ###.fr     */
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

enum	e_regex_co
{
	RR_NOT,
	RR_OR,
	RR_RANGE,
	RR_STAR,
	RR_COMMA,
	RR_QUAN_O,
	RR_QUAN_C,
	RR_CLASS_O,
	RR_CLASS_C,
	RSTART_STRING,
	REND_STRING,
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
	struct	s_match	*next;
}				t_match;

typedef struct	s_regex
{
	t_match		*match;
	char		*regex;
	char		*s1;
	int			end;
}				t_regex;

void	print_match(t_match	*reg, char	*s1);
int		count_match(t_match	*reg);
t_match	*add_list(int start, int end);
void	add_match(t_match **match, int start, int end);
t_bool	regex_start_string(char *s1, char *regex);
t_bool	match_regex(char *s1, char *regex);
t_bool	match(char *s1, char *regex);
t_bool	is_noregex(char c);
void	error_regex(void);
int		find_class(t_regex *reg, char *s1, int start);
#endif
