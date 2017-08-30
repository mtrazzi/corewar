#include "vm.h"

# define B0 0x000000ff
# define B1 0x0000ff00
# define B2 0x00ff0000
# define B3 0xff000000

int   ft_is_number(char *str)
{
  if (*str == '-' && *(str + 1) < '9' && *(str + 1) > '0')
    str++;
  while (*str)
  {
    if (*str > '9' || *str < '0')
      return (0);
    str++;
  }
  return (1);
}

int   ft_is_int(char *str)
{
  if (!ft_is_number(str))
    return (0);
  if (ft_strlen(str) > 11)
    return (0);
  if (ft_atol(str) < INT_MIN || ft_atol(str) > INT_MAX)
   return (0);
  return (1);
}

u_int   convert_uint(u_int n)
{
    return ((n & B0) << 24 | (n & B1) << 8 | (n & B2) >> 8
    | (n & B3) >> 24);
}

u_int   convert_ushort(u_short n)
{
    return ((n & B0) << 8 | (n & B1) >> 8);
}

void    color_tab(void)
{
 g_color_tab[0] = "";
 g_color_tab[1] = "\033[0;32m";          //green
 g_color_tab[2] = "\033[0;30m\033[42m";  //black on green
 g_color_tab[3] = "\033[0;34m";          //blue
 g_color_tab[4] = "\033[0;30m\033[44m";  //black on blue
 g_color_tab[5] = "\033[0;31m";          //red
 g_color_tab[6] = "\033[0;30m\033[41m";  //black on red
 g_color_tab[7] = "\033[0;36m";          //cyan
 g_color_tab[8] = "\033[0;30m\033[46m";  //black on cyan
 g_color_tab[9] = NULL;
}
