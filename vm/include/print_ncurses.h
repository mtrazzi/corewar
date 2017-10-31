/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ncurses.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 14:49:42 by laranda           #+#    #+#             */
/*   Updated: 2017/10/31 22:53:15 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_NCURSES_H
# define PRINT_NCURSES_H

# include "vm.h"
# include <ncurses.h>
# include <time.h>
# include <pthread.h>

# define BYTES_PER_LINE 64
# define COLOR_ZEROS 245
# define COLOR_FWHITE 15
# define COLOR_BLUE3 33
# define COLOR_GREEN3 10
# define COLOR_MAGENTA3 163
# define COLOR_YELLOW3 148

# define TH_NB 2//max 4

typedef struct s_view_env	t_view_env;
typedef struct s_th	t_th;


struct		s_th
{
	int			id;
	pthread_t	pth;
	t_env		*e;
	t_view_env	*v_e;
};

struct		s_view_env
{
	int					status;
	int					step;
	int					hide;
	WINDOW				*fields[TH_NB];
	// WINDOW				*field;
	WINDOW				*infos;
	WINDOW				*logo;
	WINDOW				*help;
	t_th				th[TH_NB];
};

extern	int g_log_fd;//


int			print_ncurses(t_env *e);
int			is_prc(t_env *e, u_int pos);
t_prc		*get_prc_by_champ(t_env *e, int id);
void		init_color_pairs(void);
int			get_color_pair(t_env *e, u_int pos);
void		fill_logo(WINDOW *logo);
void		fill_help(WINDOW *help);
WINDOW		*create_winbox(int height, int width,
							int starty, int startx);
// void		fill_field(t_view_env *v_e, t_env *e, int start, int end);
void	fill_field(t_view_env *v_e, t_env *e, WINDOW *field, int id);
void		fill_infos(t_view_env *v_e, t_env *e,
						int running);
u_int		print_players(WINDOW *win, t_env *e, u_int x);
int			forward_one_cycle(t_env *e, t_view_env *v_e);
void		control_speed(t_view_env *v_e);
void		check_speed_key(int key, t_view_env *v_e);
int			running_loop(t_env *e, t_view_env *v_e);
void		print_worker(t_env *e, t_view_env *v_e);
void		refresh_fields(WINDOW **fields);
int				launch_mthread_fill_field(t_view_env *v_e, t_env *e);

#endif
