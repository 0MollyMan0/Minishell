/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:13:12 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/20 15:29:39 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	verif_quotes(const char *str)
{
	int	count_one;
	int	count_two;
	int	i;

	i = 0;
	count_one = 0;
	count_two = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			count_one++;
		else if (str[i] == '\"')
			count_two++;
		i++;
	}
	if (count_one % 2 != 0 || count_two % 2 != 0)
	{
		printf("Error: Invalid use of quotes\n");
		return (0);
	}
	return (1);
}

static int	is_empty(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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
		if (is_empty(input) || !verif_quotes(input))
		{
			free(input);
			continue ;
		}
		i++;
	}
	return (input);
}
