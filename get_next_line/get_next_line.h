/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 11:59:31 by mgroen        #+#    #+#                 */
/*   Updated: 2021/11/26 14:08:10 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

char		*get_next_line(int fd);
size_t		ft_strlen_gnl(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);
int			ft_stop_newline(const char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128

# endif
#endif
