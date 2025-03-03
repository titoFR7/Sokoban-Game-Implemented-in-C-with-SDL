CC = gcc
CFLAGS = -Wall -Wextra -g $(shell sdl2-config --cflags)
LIBS = $(shell sdl2-config --libs) -lSDL2_ttf

TARGET = sokoban
SRCS = main.c jeu.c affichage.c
OBJS = $(SRCS:.c=.o)

# Règle par défaut
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LIBS)

# Règle pour compiler les fichiers objets
%.o: %.c jeu.h affichage.h
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)

# Règle pour exécuter l'application
run: $(TARGET)
	./$(TARGET)