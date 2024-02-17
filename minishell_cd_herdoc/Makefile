# Compiler and compiling flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
# Project name (executable)
NAME = microshell

# Source files and object files
SRC_DIR = ./src
SRCS =  $(SRC_DIR)/microshell.c \
		$(SRC_DIR)/token_simple.c \
		$(SRC_DIR)/split_bash.c \
		$(SRC_DIR)/token_advance.c \
		$(SRC_DIR)/shell_prep.c \
		$(SRC_DIR)/utils/before_exec.c \
		$(SRC_DIR)/utils/cleanup.c \
		$(SRC_DIR)/utils/messages.c \
		$(SRC_DIR)/testing/print_cmd_table.c \
		$(SRC_DIR)/env_expand/change_to_value.c \
		$(SRC_DIR)/env_expand/env.c \
		$(SRC_DIR)/env_expand/expand.c \
		$(SRC_DIR)/env_expand/replace_value.c \
		$(SRC_DIR)/env_expand/utils_expand.c \
		$(SRC_DIR)/env_expand/var_validtion.c \
		$(SRC_DIR)/handle_path.c \
		$(SRC_DIR)/bulit_in/dir.c \
		$(SRC_DIR)/bulit_in/cd.c \
		$(SRC_DIR)/bulit_in/echo.c \
		$(SRC_DIR)/bulit_in/env_utils.c \
		$(SRC_DIR)/bulit_in/env_utils2.c \
		$(SRC_DIR)/bulit_in/env.c \
		$(SRC_DIR)/bulit_in/export.c \
		$(SRC_DIR)/bulit_in/pwd.c \
		$(SRC_DIR)/bulit_in/unset.c \
		$(SRC_DIR)/begin_execution.c \
		$(SRC_DIR)/setup_redir.c \
		$(SRC_DIR)/handle_external.c \
		$(SRC_DIR)/here_doc/make_doc.c \
		$(SRC_DIR)/here_doc/expand_doc.c \


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
