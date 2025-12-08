CC = cc
CFLAGS = -Wall -Wextra -Werror -I../include -I../libft
LDFLAGS = -lreadline -L../libft -lft

SRCS = test_parser.c \
       ../src/lexer/tokenizer.c \
       ../src/lexer/token_utils.c \
       ../src/lexer/quote_tokens.c \
       ../src/parser/parser.c \
       ../src/parser/parser_utils.c \
       ../src/parser/syntax_validator.c

NAME = test_parser

all: $(NAME)

$(NAME): $(SRCS)
	@make -C ../libft
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $(NAME)

clean:
	@make -C ../libft clean
	rm -f $(NAME)

fclean: clean
	@make -C ../libft fclean

.PHONY: all clean fclean
