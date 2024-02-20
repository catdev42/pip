# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 15:27:14 by myakoven          #+#    #+#              #
#    Updated: 2024/02/17 21:41:21 by myakoven         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= pipex
NAME_BONUS := pipexbonus

LIBNAME = libft.a
LIBDIR = ./libft
LIBFT = ./libft/libft.a

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#

HEADERS 	:= .
SRC     	:= pipex.c pipex_utils.c
OBJS     	= $(SRC:.c=.o)

SRCBONUS	:= ./pipex_bonus/pipex_bonus.c ./pipex_bonus/pipex_utils_bonus.c
OBJSBONUS	:= $(SRCBONUS:.c=.o)

# BONUS		= 
# BONUS_OBJS	= $(BONUS:.c=.o)

CC      	:= cc
CFLAGS  	:= -Wall -Wextra -Werror -g

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
	make -C $(LIBDIR)
# cp $(LIBDIR)/$(LIBNAME) .
# mv $(LIBNAME) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o pipex
# ar -r $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	cd $(LIBDIR) && make clean
	rm -f $(OBJSBONUS)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	cd $(LIBDIR) && make fclean

re: fclean all

bonus: $(NAME_BONUS) 

$(NAME_BONUS): $(LIBFT) $(OBJSBONUS)
	$(CC) $(CFLAGS) -g $(SRCBONUS) $(LIBFT) -o pipexbonus
# 	$(CC) $(CFLAGS) -g $(OBJSBONUS) $(LIBFT) -o pipexbonus


# bonus:	$(OBJS) $(BONUS_OBJS)
# 	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

#cc $(CFLAGS) -c $(SRC) -I $(HEADERS)
