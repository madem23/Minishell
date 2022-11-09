/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:26:27 by antoine           #+#    #+#             */
/*   Updated: 2022/10/31 18:46:45 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**/
#ifndef TREE_H
# define TREE_H

#include <stdbool.h>
# include "../lexer/token.h"

typedef struct s_tree
{
	//outils
	char			*cmd_line; //commande de la branche (subtree) ou de l'arbre (=commande globale) si tree_top
	t_token			*first_token; //liste chainee de tous les tokens
	struct s_tree	*branch; //branche 1, section de l'arbre entre 2 pipes
	struct s_tree	*subtree; //branche 2, section de l'arbre a subdiviser encore (pipes), equivalent de list->next
	struct s_tree	*tree_top; //pointeur sur la cime de l'arbre, if tree_top = tree, on est sur tree_top;

	//stats global tree
	size_t	nb_pipes; //number of pipes in subtree (or tree if tree_top), = 0  IF IN BRANCH
	//size_t	nb_redir; //number of redir in subtree (or tree if tree_top)

	//stats branch: exec command
	char	*exec_name; //name of cmd
	char	**exec_args;// args and options of the said cmd
	char	*exec_path; //path to execute cmd
	int		exec_args_size; //a voir si utile
	
	//stats branch: redir
	int		nb_infiles;
	int		nb_outfiles;
	char	**infiles; //tab of all infiles
	char	**outfiles;
	bool	here_doc;
	char	*content_here_doc; //content of heredoc;

	//stats branch: pipes
	bool	piped_input;
	bool	piped_output;
	
}t_tree;

/*
typedef struct s_tree
{
	enum
	{
		TREE_CMD_LINE,
		TREE_VARIABLE_DEF,
		TREE_EXEC_CALL,
		TREE_EXEC_ARGS,
		TREE_NULL
	}type;

	//TREE_CMD_LINE
	struct s_tree	**cmd_line; //tab of all sub-trees?
	int				cmd_line_size; //nb of token ???
	
	//TREE_VARIABLE_DEF
	char	*variable_name;
	char	*variable_value;
	
	//TREE_EXEC_CALL
	char			*exec_name;
	struct s_tree	**exec_args;
	char			*exec_path;
	int				exec_args_size;

	
}t_tree;*/


#endif*/