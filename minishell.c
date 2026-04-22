/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:17:32 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/22 10:41:44 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_tokens(t_token *tokens)
{
	if (tokens)
		printf("\n| ---- TOKENIZE ---- |\n");
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
	printf("	redir:");
	if (redir->type == TOKEN_REDIR_IN)
		printf("  type = REDIR_IN\n");
	else if (redir->type == TOKEN_REDIR_OUT)
		printf("  type = REDIR_OUT\n");
	else if (redir->type == TOKEN_APPEND)
		printf("  type = APPEND\n");
	else if (redir->type == TOKEN_HEREDOC)
		printf("  type = HEREDOC\n");
	printf("		filename = [%s]\n", redir->filename);
}

void	print_cmds(t_cmd *cmds)
{
	t_cmd	*cmds_tmp;
	t_redir	*redir_tmp;

	if (cmds)
		printf("\n| ---- PARSING ---- |\n");
	cmds_tmp = cmds;
	while (cmds_tmp)
	{
		int i = 0;

		printf("command:\n");
		printf("	argv :  [");
		while (cmds_tmp->argv && cmds_tmp->argv[i])
		{
			printf("%s, ", cmds_tmp->argv[i]);
			i++;
		}
		printf("NULL]\n");

		redir_tmp = cmds_tmp->redirs;
		while (redir_tmp)
		{
			print_redir(redir_tmp);
			redir_tmp = redir_tmp->next;
		}

		cmds_tmp = cmds_tmp->next;
	}
}


static t_minish	init_minish(int ac, char **av, char **envp)
{
	t_minish	minish;

	(void)ac;
	(void)av;
	minish.exit_status = 0;
	minish.envp = dup_tab(envp);
	minish.input = NULL;
	minish.tokens = NULL;
	minish.cmds = NULL;
	return (minish);
}

int	main(int ac, char **av, char **envp)
{
	t_minish	minish;

	minish = init_minish(ac, av, envp);
	while (1)
	{
		setup_signals();
		minish.input = read_input();
		if (!minish.input)
			break ;
		add_history(minish.input);
		minish.tokens = tokenize(minish.input);
		print_tokens(minish.tokens);
		if (g_signal != 0)
			minish.exit_status = g_signal;
		minish.cmds = parser(&minish, minish.tokens);
		print_cmds(minish.cmds);
		minish.cmds = expansion(minish, minish.cmds);
		signal(SIGINT, SIG_IGN);
		if (minish.cmds)
			execute(&minish);
		free_all(&minish);
	}
	free_tab(minish.envp);
	exit_minish();
	return (0);
}
