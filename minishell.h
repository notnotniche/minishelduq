/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:40:58 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 21:10:32 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "unistd.h"
# include "stdlib.h"
# include <errno.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <readline/readline.h>		
# include <linux/limits.h>	
# include <readline/history.h>

extern int	g_status_exit_code;

# define WORD 0 // word
# define PIPE 1 // |
# define REDIR_IN 3 // <
# define REDIR_OUT 4 // >
# define HERE_DOC 5 // <<
# define APP_OUT 2 // >>
# define COMMAND_NOT_FOUND 127 // G_STATUS
# define NO_ACCESS 126// G_STATUS
# define SUCESS 0 // G_STATUS
# define ERROR 1 // NERD
# define VALID 1

// token == 0 command , token == 1 string token == 2 other  

/*
** Structure for managing quotes
*/

typedef struct s_quote
{
	char				quote;
	int					quote_bool;
}						t_quote;

/*
** Structure for managing memory allocation
*/

typedef struct s_malloc
{
	void				*adr;
	struct s_malloc		*next;
}						t_malloc;

/*
** List of strings structure
*/

typedef struct s_str_list
{
	char				*str_list;
	char				*str_list2;
	struct s_str_list	*next;
}						t_str_list;

/*
** Lexical list structure
*/

typedef struct s_lex_list
{
	char				*word;
	int					operator;
	int					must_split;
	struct s_lex_list	*next;
}						t_lex_list;

/*
** Export list structure
*/

typedef struct s_export_list
{
	char				*name;
	char				*value;
}						t_export_list;

/*
** Environmental list structure
*/

typedef struct s_env_list
{
	char				*name;
	char				*value;
	int					i;
	struct s_env_list	*next;
}						t_env_list;

/*
** Token list structure
*/

typedef struct s_token_list
{
	t_str_list			*in_file;
	int					token;
	t_str_list			*arguments;
	t_str_list			*delimeter;
	t_str_list			*out_file;
	int					i_fd;
	int					o_fd;
	struct s_token_list	*next;
}						t_token_list;

/*
** Execution initialization structure
*/

typedef struct s_exec_init
{
	int					nb_command;
	int					pipetmp;
	pid_t				realpid;
	int					mypipe[2];
	pid_t				*pid;
}						t_exec_init;

/*
** Main initialization structure
*/

typedef struct s_init
{
	char				*read_line;

	t_env_list			*lst_env;
	t_malloc			*lst_mal;
	t_lex_list			*lst_lex;
	t_token_list		*lst_token;
	char				*err_msg;
	int					check_exec;
	int					here_doc_tinker;
}						t_init;

