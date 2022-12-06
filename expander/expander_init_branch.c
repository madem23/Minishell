#include "expander.h"
#include "../parser/parser.h"
#include "../minishell.h"
#include "../libft/libft.h"

t_expander_tree	*init_branch(t_expander_tree *subtree, int type,
	int index, char *value)
{
	t_expander_tree	*branch;

	printf("Creation branch = %s, of type : %d\n", value, type);
	branch = malloc(sizeof(t_expander_tree));
	if (!branch)
		error(1, "Failed to allocate branch\n");
	branch->treetop = subtree->treetop;
	branch->index = index;
	branch->next_subtree = NULL;
	branch->subtree = subtree;
	branch->next_branch = NULL;
	branch->e_brch_type = type;
	branch->value = value;
	branch->is_subtree = false;
	branch->is_branch = true;
	return (branch);
}

int	init_var_brch(int type, int *index, int *i, t_expander_tree **current_node)
{
//	printf("----------ENTREE loop VAR i = %d\n", *i);
	(*current_node)->next_branch = init_branch(global.cur_exp_subtree, type,
			(*index)++, get_var(i, global.cur_exp_subtree->value));
	*current_node = (*current_node)->next_branch;
//	printf("SORTIE loop VAR, i = %d et last_end = %d\n", *i, (*i) - 1);
	return ((*i) - 1);
}

int	init_wd_brch(int type, int *index, int *i, t_expander_tree **current_node)
{
//	printf("----------ENTREE loop WORD/OPTK i = %d\n", *i);
	(*current_node)->next_branch = init_branch(global.cur_exp_subtree, type,
			(*index)++, get_word(i, global.cur_exp_subtree->value));
	*current_node = (*current_node)->next_branch;
//	printf("SORTIE loop WORD/OPTK, i = %d et last_end = %d\n", *i, (*i) - 1);
	return ((*i) - 1);
}

int	init_prvwd_brch(int last_end, int *index, int *i,
	t_expander_tree **current_node)
{
	if (global.cur_exp_subtree->e_brch_type == WORD
		&& (*i) == ft_strlen(global.cur_exp_subtree->value) - 1)
		(*i)++;
//	printf("----------ENTREE loop WORD i = %d et last_end = %d\n", *i, last_end);
	(*current_node)->next_branch = init_branch(global.cur_exp_subtree, WORD,
			(*index)++,
			get_prev_word(last_end, i, global.cur_exp_subtree->value));
	*current_node = (*current_node)->next_branch;
//	printf("SORTIE loop WORD, i = %d et last_end = %d\n", *i, (*i) - 1);
	return ((*i) - 1);
}

int	init_clostk_brch(int last_end, int *index, int *i,
	t_expander_tree **current_node)
{
//	printf("----ENTREE loop CLOSING TK i = %d et last_end = %d\n", *i, last_end);
	(*current_node)->next_branch = init_branch(global.cur_exp_subtree,
			CLOSING_TK, (*index)++,
			get_prev_word(last_end, i, global.cur_exp_subtree->value));
	*current_node = (*current_node)->next_branch;
	(*i)++;
//	printf("SORTIE loop CLOSING TOKEN, i = %d et last_end = %d\n", *i, (*i) - 2);
	return ((*i) - 2);
}
