
# Instruções de Execução do Simulador de Cache

## Execução:
O executável se encontra na pasta `output`. Para executá-lo, utilize o comando:

```./cache_simulator <nsets> <bsize> <assoc> <substituição> <flag_saida> arquivo_de_entrada ```


Não é necessário especificar o caminho completo do arquivo de entrada, apenas o nome.

## Requisitos Mínimos:
A única biblioteca externa utilizada é a `matplotlib`, que é necessária apenas para a geração de gráficos.  
Se não a estiver instalada, a execução ainda funcionará, mas os resultados serão exibidos apenas no terminal.

Para instalar a `matplotlib`, execute o seguinte comando na pasta `src/scripts`:

``` pip install -r requirements.txt ```


## Parâmetros de Substituição:
- `R`: Random  
- `L`: LRU (Least Recently Used)  
- `F`: FIFO (First In, First Out)  
- `M`: Executa o simulador para as três políticas de substituição

## Saída de Resultados:
- `0`: Gera um gráfico de hits/misses e a porcentagem de cada tipo de miss. Caso a política de substituição selecionada seja "M", será gerado um gráfico comparando os três métodos de substituição.
- `1`: Saída no formato padrão proposto pelo trabalho.

## Organização do Código:

### assets:
- Contém os arquivos binários e de texto necessários para a execução do simulador.

### src/config:
- `binary.c / binary.h`: Funções para leitura e armazenamento de arquivos binários.
- `data.c / data.h`: Estruturas de dados da cache e funções para manipulação.

### src/controller:
- `calc.c / calc.h`: Implementação dos cálculos de hits e misses da cache.
- `result.c / result.h`: Funções responsáveis pela geração de saída, seja no terminal ou chamando scripts para criação de gráficos.

### src/scripts:
- `graphics.py`: Gera gráficos de hits e misses utilizando a biblioteca `matplotlib`.


