/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:08:27 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/29 17:18:35 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define W2 ("(Should end with '.s')")
#define W1 ("Wrong file extension for")
#define W3 ("Can't read source file")

int		update_fd_asm(t_asm *a, char *file_name)
{
	int		size_name;
	char	*new_filename;

	size_name = ft_strlen(file_name) - 2;
	new_filename = ft_strnew(size_name + ft_strlen(EXTENSION_OUT));
	if (!new_filename)
		return (-1);
	ft_strncpy(new_filename, file_name, size_name);
	ft_strcpy(new_filename + size_name, EXTENSION_OUT);
	a->fd = open(new_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (a->fd < 0)
		return (-1);
	ft_printf("Writing output program to %s\n", new_filename);
	free(new_filename);
	return (1);
}

int		open_file(char *file_name, int *fd)
{
	char	*tmp;

	tmp = file_name + ft_strlen(file_name) - 2;
	if (ft_strcmp(tmp, ".s") != 0)
		return (-1 * ft_fprintf(ERR_OUT, "%s '%s' %s\n", W1, file_name, W2));
	*fd = open(file_name, O_RDONLY);
	if (*fd < 0)
		return (-1 * ft_fprintf(ERR_OUT, "%s '%s'\n", W3, file_name));
	return (1);
}
