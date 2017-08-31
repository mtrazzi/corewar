#ifndef LIBFT_H
# define LIBFT_H

#include <stdlib.h>
#include <unistd.h>

int		ft_free(void **to_free);

void	ft_bzero(void *s, size_t n);

size_t	ft_strlen(const char *s);

char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strsub(char const *s, unsigned int start, size_t len);

long	ft_atol(const char *nptr);
int 	ft_atoi(const char *nptr);

void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
