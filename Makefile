NAME = minishell
<<<<<<< HEAD
FUNC = built_in/exit.c built_in/env.c pars/expand.c allocate_free/init_data.c syntax_error/error.c pars/pars.c allocate_free/free_data.c  main/main.c  doubly_linked/ft_lstadd_back_d.c  doubly_linked/ft_lstadd_front_d.c  doubly_linked/ft_lstnew_d.c lexer/check_quotes.c lexer/split_tokens.c  lexer/utilis.c execution/start_executing.c execution/redirection.c
=======
FUNC = built_in/pwd.c built_in/env.c built_in/chng_dir.c built_in/echo.c pars/expand.c allocate_free/init_data.c syntax_error/error.c pars/pars.c allocate_free/free_data.c  main/main.c  doubly_linked/ft_lstadd_back_d.c  doubly_linked/ft_lstadd_front_d.c  doubly_linked/ft_lstnew_d.c lexer/check_quotes.c lexer/split_tokens.c  lexer/utilis.c execution/start_executing.c execution/redirection.c
>>>>>>> 699fcb2a1e7b8c5ea8df585099f05e830730313b
OBG = $(FUNC:.c=.o)
LIBFT = libft/libft.a
LINKING = -lreadline
CFLAGS = -g3
CC = cc
BLUE = \033[33m
GREEN = \033[32m
CYAN = \033[36m

all : $(NAME)

$(NAME): $(OBG) $(LIBFT)
	@echo "$(BLUE)Compiling project...$(RESET)"
	$(CC) $(CFLAGS) $^ $(LINKING) -o $(NAME)
	@echo "$(GREEN)✅ Build Successful!$(RESET)"

%.o : %.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

%.o : lexer/%.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

%.o : execution/%.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

%.o : built_in/%.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

%.o : pars/%.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

%.o : doubly_linked/%.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

%.o : allocate_free syntax_error//%.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

%.o : syntax_error//%.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	@echo "$(CYAN)🧹 Cleaning object files...$(RESET)"
	rm -rf $(OBG)

fclean: clean
	@echo "$(CYAN)🗑️ Removing executable...$(RESET)"
	rm -rf $(NAME)

re : fclean all

.PHONY : clean