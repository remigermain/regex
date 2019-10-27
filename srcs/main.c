/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:48:43 by rgermain          #+#    #+#             */
/*   Updated: 2019/10/11 19:47:15 by rgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

// "http://code.visualstudio.com/shortcuts/dfvd/yoyoyo.ff.rrr"  "^(<methode>http(?s)?://)?(www\.)?(<link>[\w\.\-]+)+(?<yo>/(<get>[\w-])*)+?(?(<extension>\.[\w]+))+$"
void	t(char **argv)
{
	int ret = 0;
	t_regex st;
	ft_printf("[ MATCH ]\n");
	ft_printf("[ S1  >>  %s  << ]\n", argv[1]);
	ft_printf("[ REG  >>  %s  << ]\n", argv[2]);

	ret = ft_regex_exec(&st, argv[1], argv[2]);
	if (ret > 0)
		ft_printf("\033[38;5;326mTRUE  %d\n"T_WHITE, ret);
	else if (ret == 0)
		ft_printf("\033[1;31mFALSE  %d\n"T_WHITE, ret);
	else
		ft_printf("\033[1;31mERROR MALLOC %d\n"T_WHITE, ret);	


	if (ret == 0)
	{
		//error_line_pos("error parsing", 76, st.error_pos);
		//error_line_e(st.s1, st.error_pos);
	}
	ft_regex_print(&st);

	ft_regex_free(&st);

}

void	r(char **argv)
{
	ft_printf("[ REPLACE ]\n");
	char *ptr = ft_regex_replace(argv[1], argv[2], argv[3], 1 << ft_atoi(argv[4]));
	ft_printf("[BF %s ]\n", argv[1]);
	ft_printf("[AF %s ]\n", ptr);
}

//int ret = ft_regex_exec(&st, "a{ char* {5,9, *.cor|bonjourfdcdcdc}, char {1,1, a|b|r|4}, int {55,99}, int {99, 554}};;|",
//						"^(?<flag>[a-zA-Z0-9]){1}({(?char\\(*)?|int)(.)*;;\\|)");


int main(int argc, char **argv)
{
	t_regex st;
	//"^(?<alone>[a-zA-Z0-9]?[^|])*\\|(?(?\s*(?char\\*?|char|int){1}\s*))*$");
	//int ret = ft_regex_exec(&st, "dfvdmnvdmdvvd ", "[a-z] ");
	//int ret = ft_regex_exec(&st, 
	//
	//  goood
	//"^(?<alone>[\\p])*\\|((?<flags>[\\p])(\\(((?<type>[a-zA-Z*])+(\\{(?<min>[\\d])*,(?<max>[\\d])*(,(?<pattern>[^}])*)?\\},)?)*\\))?;(?<set>[\\p])*;(?<unset>[\\p])*\\|)*$");

	int ret = ft_regex_exec(&st,
							" ju  ,  it,  weeror_wetrzpb,|     yoyoyoyo  (  char*  {  5  ,  9  } , char{1,1,\"^ddfd^f$\"},int{55},int{99,},);error, error, extra, opop, tt,;unset1 , unet2, unset3, unset4,;|werror-wetra(char*,int{1,9},char*{,,\"ceci est un patterne\"},);sddd,;ttt,;|werror-wetra;sddd,;ttt,;|a(char*{5,9},char{1,1,\"^ddfd^f$\"},int{,55},int{99,},);,;,;|size_t(char*,int,char*,);sddd,;ttt,;|werror-wetra;dd,;;|",
							"^(\\s*(?<alone>[\\w\\-]*)\\s*,)*\\s*\\|(\\s*(?<flags>[\\w\\-]+)\\s*(\\(\\s*((?<type>[a-zA-Z*_]+)\\s*((\\{\\s*((?<min>[\\d]*)\\s*,\\s*(?<max>[\\d]*)\\s*(\\s*,\\s*\"(?<pattern>[^\"]+)\"\\s*)?|\\s*(?<ex>[\\d]*)\\s*)\\s*\\})?\\s*,\\s*)?)*\\s*\\))?\\s*;\\s*((?<set>[\\w\\-]*)\\s*,\\s*)*\\s*;\\s*((?<unset>[\\w\\-]*)\\s*,\\s*)*\\s*;\\s*\\|)*$");

	//"^(\\{(((?<min>\\d+)?,(?<max>\\d+)?|(?<ex>\\d+)))?\\})$");
	//"^[a-z]*\\s*(\\{((?<ex>\\d)+|((?<min>\\d)*,(?<max>\\d)*))\\})?$");
	//"^[a-z]*\\s*(\\{(?<ex>\\d)+\\})?$");

	if (ret > 0)
		ft_printf("\033[38;5;326mTRUE  %d\n" T_WHITE, ret);
	else if (ret == 0)
		ft_printf("\033[1;31mFALSE  %d\n" T_WHITE, ret);
	else
		ft_printf("\033[1;31mERROR MALLOC %d\n" T_WHITE, ret);

	if (ret == 0)
	{
		ft_printf("lalal %d   %s\n", st.error_pos, st.s1);
		error_line_pos("error parsing", 76, st.error_pos);
		error_line_e(st.s1, st.error_pos);
	}
	ft_regex_print(&st);

	ft_regex_free(&st);
	(void)argc;
	//t(argv);
	//r(argv);
	return (0);
}
