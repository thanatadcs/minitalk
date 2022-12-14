# **************************************************************************** # #                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tanukool <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/27 11:38:43 by tanukool          #+#    #+#              #
#    Updated: 2022/08/27 11:51:36 by tanukool         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft

NAME = minitalk

S_SRC = server.c
S_NAME = server

C_SRC = client.c
C_NAME = client 

BS_SRC = server_bonus.c
BS_NAME = server_bonus

BC_SRC = client_bonus.c
BC_NAME = client_bonus

LIBFT = libft/libft.a
LIBFT_DIR = libft

all: $(NAME)

$(NAME): server client


$(S_NAME): $(S_SRC) $(LIBFT)
	$(CC) $(CFLAGS) $< -o $@

$(C_NAME): $(C_SRC) $(LIBFT)
	$(CC) $(CFLAGS) $< -o $@

bonus: $(BS_NAME) $(BC_NAME)

$(BS_NAME): $(BS_SRC) $(LIBFT)
	$(CC) $(CFLAGS) $< -o $@

$(BC_NAME): $(BC_SRC) $(LIBFT)
	$(CC) $(CFLAGS) $< -o $@


$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make fclean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(C_NAME) $(S_NAME) $(BC_NAME) $(BS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
