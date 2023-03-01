/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchu <jchu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:22:41 by jchu              #+#    #+#             */
/*   Updated: 2023/03/02 03:21:57 by jchu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(char *s)
{
	ft_putstr_fd(s, 1);
	exit(1);
}

void	print_matrix_grid(t_fdf **matrix_grid)
{
	int	y = 0;
	while (matrix_grid[y])
	{
		int x = 0;
		while (!matrix_grid[y][x].last_x)
		{
			// printf ("x : %d" , x);
			printf ("%2d " , (int)matrix_grid[y][x].z);
			x++;
		}
		printf ("\n");
		y++;
	}
}

void	print_menu(t_fdf storage)
{
	char	*menu;

	menu = "[up, down, left, right] : move picture";
	mlx_string_put(storage.mlx_ptr, storage.win_ptr, 10, 5, 0x03fc35, menu);
	menu = "[space] : 3d/2d mode ~ [+, -] : zoom";
	mlx_string_put(storage.mlx_ptr, storage.win_ptr, 10, 20, 0x03fc35, menu);
	menu = "[1, 2] : rotation ~ [3, 4] : z-scale";
	mlx_string_put(storage.mlx_ptr, storage.win_ptr, 10, 35, 0x03fc35, menu);
	menu = "[f] : full screen mode";
	mlx_string_put(storage.mlx_ptr, storage.win_ptr, 10, 50, 0x03fc35, menu);
}

void	set_window(t_fdf *a)
{
	a->scale = 20;
	a->z_scale = 1;
	a->win_width = 750;
	a->win_height = 750;
	a->angle = 0.523599;
	a->pos_x = a->win_width / 3;
	a->pos_y = a->win_height / 3;
	a->do_isometric = 1;
	a->mlx_ptr = mlx_init();
	a->win_ptr = mlx_new_window(a->mlx_ptr, a->win_width, a->win_height, "FDF");
}

int	test_key(int key, t_fdf **win_ptr)
{
	printf("KEY : %d\n" ,key);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	**matrix_grid;

	if (argc != 2)
		error("usage: ./fdf map.fdf");
	matrix_grid = initialize(argv[1]);
	set_window(&matrix_grid[0][0]);
	// print_matrix_grid(matrix_grid);
	draw(matrix_grid);
	mlx_key_hook(matrix_grid[0][0].win_ptr, /*test_key*/deal_key, matrix_grid);
	mlx_loop(matrix_grid[0][0].mlx_ptr);
}
