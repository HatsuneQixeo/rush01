#include "utils.h"

int	rush_solve(const int *arr_view, const unsigned int size);

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

static int	*rush_parse(const char *input, unsigned int *const size)
{
	int		*arr;
	size_t	i;

	*size = 0;
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
		arr[(*size)++] = ft_stoi(input, &i);
		i--;
	}
	return (arr);
}

static int	arr_view_validvalue(const int *arr_view, const unsigned int size)
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
	Imbalanced,
	InvalidValue,
	NoViableSolution,
};

typedef struct s_err
{
	enum e_error	err;
	const char		*msg;
}			t_errmessage;

static int	rush_err(const enum e_error err)
{
	const t_errmessage	errors[] = {
	{.err = Empty, .msg = "Error: Empty Argument"},
	{.err = InvalidCharacter, .msg = "Error: Invalid Character"},
	{.err = Imbalanced, .msg = "Error: Imbalanced Amount of View"},
	{.err = InvalidValue, .msg = "Error: Invalid Value"},
	{.err = NoViableSolution, .msg = "Error: No Viable Solution"}
	};
	const unsigned int	message_size = sizeof(errors) / sizeof(errors[0]);
	unsigned int		i;

	if (err == OK)
		return (0);
	i = -1;
	while (++i < message_size)
	{
		if (err != errors[i].err)
			continue ;
		ft_dputendl(2, errors[i].msg);
		return (err);
	}
	ft_dputendl(2, "Error: Unknown error code");
	return (-1);
}

int	rush01(const char *input)
{
	enum e_error	status;
	int				*arr_view;
	unsigned int	size;

	arr_view = rush_parse(input, &size);
	if (arr_view == NULL)
		status = InvalidCharacter;
	else if (size == 0)
		status = Empty;
	else if (size % 4)
		status = Unbalanced;
	else if (!arr_view_validvalue(arr_view, size))
		status = InvalidValue;
	else if (!rush_solve(arr_view, size))
		status = NoViableSolution;
	else
		status = OK;
	free(arr_view);
	return (rush_err(status));
}
