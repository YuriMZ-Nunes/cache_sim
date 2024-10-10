Instruções de Execução do Simulador de Cache

Compilção:
gcc -g -o cache_simulator src/main.c src/controller/calc.c src/controller/result.c src/config/data.c src/config/binary.c -lm

Execução:
./cache_simulator <nsets> <bsize> <assoc> <substituição> <flag_saida> arquivo_de_entrada.bin

Não é necessário especificar o caminho do arquivo usado, apenas o nome, porem o arquivo deve estar na pasta assets

Requisitos minimos
A única biblioteca externa utilizada é a matplotlib, que é usada apenas para a geração de gráficos.
Se a biblioteca matplotlib não estiver instalada, a execução ainda funcionará, mas os resultados serão exibidos apenas no terminal.
Para instalar a matplotlib, execute o seguinte comando na pasta src/scripts

pip install -r requirements.txt

Parametros de substituição
- R: Random
- L: LRU
- F: FIFO
- M: Executa o simulador para as tres politicas de substituicao

Saida de resultados
- 0: É gerado um grafico de hits/misses e % de cada tipo de misses. Caso a politica de substituicao selecionada seja "M" sera gerado um grafico comparando os tres metodos de substituicao
- 1: Padrao proposto pelo trabalho

Organizacao do codigo
assets:
- Contém os arquivos binários e de texto necessários para a execução do simulador

src/config:
- binary.c / binary.h: Funções para leitura e armazenamento de arquivos binários.
- data.c / data.h: Estruturas de dados da cache e funções para manipulação.

src/controller:
- calc.c / calc.h: Implementação dos cálculos de hits e misses da cache
- result.c / result.h: Funções responsáveis pela geração de saída, seja no terminal ou chamando scripts para criação de gráficos

src/scripts:
- graphics.py: Gera gráficos de hits e misses utilizando a biblioteca matplotlib
