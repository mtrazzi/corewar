/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 17:33:56 by pkirsch           #+#    #+#             */
/*   Updated: 2017/08/24 11:45:01 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLL_H
# define DLL_H

# include <stdlib.h>
# include <sys/types.h>

# define DLL_FIRST 0
# define DLL_LAST 1

typedef struct s_dll	t_dll;
typedef void			(t_del)();
typedef	int				(t_cmp)();
typedef	int				(t_do)();

struct			s_dll
{
	void		*content;
	t_dll		*next;
	t_dll		*prev;
};

/*
**	CREATE
*/

t_dll			*dll_new(void *content);

/*
**	PUSH_POP_APPEND
*/

void			dll_push_front(t_dll **lst, t_dll *new);
void			dll_push_back(t_dll **lst, t_dll *new);
t_dll			*dll_pop(t_dll **lst, int first);
void			dll_append(t_dll **lst, t_dll *new);

/*
**	GET
*/

t_dll			*get_first(t_dll *lst);
t_dll			*get_last(t_dll *lst);
t_dll			*get_n(t_dll *lst, u_int n);

/*
**	ITER
*/

int				dll_iter_int(t_dll *dll, t_cmp cmp, void *compare_against);
t_dll			*dll_iter_dll(t_dll *dll, t_cmp cmp, void *compare_against);
int				dll_foreach(t_dll *dll, t_do f);

/*
**	SIZE
*/

u_int			dll_size(t_dll *lst);

/*
**	UTILS
*/

int				is_in_dll(t_dll *lst, t_dll *to_extract);

/*
**	TRANFER
*/

void			dll_insert(t_dll **lst, t_dll *to_insert, u_int position);
t_dll			*dll_extract_ptr(t_dll **lst, t_dll *to_extract);
t_dll			*dll_extract_pos(t_dll **lst, u_int position);
void			dll_transfer_ptr(t_dll **lst_a, t_dll **lst_b,
									t_dll *to_transfer, u_int to_position);
void			dll_transfer_pos(t_dll **lst_a, t_dll **lst_b,
									u_int from_position, u_int to_position);

/*
**	DEL
*/

void			dll_delone(t_dll **to_del);
void			dll_del(t_dll **lst);
void			dll_del_f(t_dll **lst, t_del *f);
void			dll_delone_f(t_dll **to_del, t_del *f);

#endif
