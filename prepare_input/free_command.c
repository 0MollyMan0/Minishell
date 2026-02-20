/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:11:42 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/20 14:18:46 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_command(char *input, t_token *tokens)
{
	t_token	*next;

	free(input);

	while (tokens)
	{
		next = tokens->next;
		tokens->next = NULL;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}
