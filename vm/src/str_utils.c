#include "vm.h"

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
