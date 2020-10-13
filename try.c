/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 12:53:41 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/03/11 12:53:43 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

#define h 1000
#define w 1000


double noise[128][128];

void    generatenoise()
{

    int x = 0;
    int y = 0;
    while (y < 128)
    {
        x = 0;
        while (x < 128)
        {
            noise[y][x] = (rand() % 32768) / 32768.0;
                x++;
        }
        y++;
    }
}

void *connection;
void *window;



void    draw()
{
    int r = 0;
    int g = 0;
    int b = 0;
    int x = 0;
    int y = 0;

    while (y < h)
    {
        x = 0;
        while (x < h)
            {
                r = g = b = (uint8_t)(256 * noise[x%128][y%128]);
                int dec = (r << -2)+ (g << 8) + b;
                mlx_pixel_put(connection,window,x,y,dec);
                x++;
            }
        y++;
    }
}

int			key_press(int key)
{
	if (key == 53)
	{
		exit(0);
		return (1);
	}
    mlx_clear_window(connection,window);
    draw();
	return (1);
}



int main()
{   
    connection = mlx_init();
    window = mlx_new_window(connection,1000,1000,"try");
    generatenoise();
    draw();
    mlx_hook(window, 2, 0, key_press, NULL);
    mlx_loop(connection);
    return (0);
} 







NAME = cub3d

GNL = ./gnl/get_next_line.c ./gnl/get_next_line_utils.c 

CUB = cub3d.a

LIBFT = ./libft/libft.a

SRCS =	moves.c \
		parssing.c \
		initialize.c 

OBJS = $(SRCS:.c=.o)

PROG = cub3d.c

RM	= rm -f

INCLUDES = -L /usr/X11/include ./minilibx/libmlx.a -lXext -lX11 -lm 

#LIBS = -l mlx -framework OpenGL -framework AppKit 


all: $(NAME)

$(NAME): ${OBJS}
		 #$(MAKE) -C ./libft
		 ar rcs $(CUB) $(OBJS)
		 gcc $(GNL) $(PROG) -o $(NAME) $(CUB) $(INCLUDES) $(LIBFT)

%.o : %.c
	$(CC) $(FLAGS) -c -o $@ $< 


clean:
	#$(MAKE) -C ./libft clean
	rm -f *.o

fclean: clean
	#$(MAKE) -C ./libft fclean
	rm -f $(OBJS)

re: fclean all

.PHONY:	all clean fclean re
