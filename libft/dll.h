/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 17:33:56 by pkirsch           #+#    #+#             */
/*   Updated: 2017/08/19 21:48:34 by pkirsch          ###   ########.fr       */
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


struct					s_dll
{
	void				*content;
	t_dll				*next;
	t_dll				*prev;
};

/*
**	BASICS
*/

// t_dll					*dll_new(void *content);
// t_dll					*cdll_add(t_dll *clst, t_dll *new);
// void					dlst_delone(t_dll **to_del);
// void					cdll_del(t_dll **clst);
// void					dlst_del_first(t_dll **clst);


t_dll	*dll_new(void *content);
void	dll_push_front(t_dll **lst, t_dll *new);
void	dll_push_back(t_dll **lst, t_dll *new);

t_dll	*get_first(t_dll *lst);
t_dll	*get_last(t_dll *lst);
t_dll	*get_n(t_dll *lst, u_int n);

int	is_in_dll(t_dll *lst, t_dll *to_extract);

u_int		dll_size(t_dll *lst);

void	dll_insert(t_dll **lst, t_dll *to_insert, u_int position);
t_dll	*dll_extract_ptr(t_dll **lst, t_dll *to_extract);
t_dll	*dll_extract_pos(t_dll **lst, u_int position);
void	dll_transfer_ptr(t_dll **lst_a, t_dll **lst_b, t_dll *to_transfer, u_int to_position);
void	dll_transfer_pos(t_dll **lst_a, t_dll **lst_b, u_int from_position, u_int to_position);

void	dll_append(t_dll **lst, t_dll *new);
t_dll	*dll_pop(t_dll **lst, int first);
void	dll_delone(t_dll **to_del);
void	dll_del(t_dll **lst);
void	dll_del_f(t_dll **lst, t_del *f);
void	dll_delone_f(t_dll **to_del, t_del *f);

int		dll_iter_int(t_dll *dll, t_cmp cmp, void *compare_against);
t_dll	*dll_iter_dll(t_dll *dll, t_cmp cmp, void *compare_against);
int		dll_foreach(t_dll *dll, t_do f);

// /*
// **	STACK OPS
// */

// void					dlist_swap(t_dll **l);
// void					dlist_push_m_to_n(t_dll **top_m, t_dll **top_n);
// void					dlist_rotate(t_dll **top);
// void					dlist_rev_rotate(t_dll **top);

// void					dlist_rev_rotate_both(t_dll **l, t_dll **m);
// void					dlist_rotate_both(t_dll **l, t_dll **m);
// void					dlist_swap_both(t_dll **l, t_dll **m);

/*
**	DLIST EXTENSION
*/

// int						dlst_iter(t_dll *top, int f());
// int						dlist_max(t_dll *top);
// int						dlist_min(t_dll *top);
int						cdll_distance_to(t_dll *top, void *target);
// t_dll					*dlst_full_cpy(t_dll *top);

// int						dlist_inf(t_dll *a, int value);
int						cdll_size(t_dll *top);
// int						dlist_min_max(t_dll *lst, int *min, int *max);
// int						is_sorted_dlist(t_dll *top, int order);

// /*
// **	VISUAL
// */

// void					printf_dlist(char *msg, t_dll *clst);

#endif
