/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:59:54 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 19:23:25 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMARY_H
# define PRIMARY_H

# include "cvt.h"

t_options	*init_options();
void		reset_options(t_options *options);
int			get_unitype(char c);
void		get_optional_length_flags(const char **fmt, unsigned char *flags);
void		get_optional_flags(const char **fmt, unsigned char *flags);
void		get_optional_width_and_precision(const char **fmt,
					t_options *options, va_list *ap);

#endif
