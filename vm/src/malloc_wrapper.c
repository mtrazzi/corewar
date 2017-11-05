#include <stdlib.h>
#include <sys/types.h>

void	*malloc_wrapper(size_t size)
{
	void			*new;
	static size_t	count = 0;

	(void)count;
	if (count == 100000)
		return (NULL);
	// count++;
	new = malloc(size);
	return (new);
}
