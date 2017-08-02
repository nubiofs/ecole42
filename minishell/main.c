#include "minishell.h"

typedef struct			s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

t_env		**ft_env()
{
	static t_env	*l = NULL;

	return (&l);		
}

void		ft_setenv(char *name, char *value, int overwrite)
{
	t_env	*env;
	t_env	**root;

	if(!(*(root = ft_env())))
	{
		env = ft_memalloc(sizeof(t_env));
		env->key = ft_strdup(name);
		env->value = ft_strdup(value);
		*root = env;
		return ;
	}		
	env = *root;
	while (env)
	{
		if (ft_strcmp(env->key, name) == 0 && 0 == overwrite)
			return ;
		if (NULL == env->next)
		{
			env->next = ft_memalloc(sizeof(t_env));
			env->next->key = ft_strdup(name);
			env->next->value = ft_strdup(value);
			return;
		}
		env = env->next;
	}
}

void		ft_displayenv()
{
	t_env *env;

	env = *(ft_env());
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

char		*ft_getenv(char *name)
{
	t_env *env;

	env = *(ft_env());
	while (env)
	{
		if (ft_strcmp(name, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char		*ft_strdup_len(char *str, size_t len)
{
	size_t	i;
	char	*newstr;

	newstr = ft_strnew(len);
	ft_memcpy(newstr, str, len);
	return (newstr);
}

void		ft_putenv(char *str)
{
	char	*stop;
	char	*key;
	char	*value;

	if(!(stop = ft_strchr(str, '=')))
		return ;
	key = ft_strdup_len(str, (stop - str));
	value = ft_strdup(stop + 1);
	ft_setenv(key, value, TRUE);		
	ft_strdel(&key);
	ft_strdel(&value);
}

void		ft_loadenv(char **env)
{
	int i;

	i = 0;
	while(env[i])
	{
		ft_putenv(env[i]);
		i++;
	}
}

void		execute(char *cammand)
{
	// Trouver la command dans PATH
	// echo ; cd ; setenv ; unsetenv ; env ; exit

}

int		main(int argc, char **argv, char **env)
{
	char *command;

	command = NULL;
	ft_loadenv(env);
	ft_printf(ft_getenv("PATH"));
	while (42)
	{
		ft_printf("$>");
		ft_gnl(STDIN_FILENO, &command);
		execute(command);
		ft_strdel(&command);
	}
	exit(0);
}