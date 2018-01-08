#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile1                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/05 12:04:09 by ggrybova          #+#    #+#              #
#    Updated: 2017/06/08 13:28:04 by ggrybova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
NAMELIB = libft.a

SRC = read_map.c draw_map.c create_map.c rotation.c main.c color.c

OBJ		= $(SRC:.c=.o)

CC		= gcc
CFLAGS  = -Wall -Wextra -Werror
RM 		= rm -f

LIBDIR  = ./libft/
INCDIR	= ./


FLG = -lmlx -framework OpenGL -framework AppKit

all: obj $(NAME)

obj:
	mkdir -p $(LIBDIR)

$(INDIR)%.o: $(INDIR)%.c
	$(CC)  $(CFLAGS)  -I $(INCDIR) -c $< -o $@ 

$(NAME): $(NAMELIB) $(OBJ)
	$(CC) $(FLG) -o $(NAME) $(OBJ) -L. -lft

$(NAMELIB):
	cd $(LIBDIR); make; make clean; mv $(NAMELIB) ../;

clean:
	make -C libft/ clean
	rm -rf $(OBJ)

fclean: clean
	$(RM) $(NAME) $(NAMELIB)

re: fclean all
