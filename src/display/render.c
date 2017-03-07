/*
** render.c for raytracer.c in /home/robin.milas/Current/bsraytracer1
** 
** Made by Robin MILAS
** Login   <robin.milas@epitech.net>
** 
** Started on  Wed Feb  8 13:46:33 2017 Robin MILAS
** Last update Tue Mar  7 21:28:54 2017 Robin MILAS
*/

#include <math.h>
#include "raytracer.h"

float		find_k(t_scene *scene, sfVector3f *dir, t_obj *obj)
{
  sfVector3f	pos;
  t_intersect	intersect;

  pos.x = scene->cam.pos.x - obj->coord.pos.x;
  pos.y = scene->cam.pos.y - obj->coord.pos.y;
  pos.z = scene->cam.pos.z - obj->coord.pos.z;
  if ((intersect = intersect_decoder(obj->shape.shape)) != NULL)
    return (intersect(&pos, dir, obj));
  return (NAN);
}

float		find_cos(t_scene *scene, sfVector3f *dir, t_obj *obj, float k)
{
  sfVector3f	pos;
  sfVector3f    light;
  t_normal	normal;
  sfVector3f	normal_v;
  float		cos;

  pos.x = scene->cam.pos.x - obj->coord.pos.x;
  pos.y = scene->cam.pos.y - obj->coord.pos.y;
  pos.z = scene->cam.pos.z - obj->coord.pos.z;
  light.x = scene->light.x - (obj->coord.pos.x + dir->x * k);
  light.y = scene->light.y - (obj->coord.pos.y + dir->y * k);
  light.z = scene->light.z - (obj->coord.pos.z + dir->z * k);
  if ((normal = normal_decoder(obj->shape.shape)) != NULL)
    {
      normal_v = normal(&pos, dir, obj, k);
      cos = get_light_coef(light, normal_v);
      if (cos <= 0.0f)
	return (0.0f);
      return (cos);
    }
  return (1.0f);
}

float	        get_closest(t_scene *scene, sfVector3f *dir, t_obj **closest)
{
  t_obj	*ptr;
  float	k;
  float	temp_k;

  ptr = scene->objs;
  k = INFINITY;
  *closest = NULL;
  while (ptr)
    {
      temp_k = find_k(scene, dir, ptr);
      if (temp_k > 0.0f && temp_k < k)
	{
	  k = temp_k;
	  *closest = ptr;
	}
      ptr = ptr->next;
    }
  return (k);
}

sfColor	get_pixel(t_scene *scene, sfVector3f *dir)
{
  sfColor	color;
  t_obj		*obj;
  float		k;

  if ((k = get_closest(scene, dir, &obj)) == INFINITY)
    return (SKY);
  color = obj->shape.color;
  color = color_brightness(color, find_cos(scene, dir, obj, k));
  return (color);
}

void	raytracer(t_scene *scene, t_win *win)
{
  sfVector2i	pos;
  sfVector2i	window_size;
  sfVector3f	dir;

  window_size.x = win->fb.width;
  window_size.y = win->fb.height;
  pos.x = 0;
  pos.y = 0;
  while (pos.x < window_size.x)
    {
      pos.y = 0;
      while (pos.y < window_size.y)
	{
	  dir = calc_dir_vector(DIST, window_size, pos);
	  dir = rotate_xyz(dir, scene->cam.rot);
	  my_put_pixel(&(win->fb), pos.x, pos.y, get_pixel(scene, &dir));
	  pos.y += 1;
	}
      pos.x += 1;
    }
}
