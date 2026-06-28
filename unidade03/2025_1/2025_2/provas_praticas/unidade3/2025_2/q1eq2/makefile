CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++17 -Iheader -I../lib -MMD -MP -fsanitize=address -fno-omit-frame-pointer -g
BIN_DIR = bin

# Fontes
SRC_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(patsubst src/%.cpp, $(BIN_DIR)/%.o, $(SRC_FILES))
DEP_FILES = $(OBJ_FILES:.o=.d)
EXECUTABLE = $(BIN_DIR)/main

# Bibliotecas auxiliares
LIB_FILES = $(wildcard lib/*.cpp)
LIB_OBJ_FILES = $(patsubst lib/%.cpp, $(BIN_DIR)/%.o, $(LIB_FILES))
LIB_DEP_FILES = $(LIB_OBJ_FILES:.o=.d)

# Teste Inserir
TEST_INSERIR_SRC = $(filter-out src/main.cpp, $(SRC_FILES)) test/TesteInserir.cpp
TEST_INSERIR_OBJS = $(patsubst %.cpp, $(BIN_DIR)/%.o, $(notdir $(TEST_INSERIR_SRC))) $(LIB_OBJ_FILES)
TEST_INSERIR_DEPS = $(TEST_INSERIR_OBJS:.o=.d)
TEST_EXECUTABLE_INSERIR = $(BIN_DIR)/test-inserir

# Teste Remover
TEST_REMOVER_SRC = $(filter-out src/main.cpp, $(SRC_FILES)) test/TesteRemover.cpp
TEST_REMOVER_OBJS = $(patsubst %.cpp, $(BIN_DIR)/%.o, $(notdir $(TEST_REMOVER_SRC))) $(LIB_OBJ_FILES)
TEST_REMOVER_DEPS = $(TEST_REMOVER_OBJS:.o=.d)
TEST_EXECUTABLE_REMOVER = $(BIN_DIR)/test-remover

# Alvo padrão
all: $(EXECUTABLE) $(TEST_EXECUTABLE_INSERIR) $(TEST_EXECUTABLE_REMOVER) 

test: $(TEST_EXECUTABLE_INSERIR) $(TEST_EXECUTABLE_REMOVER)

# Execução principal
$(EXECUTABLE): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Executáveis de testes
$(TEST_EXECUTABLE_INSERIR): $(TEST_INSERIR_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_EXECUTABLE_REMOVER): $(TEST_REMOVER_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Regra para compilar .cpp → bin/%.o com dependência .d
$(BIN_DIR)/%.o: src/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: test/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: lib/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Inclusão dos arquivos de dependência
-include $(DEP_FILES) $(LIB_DEP_FILES) $(TEST_INSERIR_DEPS) $(TEST_REMOVER_DEPS)

# Execuções
.PHONY: run run-test run-test-inserir run-test-remover clean clean-doc doc

run: $(EXECUTABLE)
	./$(EXECUTABLE)

run-test: test
	./$(TEST_EXECUTABLE_INSERIR)
	./$(TEST_EXECUTABLE_REMOVER)

run-test-inserir: $(TEST_EXECUTABLE_INSERIR)
	./$(TEST_EXECUTABLE_INSERIR)

run-test-remover: $(TEST_EXECUTABLE_REMOVER)
	./$(TEST_EXECUTABLE_REMOVER)

# Limpeza
clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/*.d $(EXECUTABLE) \
		$(TEST_EXECUTABLE_INSERIR) \
		$(TEST_EXECUTABLE_REMOVER)

clean-doc:
	rm -rf ./doc/*

doc:
	doxygen Doxyfile