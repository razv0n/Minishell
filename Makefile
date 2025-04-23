NAME = minishell
FUNC = pars/pars.c  allocate_free/allocate_data.c  allocate_data/free_data.c  main/main.c  doubly_linked/ft_lstadd_back_d.c  doubly_linked/ft_lstadd_front_d.c  doubly_linked/ft_lstnew_d.c lexer/check_quotes.c lexer/split_tokens.c  lexer/utilis.c
OGJ = = $(FUNC:.c=.o)
LIBFT = libft.a

all : $(NAME)

$(NAME) : $(FUNC)