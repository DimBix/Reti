# Makefile for compiling serverHTTP and clientHTTP

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -lpthread

# Source files for server
SERVER_SRCS = network.c serverHTTP-REST.c
# Source files for client
CLIENT_SRCS = network.c serverHTTP-RESTmod.c

# Output executables
SERVER_TARGET = serverHTTP
CLIENT_TARGET = serverHTTPmod

# Default target
all: $(SERVER_TARGET) $(CLIENT_TARGET)

# Rule to build the server target
$(SERVER_TARGET): $(SERVER_SRCS)
	$(CC) $(SERVER_SRCS) -o $(SERVER_TARGET) $(CFLAGS)

# Rule to build the client target
$(CLIENT_TARGET): $(CLIENT_SRCS)
	$(CC) $(CLIENT_SRCS) -o $(CLIENT_TARGET) $(CFLAGS)

# Clean up build files
clean:
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET)
