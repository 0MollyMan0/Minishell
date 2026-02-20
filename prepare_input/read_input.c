/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:13:12 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/20 10:35:31 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*read_input()
{
	char	*input;
	int		i;

	i  = 0;
	while (i < 1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;	
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		i++;
	}
	return (input);
}
