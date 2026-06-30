# MEG6: Simulador do IAS

MEG6 é um projeto desenvolvido como trabalho da disciplina de Arquitetura
e Organização de Computadores I da Universidade Estadual de Maringá (UEM)
com o objetivo de melhor entender o funcionamento do ciclo de instrução dos
primeiros computadores, os quais serviram de base para os mais modernos.

Ele é um simulador de um dos primeiros computadores baseados na Arquitetura
de Von Neumann (o IAS) e segue o modelo desse computador descrito por
Stallings em seu livro Arquitetura e Organização de Computadores (10ª 
edição).

## Compilando o programa

Após baixar os arquivos, você pode acessar, pelo terminal, o diretório onde
eles estão e compila-los usando:

```bash
make
```

Ou você também pode compilar todos os arquivos .c manualmente com seu
compilador favorito.

## Executando

Se você compilou usando `make`, o programa pode ser executado com:

```bash
./meg6
```

Caso tenha compilado manualmente, altere `meg6` para o nome que você inseriu.

Ao iniciar, o programa vai solicitar o nome do arquivo de código que você
deseja executar (veja mais a frente como criar o seu próprio, ou use
algum exemplo pronto em `códigos de exemplo`). Após isso, você pode
escolher executar o código direto (sem pausas) ou passo a passo (para a
cada instrução executada e continua quando ENTER é pressionado).

> OBS: O arquivo de código deve estar no mesmo diretório do programa.

Durante a execução, a movimentação dos dados entre registradores e endereços de
memória é exibida na tela, tanto do ciclo de busca, quanto do ciclo de execução.
A movimentação exibida está no seguinte formato:

```
*destino* <- *origem* [*valor do dado*]
```

Ao final da execução, uma matriz 10x10 da área de dados será exibida,
mostrando o estado final dos dados na memória. O primeiro elemento da
matriz é o dado 0 e o último elemento é o dado 99.

## Escrevendo seu próprio programa em Assembly do IAS

Os arquivos de código lidos pelo compilador do programa devem ser
arquivos de texto comuns (em geral, arquivos .txt ou similares). A
sintaxe dos programas será descrita abaixo:

### Comentários

Os comentários dentro do código são marcados com `#` no inicio deles e podem
ser escritos em qualquer local.

```
# Nome do meu programa

# Dados
1
2

3 # Descrição sobre o dado

.TEXT
# Comentário sobre o código
LOAD M(0)
ADD M(1) # Explicação sobre a instrução
STOR M(2)

# Fim do programa
```

> OBS1: Não é obrigatório usar `#` após uma instrução, entretanto é
recomendável seu uso para manter o padrão estético e uma melhor legibilidade.

> OBS2: O limite do tamanho de uma linha é de 128 caractéres e esse valor conta para comentários, logo evite fazer comentários muito longos em uma
mesma linha.

### Dados

A primeira seção do código é reservada exclusivamente para dados. O
único tipo de dado aceito pelo simulador são números inteiros. Cada linha
é destinada a um dado e eles são carregados sequencialmente para as posições
de 0 a 99 da memória. Se a quantidade de dados ultrapassar o limite de 100, o
simulador recusará o código e informará o erro.

Exemplo:
```
4 # Posição 0 da memória
1 # Posição 1 da memória
2 # Posição 2 da memória

7 # Posição 3 da memória

.TEXT
# Instruções...
```

> OBS: Os endereços de memória informações até 40 bits de tamanho de palavra.
Dados que precisam mais do que isso para serem representados podem gerar
problemas e esse excesso é considerado overflow.

### Instruções

Para iniciar a seção de instruções no código e encerrar a seção de dados, é
necessário adicionar uma linha de marcação com `.TEXT`, isso informa ao
compilador que ele deve começar a ler instruções.

As instruções são carregadas à memória de forma sequencial (de forma similar
aos dados) a partir do endereço de memória 100 até o 999. Entretanto, cada 
endereço da memória suporta até 2 instruções diferentes, assim, quando duas
instruções são lidas para um mesmo endereço de memória, a primeira é salva
do lado esquerdo do endereço e a segunda é salva do lado direito. Portanto,
o simulador tem um limite de 1800 instruções por programa.

Exemplo:

```
# Dados...

.TEXT
# Inicio das instruções
LOAD M(0) # Instrução no lado esquerdo do endereço 100
ADD M(1) # Instrução no lado direito do endereço 100
STOR M(2) # Instrução no lado esquerdo do endereço 101

JUMP M(102,0:19) # Instrução no lado direito do endereço 102

# Continuação do programa...
```

As instruções disponíveis são as mesmas que o computador IAS possuia e que
estão descritas no livro do Stallings citado anteriormente:

> - M(X) -> Dado na posição X da memória
> - AC -> Acumulador (registrador de manipulação de dados dados)
> - MQ -> quociente-multiplicador (registrador para multiplicação e divisão)

| INSTRUÇÃO        | DESCRIÇÃO |
|------------------|-----------|
| LOAD MQ          | Carrega dado de MQ para AC |
| LOAD MQ,M(X)     | Carrega M(X) para o MQ |
| LOAD M(X)        | Carrega M(X) para o AC |
| LOAD -M(X)       | Carrega -M(X) para o AC|
| LOAD \|M(X)\|    | Carrega \|M(X)\| para o AC |
| LOAD -\|M(X)\|   | Carrega -\|M(X)\| para o AC |
| STOR M(X)        | Guarda o conteúdo de AC em M(X) |
| STOR M(X,8:19)   | Altera o endereço da instrução a esquerda na posição M(X) pelos 12 bits mais a direita de AC |
| STOR M(X,28:39)  | Altera o endereço da instrução a direita na posição M(X) pelos 12 bits mais a direita de AC |
| ADD M(X)         | Soma M(X) com AC e salva o resultado em AC |
| ADD \|M(X)\|     | Soma \|M(X)\| com AC e salva o resultado em AC |
| SUB M(X)         | Subtrai M(X) de AC e salva o resultado em AC |
| SUB \|M(X)\|     | Subtrai \|M(X)\| de AC e salva o resultado em AC |
| MUL M(X)         | Multiplique M(X) por MQ, guarde os 40 bits mais significativos em AC e os 40 bits menos significativos em MQ. Requer que ambos os números sejam não negativos |
| DIV M(X)         | Divida AC por M(X), guarde o quociente em MQ e o resto em AC |
| LSH              | Shift para esquerda em AC (multiplica AC por 2). Requer que o dado seja não negativo |
| RSH              | Shift para direita em AC (divide AC por 2). Requer que o dado seja não negativo |
| JUMP M(X,0:19)   | Próxima instrução a ser executada está à esquerda de M(X) |
| JUMP M(X,20:39)  | Próxima instrução a ser executada está à direita de M(X) |
| JUMP+ M(X,0:19)  | Se o número em AC for não negativo, a próxima instrução a ser executada está à esquerda de M(X) |
| JUMP+ M(X,20:39) | Se o número em AC for não negativo, a próxima instrução a ser executada está à direita de M(X) | |

O simulador encerra a execução do programa automaticamente após ler um
endereço de instrução sem instrução. Sendo assim, é possível forçar o
fim da execução redirecionando o fluxo para um local de memória onde não
foram carregadas instruções usando `JUMP` ou `JUMP+`.