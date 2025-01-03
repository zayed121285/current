#include "get_next_line.h"

int	get_check(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

int	get_len(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (i);
}

char	*get_calloc(int size)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(size);
	if (!str)
		return (NULL);
	while (size > i)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	*get_join(char *ret, char *keep)
{
	int		rlen;
	int		klen;
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	rlen = get_len(ret);
	klen = get_len(keep);
	new = get_calloc(rlen + klen);
	new[rlen + klen] = '\0';
	if (!new)
		return (NULL);
	while (rlen > i)
	{
		new[i] = ret[i];
		i++;
	}
	while (klen > j)
	{
		new[i] = keep[j];
		j++;
	}
	return (new);
}

int	get_next_calloc(char **ret, char **keep)
{
	if (!*keep)
	{
		*keep = get_calloc(BUFFER_SIZE + 1);
		if (!keep)
			return (1);
		*ret = get_calloc(BUFFER_SIZE + 1);
		if (!ret)
			return (1);
		return (0);
	}
	else
	{
		*ret = get_calloc(BUFFER_SIZE + 1);
		if (!ret)
			return (1);
		return (0);
	}
}

char	*get_line(char	**ret, char	**keep, int fd)
{
	int		flag;
	char	*freed;

	flag = 1;
	flag = get_check(*ret);
	while (flag == 1)
	{
		if ((read(fd, *keep, BUFFER_SIZE)) <= 0)
			return (*ret);
		freed = *ret;
		*ret = get_join(*ret, *keep);
		flag = get_check(*ret);
		free(freed);
	}
	return (*ret);
}

char	*get_next_line(int fd)
{
	char		*ret;
	static char	*keep;
	int			flag;

	flag = 1;
	flag = get_next_calloc(&ret, &keep);
	ret = get_line(&ret, &keep, fd);
	// ret = get_join(ret, keep);
	return (ret);
}
