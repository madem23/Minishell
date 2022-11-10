/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:24:44 by antoine           #+#    #+#             */
/*   Updated: 2022/11/09 17:40:19 by anloisea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../minishell.h"

size_t	count_token_type(t_token *first_token, size_t type)
{
	size_t	nb;

	nb = 0;
	while (first_token)
	{
		if (first_token->type == type)
			nb++;
		first_token = first_token->next_token;
	}
	return (nb);
}

//POUR LE MOMENT, SEULEMENT OK POUR TOPTREE
t_tree	*tree_init(t_parser *parser)
{
	t_tree	*tree;
	
	tree = malloc(sizeof(t_tree));
	if (!tree)
		error(1, "Failed to allocate tree\n");
	tree->first_token = parser->first_token;
	tree->branch = NULL; //fct get branch a faire
	tree->subtree = NULL; //fct get subtree a faire
	tree->tree_top = NULL;
	tree->nb_pipes = count_token_type(parser->first_token, TK_PIPE);
	tree->end_index = 0;
	
	//branch exec
	tree->exec_name = NULL; //name of cmd
	tree->exec_args = NULL;// args and options of the said cmd
	tree->exec_path = NULL; //path to execute cmd
	tree->exec_args_size = 0; //a voir si utile
	tree->envp = parser->envp;

	tree->var_def = NULL;
	
	//stats branch: redir
	tree->nb_infiles = count_token_type(parser->first_token, TK_LOWER);
	tree->nb_outfiles = count_token_type(parser->first_token, TK_GREATER);
	tree->infiles = NULL; //fonction commune pour recup tous les token
	tree->outfiles = NULL;
	if (count_token_type(parser->first_token, TK_DLOWER) > 0)
		tree->here_doc = true;
	else
		tree->here_doc = false;
	//char	*content_here_doc; //content of heredoc; A FAIRE !!

	//stats branch: pipes
	tree->piped_input = false;
	if (tree->nb_pipes > 0)
		tree->piped_output = true;
	else
		tree->piped_output = false;
	return (tree);
}