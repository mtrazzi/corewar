/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 19:55:46 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 19:23:06 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUT_H
# define FT_PUT_H

# include <limits.h>
# include <stdlib.h>
# include "cvt.h"

void	pad(int n, int c, int put(int ch));
int		get_uni(wchar_t c);

#endif
