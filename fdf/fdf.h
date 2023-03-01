/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchu <jchu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:17:11 by jchu              #+#    #+#             */
/*   Updated: 2023/03/02 02:45:20 by jchu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"

/* -----Color----- */

// gcc main.c initialize.c deal_key.c draw.c ../libft/libft.a ../minilibx_macos/libmlx.a -framework OpenGL -framework AppKit
// gcc test.c ../minilibx_macos/libmlx.a -framework OpenGL -framework AppKit

typedef struct	s_fdf
{
	float	x;
	float	y;
	float	z;
	int		last_x;

	int		scale;
	int		z_scale;
	int		pos_x;
	int		pos_y;
	int		do_isometric;
	double	angle;
	int		win_height;
	int		win_width;
	void	*mlx_ptr;
	void	*win_ptr;
}				t_fdf;

void	error(char *s);
t_fdf	**initialize(char *filename);
int		deal_key(int keycode, t_fdf **matrix);
void	draw(t_fdf **matrix);
void	print_menu(t_fdf storage);

#endif