/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:32:55 by anloisea          #+#    #+#             */
/*   Updated: 2022/10/28 17:11:26 by anloisea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)envp;
	(void)argv;
	// while (1)
	// {
		t_lexer	*lexer = lexer_init(argv[1]);
		t_token	*token = lexer_get_token(lexer);
		while (token)
		{
			printf("TOKEN(%d, %s)\n", token->type, token->value);
			free(token);
			token = lexer_get_token(lexer);
		}
	
	free(lexer);
	free(token);
	return (0);
}