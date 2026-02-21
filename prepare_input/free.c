/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:11:42 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/21 09:39:52 by anfouger         ###   ########.fr       */
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

void	free_cmds(t_cmd *cmds)
{
	(void)cmds;
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
