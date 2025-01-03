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
ARG5 = saida.txt

# Diretórios
HEADER_DIR = Headers
SRC_DIR = Sources
OBJ_DIR = Objects

# Obter automaticamente todos os arquivos .c no diretório source
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Gerar nomes de arquivos .o a partir dos arquivos .c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Regra para compilar todos os arquivos .o a partir dos arquivos .c
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	@$(COMPILADORC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Regra para criar diretórios e compilar cada arquivo .c em um arquivo .o correspondente
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | obj_dirs
	@$(COMPILADORC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

# Para rodar com valgrind e verificar vazamentos de memória
leak_1: $(EXECUTABLE)
	@valgrind --leak-check=full ./$(EXECUTABLE) $(ARG0) $(ARG1)

leak_2: $(EXECUTABLE)
	@valgrind --leak-check=full ./$(EXECUTABLE) $(ARG0) $(ARG2)

leak_3: $(EXECUTABLE)
	@valgrind --leak-check=full ./$(EXECUTABLE) $(ARG0) $(ARG3)

leak_4: $(EXECUTABLE)
	@valgrind --leak-check=full ./$(EXECUTABLE) $(ARG0) $(ARG4)

# Limpar arquivos objeto e o executável
clean:
	@rm -rf $(OBJ_DIR) $(EXECUTABLE) $(ARG5)

.PHONY: all leak_1 leak_2 leak_3 leak_4 clean