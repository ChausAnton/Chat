NAME		=	client

GTKCFLAGSLIBS	=	`pkg-config --cflags --libs gtk+-3.0`
GTKCFLAGS		=	`pkg-config --cflags gtk+-3.0`

ORACLE		=	-std=c11 -Wall -Wextra -Werror -Wpedantic
CFLAGS		=	$(ORACLE) 

SRC_DIR = src

OBJ_DIR = obj

INC_DIR = inc

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:%.c=%.o)))

INC_FILES = $(wildcard $(INC_DIR)/*.h)

MKDIR = mkdir -p
RM = rm -rf

all: $(NAME) #add clean here to delete obj dir

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $^ -o $(NAME) -I $(INC_DIR) $(GTKCFLAGSLIBS)
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) $(GTKCFLAGS)
	@printf "\r\33[2K$(NAME)\033[33;1m\t compile \033[0m$(<:$(SRC_DIR)/%.c=%)\r"

$(OBJ_DIR):
	@$(MKDIR) $@

clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(OBJ_DIR) in $(NAME)\t \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@@printf "$(NAME)\t \033[31;1muninstalled\033[0m\n"
	
reinstall: uninstall all
