/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:43:41 by antoine           #+#    #+#             */
/*   Updated: 2022/11/14 13:33:56 by antoine          ###   ########.fr       */
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
	struct s_minishell	*minishell;
	t_token			*first_token; //debut liste chainee des tokens de chaque arbre/branche), la fin pour uen branche = nb of token;
	struct s_tree	*branch; //branche 1, section de l'arbre entre 2 pipes
	struct s_tree	*subtree; //branche 2, section de l'arbre a subdiviser encore (pipes), equivalent de list->next
	struct s_tree	*treetop; //pointeur sur la cime de l'arbre, if tree_top = NULL, on est sur tree_top;
	unsigned int	end_index; //0 if on toptree or subtrees
	char			**paths;

	//stats global tree
	unsigned int	nb_pipes; //number of pipes in subtree (or tree if tree_top), = 0  IF IN BRANCH

	//stats branch: exec command
	char	*exec_name; //name of cmd
	char	**exec_args;// args and options of the said cmd
	char	*exec_path; //path to execute cmd
	char	**envp;
		
	//stats branch: redir
	int		nb_infiles;
	int		nb_outfiles;
	int		nb_outfiles_append;
	int		nb_diamonds;
	t_token	**infiles; //tab of all infiles
	t_token	**outfiles;
	t_token	**outfiles_append;
	t_token	**diamonds;
	bool	here_doc;

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
	char		**envp;
}				t_parser;

t_parser		*parser_init(t_lexer *lexer, char *envp[]);
t_tree			*parser_start(t_parser *parser, struct s_minishell *minishell);
t_tree			*parsing(t_parser *parser, struct s_minishell *minishell);
t_tree			*tree_init(t_parser *parser);
unsigned int	count_token_type(t_token *first_token, unsigned int type);
void			parsing_cmd(t_tree *branch);
int				count_unparsed_word(t_tree *branch);
void			parsing_redir(t_tree *branch);
t_token			**filling_redir_files_tab(t_tree *branch, int size, unsigned int type);
void			heredoc_parsing(t_token *begin, unsigned int end_index);
void			lexing_word_incl_dquotes(t_parser *parser);
void			interpreting_closed_quotes(t_token *token);
char			*remove_closed_quotes(char *token_value, int *save, int *i, char *s);
char			*check_and_manage_closed_quotes(char *token_value, int *save, int *i, char *s);
t_var			*variable_init(char	*name, char *value);
void			var_add_back(t_var **var, t_var *new);
void			parsing_var_def(t_tree *branch);

#endif