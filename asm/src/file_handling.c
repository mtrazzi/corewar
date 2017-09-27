/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:08:27 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/27 20:26:27 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define W2 ("(Should end with '.s')")
#define W1 ("Wrong file extension for")

int		update_fd_asm(t_asm *a, char *file_name)
{
	int		size_name;
	char	*new_filename;

	size_name = ft_strlen(file_name) - 2;
	new_filename = ft_strnew(size_name + 5);//change
	if (!new_filename)
		return (-1);
	ft_strncpy(new_filename, file_name, size_name);
	ft_strcpy(new_filename + size_name, ".corr");//CHANGE
	a->fd = open(new_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (a->fd < 0)
		return (-1);
	free(new_filename);
	return (1);
}

int		open_file(char *file_name, int *fd)
{
	char	*tmp;

	tmp = file_name + ft_strlen(file_name) - 2;
	if (ft_strcmp(tmp, ".s") != 0)
		return (-1 * ft_fprintf(2, "%s '%s' %s\n", W1, file_name, W2));
	*fd = open(file_name, O_RDONLY);
	if (*fd < 0)
		return (-1 * ft_fprintf(2, "Can't read source file '%s'\n", file_name));
	return (1);
}
