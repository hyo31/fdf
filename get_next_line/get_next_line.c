/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: milan <milan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/08 16:38:22 by milan         #+#    #+#                 */
/*   Updated: 2021/11/26 14:08:54 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <limits.h>

static char	*ft_split_line(char *save)
{
	char	*temp;
	int		i;

	i = 0;
	if ((unsigned int)ft_stop_newline(save) < ft_strlen_gnl(save))
	{
		temp = malloc(ft_strlen_gnl(save) - ft_stop_newline(save));
		if (!temp)
			return (NULL);
		while (((unsigned int)(i + ft_stop_newline(save)) < ft_strlen_gnl(save)))
		{
			temp[i] = save[ft_stop_newline(save) + i + 1];
			i++;
		}
		free(save);
		save = ft_strdup(temp);
		free(temp);
	}
	else
		save = NULL;
	return (save);
}

char	*ft_get_line(char *save, char *line)
{
	if ((unsigned int)ft_stop_newline(save) < ft_strlen_gnl(save))
		line = ft_substr(save, 0, (ft_stop_newline(save) + 1));
	else
		line = save;
	return (line);
}

static char	*ft_thisline(char *buff, char *save)
{
	char	*temp;

	if (save)
	{
		temp = ft_strjoin(save, buff);
		free(save);
		save = ft_strdup(temp);
		free(temp);
	}
	else
		save = ft_strdup(buff);
	if (save == NULL)
		free(save);
	return (save);
}

static char	*ft_get_save(char *save, int fd)
{
	char	buff[BUFFER_SIZE + 1];
	int		ret;

	ret = 1;
	while (ret > 0)
	{
		if (save)
			if (ft_stop_newline(save) != -1)
				break ;
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
			return (NULL);
		buff[ret] = '\0';
		save = ft_thisline(buff, save);
		if (save == NULL)
			return (NULL);
	}
	if (ret == 0 && ft_strlen_gnl(save) == 0)
	{
		free(save);
		return (NULL);
	}
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;

	line = NULL;
	if ((fd < 0 && fd <= OPEN_MAX) || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = ft_get_save(save[fd], fd);
	if (save[fd])
	{
		line = ft_get_line(save[fd], line);
		save[fd] = ft_split_line(save[fd]);
	}
	return (line);
}
