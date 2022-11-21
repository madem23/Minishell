/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:33:54 by anloisea          #+#    #+#             */
/*   Updated: 2022/11/21 15:53:26 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_a_variable_declaration(char *value)
{
	int	i;

	i = 0;
	while (ft_isaccepted_var_name(value[i]) && value[i] != '=')
		i++;
	if (i == 0)
		return (0);
	if (value[i] == '=' && (ft_isaccepted(value[++i]) || value[i] == 123 || value[i] == 125 || value[i] == 0))
		return (1);
	else
		return(0);	
}

t_token	*token_init(int type, char *value, t_lexer *lexer)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		error(1, "failed to allocate token\n");
	if (type == TK_WORD && is_a_variable_declaration(value))
		type = TK_EQUAL;
	token->type = type;
	token->value = value;
	if (type == TK_LOWER || type == TK_GREATER || type == TK_DLOWER
		|| type == TK_DGREATER || type == TK_LOWER_GREATER)
		token->redir_token = true;
	else
		token->redir_token = false;
	token->parsed = false;
	token->next_token = NULL;
	token->index = lexer->token_index;
	lexer->token_index++;
	return (token);
}