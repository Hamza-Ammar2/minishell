# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpons <lpons@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 00:00:00 by minishell         #+#    #+#              #
#    Updated: 2025/12/02 19:00:52 by lpons            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================== COLORS =================================== #

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

# ================================== CONFIG =================================== #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I./libft
LDFLAGS = -lreadline -L./libft -lft

# ================================ DIRECTORIES ================================ #

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# ================================== SOURCES ================================== #

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/init.c \
       $(SRC_DIR)/cleanup.c \
       $(SRC_DIR)/lexer/tokenizer.c \
       $(SRC_DIR)/lexer/token_utils.c \
       $(SRC_DIR)/lexer/quote_tokens.c \
       $(SRC_DIR)/parser/parser.c \
       $(SRC_DIR)/parser/parser_utils.c \
       $(SRC_DIR)/parser/syntax_validator.c

# ================================== OBJECTS ================================== #

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ================================== RULES ==================================== #

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ $(NAME) removed!$(RESET)"

re: fclean all

# ================================== PHONY ==================================== #

.PHONY: all clean fclean re
