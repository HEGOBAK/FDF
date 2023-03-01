/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchu <jchu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:51:36 by jchu              #+#    #+#             */
/*   Updated: 2023/03/02 03:10:47 by jchu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// up : 126
// down : 125
// left : 123
// right : 124
// ESC : 53
// + : 24
// - : 27
// f : 3
// space : 49
// w : 13
// s : 1
// d : 2
// a : 0
// 1 : 18
// 2 : 19
// 3 : 20
// 4 : 21

void	check_shift_zoom(int keycode, t_fdf *storage, t_fdf **matrix_grid)
{
	if (keycode == 126)
		storage->pos_y -= 10;
	if (keycode == 125)
		storage->pos_y += 10;
	if (keycode == 123)
		storage->pos_x -= 10;
	if (keycode == 124)
		storage->pos_x += 10;
	if (keycode == 24)
		storage->scale += 1;
	if (keycode == 27)
		storage->scale -= 1;
	if (keycode == 18)
		storage->angle += 0.05;
	if (keycode == 19)
		storage->angle -= 0.05;
	if (keycode == 20)
		storage->z_scale += 1;
	if (keycode == 21)
		storage->z_scale -= 1;
	mlx_clear_window(storage->mlx_ptr, storage->win_ptr);
	draw(matrix_grid);
}

void	full_screen(t_fdf *storage)
{
	static int	old_width;
	static int	old_height;

	if (storage->win_width != 1475 || storage->win_height != 900)
	{
		old_width = storage->win_width;
		old_height = storage->win_height;
		storage->win_width = 1475;
		storage->win_height = 900;
	}
	else
	{
		storage->win_width = old_width;
		storage->win_height = old_height;
	}
}

void	reset_window(t_fdf *a, t_fdf **matrix)
{
	mlx_destroy_window(a->mlx_ptr, a->win_ptr);
	a->mlx_ptr = mlx_init();
	a->win_ptr = mlx_new_window(a->mlx_ptr, a->win_width, a->win_height, "FDF");
	a->pos_x = a->win_width / 3;
	a->pos_y = a->win_height / 3;
	draw(matrix);
	mlx_key_hook(a->win_ptr, deal_key, matrix);
	mlx_loop(a->mlx_ptr);
}

void	mod_window(int keycode, t_fdf *storage, t_fdf **matrix)
{
	if (keycode == 13)
		storage->win_height += 100;
	if (keycode == 1)
		storage->win_height -= 100;
	if (keycode == 2)
		storage->win_width += 100;
	if (keycode == 0)
		storage->win_width -= 100;
	if (keycode == 3)
		full_screen(storage);
	reset_window(storage, matrix);
}

int	check_win_key(int keycode)
{
	if (keycode == 3 || keycode == 13 || keycode == 1)
		return (1);
	if (keycode == 2 || keycode == 0)
		return (1);
	return (0);
}

int	deal_key(int keycode, t_fdf **matrix)
{
	if (keycode == 53)
	{
		mlx_destroy_window(matrix[0][0].mlx_ptr, matrix[0][0].win_ptr);
		free(matrix);
		exit(1);
	}
	if (keycode == 49)
	{
		if (matrix[0][0].do_isometric)
			matrix[0][0].do_isometric = 0;
		else
			matrix[0][0].do_isometric = 1;
	}
	check_shift_zoom(keycode, &matrix[0][0], matrix);
	if (check_win_key(keycode))
		mod_window(keycode, &matrix[0][0], matrix);
	return (0);
}