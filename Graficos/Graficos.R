# Carregar os pacotes necessários
library(ggplot2)
library(dplyr)

# Função para remover outliers (valores muito acima da média)
remove_outliers <- function(data, column, threshold = 2) {
  mean_val <- mean(data[[column]])
  sd_val <- sd(data[[column]])
  data %>% filter(data[[column]] <= (mean_val + threshold * sd_val))  # Remove valores muito altos
}

# Função para gerar gráficos
plot_time_vs_comparisons <- function(file_paths, algorithm_names) {
  if (length(file_paths) != length(algorithm_names)) {
    stop("A quantidade de arquivos deve ser igual à quantidade de nomes de algoritmos.")
  }

  combined_data <- data.frame(Comparisons = numeric(), Time = numeric(), Algorithm = character())

  for (i in seq_along(file_paths)) {
    data <- read.table(file_paths[i], header = TRUE)
    colnames(data) <- c("Comparisons", "Time")
    data$Algorithm <- algorithm_names[i]
    combined_data <- rbind(combined_data, data)
  }

  regression_color <- "black"

  for (algo in unique(combined_data$Algorithm)) {
    algo_data <- subset(combined_data, Algorithm == algo)
    
    # Remover outliers ANTES de fazer o gráfico
    algo_data_filtered <- remove_outliers(algo_data, "Time")

    plot_individual <- ggplot(algo_data_filtered, aes(x = Comparisons, y = Time)) +
      geom_point(aes(color = "Teste"), size = 3) +  # Apenas pontos válidos
      geom_smooth(method = "lm", se = TRUE, color = regression_color, linetype = "dashed", aes(color = "Regressão")) +  
      scale_color_manual(values = c("Teste" = "blue", "Regressão" = "black")) +  
      labs(
        title = paste("Relação entre Comparações e Tempo -", algo),
        x = "Número de Comparações",
        y = "Tempo (s)",
        color = "Legenda"
      ) +
      theme_minimal() +
      theme(
        plot.title = element_text(hjust = 0.5),
        legend.position = "right"
      )
    
    ggsave(paste0("time_vs_comparisons_", algo, ".png"), plot_individual, width = 8, height = 6)
    print(plot_individual)
  }

  # Remover outliers do gráfico combinado também
  combined_data_filtered <- remove_outliers(combined_data, "Time")

  plot_combined <- ggplot(combined_data_filtered, aes(x = Comparisons, y = Time)) +
    geom_point(aes(color = "Teste"), size = 3) +  
    geom_smooth(method = "lm", se = TRUE, linetype = "dashed", aes(color = Algorithm)) +  
    scale_color_manual(values = c("Teste" = "blue", "Força_Bruta" = "red", "KMP" = "green", "Shift-And" = "purple", "BMH" = "orange")) +
    labs(
      title = "Relação entre Comparações e Tempo - Todos os Algoritmos",
      x = "Número de Comparações",
      y = "Tempo (s)",
      color = "Legenda"
    ) +
    theme_minimal() +
    theme(
      plot.title = element_text(hjust = 0.5),
      legend.position = "right"
    )
  
  ggsave("time_vs_comparisons_all_algorithms.png", plot_combined, width = 8, height = 6)
  print(plot_combined)
}

# Exemplo de uso:
file_paths <- c("Força_Bruta.txt", "KMP.txt", "Shift-And.txt", "BMH.txt")
algorithm_names <- c("Força_Bruta", "KMP", "Shift-And", "BMH")

plot_time_vs_comparisons(file_paths, algorithm_names)
