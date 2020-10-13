/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 12:52:45 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/03/11 12:52:57 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



//https://github.com/Glagan/42-cub3d

#include "cub3d.h"


int ft_close(void)
{
	exit(0);
}

int main(int argc, char **argv)
{
	if(argc < 2)
		ft_putstr_fd("too few arguments\n", 1);
	else if(argc > 2)
		ft_putstr_fd("too many arguments\n", 1);
	else
	{
		t_cub3d cub3d;
		t_data cubdata;
		initialize(&cub3d);
		parssing(&cubdata, argv[1]);
		cub3d.connection = mlx_init();
		cub3d.window = mlx_new_window(cub3d.connection, screenWidth,screenHeight, "Cub3D");
		cub3d.image_ptr = mlx_new_image(cub3d.connection, screenWidth, screenHeight);
		cub3d.data = (int*)mlx_get_data_addr(cub3d.image_ptr, &(cub3d.bpp), &(cub3d.size), &(cub3d.endian));
		draw_wall(&cub3d);//to draw walls for the first time the screen is opened 
		mlx_put_image_to_window(cub3d.connection, cub3d.window, cub3d.image_ptr, 0, 0);
		mlx_hook(cub3d.window, 2, 0, ft_key_press, &cub3d);
		mlx_hook(cub3d.window, 17, 0, ft_close, &cub3d);
		mlx_loop(cub3d.connection);
	}
	
	return (0);
}























