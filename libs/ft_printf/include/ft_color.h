/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 20:54:00 by Philippe          #+#    #+#             */
/*   Updated: 2017/05/23 19:19:38 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLOR_H
# define FT_COLOR_H

# define MAX_COLOR 12

typedef struct	s_color
{
	char *str;
	char *code;
}				t_color;

static	t_color g_color_tab[] =
{
	{"eoc", "\033[0m"},
	{"black", "\033[0;30m"},
	{"red", "\033[0;31m"},
	{"green", "\033[0;32m"},
	{"yellow", "\033[0;33m"},
	{"blue", "\033[0;34m"},
	{"purple", "\033[0;35m"},
	{"cyan", "\033[0;36m"},
	{"white", "\033[0;37m"},
	{"Bblack", "\033[1;30m"},
	{"Bred", "\033[1;31m"},
	{"Bgreen", "\033[1;32m"},
	{"Byellow", "\033[1;33m"},
	{"Bblue", "\033[1;34m"},
	{"Bpurple", "\033[1;35m"},
	{"Bcyan", "\033[1;36m"},
	{"Bwhite", "\033[1;37m"},
	{"Ublack", "\033[4;30m"},
	{"Ured", "\033[4;31m"},
	{"Ugreen", "\033[4;32m"},
	{"Uyellow", "\033[4;33m"},
	{"Ublue", "\033[4;34m"},
	{"Upurple", "\033[4;35m"},
	{"Ucyan", "\033[4;36m"},
	{"Uwhite", "\033[4;37m"},
	{"On_black", "\033[40m"},
	{"On_red", "\033[41m"},
	{"On_green", "\033[42m"},
	{"On_yellow", "\033[43m"},
	{"On_blue", "\033[44m"},
	{"On_purple", "\033[45m"},
	{"On_cyan", "\033[46m"},
	{"On_white", "\033[47m"},
	{"Iblack", "\033[0;90m"},
	{"Ired", "\033[0;91m"},
	{"Igreen", "\033[0;92m"},
	{"Iyellow", "\033[0;93m"},
	{"Iblue", "\033[0;94m"},
	{"Ipurple", "\033[0;95m"},
	{"Icyan", "\033[0;96m"},
	{"Iwhite", "\033[0;97m"},
	{"BIblack", "\033[1;90m"},
	{"BIred", "\033[1;91m"},
	{"BIgreen", "\033[1;92m"},
	{"BIyellow", "\033[1;93m"},
	{"BIblue", "\033[1;94m"},
	{"BIpurple", "\033[1;95m"},
	{"BIcyan", "\033[1;96m"},
	{"BIwhite", "\033[1;97m"},
	{"On_Iblack", "\033[0;100m"},
	{"On_Ired", "\033[0;101m"},
	{"On_Igreen", "\033[0;102m"},
	{"On_Iyellow", "\033[0;103m"},
	{"On_Iblue", "\033[0;104m"},
	{"On_Ipurple", "\033[0;105m"},
	{"On_Icyan", "\033[0;106m"},
	{"On_Iwhite", "\033[0;107m"}
};

int				do_color(const char **fmt, int put(int c));

#endif
