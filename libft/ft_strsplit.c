/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 17:09:29 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/08/14 18:18:30 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	cnt_wrd(char const *s, char c)
{
	int i;
	int n;

	n = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] && (s[i] == c))
		i++;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			n++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (n);
}

static	size_t	strlen_char(char const *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char			*ft_strsplit_aux(char **tmp)
{
	char *str;

	str = ft_strdup(*tmp);
	free(*tmp);
	free(tmp);
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	char	**tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	if ((tab = (char **)malloc(sizeof(char *) * (cnt_wrd(s, c) + 1))) == NULL)
		return (NULL);
	while (j < cnt_wrd(s, c))
	{
		tmp = (char **)malloc(sizeof(char *));
		while (s[i] == c)
			i++;
		if ((*tmp = ft_strnew(strlen_char(s + i, c))) == NULL)
			return (NULL);
		ft_strncpy(*tmp, s + i, strlen_char(s + i, c));
		i += strlen_char(s + i, c);
		tab[j] = ft_strsplit_aux(tmp);
		j++;
	}
	tab[j] = 0;
	return (tab);
}