//utils
int				ft_atoi(const char *str);
int				ft_strcmp(char *str, char *str2);
int				ft_strlen(char *str);
void			exec_parent_process(t_exec_init *exec_init);
void			set_value(t_env_list *tmp, char *new_value);
int				at_least_oneisspace(char *str);
char			**split_for_expand(t_init *init, char *str);
void			update_env_or_export(char *name, char *new_val, \
t_init *init, int flag);
void			expand_env(char **str, char **result, t_init *init);
void			add_back_env(t_init *init, char *name, char *new_value);
void			my_wait_pid(t_exec_init exec_init);
void			initialize_exec(t_init *init, int *i, t_exec_init *exec_init);
char			*ft_strtrim(char *str, int i, int y);
int				ft_strsame(char *str1, char *str2);
char			**ft_split(const char *s, char c);
void			exec_child_process(t_init *init, int i, t_exec_init exec_init);
int				is_only_isspace(char *str);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*heredoc_name(char *delimiteur, t_init *init);
void			closer_totally_spies(int fd, int oui, char *line);
void			closer_the_magasine(int fd, char *filename, \
int oui, t_init *init);
void			the_writer(int fd, char *str, int size_str);
char			**args_to_str(t_str_list *str, int size_str, t_init *init);
char			**ft_split_piscine(char *str, char *charset);
char			*ft_strjoin(char *str1, char *str2);
int				ft_isalpha(char c);
void			check_pipe(int fd);
int				ft_isalnum(char c);
void			heredoc_supp(t_token_list *token_lst);
int				is_quote(char c);
void			exec(t_init *init);
int				here_doc_exist(t_init *init);
char			*ft_strcpy(char *dest, const char *src);
void			close_fds(int fd_nbr, ...);
char			*ft_strcat(char *dest, const char *src);
int				handle_syntax_error(t_init *init);
int				redir_in_error(int count, t_init *init);
int				increment_redir_in_count(t_lex_list *lst_lex);
int				redir_out_error(int count, t_init *init);
char			*execute_from_path(char **splittos, t_str_list *c);
int				ft_isitenv(char c);
char			*expand_env_and_quote(char *str, t_init *init);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(char *str);
void			f_msg(t_init *init, char *str, char *err_msg);
int				tinker_path(t_init *init, t_exec_init *exec_init, char *str);
void			free_close_exit(t_init *init, \
t_exec_init *exec_init, int exittos);
char			*concatenate_strings(char *s1, char *s2);
char			*ft_itoa(int n);
char			*ft_join_str_in_init(t_init *init, char c, char *src);
void			ft_print_fd(char *str, int fd);
int				syntax_redir_in(t_init *init);
int				handle_heredoc_error(t_init *init);
char			*ft_strjoin_cr(char const *s1, char s2);
int				syntax_error(int count, t_init *init);
char			*cd_error_no_access(char *path, t_init *init);
int				syntax_redir_out(t_init *init);
int				increment_pipe_count(t_lex_list *lst_lex);
char			*get_home_path(char **envp, t_init *init);
int				is_word_after_operator(t_init *init);
int				is_disallowed_op(t_lex_list *lst_lex);
int				increment_redir_out_count(t_lex_list *lst_lex);
int				ft_size_token(t_token_list *list);
int				ft_size_env(t_env_list *head);
int				ft_size_str(t_str_list *head);
int				check_quote_ends(char *str);
t_str_list		*lstnew_str(char *content, t_init *init);
t_str_list		*lstlast_str(t_str_list *str_list);
void			lstaddback_str(t_str_list **str_list, t_str_list *new);
void			print_str(t_str_list *str_list, char *str);
t_env_list		*v_value(t_init *init);
char			*ft_strjoin_space(char *s1, char *s2, t_init *init);
int				ft_scmp(const char *s1, const char *s2);
void			print_all_str(t_init *init);
int				echo_n_option(char **line, int i);
void			delete_last_node_lex(t_lex_list **list);

//check_error
int				check_error(t_init *init);
void			free_s_init(t_init *init);

// utils_malloc_list

t_malloc		*lstnew_malloc(void *adr);
t_malloc		*lstlast_malloc(t_malloc *nodes);
void			lstaddback_malloc(t_init *init, t_malloc *new);
void			free_lst_malloc(t_malloc *lst);

//lexer
int				ft_is_operator(char *read_line);
int				ft_isspace(char c);
int				length_word(char *word);
void			write_word(char *word, char **split);
void			end_of_word(char **splittos);

void			operator_manager(char **read_line, \
t_lex_list **lex_list, t_init *init);
void			word_manager(char *read_line, \
t_lex_list **lex_list, t_init *init);
t_lex_list		*lexer_lexing(char *read_line, t_init *init);

//token
void			token_add_app_out(t_token_list **token, \
t_lex_list **lex_list, t_init *init);
void			token_add_word(t_token_list **token, \
t_lex_list **lex_list, t_init *init);
void			token_here_doc(t_token_list **token, \
t_lex_list **lex_list, t_init *init);
void			token_add_redir_in(t_token_list **token, \
t_lex_list **lex_list, t_init *init);
void			token_add_redir_out(t_token_list **token, \
t_lex_list **lex_list, t_init *init);

