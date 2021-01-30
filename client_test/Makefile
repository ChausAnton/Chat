NAME		=	client

#GTKFLAGS	=	`pkg-config --cflags --libs gtk+-3.0`
GTKFLAGS	=   -L resource/gtk3/lib -lgtk-3.0 -L resource/gtk3/lib -lgdk-3.0

GLIBFLAGS   =   -L resource/glib/lib -lglib-2.0 -lgobject-2.0
GIOFLAGS   =	-L resource/glib/lib -lgio-2.0 
PANGOFLAGS   =	-L resource/pango/lib -lpango-1.0
CAIROFLAGS   =	-L resource/cairo/lib -lcairo-gobject -lcairo
PBUFFFLAGS   =  -L resource/gdkpixbuf/lib -lgdk_pixbuf-2.0
ATKFLAGS   =	-L resource/atk/lib -latk-1.0	
HBUZZFLAGS   =	-L resource/harfbuzz/lib -lharfbuzz.0				
				

ORACLE		=	-std=c11 -Wall -Wextra -Werror -Wpedantic
CFLAGS		=	$(ORACLE)
GTK 		= 	$(GTKFLAGS) $(GLIBFLAGS) $(GIOFLAGS) $(PANGOFLAGS) $(CAIROFLAGS) $(PBUFFFLAGS) $(ATKFLAGS) $(HBUZZFLAGS)

SRC_DIR = src

OBJ_DIR = obj

INC_DIR = inc

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:%.c=%.o)))

INC_FILES = $(wildcard $(INC_DIR)/*.h)

AR = ar

AFLAGS = rcs

MKDIR = mkdir -p
RM = rm -rf

PREFIX_NAME = $(addprefix ./, $(NAME))
QUARTZ_PATH = /Users/irazumeyko/.brew/Cellar/gtk+3/3.24.24/lib/gtk-3.0/3.0.0/immodules/im-quartz.so
PIXBUFFLOADER_PATH = /Users/irazumeyko/.brew/lib/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-png.so

all: install clean

install: $(OBJ_FILES)
	@$(CC) $(CFLAGS) $^ -o $(NAME) -I $(INC_DIR) $(GTK)
	@install_name_tool -change /Users/$$USER/.brew/opt/gdk-pixbuf/lib/libgdk_pixbuf-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgmodule-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgmodule-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libglib-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgobject-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgio-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/pango/lib/libpangocairo-1.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/pango/lib/libpangocairo-1.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/pango/lib/libpangoft2-1.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/pango/lib/libpangoft2-1.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/cairo/lib/libcairo.2.dylib /Users/$$USER/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/cairo/lib/libcairo-gobject.2.dylib /Users/$$USER/Desktop/Chat/client_test/resource/cairo/lib/libcairo-gobject.2.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/atk/lib/libatk-1.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/atk/lib/libatk-1.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/harfbuzz/lib/libharfbuzz.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib resource/gtk3/lib/libgtk-3.0.dylib

	@install_name_tool -change /Users/$$USER/.brew/opt/gdk-pixbuf/lib/libgdk_pixbuf-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgmodule-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgmodule-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libglib-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgobject-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgio-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/pango/lib/libpango-1.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/pango/lib/libpango-1.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/pango/lib/libpangocairo-1.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/pango/lib/libpangocairo-1.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/cairo/lib/libcairo.2.dylib /Users/$$USER/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/cairo/lib/libcairo-gobject.2.dylib /Users/$$USER/Desktop/Chat/client_test/resource/cairo/lib/libcairo-gobject.2.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/atk/lib/libatk-1.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/atk/lib/libatk-1.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib

	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libglib-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgobject-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgio-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib

	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libglib-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/pango/lib/libpango-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgobject-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/pango/lib/libpango-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgio-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/pango/lib/libpango-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/harfbuzz/lib/libharfbuzz.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib resource/pango/lib/libpango-1.0.0.dylib

	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libglib-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgobject-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgio-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/harfbuzz/lib/libharfbuzz.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/cairo/lib/libcairo.2.dylib /Users/$$USER/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/pango/lib/libpangocairo-1.0.0.dylib

	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libglib-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/pango/lib/libpangoft2-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgobject-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/pango/lib/libpangoft2-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgio-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/pango/lib/libpangoft2-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/harfbuzz/lib/libharfbuzz.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib resource/pango/lib/libpangoft2-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/cairo/lib/libcairo.2.dylib /Users/$$USER/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/pango/lib/libpangoft2-1.0.0.dylib

	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libglib-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/harfbuzz/lib/libharfbuzz.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgobject-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/harfbuzz/lib/libharfbuzz.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgio-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/harfbuzz/lib/libharfbuzz.0.dylib

	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libglib-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/cairo/lib/libcairo-gobject.2.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgobject-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/cairo/lib/libcairo-gobject.2.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgio-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/cairo/lib/libcairo-gobject.2.dylib

	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libglib-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/atk/lib/libatk-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgobject-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/atk/lib/libatk-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgio-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/atk/lib/libatk-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/harfbuzz/lib/libharfbuzz.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib resource/atk/lib/libatk-1.0.0.dylib
	@install_name_tool -change /Users/$$USER/.brew/opt/cairo/lib/libcairo.2.dylib /Users/$$USER/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/atk/lib/libatk-1.0.0.dylib

	@install_name_tool -change /Users/$$USER/.brew/opt/gtk+3/lib/libgtk-3.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/gtk3/lib/libgtk-3.0.dylib $(QUARTZ_PATH)
	@install_name_tool -change /Users/$$USER/.brew/opt/gtk+3/lib/libgdk-3.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/gtk3/lib/libgdk-3.0.dylib $(QUARTZ_PATH)
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libglib-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $(QUARTZ_PATH)
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgobject-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $(QUARTZ_PATH)
	@install_name_tool -change /Users/$$USER/.brew/opt/pango/lib/libpango-1.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/pango/lib/libpango-1.0.0.dylib $(QUARTZ_PATH)

	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libglib-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $(PIXBUFFLOADER_PATH)
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgobject-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $(PIXBUFFLOADER_PATH)

	@install_name_tool -change /Users/$$USER/.brew/opt/gtk+3/lib/libgtk-3.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/gtk3/lib/libgtk-3.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$$USER/.brew/opt/gtk+3/lib/libgdk-3.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/gtk3/lib/libgdk-3.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$$USER/.brew/opt/gdk-pixbuf/lib/libgdk_pixbuf-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgio-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libglib-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$$USER/.brew/opt/glib/lib/libgobject-2.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$$USER/.brew/opt/pango/lib/libpango-1.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/pango/lib/libpango-1.0.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$$USER/.brew/opt/cairo/lib/libcairo-gobject.2.dylib /Users/$$USER/Desktop/Chat/client_test/resource/cairo/lib/libcairo-gobject.2.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$$USER/.brew/opt/cairo/lib/libcairo.2.dylib /Users/$$USER/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$$USER/.brew/opt/atk/lib/libatk-1.0.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/atk/lib/libatk-1.0.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$$USER/.brew/opt/harfbuzz/lib/libharfbuzz.0.dylib /Users/$$USER/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib $(PREFIX_NAME)
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)
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
	
reinstall: uninstall install clean
