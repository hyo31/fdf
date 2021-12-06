#include "fdf.h"

void	ft_error(char *msg)
{
	perror(msg);
	exit(1);
}

void	get_file_row(char *fname, int i[2])
{
	int		fd;
	char	*buf;
	char	**buff;

	i[0] = 0;
	i[1] = 0;
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		exit(1);
	buf = get_next_line(fd);
	buff = ft_split(buf, ' ');
	while (buff[i[1]])
	{	
		free(buff[i[1]]);
		i[1]++;
	}
	i[1]--;
	free (buff);
	while (buf)
	{
		free (buf);
		buf = get_next_line(fd);
		i[0]++;
	}
	close(fd);
}

int	read_buff_to_int(struct s_map *row, int x, int i, char **big_buff)
{
	int	j;

	j = 0;
	if (x == 0)
		row[i].val = 0;
	row[i].colour = 0xFFFFFF;
	row[i].old_val = row[i].val;
	while (big_buff[i][j] != ',' && big_buff[i][j] != ' ' && big_buff[i][j])
		j++;
	big_buff[i][j] = '\0';
	row[i].val = ft_atoi(big_buff[i]);
	row[i].len = i + 1;
	free(big_buff[i]);
	i++;
	return (i);
}

int	read_line(struct s_map	*row, int fd, int x)
{
	char	*buff;
	char	**big_buff;
	int		i;

	i = 0;
	buff = get_next_line(fd);
	if (!buff)
		return (1);
	while (buff[i] != '\n')
		i++;
	buff[i] = '\0';
	i = 0;
	big_buff = ft_split(buff, ' ');
	while (big_buff[i])
		i = read_buff_to_int(row, x, i, big_buff);
	row[i].old_val = row[i].val;
	row[i].colour = 0xFFFFFF;
	row[i].val = 0;
	row[i].len = 0;
	free(buff);
	free(big_buff);
	return (0);
}

void	read_map(char *fname, t_vars vars, int len[2])
{
	int				i;
	int				fd;
	struct s_map	*row;

	i = 0;
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		exit(1);
	row = (struct s_map *)malloc(sizeof(struct s_map) * (len[1] + 2));
	if (!row)
		ft_error("malloc error\n");
	vars.diff = tan(vars.degrees * (3.14159265 / 180));
	vars.scale[0] = vars.start[2];
	if (vars.scale[0] < 2)
		vars.scale[0] = 2;
	vars.scale[1] = vars.scale[0] * vars.diff;
	vars.scale[2] = (-2 * vars.scale[0]) * (1 - vars.diff);
	while (!read_line(row, fd, i))
	{
		make_rectangle(row, i, vars, len);
		i++;
	}
	free (row);
	close (fd);
}
