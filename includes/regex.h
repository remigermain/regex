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

enum e_regex_quan
{
	QUAN_MIN = 0b1,
	QUAN_MAX = 0b10,
	QUAN_EX = 0b100,
};

typedef struct s_regex_quan
{
	int number_1;
	int	number_2;
	int isset;
}				t_regex_quan;

/*
**-------------------------------------------------------
**          regex_class.c
**-------------------------------------------------------
*/
t_bool	match(const char *s1, const char *regex);
t_bool	regex_cmp(const char *s1, const char *reg);


/*
**-------------------------------------------------------
**          regex_class.c
**-------------------------------------------------------
*/
t_bool  regex_class(const char *s1, const char *reg);

/*
**-------------------------------------------------------
**          regex_enclosed.c
**-------------------------------------------------------
*/
t_bool  regex_enclosed(const char *s1, const char *reg);

/*
**-------------------------------------------------------
**          regex_quantifier_func.c
**-------------------------------------------------------
*/
t_bool	regex_plus(char c, const char *s1, const char *reg);
t_bool	regex_inter(char c, const char *s1, const char *reg);
t_bool	regex_star(char c, const char *s1, const char *reg);

/*
**-------------------------------------------------------
**          regex_quantifier.c
**-------------------------------------------------------
*/
t_bool          regex_quantifier(char c, const char *s1, const char *reg);

/*
**-------------------------------------------------------
**          regex_get_quantifier.c
**-------------------------------------------------------
*/
int     get_quantifier(t_regex_quan *st, char *reg);
t_bool  verif_quantifier(t_regex_quan *st, int i);


#endif
