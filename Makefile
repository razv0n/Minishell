NAME = minishell
FUNC = execution/herdoc_utils.c built_in/export/export_0.c built_in/export/export_1.c built_in/export/export_2.c built_in/echo.c built_in/pwd.c built_in/unset.c built_in/chng_dir.c built_in/exit.c built_in/env.c pars/expand.c allocate_free/init_data.c syntax_error/error.c pars/pars.c allocate_free/free_data.c  main/main.c  doubly_linked/ft_lstadd_back_d.c  doubly_linked/ft_lstadd_front_d.c  doubly_linked/ft_lstnew_d.c lexer/check_quotes.c lexer/split_tokens.c  lexer/utilis.c execution/start_executing/execution_utils_0.c  execution/start_executing/execution_utils_1.c execution/start_executing/execution_utils_2.c execution/redirection.c
OBG = $(FUNC:.c=.o)
LIBFT = libft/libft.a
LINKING = -lreadline
CFLAGS = -g3
CC = cc
BLUE = \033[33m
GREEN = \033[32m
CYAN = \033[36m
RESET = "\033[0m"

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