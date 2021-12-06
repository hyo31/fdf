#ifndef FDF_H
# define FDF_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

struct			s_line
{
	int		x;
	float	xstart;
	int		xend;
	int		y;
	float	ystart;
	int		yend;
	float	diff;
};

struct			s_map
{
	int	val;
	int	len;
	int	old_val;
	int	colour;
};

typedef struct s_vars {
	void	*mlx;
	void	*win;
	char	*fname;
	int		len[2];
	int		start[3];
	float	diff;
	float	scale[3];
	int		degrees;
}				t_vars;

void	read_map(char *fname, t_vars vars, int len[2]);
void	make_rectangle(struct s_map	*row, int i, t_vars vars, int len[2]);
void	get_file_row(char *fname, int i[2]);
void	ft_error(char *msg);

#endif