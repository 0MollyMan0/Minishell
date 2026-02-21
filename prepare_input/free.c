/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:11:42 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/21 14:10:50 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		tokens->next = NULL;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

static void free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next_cmd;
	t_redir	*next_redir;

	while (cmds)
	{
		next_cmd = cmds->next;
		cmds->next = NULL;
		free_tab(cmds->argv);
		if (!cmds->redirs)
			printf("there is not redirs\n");
		while (cmds->redirs)
		{
			printf("there is a redirs\n");
			next_redir = cmds->redirs->next;
			cmds->redirs->next = NULL;
			free(cmds->redirs->filename);
			free(cmds->redirs);
			cmds->redirs = next_redir;
		}
		free(cmds);
		cmds = next_cmd;
	}
}

void	free_all(char *input, t_token *tokens, t_cmd *cmds)
{	
	if (input)
		free(input);
	if (tokens)
		free_tokens(tokens);
	if (cmds)
		free_cmds(cmds);
}
