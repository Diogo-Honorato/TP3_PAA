COMPILADORC = gcc

CFLAGS = -Wall -Wextra -O2 -g

LDFLAGS = -lm

# Nome do executável
EXECUTABLE = tp3

# Variáveis para argumentos
ARG0 = entrada.txt
ARG1 = 1
ARG2 = 2
ARG3 = 3
ARG4 = 4

# Diretórios
HEADER_DIR = Headers
SRC_DIR = Sources
OBJ_DIR = Objects
RESULT_DIR = Resultados

# Obter automaticamente todos os arquivos .c no diretório source
SRCS = $(wildcard $(SRC_DIR)/*.c)


# Gerar nomes de arquivos .o a partir dos arquivos .c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))


# Regra padrão para compilar o programa
all: dirs $(EXECUTABLE)

# Regra para gerar o executável a partir dos arquivos .o
$(EXECUTABLE): $(OBJS)
	@$(COMPILADORC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Regra para compilar arquivos .c em arquivos .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | dirs
	@$(COMPILADORC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

# Criação dos diretórios necessários
dirs: obj_dirs result_dirs

obj_dirs:
	@mkdir -p $(OBJ_DIR)


result_dirs:
	@mkdir -p $(RESULT_DIR)

# Limpar arquivos objeto e o executável
clean:
	@rm -rf $(OBJ_DIR) $(EXECUTABLE) $(RESULT_DIR)


.PHONY: all clean