# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/18 15:34:09 by trabut            #+#    #+#              #
#    Updated: 2020/03/05 15:21:55 by lbonnete         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

FLAGS       = -Wall -Wextra -Werror -O3

SDL			= -lpthread -F ./frameworks/ -framework SDL2 -framework SDL2_image 
SDL_HEADER	= -I ./frameworks/SDL2.framework/Headers -I ./frameworks/SDL2_image.framework/Headers

LIBFT = libft/libft.a

CC = gcc

HEAD_DIR = INC
SRC_DIR	 = SRC
OBJ_DIR	 = OBJ

SRC =	main.c\
		dealers.c\
		dealers2.c\
		dealers3.c\
		dealers4.c\
		testaffichage3d.c\
		tools.c\
		algo.c\
		tools2.c\
		checker.c\
		mapper.c\
		ft_multi.c\
		blank.c\
		sdl_use.c\
		diag.c

INC = wolf3d_define.h wolf3d_struc.h wolf3d.h
OBJ	= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

$(shell mkdir -p $(OBJ_DIR))

all: $(NAME)
	echo "wolf3D ready"

$(NAME): $(OBJ) $(LIBFT) 
	$(CC) -I $(HEAD_DIR) -o $@ $(OBJ) $(SDL) $(LIBFT) $(FLAGS) 


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I $(HEAD_DIR) -o $@ $(SDL_HEADER) -c $< $(FLAGS)

$(LIBFT):
	make -C libft/ libft.a

p: all clean

clean:
	make clean -C libft
	/bin/rm -f $(OBJ)
	echo "Objects Destroyed"

fclean:	clean
	make fclean -C libft
	/bin/rm -f $(NAME)
	echo "Project Destroyed"

re:	fclean all

.PHONY:	all clean fclean re norm p

.SILENT:
