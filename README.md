Este trabalho visa abordar o problema do Caminho Mais Curto (shortest path). A problemática vem sendo atacada a muitas décadas e tem muitas aplicações práticas, como em rodas de mapas e principalmente em roteadores e controladores de redes de computadores. Este tema é bem trabalhado nos livros do (ANDREW S. TANENBAUM E DAVID WETHERALL, 2011; CORMEN, 2012; KUROSE; ROSS, 2010). 
A família de algoritmos que abordam esse assunto é dividida segundo duas técnicas, sendo, Métodos Gulosos e Programação Dinâmica (metodologias Bottom/Up e Top/Down), estas metodologia trabalham com maximização ou minimização e o objetivo deste trabalho busca apresentar, dentre de algoritmos clássicos, os custos de minimização através do menor caminho para, por exemplo, um melhor fluxo de rede.
Para analise serão apresentados brevemente o Método Guloso de Dijkstra e os Métodos de Programação Dinâmica Bellman-Ford e Floyd-Warshall, assim como uma implementação dos mesmos.

Para ploagem dos graficos em http://www.webgraphviz.com.
Exemplo de grafo:

digraph g{
  rankdir=LR;
  "0" -> "1" [dir=none color="black" label="2"]
  "0" -> "2" [dir=none color="black" label="4"]
  "1" -> "2" [dir=none color="black" label="1"]
  "1" -> "3" [dir=none color="black" label="4"]
  "1" -> "4" [dir=none color="black" label="2"]
  "2" -> "4" [dir=none color="black" label="3"]
  "3" -> "4" [dir=none color="black" label="3"]
  "3" -> "5" [dir=none color="black" label="2"]
  "4" -> "5" [dir=none color="black" label="2"]
}
