# Compiler and compiling flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
# Project name (executable)
NAME = microshell

# Source files and object files
SRC_DIR = ./src
SRCS =  $(SRC_DIR)/microshell.c \


OBJS = $(SRCS:.c=.o)

# Libraries
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_LIB = $(LIBFT_DIR)/printf/libftprintf.a

# Include directory
INCLUDES = -I$(LIBFT_DIR)

# Rule for making the executable
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(PRINTF_LIB) $(INCLUDES) $(LDFLAGS)

# Rule for making the libft library
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean object files
clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Full clean (objects and executable)
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Re-make everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re