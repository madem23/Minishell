/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:43:41 by antoine           #+#    #+#             */
/*   Updated: 2022/11/26 14:54:21 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include "../lexer/lexer.h"

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
	bool			env;
	int				exit_state;
}					t_var;

//structure for parsing tree, each node starts at first_token
//and ends at EOC or end_index for branches.
//NB: number of pipes = 0 IF IN BRANCH
typedef struct s_tree
{
	struct s_minishell	*minishell;
	t_token				*first_token;
	struct s_tree		*branch;
	struct s_tree		*subtree;
	struct s_tree		*treetop;
	int					end_index;
	char				**paths;

	unsigned int		nb_pipes;

	char				*exec_name;
	char				**exec_args;
	char				*exec_path;
	char				**envp;

	int					nb_infiles;
	int					nb_outfiles;
	int					nb_outfiles_append;
	t_token				**infiles;
	t_token				**outfiles;
	t_token				**outfiles_append;
	int					here_doc;
	bool				piped_input;
	bool				piped_output;
}						t_tree;

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

t_parser		*parser_init(t_lexer *lexer, struct s_minishell *minishell);
t_tree			*parser_start(t_parser *parser, struct s_minishell *minishell);
t_parser		*lexing_start(t_parser *parser);
t_tree			*parsing(t_parser *parser, struct s_minishell *minishell);
t_tree			*tree_init(t_parser *parser);
t_tree			*create_branch(t_token *begin, t_token *end, t_tree *treetop,
					struct s_minishell *minishell);
t_tree			*create_subtree(t_token *begin, t_tree *treetop);
unsigned int	count_tk(t_token *first_token, int end_index,
					unsigned int type);
void			parsing_cmd(t_tree *branch);
int				count_unparsed_word(t_tree *branch);
void			parsing_redir(t_tree *branch);
t_token			**filling_redir_files_tab(t_tree *branch, int size,
					unsigned int type);
int				heredoc_parsing(t_token *begin, int end_index, unsigned int nb);
char			*remove_closed_quotes(char **tk_value, int *save,
					int *i, char *s);
char			*check_and_manage_closed_quotes(char **tk_value, int *save,
					int *i, char *s);
int				parsing_var_def(t_tree *branch);
void			var_add_back(t_var **var, t_var *new);
t_var			*var_init(char	*name, char *value, bool env);
void			lexing_dollar_token(t_parser *parser,
					struct s_minishell *minishell);
char			*managing_non_alpha(char *value, int i, int j,
					struct s_minishell *minishell);
char			*managing_curly_brakets(char *value, int i,
					struct s_minishell *minishell);
char			*search_var_list_and_replace(char *value,
					struct s_minishell *minishell);

#endif