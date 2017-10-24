/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ncurses.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 14:49:42 by laranda           #+#    #+#             */
/*   Updated: 2017/09/13 14:49:44 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_NCURSES_H
# define PRINT_NCURSES_H

# include "vm.h"
# include <ncurses.h>
# include <time.h>

# define BYTES_PER_LINE 64
# define COLOR_ZEROS 245
# define COLOR_BLUE3 33
# define COLOR_GREEN3 10
# define COLOR_MAGENTA3 163
# define COLOR_YELLOW3 148

typedef struct s_view_env	t_view_env;

struct 						s_view_env
{
	int					status;
	int					speed;
	unsigned long long	t;
	WINDOW				*field;
	WINDOW				*infos;
};

int							print_ncurses(t_env *e);

#endif
