/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:48:12 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 20:02:02 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CVT_H
# define CVT_H

# include <stdarg.h>

typedef struct		s_options
{
	unsigned char	flags[256];
	int				width;
	int				precision;
	int				no_precision;
	int				code;
	int				zero;
}					t_options;

int					cvt_o(t_options *op, va_list *app, int put(int c));
int					cvt_p(t_options *op, va_list *app, int put(int c));
int					cvt_s(t_options *op, va_list *app, int put(int c));
int					cvt_u(t_options *op, va_list *app, int put(int c));
int					cvt_x(t_options *op, va_list *app, int put(int c));
int					cvt_c(t_options *op, va_list *app, int put(int c));
int					cvt_d(t_options *op, va_list *app, int put(int c));
int					cvt_lc(t_options *op, va_list *app, int put(int c));
int					cvt_ls(t_options *op, va_list *app, int put(int c));
int					cvt_percent(t_options *op, va_list *app, int put(int c));

int					cvt_b(t_options *op, va_list *app, int put(int c));
int					cvt_f(t_options *op, va_list *app, int put(int c));
int					cvt_n(t_options *op, va_list *app, int put(int c));

int					uni(int c, int put(int c));
long long			get_ret_value();
long long			get_sprintf_index();
int					cvt_bad_ident(t_options *op, unsigned int c,
						unsigned int uni_lvl, int put(int c));
int					most_significant_bit_position_u(unsigned int n);

#endif
