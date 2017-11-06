/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:08:27 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/29 15:30:46 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		error_parse(t_parse *p)
{
	ft_fprintf(ERR_OUT, "Error at [line, char][%d, %d]: {%s}\n",
				p->line_count + 1, p->alc - p->add_line_start + 1, p->alc);
	return (1);
}

int		reopen_error(char *file_name)
{
	ft_fprintf(ERR_OUT, "Can't reopen source file '%s'\n", file_name);
	return (1);
}
