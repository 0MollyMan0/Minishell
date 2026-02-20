/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:17:32 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/20 10:05:08 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(void)
{
	char *input;
	setup_signals();
	while (1)
	{
		input = read_input();
		
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		printf("You typed: %s\n", input);
		free(input);
	}
	return (0);
}
