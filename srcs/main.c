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
//						"^(?<flag>\\s*[a-zA-Z0-9]\\s*){1}({(?char\\(*)?|int)(.)*;;\\|)");


int main(int argc, char **argv)
{
	t_regex st;
	//"^(?<alone>[a-zA-Z0-9]?[^|])*\\|(?(?\s*(?char\\*?|char|int){1}\s*))*$");
	//int ret = ft_regex_exec(&st, "dfvdmnvdmdvvd ", "[a-z] ");
	//int ret = ft_regex_exec(&st, "|a(char*{5515,9,*.cor|bonjourfdcdcdc},char{1,1,a|b|r|4},int{18,12,ddd},int{99,554});CDFV5151fefee;165SDDDsfdvvfdv55|",
	// "juitpb|a(char*{5,9,*.cor|bonjourfdcdcdc},char{1,1,a|b|r|4},int{55,99},int{99,554});;|r(char*{5,9,*.cor|bonjourfdcdcdc},char{,,a|b|r|*|4},int{55,99},int{99,554});;|",
	//
	//  goood
	//"^(?<alone>[\\p])*\\|((?<flags>[\\p])(\\(((?<type>[a-zA-Z*])+(\\{(?<min>[\\d])*,(?<max>[\\d])*(,(?<pattern>[^}])*)?\\},)?)*\\))?;(?<set>[\\p])*;(?<unset>[\\p])*\\|)*$");

	int ret = ft_regex_exec(&st, "RaArfGFsTLt|lflag(unzipfile{11, 22 ,je sios la}, dffd{55,66},);;1m|g;l;m|d;a;|1;;l|n;l;m|m;;l1|p;;F|S;;t|U;;uc|u;;Uc|c;;Uu|",

							"^(?<alone>[\\p])*\\|(\\s*(?<flags>[\\p])+\\s*(\\((\\s*(?<type>[a-zA-Z*])+\\s*(\\{\\s*(?<min>[\\d])*\\s*,\\s*(?<max>[\\d])*\\s*(,(?<pattern>[^}])*)?\\}\\s*,\\s*)?)*\\))?\\s*;\\s*(?<set>[\\p])*\\s*;\\s*(?<unset>[\\p])*\\s*\\|)*$");

	if (ret > 0)
		ft_printf("\033[38;5;326mTRUE  %d\n" T_WHITE, ret);
	else if (ret == 0)
		ft_printf("\033[1;31mFALSE  %d\n" T_WHITE, ret);
	else
		ft_printf("\033[1;31mERROR MALLOC %d\n" T_WHITE, ret);

	if (ret == 0)
	{
		//error_line_pos("error parsing", 76, st.error_pos);
		//error_line_e(st.s1, st.error_pos);
	}
	ft_regex_print(&st);

	ft_regex_free(&st);
	(void)argc;
	//t(argv);
	//r(argv);
	return (0);
}
