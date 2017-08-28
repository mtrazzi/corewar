/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:58:27 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 20:22:40 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "cvt.h"
# include <stdarg.h>
# include <stdlib.h>

typedef int	(*t_cvt_func)(t_options *op, va_list *app, int put(int c));

int		get_format(int put(int c), const char *fmt, va_list ap, int *error);

int		ft_printf(const char *fmt, ...);
int		ft_sprintf(char *str, const char *fmt, ...);
int		ft_vsprintf(char *str, const char *format, va_list ap);
int		ft_fprintf(int fd, const char *fmt, ...);

void	ft_puts(const char *str, int len, int put(int c), t_options *op);
void	ft_putd(const char *str, int len, int put(int c), t_options *op);
void	ft_puto(const char *str, int len, int put(int c), t_options *op);
void	ft_putx(const char *str, int len, int put(int c), t_options *op);
void	ft_putp(const char *str, int len, int put(int c), t_options *op);
void	ft_putu(const char *str, int len, int put(int c), t_options *op);
void	ft_putf(const char *str, int len, int put(int c), t_options *op);
int		ft_putls(const wchar_t *str, int len, int put(int c), t_options *op);

#endif
