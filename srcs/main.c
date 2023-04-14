#include "rush.h"

static unsigned int	ft_delimiter_count(const char *input, const char c)
{
	unsigned int	count;

	count = 0;
	ft_strskip(&input, c);
	while (*input != '\0')
	{
		count++;
		while (*input != '\0' && *input != c)
			input++;
		ft_strskip(&input, c);
	}
	return (count);
}

int	*rush_parse(const char *input, unsigned int *size)
{
	int		*arr;
	size_t	i_arr;
	size_t	i;

	*size = 0;
	i_arr = 0;
	i = -1;
	arr = malloc(ft_delimiter_count(input, ' ') * sizeof(int));
	if (arr == NULL)
		return (NULL);
	while (input[++i] != '\0')
	{
		if (input[i] == ' ')
			continue ;
		else if (!(ft_isdigit(input[i]) || input[i] == '-' || input[i] == '+'))
		{
			free(arr);
			return (NULL);
		}
		arr[i_arr++] = ft_stoi(input, &i);
		i--;
	}
	*size = i_arr;
	return (arr);
}

int	arr_view_validvalue(const int *arr_view, const unsigned int size)
{
	const int		largest = size / 4;
	unsigned int	i;

	i = 0;
	while (i < size && 1 <= arr_view[i] && arr_view[i] <= largest)
		i++;
	return (i == size);
}

enum e_error
{
	OK,
	Empty,
	InvalidCharacter,
	Unbalanced,
	InvalidValue,
	NoViableSolution,
};

int	rush01(const char *input)
{
	enum e_error	status;
	int				*arr_view;
	unsigned int	size;

	arr_view = rush_parse(input, &size);
	if (size > 0)
	{
		for (unsigned int i = 0; i < size - 1; i++)
			printf("%d, ", arr_view[i]);
		printf("%d\n", arr_view[size -1]);
	}
	if (arr_view == NULL)
		status = InvalidCharacter;
	else if (size == 0)
		status = Empty;
	else if (size % 4)
		status = Unbalanced;
	else if (!arr_view_validvalue(arr_view, size))
		status = InvalidValue;
	else if (rush_solve(arr_view, size))
		status = NoViableSolution;
	else
		status = OK;
	free(arr_view);
	return (status);
}

typedef struct s_err
{
	enum e_error	err;
	const char		*msg;
}			t_errmessage;

int	rush_err(const enum e_error err)
{
	const t_errmessage	erros[] = {
	{.err = Empty, .msg = "Error: Empty Argument"},
	{.err = InvalidCharacter, .msg = "Error: Invalid Character"},
	{.err = Unbalanced, .msg = "Error: Unbalanced Amount of View"},
	{.err = InvalidValue, .msg = "Error: Invalid Value"},
	{.err = NoViableSolution, .msg = "Error: No Viable Solution"}
	};
	const unsigned int	message_size = sizeof(erros) / sizeof(erros[0]);
	unsigned int		i;

	if (err == OK)
		return (0);
	i = -1;
	while (++i < message_size)
	{
		if (err != erros[i].err)
			continue ;
		ft_dputendl(2, erros[i].msg);
		return (err);
	}
	ft_dputendl(2, "Error: Unknown error code");
	return (-1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_dputendl(2, "Error: Bad Arguments");
	else
		return (rush_err(rush01(argv[1])));
	return (1);
}
