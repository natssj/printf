NAME		= libftprintf.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
RM			= rm -f

SRCS		= ft_printf.c \
			  ft_print_words.c \
			  ft_print_numbers.c \
			  utils.c

OBJS		= $(SRCS:.c=.o)

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

HEADER		= ft_printf.h

all:		$(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(OBJS)


%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re:			fclean all

.PHONY:		all clean fclean re
