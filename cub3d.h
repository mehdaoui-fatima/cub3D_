/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:35:52 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/03/11 12:52:24 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  CUB3D_H
# define  CUB3D_H

#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h> //..perror
#include <stdlib.h>
#include <errno.h> //errno
#include <string.h> //strerror
#include "./libft/libft.h"
#include "./gnl/get_next_line.h"


#define mapWidth 24
#define mapHeight 24
#define screenWidth 700
#define screenHeight 700
#define lookup 126
#define lookdown  125
#define moveright 124
#define moveleft 123
#define max_width 1024
#define max_height 768


typedef struct s_cub3d{
    int *connection;
    int *window;
    double posx; //player position 
    double posy;
    double dirx; //player direction 
    double diry;
    double planx; //plan coordinates

    double plany;
    double cx;    //camera cordinate x
    double x;     // counter 
    double raydirx;  // ray coordinate
    double raydiry;
    int mapx;
    int mapy;
    double sidedistx;
    double sidedisty;
    double perpwalldist;
    int stepx;
    int stepy;
    int hit;
    int side;
    double deltadistx;
    double deltadisty;
    int color ;
    double movespeed;
    double rotspeed;
    double olddirx;
    double oldplanx;
    void   *image_ptr;//to under
    int *data;//to under
    int bpp;//to 
    int endian;
    int size;
    int lineHeight;
    int drawStart ;
    int drawEnd;
    int change;
   int plus;//for lookup lookdown
   int jump;//too jump
   int jumpback;//how much we will jump


}				t_cub3d;

// used to parse map.cub
typedef struct s_data{
  char *line;
  int r;
  int fd;
  int rx;
  int ry;
  char **newline;
  char **new;
  int cr;
  int cg;
  int cb;
  int fr;
  int fg;
  int fb;
	int res;
  char *no;
  char *so;
  char *we;
  char *ea;
  char *s;
  char *map;
}				t_data;


t_cub3d     *initialize(t_cub3d  *cub3d);//init cub3d
t_data      *parssing(t_data *cubdata, char *argv); //parsing .cub
void    draw_wall(t_cub3d *cub3d);// drawing walls
int ft_key_press(int keycode, t_cub3d *cub3d);//to be able to used by main




#endif
