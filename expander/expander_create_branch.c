#include "expander.h"
#include "../parser/parser.h"
#include "../minishell.h"
#include "../libft/libft.h"

/* Creates each branch according to its type : VAR, WORD, CLOSING/OPENING TK.
Check and send the info to the init functions.
*/
void	create_exp_branches_bis(t_expander_tree *cur_nod, char *value,
	int i, int type)
{
	int	lst_end;

	global.u->len = ft_strlen(value) - 1;
	lst_end = -1;
	while (value[i])
	{
		while (value[i] && value[i] != '$'
			&& value[i] != '\'' && value[i] != '"')
			i++;
		if ((lst_end == -1 && (i > 0 || (i == 0 && ft_strlen(value) == 1)))
			|| (i - lst_end > 1 && lst_end >= 0))
			lst_end = init_prvwd_brch(lst_end, &global.u->index, &i, &cur_nod);
		if (value[i] == '$' && type != SQUOTE)
			lst_end = init_var_brch(DOLLAR, &global.u->index, &i, &cur_nod);
		else if (value[i] == '$' && type == SQUOTE)
			lst_end = init_wd_brch(WORD, &global.u->index, &i, &cur_nod);
		else if ((value[i] == '\'' && type == SQUOTE && i == 0)
			|| (value[i] == '"' && type == DQUOTE && i == 0))
			lst_end = init_wd_brch(OPENING_TK, &global.u->index, &i, &cur_nod);
		else if ((value[i] == '\'' && type == SQUOTE && i == global.u->len)
			|| (value[i] == '"' && type == DQUOTE && i == global.u->len))
			lst_end = init_clostk_brch(lst_end, &global.u->index, &i, &cur_nod);
		else if (value[i])
			i++;
	}
}

/* Creates the list of branches for the received subtree.
Value = subtree's string;
Type = subtree's type;
*/
void	create_exp_branches(t_expander_tree *subtree, char *value,
	int type)
{
	t_expander_tree	*current_node;

	global.u->index = 0;
	current_node = subtree;
	create_exp_branches_bis(current_node, value, 0, type);
}
