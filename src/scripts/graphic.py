import matplotlib.pyplot as plt
import sys

def main():
    if len(sys.argv) != 7:
        print("Numero de argumentos incorreto.")
        exit(1)

    access = int(sys.argv[1])
    hitRatio = float(sys.argv[2])
    missRatio = float(sys.argv[3])
    compRatio = float(sys.argv[4])
    capRatio = float(sys.argv[5])
    confRatio = float(sys.argv[6])

    # hit x miss graphic
    labelsHitMiss = ['Hit', 'Miss']
    sizesHitMiss = [hitRatio, missRatio]
    colorsHitMiss = ['#B0D27E', '#ff9999']

    # miss types graphic
    labelsMissTypes = ['Compusório', 'Capacidade', 'Conflito']
    sizesMissTypes = [compRatio, capRatio, confRatio]
    colorsMissTypes = ['#FAAE39', '#9F72B1', '#25BCBA']

    # pizza
    fig, (g1, g2) = plt.subplots(1, 2, figsize=(12, 6))

    fig.suptitle(f'Resultados - {access} acessos', fontsize=14)

    g1.pie(sizesHitMiss, colors=colorsHitMiss, autopct='%1.1f%%', startangle=90)
    g1.set_title('Hit x Miss')
    g1.legend(labelsHitMiss, loc='upper left')

    g2.pie(sizesMissTypes, colors=colorsMissTypes, autopct='%1.1f%%', startangle=90)
    g2.set_title('Tipos de Miss')
    g2.legend(labelsMissTypes, loc='upper right')

    plt.tight_layout()
    plt.show()  

if __name__ == '__main__':
    main()