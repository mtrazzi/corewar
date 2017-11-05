#include <stdlib.h>
#include <sys/types.h>

void	*malloc_wrapper(size_t size)
{
	void			*new;
	static size_t	count = 0;

	(void)count;
	count++;
	if (count == 10)//
		return (NULL);
	new = malloc(size);
	return (new);
}
