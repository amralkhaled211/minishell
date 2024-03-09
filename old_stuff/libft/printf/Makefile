# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/27 16:32:32 by aismaili          #+#    #+#              #
#    Updated: 2023/12/14 21:58:56 by aismaili         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = /bin/rm -f

NAME = libftprintf.a

SRCS =  ft_printf.c ft_printaddress.c ft_printunbr.c ft_printhexab.c ft_printhexas.c ft_printchar.c ft_printstr.c ft_printnbr.c
OBJS = $(SRCS:.c=.o)

#Execute when run make
all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

#Build object files from .c files
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

#Remove object files
clean:
	$(RM) $(OBJS)

#Remove object files
fclean:
	$(RM) $(OBJS) $(NAME)

#Rebuild program
re: fclean all

#These targets are always executed
.PHONY: all clean fclean re
