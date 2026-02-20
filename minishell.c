/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:17:32 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/20 12:04:12 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("TOKEN ");
		if (tokens->type == TOKEN_WORD)
			printf("WORD");
		else if (tokens->type == TOKEN_PIPE)
			printf("PIPE");
		else if (tokens->type == TOKEN_REDIR_IN)
			printf("REDIR_IN");
		else if (tokens->type == TOKEN_REDIR_OUT)
			printf("REDIR_OUT");
		printf(" : [%s]\n", tokens->value);
		tokens = tokens->next;
	}
}

int main(void)
{
	char *input;
	t_token *tokens;
	
	setup_signals();

	while (1)
	{
		input = read_input();
		if (!input)
			break ;
		add_history(input);
		printf("You typed: %s\n", input);
		tokens = tokenize(input);
		print_tokens(tokens);
		free(input);
	}
	exit_minish();
	return (0);
}
