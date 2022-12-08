/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:34:12 by antoine           #+#    #+#             */
/*   Updated: 2022/12/08 18:02:26 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include <stdbool.h>
# include "../lexer/lexer.h"
# include "../parser/parser.h"

/* Each subtree is connected to the treetop, the next subtree
and to its list of branches. Each branch is connected to the treetop,
its subtree and the next branch if any.
Types : D/SQUOTES for subtrees, WORD for both, OP/CLOSING TK
and DOLLAR for branches.
Index: for branches. */
typedef struct s_expander_tree
{
	struct s_expander_tree	*treetop;
	struct s_expander_tree	*subtree;
	struct s_expander_tree	*next_branch;
	struct s_expander_tree	*next_subtree;
	enum
	{
		DQUOTE,
		SQUOTE,
		WORD,
		OPENING_TK,
		CLOSING_TK,
		DOLLAR
	}	e_brch_type;
	bool					is_subtree;
	bool					is_branch;
	char					*value;
	int						index;
}				t_expander_tree;

void			expander(struct s_parser *parser, struct s_minishell
					*minishell);
char			*expander_convert(struct s_minishell *minishell,
					t_expander_tree *tree);
char			*get_var(int *i, char *value);
char			*get_word(int *i, char *value);
char			*get_prev_word(int last_end, int *i, char *value);
t_expander_tree	*creating_expander_tree(char *value);
void			create_exp_subtree(int *i, int *i_end,
					t_expander_tree **current_node, char quote);
t_expander_tree	*init_exp_subtree(int type, t_expander_tree *treetop,
					char *value);
void			create_exp_branches(t_expander_tree *subtree,
					char *value_subtree, int type_subtree);
t_expander_tree	*init_branch(t_expander_tree *subtree, int type, int index,
					char *value);
int				init_var_brch(int type, int *index, int *i,
					t_expander_tree **current_node);
int				init_wd_brch(int type, int *index, int *i,
					t_expander_tree **current_node);
int				init_prv_brch(int last_end, int *index, int *i,
					t_expander_tree **current_node);
int				init_clostk_brch(int last_end, int *index, int *i,
					t_expander_tree **current_node);
void			move_to_next(t_expander_tree **tree, bool branch);
#endif