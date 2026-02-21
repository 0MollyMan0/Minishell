/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:17:32 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/21 12:34:40 by anfouger         ###   ########.fr       */
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
		else if (tokens->type == TOKEN_APPEND)
			printf("APPEND");
		else if (tokens->type == TOKEN_HEREDOC)
			printf("HEREDOC");
		printf(" : [%s]\n", tokens->value);
		tokens = tokens->next;
	}
}

void	print_redir(t_redir *redir)
{
	printf("|	redir\n");
	if (redir->type == TOKEN_REDIR_IN)
		printf("	|	type = REDIR_IN\n");
	else if (redir->type == TOKEN_REDIR_OUT)
		printf("	|	type = REDIR_OUT\n");
	else if (redir->type == TOKEN_APPEND)
		printf("	|	type = APPEND\n");
	else if (redir->type == TOKEN_HEREDOC)
		printf("	|	type = HEREDOC\n");
	printf("	|	filename = [%s]\n", redir->filename);
}

void	print_cmds(t_cmd *cmds)
{
	while (cmds)
	{
		int i = 0;
		printf("command:\n");
		printf("|	argv : [");
		while (cmds->argv[i])
		{
			printf("%s, ", cmds->argv[i]);
			i++;
		}
		printf("NULL]\n");
		while  (cmds->redirs)
		{
			print_redir(cmds->redirs);
			cmds->redirs = cmds->redirs->next;
		}
		cmds = cmds->next;
	}
}

int main(void)
{
	char *input;
	t_token *tokens;
	t_cmd	*cmds;
	
	setup_signals();

	while (1)
	{
		input = read_input();
		if (!input)
			break ;
		add_history(input);
		tokens = tokenize(input);
		print_tokens(tokens);
		cmds = parser(tokens);
		print_cmds(cmds);
		free_all(input, tokens, cmds);
	}
	exit_minish();
	return (0);
}
