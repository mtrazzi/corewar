
#include "vm.h"

#define BYTES_PER_LINE 64//move
#define BPL BYTES_PER_LINE
#define RADIUS 5

void	reset_color(t_env *e, u_int pos, t_prc *prc)
{
	e->map_color[pos].color = 0;
	e->map_color[pos].is_prc = 0;
	e->map_color[pos].prc_count = 0;
	e->map_color[pos].color_live = 0;
	e->map_color[pos].live_count = 0;
	e->map[pos] = 0;
}

int		kamikaze(t_env *e, t_prc *prc)
{
	int	r;
	int pos;
	int y;
	int x;

	if (e->par.opts & OPT_V4)
		printf("P %4d | exploding\n", prc->id);
	r = RADIUS + 1;
	pos = prc->pc;
	y = 0;
	while (--r > 0)
	{
		x = -r - 1;
		while (++x < r)
		{
			if (pos + y <= MEM_SIZE && (pos + y) / BPL == (pos + y + x) / BPL)
				reset_color(e, mod_map(pos + y + x), prc);
			if (pos - y >= 0 && (pos + y) / BPL == (pos - y + x) / BPL)
				reset_color(e, mod_map(pos - y + x), prc);
		}
		y += BPL;
	}
	return (1);
}