# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbozic <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/29 18:54:12 by dbozic            #+#    #+#              #
#    Updated: 2024/03/20 12:55:12 by dbozic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror
SOURCES = ft_printf.c ft_printf_c.c ft_printf_s.c \
	  ft_printf_p.c ft_printf_d.c ft_printf_u.c \
	  ft_printf_xx.c ft_putchar_fd.c ft_putnbr_fd.c \
	  ft_putstr_fd.c ft_strlen.c ft_bzero.c \
	  ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
	  ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
	  ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
	  ft_lstmap_bonus.c
OBJECTS = $(SOURCES:%.c=%.o)
NAME = push_swap.a

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

%.o: %.c 
	$(CC) $(FLAGS) -I. -o $@ -c $<

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

full: all clean
	clear

.PHONY: clean fclean