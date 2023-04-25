/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:49:25 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 12:43:14 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../Includes/lib.h"
# include "../../Includes/struct.h"

typedef struct s_quote_flags
{
	t_env	**ourenv;
	int		simple_quote;
	int		double_quote;
}	t_quote_flags;

typedef struct s_split
{
	int		simple_quote;
	int		double_quote;
	size_t	i;
	size_t	j;
	size_t	t;
	char	*tab;
}	t_split;

typedef struct s_redi
{
	int		i;
	int		j;
	int		in_simple;
	int		in_double;
	int		order;
}	t_redi;

typedef struct s_r_out
{
	int		i;
	int		j;
	int		in_simple;
	int		in_double;
}	t_r_out;

typedef struct s_pipe
{
	int		i;
	int		len;
	int		in_quote;
	int		in_apostrophe;
}	t_pipe;

void	free_char_array(char **array);
void	*free_ptr(void *ptr);
void	init_var_redi(t_redi *redi);
void	handle_quotes_redi(char current_char, t_redi *redi);
int		syntax_error(char c);
// Fonctions for the management of linked list

t_stack	*create_cell(char *cmd_sep);
void	add_cell_tstack(t_stack **list, char *cmd_sep);
void	add_cell_redirections(t_file **list, char *str, int i, int order);
void	print_list(t_stack **lst);
void	freelist(t_stack *stack);
void	freelist_env(t_env *stack);
void	freelist_redi(t_file *stack);
void	free_char_array(char **array);
void	free_stack(t_stack *lst);

//Fonction for the parsing of the input
t_stack	*filter_pipe(t_stack *lst, char *line); // gere les '|'
void	parse_commande(t_stack *lst, t_env	*our_env);
char	*ft_for_output_redirection(char *str, t_file **in, t_env **env);
char	*ft_for_input_redirection(char *str, t_file **in, t_env **our_env);
char	*parse_quotes(char *input);
char	*ft_strjoin_char(char *s1, char s2);
char	*to_down(char *str);
int		get_next_space(char *str);
int		is_letter(char c);
int		is_digit(char c);
int		get_next_space_var(char *str, int *simple_quote, int *double_quote);
int		is_legit(char c);
//remplace var
char	*replace_env_variables(char *str, t_env **ourenv);
char	*verif_sub_in_list(char *str, t_env **ourenv);
char	*handle_dollar_question_mark(char *new_str, int *i);
void	init_variables(t_quote_flags *quotes, t_env **ourenv);
char	*handle_dollar_variable(char *str, int *i, t_quote_flags *q, char *new);
char	*ft_strncpy_until_char(char *src, char delimiter);
char	*handle_tild(char *str, int *i, t_quote_flags *q, char *new);

//verif string
int		verif_string(char *str);

// Other fonction
int		env(char **our_env, char **cmds);

//the split
char	**ft_split_for_quotes(char const *s);
int		ft_count(char const *s, int t);
size_t	ft_count_words(const char *str);
size_t	ft_len_split(const char *s);
void	*ft_freearray(char **s, int i);
void	int_check_in_quotes(char c, int *simple_quote, int *double_quote);
void	fill_tab(char const *s, t_split *vars, char **tab);

//env fonction
void	add_cell_env(t_env **list_env, char *name, char *value);
t_env	*parse_environnement(char **envp, t_env *our_env);
t_env	*increment_shlvl(t_env *our_env);
int		is_only_space_start(char *str);

#endif