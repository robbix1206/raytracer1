/*
** utils.c for raytracer in /home/robin.milas/Current/raytracer1
** 
** Made by Robin MILAS
** Login   <robin.milas@epitech.net>
** 
** Started on  Tue Mar  7 21:58:14 2017 Robin MILAS
** Last update Mon Mar 20 11:59:08 2017 Milas Robin
*/

#include <math.h>

float	intersection(double a, double b, double c)
{
  double	d;
  double	t1;
  double	t2;

  d = pow(b, 2) - (4 * a * c);
  if (d < 0)
    {
      return (-1.0f);
    }
  else if (d == 0.0)
    {  
      return (((t1 = (-b / (2 * a))) >= 0) ? t1 : -1.0f);
    }
  else
    {
      t1 = (-b + sqrt(d)) / (2 * a);
      t2 = (-b - sqrt(d)) / (2 * a);
      if (t1 >= 0.0f && (t1 < t2 || t2 <= 0.0f))
	return (t1);
      if (t2 >= 0.0f)
	return (t2);
      else
	return (-1.0f);
    }
}

int	my_strcmp(char *s1, char *s2)
{
  int	index;

  index = 0;
  while (s1[index] == s2[index])
    {
      if (s1[index] == '\0')
	{
	  return (0);
	}
      index = index + 1;
    }
  return (s1[index] - s2[index]);
}
