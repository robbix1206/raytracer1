/*
** cone.c for 104 in /home/robin.milas/Current/104intersection
** 
** Made by Robin MILAS
** Login   <robin.milas@epitech.net>
** 
** Started on  Tue Jan  3 14:36:45 2017 Robin MILAS
** Last update Fri Mar 17 12:55:21 2017 Milas Robin
*/

#include <math.h>
#include <SFML/System.h>
#include "raytracer.h"

sfVector3f	get_normal_cone(sfVector3f intersection_point,
				float semiangle)
{
  if (semiangle <= 0 || semiangle >= 90)
    {
      intersection_point.x = 0.0f;
      intersection_point.y = 0.0f;
      intersection_point.z = 0.0f;
      return (intersection_point);
    }
  intersection_point.z *= -cos(semiangle * M_PI / 180);
  return (intersection_point);
}

float	intersect_cone(sfVector3f pos, sfVector3f dir, float p)
{
  float	a;
  float	b;
  float	c;
  float	angle;

  if (p <= 0 || p >= 90)
    {
      return (-1.0f);
    }
  angle = p * M_PI / 180;
  a = powf(dir.x, 2) + powf(dir.y, 2) - powf(dir.z, 2) * powf(tanf(angle), 2);
  b = 2 * (pos.x * dir.x
	   + pos.y * dir.y
	   - pos.z * dir.z * powf(tanf(angle), 2));
  c = powf(pos.x, 2) + powf(pos.y, 2);
  c -= (powf(pos.z, 2) * powf(tanf(angle), 2));
  return (intersection(a, b, c));
}
