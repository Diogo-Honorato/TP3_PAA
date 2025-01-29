import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
import os

# Função para ler os dados de um arquivo
def ler_dados(nome_arquivo):
    with open(nome_arquivo, 'r') as file:
        lines = file.readlines()[1:]  # Ignora o cabeçalho
        data = [line.strip().split() for line in lines]
        comparisons = [int(row[0]) for row in data]
        times = [float(row[1]) for row in data]
    return comparisons, times

# Função para calcular a regressão linear
def calcular_regressao(x, y):
    x = np.array(x).reshape(-1, 1)
    y = np.array(y)
    model = LinearRegression()
    model.fit(x, y)
    return model

# Função para calcular pontos médios dos agrupamentos ao longo da reta
def calcular_agrupamentos(comparisons, times, model, num_intervalos=5):
    # Prever os valores de y (Time) usando a reta de regressão
    y_pred = model.predict(np.array(comparisons).reshape(-1, 1))
    
    # Dividir os pontos em intervalos ao longo do eixo x (Comparisons)
    x_min, x_max = min(comparisons), max(comparisons)
    intervalos = np.linspace(x_min, x_max, num_intervalos + 1)
    
    agrupamentos_x = []
    agrupamentos_y = []
    
    for i in range(len(intervalos) - 1):
        # Filtrar pontos dentro do intervalo atual
        mask = (np.array(comparisons) >= intervalos[i]) & (np.array(comparisons) < intervalos[i + 1])
        pontos_x = np.array(comparisons)[mask]
        pontos_y = np.array(times)[mask]
        
        # Se houver pontos no intervalo, calcular a média
        if len(pontos_x) > 0:
            agrupamentos_x.append(np.mean(pontos_x))
            agrupamentos_y.append(np.mean(pontos_y))
    
    return agrupamentos_x, agrupamentos_y

# Função para plotar a regressão e salvar como .png
def plotar_regressao(comparisons, times, model, title, filename):
    plt.figure()  # Cria uma nova figura
    
    # Plotar os pontos
    plt.scatter(comparisons, times, color='blue', label='Dados')
    
    # Plotar a reta de regressão
    plt.plot(comparisons, model.predict(np.array(comparisons).reshape(-1, 1)), color='red', label='Reta de Regressão')
    
    # Calcular e plotar os agrupamentos ao longo da reta
    agrupamentos_x, agrupamentos_y = calcular_agrupamentos(comparisons, times, model)
    plt.scatter(agrupamentos_x, agrupamentos_y, color='green', s=100, label='Agrupamentos', edgecolor='black')
    
    plt.xlabel('Comparisons')
    plt.ylabel('Time')
    plt.title(title)
    plt.legend()
    plt.savefig(filename)  # Salva o gráfico como .png
    plt.close()  # Fecha a figura para liberar memória

# Caminho da pasta onde os gráficos serão salvos
pasta_saida = 'retas'

# Verifica se a pasta existe, se não, cria
if not os.path.exists(pasta_saida):
    os.makedirs(pasta_saida)

# Lista de arquivos
arquivos = ['Força_Bruta.txt', 'KMP.txt', 'BMH.txt', 'Shift-And.txt']

# Dicionário para armazenar os tempos de todos os algoritmos
todos_tempos = []

# Processar cada arquivo
for arquivo in arquivos:
    comparisons, times = ler_dados(arquivo)
    
    # Filtrar pontos com Time <= 10
    comparisons_filtrado = []
    times_filtrado = []
    for comp, time in zip(comparisons, times):
        if time <= 10:  # Mantém apenas os pontos com Time <= 10
            comparisons_filtrado.append(comp)
            times_filtrado.append(time)
    
    # Adicionar os tempos filtrados à lista de todos os tempos
    todos_tempos.extend(times_filtrado)
    
    # Calcular a regressão linear apenas com os pontos filtrados
    if comparisons_filtrado:  # Verifica se há pontos para calcular a regressão
        model = calcular_regressao(comparisons_filtrado, times_filtrado)
        
        # Gerar o nome do arquivo de saída (com caminho da pasta)
        nome_saida = os.path.join(pasta_saida, arquivo.replace('.txt', '_regressao.png'))
        
        # Plotar a regressão e salvar como .png
        plotar_regressao(comparisons_filtrado, times_filtrado, model, f'Regressão Linear - {arquivo} (Time <= 10)', nome_saida)

# Calcular a média dos tempos filtrados (Time <= 10)
media_tempos = np.mean(todos_tempos)

# Plotar os pontos que não passam da média e têm Time <= 10, e salvar como .png
plt.figure()
plt.scatter(range(len(todos_tempos)), todos_tempos, color='blue', label='Dados')
plt.axhline(y=media_tempos, color='red', linestyle='--', label=f'Média dos Tempos: {media_tempos:.2f}')
plt.xlabel('Índice do Ponto')
plt.ylabel('Time')
plt.title('Pontos com Time <= 10')
plt.legend()
plt.savefig(os.path.join(pasta_saida, 'pontos_time_menor_igual_10.png'))  # Salva o gráfico como .png
plt.close()  # Fecha a figura