#ifndef EXPANDER_H
# define EXPANDER_H

#include <stdbool.h>
# include "../lexer/lexer.h"
# include "../parser/parser.h"

typedef struct s_expander_tree
{
	struct s_expander_tree	*treetop;
	struct s_expander_tree	*subtree; //dispo dans chaque branch pour remonter au debut de la chaine
	struct s_expander_tree	*next_branch; 
	struct s_expander_tree	*next_subtree;

	enum
	{
		DQUOTE, //subtree types
		SQUOTE,//subtree types
		WORD,//subtree/branch types
		OPENING_TK, //branch types
		CLOSING_TK,//branch types
		DOLLAR//branch types, not picked out in squotes
	}	type;

	bool	is_subtree;
	bool	is_branch;
	char 	*value;	
	int		index; //for branches
}				t_expander_tree;

void				expander(struct s_parser *parser, struct s_minishell *minishell);
char				*expander_convert(char *value, struct s_minishell *minishell, t_expander_tree *tree);
char				*get_var(unsigned int *i, char *value);
char				*get_word(unsigned int *i, char *value);
char				*get_prev_word(unsigned int last_end, unsigned int *i, char *value);
t_expander_tree		*creating_expander_tree(char *value, struct s_minishell *minishell);
t_expander_tree		*create_parsing_subtree(int type, t_expander_tree *treetop, char *value);
void				create_parsing_branches(t_expander_tree *subtree, char *value_subtree, int type_subtree);
t_expander_tree		*init_branch(t_expander_tree *subtree, int type, int index, char *value);

#endif