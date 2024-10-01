import matplotlib.pyplot as plt
import numpy as np
import csv
import sys

class Result:
    def __init__(self, access, hitRatio, missRatio, compRatio, capRatio, confRatio):
        self.access = access
        self.hitRatio = hitRatio
        self.missRatio = missRatio
        self.compRatio = compRatio
        self.capRatio = capRatio
        self.confRatio = confRatio

def oneSubGraph():
    with open('src/scripts/results.csv', mode='r') as file:
        results = csv.reader(file,delimiter=' ')
        for lines in results:
            result = Result(int(lines[0]), float(lines[1]), float(lines[2]), float(lines[3]), float(lines[4]), float(lines[5]))

    # hit x miss graphic
    labelsHitMiss = ['Hit', 'Miss']
    sizesHitMiss = [result.hitRatio, result.missRatio]
    colorsHitMiss = ['#B0D27E', '#ff9999']

    # miss types graphic
    labelsMissTypes = ['Compusório', 'Capacidade', 'Conflito']
    sizesMissTypes = [result.compRatio, result.capRatio, result.confRatio]
    colorsMissTypes = ['#FAAE39', '#9F72B1', '#25BCBA']

    # pizza
    fig, (g1, g2) = plt.subplots(1, 2, figsize=(12, 6))

    fig.suptitle(f'Resultados - {result.access} acessos', fontsize=14)

    g1.pie(sizesHitMiss, colors=colorsHitMiss, autopct='%1.1f%%', startangle=90)
    g1.set_title('Hit x Miss')
    g1.legend(labelsHitMiss, loc='upper left')

    g2.pie(sizesMissTypes, colors=colorsMissTypes, autopct='%1.1f%%', startangle=90)
    g2.set_title('Tipos de Miss')
    g2.legend(labelsMissTypes, loc='upper right')

    plt.tight_layout()
    plt.show()  


    print(result)
    
def addBarInfos(bars, ax):
    for bar in bars:
        height = bar.get_height()
        ax.annotate(f'{height: .2f}%',
                    xy=(bar.get_x() + bar.get_width() / 2, height),
                    xytext=(0, 3),  # 3 pontos de deslocamento acima da barra
                    textcoords="offset points",
                    ha='center', va='bottom')

def compairSubsGraph():
    results = []

    with open('src/scripts/results.csv', mode='r') as file:
        result = csv.reader(file,delimiter=' ')
        for lines in result:
            results.append(Result(int(lines[0]), float(lines[1]), float(lines[2]), float(lines[3]), float(lines[4]), float(lines[5])))

    percResults = [
        [results[0].hitRatio * 100, results[0].missRatio * 100, results[0].compRatio * 100, results[0].capRatio * 100, results[0].confRatio * 100],
        [results[1].hitRatio * 100, results[1].missRatio * 100, results[1].compRatio * 100, results[1].capRatio * 100, results[1].confRatio * 100],
        [results[2].hitRatio * 100, results[2].missRatio * 100, results[2].compRatio * 100, results[2].capRatio * 100, results[2].confRatio * 100]
    ]

    labels = ['Hit Ratio', 'Miss Ratio', 'Compulsory Miss Ratio', 'Capacity Miss Ratio', 'Conflict Miss Ratio']
    x = np.arange(len(labels))
    width = 0.2

    fig, ax = plt.subplots()

    barR = ax.bar(x - width, percResults[0], width, label='Random')
    barL = ax.bar(x, percResults[1], width, label='LRU')
    barF = ax.bar(x + width, percResults[2], width, label='FIFO')

    addBarInfos(barR, ax)
    addBarInfos(barL, ax)
    addBarInfos(barF, ax)

    ax.set_ylabel('Percentual (%)')
    ax.set_title(f'Resultados - {results[0].access} acessos para substituição Random, LRU e FIFO', fontsize=14)

    ax.set_xticks(x)
    ax.set_xticklabels(labels)
    ax.legend()

    fig.set_size_inches(1920 / 100, 1080 / 100)

    plt.show()

def main():
    if len(sys.argv) > 1:
        arg = sys.argv[1]
        print(arg)
        if (arg == 'M'):
            compairSubsGraph()
        else:
            oneSubGraph()
    else:
        print("Nenhum argumento foi passado.")


    
if __name__ == '__main__':
    main()