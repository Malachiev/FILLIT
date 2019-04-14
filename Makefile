# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gconroy <gconroy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/31 18:31:32 by gconroy           #+#    #+#              #
#    Updated: 2019/04/08 20:48:30 by gconroy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
FLAGS = -Wall -Wextra -Werror
FUNC  = main.c open_file.c read_and_verify.c write_to_sheet.c print.c
OBJS = $(patsubst %.c, %.o, $(FUNC))
LIB_OPT = -L./libft/ -lft
LIBFT = libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	gcc $(FLAGS) $(OBJS) $(LIB_OPT) -o $(NAME) -g

%.o: %.c
	gcc $(FLAGS) -c $< -o $@ -I./libft/includes -g

$(LIBFT):
		make -C libft/
clean:
		/bin/rm -f $(OBJS)
		make clean -C libft/

fclean: clean
		/bin/rm -f $(NAME)
		make fclean -C libft/

re:		fclean all