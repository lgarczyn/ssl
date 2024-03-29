# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/06 14:07:52 by lgarczyn          #+#    #+#              #
#    Updated: 2019/10/13 02:20:01 by lgarczyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wextra -Wall -Werror

LFLAGS = -O3 -march=native -flto

CC = gcc

AR = ar rc

SRC = ft_atoi.c \
	  ft_bzero.c \
	  ft_intlen.c \
	  ft_isalnum.c \
	  ft_isalpha.c \
	  ft_isascii.c \
	  ft_isdigit.c \
	  ft_isempty.c \
	  ft_isprint.c \
	  ft_isspace.c \
	  ft_itoa.c \
	  ft_lstadd.c \
	  ft_lstdel.c \
	  ft_lstdelone.c \
	  ft_lstiter.c \
	  ft_lstmap.c \
	  ft_lstnew.c \
	  ft_memalloc.c \
	  ft_memccpy.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memdel.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_putchar.c \
	  ft_putchar_fd.c \
	  ft_putendl.c \
	  ft_putendl_fd.c \
	  ft_putnbr.c \
	  ft_putnbr_fd.c \
	  ft_putnstr.c \
	  ft_putnstr_fd.c \
	  ft_putspace.c \
	  ft_putstr.c \
	  ft_putstr_fd.c \
	  ft_realloc.c \
	  ft_strcat.c \
	  ft_strchr.c \
	  ft_strclr.c \
	  ft_strcmp.c \
	  ft_strcmp_fast.c \
	  ft_strcpy.c \
	  ft_strdel.c \
	  ft_strdup.c \
	  ft_strequ.c \
	  ft_striter.c \
	  ft_striteri.c \
	  ft_strjoin.c \
	  ft_strlcat.c \
	  ft_strlen.c \
	  ft_strlen_fast.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_strncat.c \
	  ft_strncmp.c \
	  ft_strncpy.c \
	  ft_strnequ.c \
	  ft_strnew.c \
	  ft_strnstr.c \
	  ft_strrchr.c \
	  ft_strsplit.c \
	  ft_strstr.c \
	  ft_strsub.c \
	  ft_strtrim.c \
	  ft_tolower.c \
	  ft_toupper.c \
	  ft_buf.c \
	  ft_flush_buf.c \
	  ft_get_buf.c \
	  ft_putchar_buf.c \
	  ft_putendl_buf.c \
	  ft_putnbr_buf.c \
	  ft_putnendl_buf.c \
	  ft_putnstr_buf.c \
	  ft_putspace_buf.c \
	  ft_putstr_buf.c \
	  ft_reset_buf.c \
	  ft_setfd_buf.c \

RM = rm -f

NOM = $(basename $(SRC))
OBJ = $(addsuffix .o, $(NOM))
DEB = 

all: $(NAME)

%.o: src/%.c
	$(CC) $(LFLAGS) -o $@ -c $< $(FLAGS) $(DEB)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
