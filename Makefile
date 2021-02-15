UCHAT  = uchat
SERVER  = uchat_server

GTKCFLAGSLIBS = `pkg-config --cflags --libs gtk+-3.0`
GTKCFLAGS  = `pkg-config --cflags gtk+-3.0`

ORACLE  = -std=c11 -Wall -Wextra -Werror -Wpedantic
CFLAGS  = $(ORACLE) 

UCHAT_SRC_DIR = ui/src
UCHAT_OBJ_DIR = ui/obj
UCHAT_INC_DIR = ui/inc

UCHAT_SRC_FILES = $(wildcard $(UCHAT_SRC_DIR)/*.c)
UCHAT_OBJ_FILES = $(addprefix $(UCHAT_OBJ_DIR)/, $(notdir $(UCHAT_SRC_FILES:%.c=%.o)))
UCHAT_INC_FILES = $(wildcard $(UCHAT_INC_DIR)/*.h)

SERVER_SRC_DIR = Server/src
SERVER_OBJ_DIR = Server/obj
SERVER_INC_DIR = Server/inc

SERVER_SRC_FILES = $(wildcard $(SERVER_SRC_DIR)/*.c)
SERVER_OBJ_FILES = $(addprefix $(SERVER_OBJ_DIR)/, $(notdir $(SERVER_SRC_FILES:%.c=%.o)))
SERVER_INC_FILES = $(wildcard $(SERVER_INC_DIR)/*.h)

SQLITE3_DIR = sqlite3/
SQLITE3_FILES:= $(SQLITE3_DIR)/libsqlite3.a
SQLITE3_INC_FILES:= $(SQLITE3_DIR)/include

LIBS_FLAGS = -lsqlite3 -L$(SQLITE3_DIR) -I$(SQLITE3_INC_FILES)

MKDIR = mkdir -p
RM = rm -rf

all: cleandb $(SERVER) $(UCHAT) #add clean here to delete obj dir

cleandb:
	@$(RM) database

#Server
$(SERVER): $(SERVER_OBJ_FILES)
	@$(CC) $(CFLAGS) $(LIBS_FLAGS) $^ -o $(SERVER) -I $(SERVER_INC_DIR) $(GTKCFLAGSLIBS)
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

$(SERVER_OBJ_FILES): | $(SERVER_OBJ_DIR)

$(SERVER_OBJ_DIR)/%.o: $(SERVER_SRC_DIR)/%.c $(SERVER_INC_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(SERVER_INC_DIR) $(GTKCFLAGS)
	@printf "\r\33[2K$(SERVER)\033[33;1m\t compile \033[0m$(<:$(SERVER_SRC_DIR)/%.c=%)\r"

$(SERVER_OBJ_DIR):
	@$(MKDIR) $@

#UCHAT
$(UCHAT): $(UCHAT_OBJ_FILES)
	@$(CC) $(CFLAGS) $^ -o $(UCHAT) -I $(UCHAT_INC_DIR) $(GTKCFLAGSLIBS)
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

$(UCHAT_OBJ_FILES): | $(UCHAT_OBJ_DIR)

$(UCHAT_OBJ_DIR)/%.o: $(UCHAT_SRC_DIR)/%.c $(UCHAT_INC_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(UCHAT_INC_DIR) $(GTKCFLAGS)
	@printf "\r\33[2K$(UCHAT)\033[33;1m\t compile \033[0m$(<:$(UCHAT_SRC_DIR)/%.c=%)\r"

$(UCHAT_OBJ_DIR):
	@$(MKDIR) $@

clean: cleandb
	@$(RM) $(UCHAT_OBJ_DIR)
	@printf "$(UCHAT_OBJ_DIR) in $(UCHAT)\t \033[31;1mdeleted\033[0m\n"
	@$(RM) $(SERVER_OBJ_DIR)
	@printf "$(SERVER_OBJ_DIR) in $(SERVER)\t \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@$(RM) $(UCHAT_OBJ_DIR)
	@$(RM) $(UCHAT)
	@@printf "$(UCHAT)\t \033[31;1muninstalled\033[0m\n"
	@$(RM) $(SERVER_OBJ_DIR)
	@$(RM) $(SERVER)
	@@printf "$(SERVER)\t \033[31;1muninstalled\033[0m\n"
 
reinstall: uninstall all
