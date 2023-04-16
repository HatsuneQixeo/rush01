NAME		:=	rush01

CC			:=	gcc
CXXFLAGS	:=	-Wall -Wextra -Werror
CXXFLAGS	+=	-g
# CXXFLAGS	+=	-fsanitize=address
CXXFLAGS	+=	-Wno-unused-variable -Wno-unused-parameter -Wno-unused-but-set-variable

SRC_DIR		:=	srcs
SRCS		:=	$(shell find $(SRC_DIR) -name "*.c")

OBJ_DIR		:=	objs
OBJS		:=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

HEADER		:=	$(shell find $(SRC_DIR) -name "*.h")
CFLAGS		:=	$(addprefix -I, $(dir $(HEADER)))

all: $(NAME)

$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CXXFLAGS) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
