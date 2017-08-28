/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 16:44:17 by pkirsch           #+#    #+#             */
/*   Updated: 2017/08/28 16:33:34 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1024
# define END_FILE 0
# define FAILURE -1
# define FOUND_SOMETHING 1
# define FOUND_LINE 1

# define MAL_ERR_GNL -1221

#include <fcntl.h>
#include "libft.h"

typedef struct s_gnl	t_gnl;

struct		s_gnl
{
	char	**line;
	char	**rem;
	int		fd;
};

int			get_next_line(int const fd, char **line, char **rem);

#endif
