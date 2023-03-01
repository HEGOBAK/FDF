/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchu <jchu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:18:45 by jchu              #+#    #+#             */
/*   Updated: 2023/02/28 22:23:43 by jchu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// demo
// 1 1 1 1
// 2 2 2 2
// 3 3 3 3
// 4 4 4 4
// 5 5 5 5

void	print_array(char **array)
{
	int i = 0;
	while (array[i])
		printf ("%s - ", array[i++]);
}

void	fill_matrix(int height, t_fdf **matrix_grid, char *filename)
{
	int		i;
	int		j;
	int		fd;
	char	**array;

	j = 0;
	fd = open(filename, O_RDONLY);
	while (j < height) // height = 5
	{
		i = 0;
		array = ft_split(get_next_line(fd), ' ');
		while (array[i])
		{
			matrix_grid[j][i].y = j;
			matrix_grid[j][i].x = i;
			matrix_grid[j][i].last_x = 0;
			matrix_grid[j][i].z = ft_atoi(array[i]);
			i++;
		}
		free(array);
		j++;
	}
	close(fd);
}

t_fdf	**memory_allocation(int *x, int *y, char *filename)
{
	int		i;
	int		fd;
	char	*line;
	t_fdf	**matrix_grid;

	i = 0;
	fd = open(filename, O_RDONLY, 0);
	if (!fd)
		error("File does not exist");
	line = get_next_line(fd);
	*x = count_strs(line, ' '); // x = 4
	while (line)
	{
		(*y)++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	matrix_grid = (t_fdf **)malloc(sizeof(t_fdf *) * ((*y) + 1)); //6 [0] [1] [2] [3] [4] [5]
	while (i < (*y)) //y = 5
		matrix_grid[i++] = (t_fdf *)malloc(sizeof(t_fdf) * ((*x) + 1)); // [0] [1] [2] [3] [4]
	close(fd);
	return (matrix_grid); // return x = 4 | y = 5
}

t_fdf	**initialize(char *filename)
{
	int		i;
	int		x;
	int		y;
	t_fdf	**matrix_grid;

	y = 0;
	x = 0;
	matrix_grid = memory_allocation(&x, &y, filename);
	/*
	x = 4
	y = 5
	ret = [1] [1] [1] [1] []
	 	  [2] [2] [2] [2] []
		  [3] [3] [3] [3] []
		  [4] [4] [4] [4] []
		  [5] [5] [5] [5] []
		  []  []  []  []  []
	*/
	fill_matrix(y, matrix_grid, filename);
	i = 0;
	while (i < y)
		matrix_grid[i++][x].last_x = 1;
	matrix_grid[y] = NULL;
	return (matrix_grid);
}
