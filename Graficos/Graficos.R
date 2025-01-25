# Carregar os pacotes necessários
library(ggplot2)
library(dplyr)

# Definir uma função para ler os dados e plotar os gráficos
plot_comparisons <- function(file_paths, algorithm_names) {
  # Verificar se o número de arquivos e nomes de algoritmos correspondem
  if (length(file_paths) != length(algorithm_names)) {
    stop("A quantidade de arquivos deve ser igual à quantidade de nomes de algoritmos.")
  }

  # Criar um data frame vazio para armazenar os dados combinados
  combined_data <- data.frame(Comparisons = numeric(), Time = numeric(), Algorithm = character())

  # Ler cada arquivo e adicionar ao data frame combinado
  for (i in seq_along(file_paths)) {
    data <- read.table(file_paths[i], header = TRUE)
    colnames(data) <- c("Comparisons", "Time")
    data$Algorithm <- algorithm_names[i]
    combined_data <- rbind(combined_data, data)
  }

  # Calcular a média de comparações por algoritmo e arredondar para inteiro
  avg_comparisons <- combined_data %>%
    group_by(Algorithm) %>%
    summarise(AverageComparisons = round(mean(Comparisons), 0)) %>%  # Arredonda para inteiro
    arrange(AverageComparisons)  # Ordena de menor para maior

  # Título com quebra de linha
  title_text <- "Média de Comparações por Algoritmo\n(texto: 1000 caracteres, padrão: 128 caracteres)"

  # Gráfico de barras para a média de Comparações por Algoritmo
  plot_comparisons <- ggplot(avg_comparisons, aes(x = reorder(Algorithm, AverageComparisons), y = AverageComparisons, fill = Algorithm)) +
    geom_bar(stat = "identity", show.legend = FALSE) +
    geom_text(aes(label = AverageComparisons), vjust = -0.5, hjust = 0.5) +  # Centraliza o texto
    labs(title = title_text, x = "Algoritmo", y = "Média de Comparações") +
    theme_minimal() +
    theme(axis.text.x = element_text(angle = 45, hjust = 1),  # Ajusta o texto do eixo x
          plot.title = element_text(hjust = 0.5, size = 15))  # Centraliza o título e ajusta o tamanho da fonte

  # Salvar a imagem como .png
  ggsave("comparisons_by_algorithm.png", plot_comparisons, width = 8, height = 6)

  # Mostrar o gráfico
  print(plot_comparisons)  # Exibe o gráfico de barras para comparações
}

# Exemplo de uso:
file_paths <- c("Força_Bruta.txt", "KMP.txt", "BMH.txt", "Shift-And.txt")
algorithm_names <- c("Força_Bruta", "KMP", "BMH", "Shift-And")

# Chamar a função para plotar o gráfico de comparações
plot_comparisons(file_paths, algorithm_names)
