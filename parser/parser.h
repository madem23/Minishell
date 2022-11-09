/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:43:41 by antoine           #+#    #+#             */
/*   Updated: 2022/11/09 18:00:19 by anloisea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <stdbool.h>
# include "../lexer/lexer.h"

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}				t_var;

typedef struct s_tree
{
	//outils
	t_token			*first_token; //debut liste chainee des tokens de chaque arbre/branche), la fin pour uen branche = nb of token;
	struct s_tree	*branch; //branche 1, section de l'arbre entre 2 pipes
	struct s_tree	*subtree; //branche 2, section de l'arbre a subdiviser encore (pipes), equivalent de list->next
	struct s_tree	*tree_top; //pointeur sur la cime de l'arbre, if tree_top = NULL, on est sur tree_top;
	size_t			end_index; //0 if on toptree or subtrees

	//stats global tree
	size_t	nb_pipes; //number of pipes in subtree (or tree if tree_top), = 0  IF IN BRANCH
	//size_t	nb_redir; //number of redir in subtree (or tree if tree_top)

	//stats branch: exec command
	char	*exec_name; //name of cmd
	char	**exec_args;// args and options of the said cmd
	char	*exec_path; //path to execute cmd
	int		exec_args_size; //a voir si utile
	
	//variable definition
	t_var	*var_def;
	
	//stats branch: redir
	int		nb_infiles;
	int		nb_outfiles;
	int		nb_outfiles_append;
	int		nb_diamonds;
	t_token	**infiles; //tab of all infiles
	t_token	**outfiles;
	t_token	**outfiles_append;
	t_token	**diamonds;
	//t_token	**cmds;
	bool	here_doc;
	//char	*content_here_doc; //content of heredoc, a voir si utile, tmp file cree

	//stats branch: pipes
	bool	piped_input;
	bool	piped_output;
	
}			t_tree;

typedef struct s_parser
{
	t_lexer		*lexer;
	t_token		*first_token;
	t_token		*current_token;
	t_token		*previous_token;
	char		**cmd_paths;
	t_tree		*treetop;
}				t_parser;

t_parser	*parser_init(t_lexer *lexer, char *envp[]);
t_tree		*parser_start(t_parser *parser);
t_tree		*parsing(t_parser *parser);
t_tree		*tree_init(t_parser *parser);
size_t		count_token_type(t_token *first_token, size_t type);
void		parsing_cmd(t_tree *branch);
int			count_unparsed_word(t_tree *branch);
void		parsing_redir(t_tree *branch);
t_token		**filling_redir_files_tab(t_tree *branch, int size, size_t type);
void		heredoc_parsing(t_token *begin, size_t end_index);
t_var		*variable_init(char	*name, char *value);

#endif