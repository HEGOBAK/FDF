/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchu <jchu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:25:15 by jchu              #+#    #+#             */
/*   Updated: 2023/03/02 03:07:41 by jchu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(t_fdf *point_a, t_fdf *point_b, t_fdf storage)
{
	point_a->x *= storage.scale;
	point_b->x *= storage.scale;
	point_a->y *= storage.scale;
	point_b->y *= storage.scale;
	point_a->z *= storage.z_scale;
	point_b->z *= storage.z_scale;
}

void	pos(t_fdf *point_a, t_fdf *point_b, t_fdf storage)
{
	point_a->x += storage.pos_x;
	point_b->x += storage.pos_x;
	point_a->y += storage.pos_y;
	point_b->y += storage.pos_y;
}

void	do_isometric(t_fdf *pa, t_fdf *pb, t_fdf storage)
{
	if (storage.do_isometric)
	{
		pa->x = (pa->x - pa->y) * cos(storage.angle);
		pa->y = (pa->x + pa->y) * sin(storage.angle) - pa->z;
		pb->x = (pb->x - pb->y) * cos(storage.angle);
		pb->y = (pb->x + pb->y) * sin(storage.angle) - pb->z;
	}
}

void	set_param(t_fdf *point_a, t_fdf *point_b, t_fdf storage)
{
	zoom(point_a, point_b, storage);
	do_isometric(point_a, point_b, storage);
	pos(point_a, point_b, storage);
}

float	abs_val(float i)
{
	if (i < 0)
		return (-i);
	return (i);
}

float	find_max(float a, float b)
{
	float	x;
	float	y;

	x = abs_val(a);
	y = abs_val(b);
	if (x > y)
		return (x);
	return (y);
}

void	set_color(int *color, t_fdf a, t_fdf b)
{
	int	tmp;

	if (a.z || b.z)
		tmp = 0xfc0345;
	else
		tmp = 0xBBFAFF;
	if (a.z != b.z)
		*color = 0xfc031c;
	else
		*color = tmp;
}

void	line(t_fdf point_a, t_fdf point_b, t_fdf x)
{
	float	step_x;
	float	step_y;
	float	max;
	int		color;

	set_param(&point_a, &point_b, x);
	step_x = point_b.x - point_a.x;
	step_y = point_b.y - point_a.y;
	max = find_max(step_x, step_y);
	step_x /= max;
	step_y /= max;
	set_color(&color, point_a, point_b);
	while ((int)(point_a.x - point_b.x) || (int)(point_a.y - point_b.y))
	{
		mlx_pixel_put(x.mlx_ptr, x.win_ptr, point_a.x, point_a.y, color);
		point_a.x += step_x;
		point_a.y += step_y;
		if (point_a.x > x.win_width || point_a.y > x.win_height)
			break ;
		if (point_a.x < 0 || point_a.y < 0)
			break ;
	}
}

void	draw(t_fdf **matrix)
{
	int	y;
	int	x;

	print_menu(matrix[0][0]);
	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (1)
		{
			if (matrix[y + 1])
				line(matrix[y][x], matrix[y + 1][x], matrix[0][0]);
			if (matrix[y][x + 1].last_x)
				break ;
			else
				line(matrix[y][x], matrix[y][x + 1], matrix[0][0]);
			x++;
		}
		y++;
	}
}