NAME = chatik

SRC_DIR = src

OBJ_DIR = obj

INC_DIR = inc

SDL = -F resource/framework \
		-I resource/framework/SDL2.framework/SDL2 \
		-I resource/framework/SDL2_image.framework/SDL2_image \
		-I resource/framework/SDL2_mixer.framework/SDL2_mixer \
		-I resource/framework/SDL2_ttf.framework/SDL2_ttf

# сделать список всех файлов в папке src, которые имеют расширение .с
# формат каждой записи src/<file_name>.c
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# добавить префикс obj/ к каждой записи из SRC_FILES, в который убрали
# путь (до notdir src/<file_name>.c, после <file_name>.c) и изменить
# расширение с .с на .о
# результат выполнения src/<file_name>.o  --> obj/<file_name>.o
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:%.c=%.o)))

# сделать список всех файлов в папке inc, которые имеют расширение .h
# формат каждой записи inc/<file_name>.h
INC_FILES = $(wildcard $(INC_DIR)/*.h)

CC = clang

# флаги для компилятора (добабить префикс -W ко всем записям после
# запятой)
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -g \

SDL_FLAGS = -rpath resource/framework -framework SDL2 \
		-framework SDL2_image \
		-I resource/framework/SDL2_image.framework/Headers \
		-framework SDL2_mixer \
		-I resource/framework/SDL2_mixer.framework/Headers \
		-framework SDL2_ttf \
		-I resource/framework/SDL2_ttf.framework/Headers \

# архиватор для формирования библиотеки из о-файлов
AR = ar

#флаги для архиватора
AFLAGS = rcs

MKDIR = mkdir -p
RM = rm -rf

all: $(NAME)

# $@ - переменная, которая означает имя цели
# $^ - переменная, которая означает все зависимости текущей цели
$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR) $(SDL_FLAGS) $(SDL)
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

# перед компиляцией o-файлов создаем папку obj
$(OBJ_FILES): | $(OBJ_DIR)

# сравниваем время последней модификации по одному каждого о-файла
# с с-файлом c точно таким же именем и h-файлами. Если дата последней
# модицикации o-файла раньше, то будет перекомпилирован только этот
# с-файл и библиотека будет пересобрана. в случае с h-файлом будут
# перекомпилированы все c-файлы, т.к. это изменение касается каждого файла
# $< - переменная, которая означает имя первой зависимости цели
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) $(SDL)
	@printf "\r\33[2K$(NAME)\033[33;1m\t compile \033[0m$(<:$(SRC_DIR)/%.c=%)\r"

$(OBJ_DIR):
	@$(MKDIR) $@

clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(OBJ_DIR) in $(NAME)\t \033[31;1mdeleted\033[0m\n"

uninstall:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@@printf "$(NAME)\t \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all

# .PHONY - это явное указание имен целей мейкфайла, например, если
# в папке будет файл clean и попытаться выполнить команду make clean,
# то make попытается выполнить файл clean, а не цель clean
.PHONY: all uninstall clean reinstall