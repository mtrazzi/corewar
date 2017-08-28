
#include "libft.h"

int		ft_free(void **to_free)
{
	if (to_free && *to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
	return (1);
}
