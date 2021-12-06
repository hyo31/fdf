#include "fdf.h"

int	close_win(int key, t_vars *vars)
{
	if (key == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	zoom2(int key, t_vars *vars)
{
	if (key == 125)
	{
		mlx_clear_window(vars->mlx, vars->win);
		vars->start[1] += 10;
		read_map(vars->fname, *vars, vars->len);
	}
	else if (key == 124)
	{
		mlx_clear_window(vars->mlx, vars->win);
		vars->start[0] += 10;
		read_map(vars->fname, *vars, vars->len);
	}
	else if (key == 121 && vars->degrees + 1 <= 45)
	{
		mlx_clear_window(vars->mlx, vars->win);
		vars->degrees += 1;
		read_map(vars->fname, *vars, vars->len);
	}
	else if (key == 116 && vars->degrees - 1 >= 1)
	{
		mlx_clear_window(vars->mlx, vars->win);
		vars->degrees -= 1;
		read_map(vars->fname, *vars, vars->len);
	}
	return (0);
}

int	zoom(int key, t_vars *vars)
{
	if (key == 69 && vars->start[2] + 2 >= 2)
	{
		mlx_clear_window(vars->mlx, vars->win);
		vars->start[2] = vars->start[2] + 2 ;
		read_map(vars->fname, *vars, vars->len);
	}
	else if (key == 78 && vars->start[2] - 2 >= 2)
	{
		mlx_clear_window(vars->mlx, vars->win);
		vars->start[2] = vars->start[2] - 2;
		read_map(vars->fname, *vars, vars->len);
	}
	else if (key == 123 || key == 126)
	{
		mlx_clear_window(vars->mlx, vars->win);
		if (key == 123)
			vars->start[0] -= 10;
		else if (key == 126)
			vars->start[1] -= 10;
		read_map(vars->fname, *vars, vars->len);
	}
	else if (key == 125 || key == 124 || (key == 121 && vars->diff + 0.1 <= 1)
		|| (key == 116 && vars->diff - 0.1 >= -1))
		return (zoom2(key, vars));
	return (0);
}

void	assign_args(char *fname, int len[2], t_vars *vars)
{
	vars->fname = fname;
	vars->len[0] = len[0];
	vars->len[1] = len[1];
	vars->start[0] = 600;
	vars->start[1] = 0;
	vars->start[2] = 200 / ((len[0] + len[1]) / 2);
	vars->degrees = 30;
	vars->diff = tan(vars->degrees * (3.14159265 / 180));
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		len[2];

	if (argc != 2)
		return (1);
	get_file_row(argv[1], len);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 2500, 1250, "fdf");
	assign_args(argv[1], len, &vars);
	read_map(argv[1], vars, len);
	mlx_key_hook(vars.win, zoom, &vars);
	mlx_hook(vars.win, 2, 1L << 0, close_win, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
