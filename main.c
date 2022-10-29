/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:32:55 by anloisea          #+#    #+#             */
/*   Updated: 2022/10/29 11:25:27 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)envp;
	(void)argv;
	// while (1)
	// {
		t_lexer	*lexer = lexer_init(argv[1]);
		t_token	*token = lexer_get_next_token(lexer);
		while (token->type != TK_EOC)
		{
			printf("TOKEN(%d, %s)\n", token->type, token->value);
			free(token);
			token = lexer_get_next_token(lexer);
		}
	
	free(lexer);
	free(token);
	return (0);
}