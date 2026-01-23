

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
CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR) -I./libft
LDFLAGS = -lreadline -L./libft -lft

# ================================ DIRECTORIES ================================ #

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# ================================== SOURCES ================================== #

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/init.c \
       $(SRC_DIR)/cleanup.c \
	   $(SRC_DIR)/signal_stuff.c \
       $(SRC_DIR)/lexer/tokenizer.c \
       $(SRC_DIR)/lexer/token_utils.c \
       $(SRC_DIR)/lexer/quote_tokens.c \
       $(SRC_DIR)/lexer/word_builder.c \
       $(SRC_DIR)/parser/parser.c \
       $(SRC_DIR)/parser/parser_utils.c \
       $(SRC_DIR)/parser/syntax_validator.c \
       $(SRC_DIR)/parser/pipline_parsing.c \
       $(SRC_DIR)/parser/redirection_parsing.c \
       $(SRC_DIR)/parser/pipe_redirect_validation.c \
       $(SRC_DIR)/parser/debug_print.c \
	   $(SRC_DIR)/ft_fprintf/ft_fprintf_utils.c \
	   $(SRC_DIR)/ft_fprintf/ft_fprintf.c \
	   $(SRC_DIR)/exec/exec.c \
	   $(SRC_DIR)/exec/utils.c \
	   $(SRC_DIR)/exec/builtins.c \
	   $(SRC_DIR)/exec/builtins2.c \
	   $(SRC_DIR)/exec/utils_str.c \
	   $(SRC_DIR)/exec/env_stuff.c \
	   $(SRC_DIR)/exec/directio.c \
	   $(SRC_DIR)/exec/exec_func_utils.c \
	   $(SRC_DIR)/exec/get_next_line.c \
	   $(SRC_DIR)/exec/get_next_line_utils.c \
	   $(SRC_DIR)/exec/exec_utils.c \
	   $(SRC_DIR)/exec/here_doc_stuff.c \
	   $(SRC_DIR)/exec/builtins3.c \
	   $(SRC_DIR)/exec/builtins4.c \
	   $(SRC_DIR)/exec/cd.c \
	   $(SRC_DIR)/exec/handle_quotes.c \
	   $(SRC_DIR)/exec/handle_quotes_hd.c \
	   $(SRC_DIR)/exec/pipe.c

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
