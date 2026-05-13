# Welcher Compiler?
CC = gcc

CFLAGS = -I include -Wall -Wextra

# Name
TARGET = Station_Gate

# Welche Dateien
SRCS = src/main.c src/game.c src/ui.c src/generator.c src/assets.c src/validator.c src/rules.c src/stats.c 

#Regeln
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

test: src/test_logic.c src/validator.c src/rules.c
		$(CC) $(CFLAGS) -o test_suite src/test_logic.c src/validator.c src/rules.c
