#include "../include/minishell.h"

/* Test 1: Simple tokenization */
void test_tokenize_simple(void)
{
	t_token *tokens = tokenize("ls -la");
	
	printf("Test: tokenize(\"ls -la\")\n");
	if (tokens && tokens->type == TOKEN_WORD)
		printf("First token: type=%d, value=%s\n", tokens->type, tokens->value);
	else
		printf("FAIL\n");
	if (tokens->next && tokens->next->type == TOKEN_WORD)
		printf("Second token: type=%d, value=%s\n", tokens->next->type, tokens->next->value);
	else
		printf("FAIL\n");
	free_tokens(tokens);
	printf("\n");
}

/* Test 2: Pipe tokenization */
void test_tokenize_pipe(void)
{
	t_token *tokens = tokenize("ls | grep test");
	
	printf("Test: tokenize(\"ls | grep test\")\n");
	if (tokens && tokens->type == TOKEN_WORD)
		printf("First token: WORD (%s)\n", tokens->value);
	else
		printf("FAIL\n");
	if (tokens->next && tokens->next->type == TOKEN_PIPE)
		printf("Second token: PIPE\n");
	else
		printf("FAIL\n");
	free_tokens(tokens);
	printf("\n");
}

/* Test 3: Valid syntax */
void test_syntax_valid(void)
{
	t_token *tokens = tokenize("ls -la");
	
	printf("Test: validate_syntax(\"ls -la\")\n");
	if (validate_syntax(tokens))
		printf("Accepted valid syntax\n");
	else
		printf("FAIL - rejected valid syntax\n");
	free_tokens(tokens);
	printf("\n");
}

/* Test 4: Invalid syntax - starts with pipe */
void test_syntax_pipe_start(void)
{
	t_token *tokens = tokenize("| ls");
	
	printf("Test: validate_syntax(\"| ls\")\n");
	if (!validate_syntax(tokens))
		printf("Rejected (starts with pipe)\n");
	else
		printf("FAIL - should reject\n");
	free_tokens(tokens);
	printf("\n");
}

/* Test 5: Invalid syntax - ends with pipe */
void test_syntax_pipe_end(void)
{
	t_token *tokens = tokenize("ls |");
	
	printf("Test: validate_syntax(\"ls |\")\n");
	if (!validate_syntax(tokens))
		printf("Rejected (ends with pipe)\n");
	else
		printf("FAIL - should reject\n");
	free_tokens(tokens);
	printf("\n");
}

/* Test 6: Parse simple command */
void test_parse_simple(void)
{
	t_token *tokens = tokenize("echo hello");
	t_command *cmd = parse(tokens);
	
	printf("Test: parse(\"echo hello\")\n");
	if (cmd && cmd->args[0])
		printf("args[0] = \"%s\"\n", cmd->args[0]);
	else
		printf("FAIL\n");
	if (cmd && cmd->args[1])
		printf("args[1] = \"%s\"\n", cmd->args[1]);
	else
		printf("FAIL\n");
	if (cmd && cmd->args[2] == NULL)
		printf("args[2] = NULL (properly terminated)\n");
	else
		printf("FAIL - not NULL terminated\n");
	free_commands(cmd);
	free_tokens(tokens);
	printf("\n");
}

/* Test 7: Single quotes */
void test_single_quotes(void)
{
	t_token *tokens = tokenize("echo 'hello world'");
	
	printf("Test: tokenize(\"echo 'hello world'\")\n");
	if (tokens && tokens->type == TOKEN_WORD)
		printf("Token 1: value=\"%s\", quote_type=%d\n", tokens->value, tokens->quote_type);
	if (tokens->next && tokens->next->type == TOKEN_WORD)
		printf("Token 2: value=\"%s\", quote_type=%d\n", tokens->next->value, tokens->next->quote_type);
	free_tokens(tokens);
	printf("\n");
}

/* Test 8: Double quotes */
void test_double_quotes(void)
{
	t_token *tokens = tokenize("echo \"hello world\"");
	
	printf("Test: tokenize(\"echo \\\"hello world\\\"\")\n");
	if (tokens && tokens->type == TOKEN_WORD)
		printf("Token 1: value=\"%s\", quote_type=%d\n", tokens->value, tokens->quote_type);
	if (tokens->next && tokens->next->type == TOKEN_WORD)
		printf("Token 2: value=\"%s\", quote_type=%d\n", tokens->next->value, tokens->next->quote_type);
	free_tokens(tokens);
	printf("\n");
}

/* Test 9: Mixed quotes */
void test_mixed_quotes(void)
{
	t_token *tokens = tokenize("echo 'single' \"double\" unquoted");
	t_token *current = tokens;
	int i = 1;
	
	printf("Test: tokenize(\"echo 'single' \\\"double\\\" unquoted\")\n");
	while (current)
	{
		printf("Token %d: value=\"%s\", quote_type=%d\n", i++, current->value, current->quote_type);
		current = current->next;
	}
	free_tokens(tokens);
	printf("\n");
}

/* Test 10: Empty quotes */
void test_empty_quotes(void)
{
	t_token *tokens = tokenize("echo \"\"");
	
	printf("Test: tokenize(\"echo \\\"\\\"\")\n");
	if (tokens && tokens->type == TOKEN_WORD)
		printf("Token 1: value=\"%s\", quote_type=%d\n", tokens->value, tokens->quote_type);
	if (tokens->next && tokens->next->type == TOKEN_WORD)
		printf("Token 2: value=\"%s\", quote_type=%d\n", tokens->next->value, tokens->next->quote_type);
	free_tokens(tokens);
	printf("\n");
}

/* Test 11: Unclosed quote */
void test_unclosed_quote(void)
{
	t_token *tokens = tokenize("echo \"hello");
	
	printf("Test: tokenize(\"echo \\\"hello\") - should error\n");
	if (tokens == NULL)
		printf("✓ Correctly returned NULL for unclosed quote\n");
	else
		printf("✗ FAIL - should return NULL\n");
	free_tokens(tokens);
	printf("\n");
}

int main(void)
{
	printf("\n=== MINISHELL TESTS ===\n\n");
	
	test_tokenize_simple();
	test_tokenize_pipe();
	test_syntax_valid();
	test_syntax_pipe_start();
	test_syntax_pipe_end();
	test_parse_simple();
	
	printf("=== QUOTE HANDLING TESTS ===\n\n");
	test_single_quotes();
	test_double_quotes();
	test_mixed_quotes();
	test_empty_quotes();
	test_unclosed_quote();
	
	printf("\n=== DONE ===\n\n");
	return (0);
}
