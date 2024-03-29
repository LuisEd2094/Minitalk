# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 17:25:23 by lsoto-do          #+#    #+#              #
#    Updated: 2023/07/12 17:25:26 by lsoto-do         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	Minitalk
CLIENT		= 	client
SERVER		=	server
NAME_BCL	=	client_bonus
NAME_BSR	=	server_bonus
CFLAGS      = 	-Wall -Wextra -Werror
RM          = 	rm -f
LIB_PATH	= 	./Libft
LIB			=	$(LIB_PATH)/libft.a
LDFLAGS		= 	-L$(LIB_PATH) -lft
SHARED_PATH	=	shared_src/
SRCS_C_PATH	= 	client_src/
SRCS_S_PATH	= 	server_src/
OBJS_PATH	= 	obj/
OB_C_PATH	= 	$(OBJS_PATH)client/
OB_S_PATH	=	$(OBJS_PATH)server/
OB_SHARED_P	=	$(OBJS_PATH)shared/
DEPS_PATH	=	deps/
DEPS_C_PATH	=	$(DEPS_PATH)client/
DEPS_S_PATH	=	$(DEPS_PATH)server/
DEPS_SHARED	=	$(DEPS_PATH)shared/
INCS        =	-I./include/shared -I$(LIB_PATH)/includes
INCS_CL		=	-I./include/client_inc
INCS_SR		=	-I./include/server_inc


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

### FOR ALL ##

SRC_C		=	client.c aux_client.c

SRC_S		=	server.c  server_aux.c

SHARED_SRC	=	send_signal.c

## SRCS FOR BONUS ##

BONUS_C		=	$(SRC_C:.c=_bonus.c)

BONUS_S		=	$(SRC_S:.c=_bonus.c)

BONUS_SH	=	$(SHARED_SRC:.c=_bonus.c)

## OBJS FOR ALL ##

OBJS_C		=	$(addprefix $(OB_C_PATH), $(SRC_C:.c=.o))

OBJS_S		=	$(addprefix $(OB_S_PATH), $(SRC_S:.c=.o))

OBJS_SHARED	=	$(addprefix $(OB_SHARED_P), $(SHARED_SRC:.c=.o))

## OBJS FOR BONUS ##

OBJS_C_B	=	$(addprefix $(OB_C_PATH), $(BONUS_C:.c=.o))

OBJS_S_B	=	$(addprefix $(OB_S_PATH), $(BONUS_S:.c=.o))

OBJS_SH_B	=	$(addprefix $(OB_SHARED_P), $(BONUS_SH:.c=.o))

## DEPS FOR ALL ##

DEPS		=	$(addprefix $(DEPS_C_PATH), $(SRC_C:.c=.d)) \
				$(addprefix $(DEPS_S_PATH), $(SRC_S:.c=.d)) \
				$(addprefix $(DEPS_SHARED), $(SHARED_SRC:.c=.d))

## DEPS FOR BONUS ##

DEPS_BONUS	=	$(addprefix $(DEPS_C_PATH), $(BONUS_C:.c=.d)) \
				$(addprefix $(DEPS_S_PATH), $(BONUS_S:.c=.d)) \
				$(addprefix $(DEPS_SHARED), $(BONUS_SH:.c=.d))

all: make_lib $(NAME)

bonus: make_lib $(NAME_BCL) $(NAME_BSR)
	@echo "$(BLUE)Done$(DEF_COLOR)"


make_lib:
	@echo "$(GREEN)Checking Libft$(DEF_COLOR)"
	@$(MAKE) -s -C $(LIB_PATH)
	@echo "$(BLUE)Done checking Libft$(DEF_COLOR)"

## Make Client Bonus ##
$(NAME_BCL): $(OBJS_C_B) $(OBJS_SH_B) $(LIB)
	@$(CC) $(CFLAGS) $(INCS) $(INCS_CL) $(OBJS_C_B) $(OBJS_SH_B) -o $(NAME_BCL) $(LDFLAGS)
	@echo "$(BLUE)Created $(CLIENT) executable with Bonus files$(DEF_COLOR)"


