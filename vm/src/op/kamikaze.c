
#include "vm.h"

#define BYTES_PER_LINE 64//move
#define BPL BYTES_PER_LINE
#define RADIUS 30

void	reset_color(t_env *e, u_int pos, t_prc *prc)
{
	e->map_color[pos].color = 0;
	e->map_color[pos].is_prc = 0;
	e->map_color[pos].prc_count = 0;
	e->map_color[pos].color_live = 0;
	e->map_color[pos].live_count = 0;
	e->map[pos] = 0;

	t_dll	*current;
	t_dll	*tmp;
	t_prc	*tmp_prc;

	current = e->prc_lst;
	while (current)
	{
		tmp = current->next;
		tmp_prc = (t_prc *)current->content;
		if (mod_map(tmp_prc->pc) == pos
				&& tmp_prc->id != prc->id)
			dll_delone(&current);
		current = tmp;
	}
}

int		kamikaze(t_env *e, t_prc *prc)
{
	int	r;
	int pos;
	int y;
	int x;

	r = RADIUS + 1;
	pos = prc->pc;
	y = 0;
	while (--r > 0)
	{
		x = -r - 1;
		while (++x < r)
		{
			if (pos + y <= MEM_SIZE && (pos + y) / BPL == (pos + y + x) / BPL)//simplify
				reset_color(e, mod_map(pos + y + x), prc);
			if (pos - y >= 0 && (pos + y) / BPL == (pos - y + x) / BPL)
				reset_color(e, mod_map(pos - y + x), prc);
		}
		y += BPL;
	}
	if (e->par.opts & OPT_V4)
		printf("P %4d | Bomb has been planted, escaping the site to %d\n", prc->id, mod_map(prc->pc + RADIUS + 1));
	prc->pc = mod_map(prc->pc + RADIUS + 1);
	return (1);
}