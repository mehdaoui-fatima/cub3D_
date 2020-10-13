# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmehdaou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/21 16:49:15 by fmehdaou          #+#    #+#              #
#    Updated: 2019/12/30 12:18:21 by fmehdaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



######### addddddd flags !!!!!!!!
NAME =	cub3d

LIBFT = ./libft/libft.a

CUB3D = cub3d.c

CUBLIB = cub3d.a

GNL = ./gnl/get_next_line.c ./gnl/get_next_line_utils.c 

SRCS = initialize.c \
	   parsing.c \
	   walls.c 
		
OBJS =$(SRCS:.c=.o)

FLAGS=-Wall -Werror -Wextra

CC=gcc

INCLUDES = -L /usr/X11/include ./minilibx/libmlx.a -lXext -lX11 -lm 

LIBS = -l mlx -framework OpenGL -framework AppKit 

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): ${OBJS}
		 #$(MAKE) -C ./libft
		 ar rcs $(CUBLIB) $(OBJS)
		 gcc $(GNL) $(CUB3D) -o $(NAME) $(CUBLIB) $(INCLUDES) $(LIBFT)


%.o : %.c
	$(CC) -c -o $@ $< 
 
clean:
	$(MAKE) -C ./libft clean
	rm -f *.o
fclean: clean
	#$(MAKE) -C ./libft fclean
	rm -f $(NAME)
	rm -f $(CUBLIB)
re: fclean all