t_token_list	*lst_new_token(t_init *init);
t_token_list	*lstlast_token(t_token_list *lst);
void			lstaddback_token(t_token_list **lst, t_token_list *new);
void			print_all_token(t_token_list *lst);
t_token_list	*get_all_token(t_init *init);

//lexer_utils
t_lex_list		*lstnew_lex(char *word, int operator, t_init *init);
t_lex_list		*lstlast_lex(t_lex_list *list);
void			lstadd_back_lex(t_lex_list **list, t_lex_list *new);
void			print_lst_lex(t_lex_list *list);

//env_list_utils
void			print_lst_env(t_env_list *list);
int				valid_after_equal(char *str);
int				valid_export(char **arguments);
int				size_double_tab(char **arguments);
int				valid_first_letter(char *str, int i);
int				valid_only_str(char *str);
int				valid_until_equal(char *str);
void			lstadd_back_env(t_env_list **list, t_env_list *new);
t_env_list		*lstlast_env(t_env_list *list);
t_env_list		*lstnew_env(char *name, char *value);

//env_list
int				env_name_size(char *env);
void			end_env_name(char **str);
void			routine_start(int sig);
char			*env_name(char *env);
t_env_list		*init_env_list(char **env);
void			change_env_value(char *name, char *new_value, t_init *init);
char			*get_env_value(char *name, t_init *init);
t_env_list		*lstnew_env(char *name, char *value);
t_env_list		*lstlast_env(t_env_list *list);
void			lstadd_back_env(t_env_list **list, t_env_list *new);

//expand
int				is_env(char *str);
int				size_double_tab(char **arguments);
int				valid_first_letter(char *str, int i);
char			*env_name_expander(char *str);
void			print_export(t_env_list *list);
void			expander_expanding(t_init *init);

//builtins
void			the_real_exit(char **all_args, t_init *init);
char			*get_path_from_home(char *path, char **envp, t_init *init);
int				builtin_manage(t_init *init, char *str, char **all_args);
int				is_command_builtin(char *str);
void			sh_lvl_manager(t_init *init);
void			the_real_cd(char **path, char **envp, t_init *init);
void			the_real_env(char **arguments, t_init *init);
void			free_tab_tab(char **splittos);
void			the_real_unset(char **arguments, t_init *init);
void			text_to_print(char **line, t_init *init);
void			printLinkedList(t_env_list *head);
int				fork_builtin(char *str);
void			the_real_export(char **arguments, t_init *init);
void			free_env_list(t_env_list *head);
void			while_here_doc_exist(t_init *init);
void			ft_echo(char *cmd);
int				the_real_pwd(t_init *init);

//exec
void			heredoc_sigint(int sig);
void			handle_sigint(int sig);
void			ft_heredoc(char *delimiteur, t_init *init);
void			real_exec(t_init *init);
char			*is_pathabs(t_init *init, char *str, t_exec_init *exec_init);
int				check_outfile_fd(t_token_list *tok_list);
int				check_infile_fd(t_token_list *tok_list);
int				check_if_directory(char *path);
int				file_exec(char *path);
char			**env_to_str(t_init *init, t_env_list *env_list, int size_env);
void			printalltab(char **tarb, char *arg);
int				name_exist_in_env(char *str, t_init *init);
int				check_file_exist(char *path);
void			exec_all_pid(t_init *init, int i, t_exec_init exec_init);
char			*path_maker(t_init *init, t_str_list *cmd, \
char *path, t_exec_init *exec_init);
void			command_manager(t_init *init, t_exec_init *exec_init, int i);
void			close_fd(int fd_nbr, int *fd_array);
t_exec_init		init_exec_struct(t_init *init);

//exec file_manager
void			redir_out_manager(t_token_list *token_list);
void			app_out_manager(t_token_list *token_list);
void			redir_in_manager(t_token_list *token_list);
void			redir_here_doc(t_token_list *token_list);

#endif