$(OB_C_PATH)%_bonus.o: $(SRCS_C_PATH)%_bonus.c | $(OB_C_PATH) $(DEPS_C_PATH)
	@echo "$(GREEN)Compiling $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCS) $(INCS_CL) -MMD -MP -c $< -o $@
	@mv $(OB_C_PATH)$(notdir $(basename $<)).d $(DEPS_C_PATH)


$(NAME_BSR): $(OBJS_S_B) $(OBJS_SH_B) $(LIB)
	@$(CC) $(CFLAGS) $(INCS) $(INCS_SR) $(OBJS_S_B) $(OBJS_SH_B) -o $(NAME_BSR) $(LDFLAGS)
	@echo "$(BLUE)Created $(SERVER) executable with Bonus files$(DEF_COLOR)"

$(OB_S_PATH)%.o: $(SRCS_S_PATH)%.c | $(OB_S_PATH) $(DEPS_S_PATH)
	@echo "$(GREEN)Compiling $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCS) $(INCS_SR) -MMD -MP -c $< -o $@
	@mv $(OB_S_PATH)$(notdir $(basename $<)).d $(DEPS_S_PATH)




## ORDES TO MAKE ALL ##


$(OB_SHARED_P)%.o: $(SHARED_PATH)%.c | $(OB_SHARED_P) $(DEPS_SHARED)
	@echo "$(GREEN)Compiling $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCS) -MMD -MP -c $< -o $@
	@mv $(OB_SHARED_P)$(notdir $(basename $<)).d $(DEPS_SHARED)

$(OB_C_PATH)%.o: $(SRCS_C_PATH)%.c | $(OB_C_PATH) $(DEPS_C_PATH)
	@echo "$(GREEN)Compiling $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCS) $(INCS_CL) -MMD -MP -c $< -o $@
	@mv $(OB_C_PATH)$(notdir $(basename $<)).d $(DEPS_C_PATH)

$(OB_S_PATH)%.o: $(SRCS_S_PATH)%.c | $(OB_S_PATH) $(DEPS_S_PATH)
	@echo "$(GREEN)Compiling $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCS) $(INCS_SR) -MMD -MP -c $< -o $@
	@mv $(OB_S_PATH)$(notdir $(basename $<)).d $(DEPS_S_PATH)

$(CLIENT): $(OBJS_C) $(OBJS_SHARED) $(LIB)
	@$(CC) $(CFLAGS) $(INCS) $(INCS_CL) $(OBJS_C) $(OBJS_SHARED) -o $(CLIENT) $(LDFLAGS)
	@echo "$(BLUE)Created $(CLIENT) executable$(DEF_COLOR)"

$(SERVER): $(OBJS_S) $(OBJS_SHARED) $(LIB)
	@$(CC) $(CFLAGS) $(INCS) $(INCS_SR) $(OBJS_S) $(OBJS_SHARED) -o $(SERVER) $(LDFLAGS)
	@echo "$(BLUE)Created $(SERVER) executable$(DEF_COLOR)"


$(NAME): $(CLIENT) $(SERVER) $(LIB) 
	@echo "$(BLUE)Done$(DEF_COLOR)"



## CREATE ALL DIRECTORIES ##


$(OB_SHARED_P):
	@echo "$(GREEN)Creating shared Obj Dir $(DEF_COLOR)"
	@mkdir -p $(OB_SHARED_P)


$(DEPS_SHARED):
	@echo "$(GREEN)Creating shared Deps Dir $(DEF_COLOR)"
	@mkdir -p $(DEPS_SHARED)


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

-include $(DEPS) $(DEPS_BONUS)
fclean_lib:
	@$(MAKE) fclean -s -C $(LIB_PATH)

clean_lib:
	@$(MAKE) clean -s -C $(LIB_PATH) 

clean: clean_lib clean_objects

fclean: fclean_lib clean_objects
	@$(RM) $(CLIENT)
	@$(RM) $(SERVER)
	@$(RM) $(NAME_BCL)
	@$(RM) $(NAME_BSR)
	@echo "$(GREEN)Client and Server executable cleaned!$(DEF_COLOR)"

clean_objects:
	@echo "$(GREEN)Client and Server Objects and Dependencies cleaned!$(DEF_COLOR)"
	@$(RM) -r $(OBJS_PATH) $(DEPS_PATH)


re: fclean all

.PHONY: all fclean clean fclean_lib clean_lib re bonus make_lib
