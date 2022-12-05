/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:11:57 by mdemma            #+#    #+#             */
/*   Updated: 2022/12/05 17:11:58 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer.h"

//Moves forward in cmd line if char is a space
void	ignore_spaces(t_lexer *lexer)
{
	while (ft_isspace(lexer->c))
		lexer_read_next_char(lexer);
}

//Returns number of char in s before end_index
int	count_char(char *s, int end_index)
{
	int	i;

	i = 0;
	while (s[i] && i <= end_index)
		i++;
	return (i);
}
