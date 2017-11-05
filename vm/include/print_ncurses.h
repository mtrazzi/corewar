/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ncurses.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 14:49:42 by laranda           #+#    #+#             */
/*   Updated: 2017/11/05 19:01:15 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_NCURSES_H
# define PRINT_NCURSES_H

# include "vm.h"
# include <ncurses.h>

# define BYTES_PER_LINE 64
# define COLOR_ZEROS 245
# define COLOR_FWHITE 15
# define COLOR_BLUE3 33
# define COLOR_GREEN3 10
# define COLOR_MAGENTA3 177
# define COLOR_YELLOW3 229

# define VE_USER_QUIT 2

# define GOTO_LINE 5
# define BKDN_LINE 19
# define MSG_CURRENT_PERIOD ("Live breakdown for current period :")
# define MSG_LAST_PERIOD ("Live breakdown for last period :")
# define BKDN ("[------------------------------------------------------]")
# define MSG_PROGRESS_BAR ("Current period progress :")

typedef struct s_view_env	t_view_env;

struct		s_view_env
{
	int					status;
	int					step;
	int					hide;
	WINDOW				*field;
	WINDOW				*infos;
	WINDOW				*logo;
	WINDOW				*help;
};

/*
** NCURSES
*/

int			print_ncurses(t_env *e);
void		fill_field(t_view_env *v_e, t_env *e);

/*
** CONTROLS
*/

int			do_forward_one_cycle(t_env *e, t_view_env *v_e);
void		print_worker(t_env *e, t_view_env *v_e);
int			running_loop(t_env *e, t_view_env *v_e);

/*
** HELPERS
*/

void		update_champ(t_env *e);
void		check_step_key(int key, t_view_env *v_e);
void		check_hide(int key, t_view_env *v_e, t_env *e);
void		refill_field(t_view_env *v_e, t_env *e);
void		decrement_color_mods(t_env *e);

/*
** INFOS
*/

void		fill_infos(t_view_env *v_e, t_env *e, int running);
void		print_winner(t_env *e, t_view_env *v_e);

/*
** STATS
*/

void		print_breakdown(WINDOW *win, t_env *e, u_int x, char *msg);
void		print_progress_bar(WINDOW *win, t_env *e, u_int x, char *msg);

/*
** STYLE
*/

WINDOW		*create_winbox(int height, int width, int y, int x);
void		init_color_pairs(void);
int			get_color_pair(t_env *e, u_int pos);
void		fill_logo(WINDOW *logo);
void		fill_help(WINDOW *help);

#endif
