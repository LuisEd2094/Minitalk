

NAME		=	Minitalk
CLIENT		= 	client
SERVER		=	server
CFLAGS      = 	-Wall -Wextra  -Werror
RM          = 	rm -f
LIB_PATH	= 	./Libft
LIB			=	$(LIB_PATH)/libft.a
LDFLAGS		= 	-L$(LIB_PATH) -lft
SRCS_C_PATH	= 	client_src/
SRCS_S_PATH	= 	server_src/
OBJS_PATH	= 	obj/
OB_C_PATH	= 	$(OBJS_PATH)client/
OB_S_PATH	=	$(OBJS_PATH)server/
DEPS_PATH	=	deps/
DEPS_C_PATH	=	$(DEPS_PATH)client/
DEPS_S_PATH	=	$(DEPS_PATH)server/
INCS        =	-I$(LIB_PATH)/includes

#Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
LIGHT_GREEN = \033[1;92m

###

SRC_C		=	client.c

SRC_S		=	server.c 

OBJS_C		=	$(addprefix $(OB_C_PATH), $(SRC_C:.c=.o))

OBJS_S		=	$(addprefix $(OB_S_PATH), $(SRC_S:.c=.o))

DEPS		=	$(addprefix $(DEPS_C_PATH), $(SRC_C:.c=.d)) \
				$(addprefix $(DEPS_S_PATH), $(SRC_S:.c=.d))

all: make_lib make_client make_server $(NAME)


$(OB_C_PATH)%.o: $(SRCS_C_PATH)%.c | $(OB_C_PATH) $(DEPS_C_PATH)
	@echo "$(GREEN)Compiling $< $(DEF_COLOR)"
	$(CC) $(CFLAGS) $(INCS) -MMD -MP -c $< -o $@
	@mv $(OB_C_PATH)$(notdir $(basename $<)).d $(DEPS_C_PATH)


make_client: $(OBJS_C)
	$(CC) $(CFLAGS) $(INCS) $(OBJS_C) -o $(CLIENT) $(LDFLAGS)
	@echo "$(LIGHT_GREEN)Created $(CLIENT) executable$(DEF_COLOR)"

$(OB_S_PATH)%.o: $(SRCS_S_PATH)%.c | $(OB_S_PATH) $(DEPS_S_PATH)
	@echo "$(GREEN)Compiling $< $(DEF_COLOR)"
	$(CC) $(CFLAGS) $(INCS) -MMD -MP -c $< -o $@
	@mv $(OB_S_PATH)$(notdir $(basename $<)).d $(DEPS_S_PATH)


make_server: $(OBJS_S)
	$(CC) $(CFLAGS) $(INCS) $(OBJS_S) -o $(SERVER) $(LDFLAGS)
	@echo "$(LIGHT_GREEN)Created $(SERVER) executable$(DEF_COLOR)"


$(NAME): $(CLIENT) $(SERVER)
	@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"


$(DEPS_C_PATH):
	@echo "$(GREEN)Creating $(CLIENT) Deps Dir $(DEF_COLOR)"
	@mkdir -p $(DEPS_C_PATH)

$(OB_C_PATH):
	@echo "$(GREEN)Creating $(CLIENT) Obj Dir $(DEF_COLOR)"
	@mkdir -p $(OB_C_PATH)

$(DEPS_S_PATH):
	@echo "$(GREEN)Creating $(SERVER) Deps Dir $(DEF_COLOR)"
	@mkdir -p $(DEPS_S_PATH)

$(OB_S_PATH):
	@echo "$(GREEN)Creating $(SERVER) Obj Dir $(DEF_COLOR)"
	@mkdir -p $(OB_S_PATH)

make_lib:
	@echo "$(GREEN)Checking Libft$(DEF_COLOR)"
	@$(MAKE) -s -C $(LIB_PATH)
	@echo "$(BLUE)Done$(DEF_COLOR)"
	

-include $(DEPS)

fclean_lib:
	@$(MAKE) fclean -s -C $(LIB_PATH)

clean_lib:
	@$(MAKE) clean -s -C $(LIB_PATH) 

clean: clean_lib clean_objects

fclean: fclean_lib clean_objects
	@$(RM) $(CLIENT)
	@$(RM) $(SERVER)
	@echo "$(GREEN)Client and Server executable cleaned!$(DEF_COLOR)"

clean_objects:
	@echo "$(GREEN)Client and Server Objects and Dependencies cleaned!$(DEF_COLOR)"
	@$(RM) -r $(OBJS_PATH) $(DEPS_PATH)


re: fclean all

.PHONY: all fclean clean fclean_lib clean_lib re
