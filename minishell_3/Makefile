# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/04 11:23:52 by aismaili          #+#    #+#              #
#    Updated: 2024/03/17 19:03:19 by aismaili         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
NAME = minishell

SRC_DIR = ./src
SRCS =  $(SRC_DIR)/main/microshell.c \
		$(SRC_DIR)/parsing/token_simple.c \
		$(SRC_DIR)/parsing/token_simple2.c \
		$(SRC_DIR)/lexar/split_bash.c \
		$(SRC_DIR)/lexar/split_bash_utils.c \
		$(SRC_DIR)/lexar/split_bash_utils2.c \
		$(SRC_DIR)/lexar/split_bash_utils3.c \
		$(SRC_DIR)/lexar/split_bash_utils4.c \
		$(SRC_DIR)/lexar/split_bash_utils5.c \
		$(SRC_DIR)/lexar/split_bash_utils6.c \
		$(SRC_DIR)/lexar/split_bash_utils7.c \
		$(SRC_DIR)/lexar/ft_split_sec.c \
		$(SRC_DIR)/lexar/split_sec_utils.c \
		$(SRC_DIR)/lexar/split_sec_utils2.c \
		$(SRC_DIR)/parsing/token_advance.c \
		$(SRC_DIR)/parsing/token_advance2.c \
		$(SRC_DIR)/parsing/token_advance3.c \
		$(SRC_DIR)/parsing/token_advance4.c \
		$(SRC_DIR)/parsing/syntax_check.c \
		$(SRC_DIR)/main/shell_prep.c \
		$(SRC_DIR)/utils/before_exec.c \
		$(SRC_DIR)/utils/before_exec2.c \
		$(SRC_DIR)/utils/cleanup.c \
		$(SRC_DIR)/utils/cleanup2.c \
		$(SRC_DIR)/utils/cleanup3.c \
		$(SRC_DIR)/utils/cleanup4.c \
		$(SRC_DIR)/utils/messages.c \
		$(SRC_DIR)/env_expand/change_to_value.c \
		$(SRC_DIR)/env_expand/expand.c \
		$(SRC_DIR)/env_expand/replace_value.c \
		$(SRC_DIR)/env_expand/utils_expand.c \
		$(SRC_DIR)/env_expand/var_validtion.c \
		$(SRC_DIR)/parsing/handle_path.c \
		$(SRC_DIR)/parsing/handle_path2.c \
		$(SRC_DIR)/bulit_in/cd.c \
		$(SRC_DIR)/bulit_in/cd_utils.c \
		$(SRC_DIR)/bulit_in/dir.c \
		$(SRC_DIR)/bulit_in/echo.c \
		$(SRC_DIR)/bulit_in/env_utils.c \
		$(SRC_DIR)/bulit_in/env_utils2.c \
		$(SRC_DIR)/bulit_in/env_utils3.c \
		$(SRC_DIR)/bulit_in/env_utils4.c \
		$(SRC_DIR)/bulit_in/env.c \
		$(SRC_DIR)/bulit_in/export.c \
		$(SRC_DIR)/bulit_in/export_utils.c \
		$(SRC_DIR)/bulit_in/pwd.c \
		$(SRC_DIR)/bulit_in/unset.c \
		$(SRC_DIR)/bulit_in/ft_exit.c \
		$(SRC_DIR)/bulit_in/ft_exit_utils.c \
		$(SRC_DIR)/exec/begin_execution.c \
		$(SRC_DIR)/exec/handle_execution.c \
		$(SRC_DIR)/exec/exec_utils.c \
		$(SRC_DIR)/exec/exec_utils2.c \
		$(SRC_DIR)/exec/exec_utils3.c \
		$(SRC_DIR)/exec/exec_utils4.c \
		$(SRC_DIR)/parsing/setup_redir.c \
		$(SRC_DIR)/parsing/setup_redir2.c \
		$(SRC_DIR)/here_doc/make_doc.c \
		$(SRC_DIR)/here_doc/expand_doc.c \
		$(SRC_DIR)/here_doc/doc_utils.c \
		$(SRC_DIR)/here_doc/doc_utils2.c \
		$(SRC_DIR)/parsing/after_expansion.c \
		$(SRC_DIR)/main/signals_child.c \
		$(SRC_DIR)/main/signals_parent.c \
		$(SRC_DIR)/testing/print_cmd_table.c \
		$/gnl/get_next_line.c \
		$/gnl/get_next_line_utils.c \

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
