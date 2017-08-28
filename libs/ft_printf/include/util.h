/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 20:02:12 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 20:06:11 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <unistd.h>

size_t			ft_strlen(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isdigit(int c);
long double		iterative_power_long_double(long double nb, int power);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strchr(const char *s, int c);
void			ft_strclr(char *s);

#endif
