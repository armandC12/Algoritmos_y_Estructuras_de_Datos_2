#include <assert.h>
#include <stdlib.h>

#include "cost.h"
#include "graph.h"
#include "mini_set.h"

vertex_t min_edge(cost_t *D, set C, vertex_t max){

    vertex_t c = set_get(C);					     // c = 1
    cost_t cost = D[c];							     // cost = D[c] = 4 
    for (vertex_t i = 0u; i < max; ++i){             // D[c] = 0,{4,(1),10,#,#} ignoramos el cero     
        if(cost >= D[i] && set_member(i, C)){        // i = 2: 4 > 1 && set_member(2,C) -> true && true -> true
        	c = i;  								 // c = 2
        }
    }
    return c;
}

cost_t *dijkstra(graph_t graph, vertex_t init) {
	vertex_t c;
	set C = set_empty();
	vertex_t max = graph_max_vertexs(graph);     // max = 6
	for(vertex_t i = 0u; i < max; ++i){
		C = set_add(C,i);                        // C = (0,1,2,3,4,5)
	}
	C = set_elim(C, init);                       // C = (1,2,3,4,5)

	cost_t *D = calloc(max, sizeof(cost_t));
    for (vertex_t i = 0u; i < max; ++i) {
        D[i] = graph_get_cost(graph, init, i);   // D[max] = {0,4,1,10,#,#}
    }

	while(!set_is_empty(C)){
		c = min_edge(D, C, max);                                       // c = 2
		C = set_elim(C,c);						                  // C = {1,3,4,5}
		for(vertex_t j = 0u ; j < max; ++j){			  	
			if(cost_le(D[c] + graph_get_cost(graph,c,j), D[j]) && set_member(j,C)){  // min(D[c]+L[c,j], D[j])
				D[j] = D[c] + graph_get_cost(graph,c,j);          // 
			}
		}
	}
    return D;
}
/*
6
    0 1 2  3 4 5 		   
  ---------------			 
0 | 0 4 1 10 # #
1 | 4 0 3  # 1 #
2 | # 2 0  8 4 #
3 | 2 # 2  0 # #
4 | # # 3  # 0 3
5 | # # 2  1 # 0
*/

/*
fun Dijkstra(L: array[1..n,1..n] of Nat, v: Nat) ret D: array[1..n] of Nat
    var c: Nat
    var C: Set of Nat
    for i := 1 to n do 
        add(C,i) 
    od
    elim(C,v)
    for j:= 1 to n do 
        D[j]:= L[v,j] 
    od
    do (not is_empty_set(C))→
        c:= “elijo elemento c de C tal que D[c] sea mínimo”
        elim(C,c)
        for j in C do D[j]:= min(D[j],D[c]+L[c,j]) od / for j = C[i] con i = [0,..,N] Siendo N la cantidad de elementos
    od
end fun
*/