#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
	STRING,
	PIPE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}						TokenType;

typedef struct TokenNode
{
	char				*token;
	TokenType			type;
	struct TokenNode	*next;
}						TokenNode;

TokenNode	*create_node(const char *token, TokenType type)
{
	TokenNode	*new_node;

	new_node = (TokenNode *)malloc(sizeof(TokenNode));
	if (!new_node)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	new_node->token = strdup(token);
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	append_node(TokenNode **head, const char *token, TokenType type)
{
	TokenNode	*new_node;
	TokenNode	*current;

	if (strlen(token) == 0)
		return ; // Boş tokenları eklemiyoruz
	new_node = create_node(token, type);
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

char	**list_to_array(TokenNode *head, int *count)
{
	int			size;
	TokenNode	*current;
	char		**tokens;
	TokenNode	*temp;

	size = 0;
	current = head;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	tokens = (char **)malloc((size + 1) * sizeof(char *));
	if (!tokens)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	current = head;
	for (int i = 0; i < size; i++)
	{
		tokens[i] = strdup(current->token);
		temp = current;
		current = current->next;
		free(temp->token);
		free(temp);
	}
	tokens[size] = NULL;
	*count = size;
	return (tokens);
}

void	print_tokens(TokenNode *head)
{
	TokenNode	*current;

	current = head;
	while (current != NULL)
	{
		const char *type_str = current->type == STRING ? "STRING" : current->type == PIPE ? "PIPE"
			: current->type == SINGLE_QUOTE                                               ? "SINGLE_QUOTE"
																							: "DOUBLE_QUOTE";
		printf("Token: %s, Type: %s\n", current->token, type_str);
		current = current->next;
	}
}

char	**lexer(const char *input, int *count)
{
	TokenNode	*head;
	int			length;
	char		*token;
	int			j;
	int			in_single_quotes;
	int			in_double_quotes;
	char		**tokens;

	head = NULL;
	length = strlen(input);
	token = (char *)malloc((length + 1) * sizeof(char));
	if (!token)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	j = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	for (int k = 0; k < length; k++)
	{
		if (input[k] == '|' && !in_single_quotes && !in_double_quotes)
		{
			if (j > 0)
			{
				token[j] = '\0';
				append_node(&head, token, PIPE);
				j = 0;
			}
			append_node(&head, "|", PIPE);
		}
		else if (input[k] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			token[j++] = input[k];
		}
		else if (input[k] == '"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			token[j++] = input[k];
		}
		else if ((input[k] != ' ' || in_single_quotes || in_double_quotes))
		{
			token[j++] = input[k];
		}
		else
		{
			if (j > 0)
			{
				token[j] = '\0';
				append_node(&head, token, STRING);
				j = 0;
			}
		}
	}
	if (j > 0)
	{
		token[j] = '\0';
		append_node(&head, token, STRING);
	}
	free(token);
	print_tokens(head);
	tokens = list_to_array(head, count);
	return (tokens);
}

int	main(void)
{
	const char	*input;
	int			count;
	char		**tokens;

	input = "echo   d \"mer\" d ";
	tokens = lexer(input, &count);
	for (int i = 0; i < count; i++)
	{
		printf("Token[%d]: %s\n", i, tokens[i]);
		free(tokens[i]);
	}
	free(tokens);
	return (0);
}
