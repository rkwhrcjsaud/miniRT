# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 13:33:49 by gibkim            #+#    #+#              #
#    Updated: 2023/11/15 16:41:48 by gibkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror
MANDATORY=atoi bzero calloc isalnum isalpha isascii\
	isdigit isprint itoa memchr\
	memcmp memcpy memmove memset putchar_fd putendl_fd putnbr_fd putstr_fd\
	split strchr strdup striteri strjoin strlcat strlcpy strlen strmapi\
	strncmp strnstr strrchr strtrim substr tolower toupper\
	print_bx print_c print_d print_p print_percent print_s print_sx\
	print_u printf_utils printf setflag sizetohex uitoa strcmp\
	get_next_line get_next_line_utils atof
BONUS=lstadd_back lstadd_front lstclear lstdelone lstiter\
	lstlast lstmap lstnew lstsize
MSRCS=$(addsuffix .c, $(addprefix ft_, $(MANDATORY)))
MOBJS=$(MSRCS:.c=.o)
BSRCS=$(addsuffix _bonus.c, $(addprefix ft_, $(BONUS)))
BOBJS=$(BSRCS:.c=.o)
NAME=libft.a

ifdef ADD_BONUS
	OBJS=$(MOBJS) $(BOBJS)
else
	OBJS=$(MOBJS)
endif

.PHONY: all clean fclean re bonus

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I./

bonus:
	@make ADD_BONUS=1 all

$(NAME): $(OBJS)
	@ar crus $@ $^

clean:
	@rm -f $(MOBJS) $(BOBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean
	@make all
