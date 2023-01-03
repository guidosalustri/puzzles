//
// Este archivo contiene las definiciones de las funciones que implementan los ejercicios
//

#include <stdio.h>
#include <iostream>
#include <fstream>


#include "definiciones.h"
#include "ejercicios.h"
#include "auxiliares.h"

using namespace std;

/******++++**************************** EJERCICIO minasAdyacentes ***********+++***********************/
// La complejidad de minasAdyacentes es de O(1), pues la complejidad de todas las lineas es O(1).
int minasAdyacentes(tablero& t, pos p) {
    int i = -1; //O(1)
    int j; //O(1)
    int res = 0; //O(1)
    int p_0 = p.first; //O(1)
    int p_1 = p.second; //O(1)
    while (i<=1){ //O(1)
        j= -1; //O(1)
        while (j<=1){ //O(1)
            if (esAdyacenteValida(p,i,j,t)){ //O(1)
                if (t[p_0 + i][p_1 + j]) { //O(1)
                    res++; //O(1)
                }
            }
            j++; //O(1)
        }
        i++; //O(1)
    }
    return res; //O(1)
}

/******++++**************************** EJERCICIO plantarBanderita ***********+++***********************/
// La complejidad de cambiarBanderita es O(n), donde n es b.size(), porque en el ṕeor caso,
// pasa una vez por la guarda y entra en sacaBanderita que tiene mayor complejidad. Ambas iteran por
// toda la lista de banderitas una vez.
void cambiarBanderita(tablero& t, jugadas& j, pos p, banderitas& b) {
    if (esBanderita(p, b)){ //O(n) * O(1)
        sacaBanderita(p, b); //O(n)
    } else{
        plantaBanderita(p,b); //O(1)
    }
}

/******++++**************************** EJERCICIO perdio ***********+++***********************/
bool perdio(tablero& t, jugadas& j) {
    int i = 0; //O(1)
    while (i < j.size() && !t[j[i].first.first][j[i].first.second]){ //O(n)
        i++; //O(1)
    }
    return i < j.size(); //O(1)
}
/* En el peor caso, la lista de jugadas no contendra bombas, y el ciclo se cortará con el final de la misma.
 De esta manera, se recorrera la lista de jugadas en su enteridad y la funcion de complejidad será O(n).
 Decimos que perdio tiene un tiempo de ejecucion en el peor caso lineal con respecto a la longitud de jugadas
 */
/******++++**************************** EJERCICIO gano ***********+++***********************/
bool gano(tablero& t, jugadas& j) {
    int i = 0; //O(1)
    int k; //O(1)
    int cantfalse = 0; //O(1)
    while (i < t.size()){ //O(n)
        k=0; //O(1)
        while ( k < t.size()){ //O(n)
            if (!t[i][k]){ //O(1)
                cantfalse++; //O(1)
            }

            k++; //O(1)
        }
        i++; //O(1)
    }
    bool noHayMinasJugadas = true; //O(1)
    for (int z = 0; z < j.size() ; z++){ //O(y)
        pos p = j[z].first; //O(1)
        noHayMinasJugadas = noHayMinasJugadas && !t[p.first][p.second]; //O(1)
    }
    return cantfalse == j.size() && noHayMinasJugadas; //O(1)
}
// Complejidad temporal: O(n²) + O(y) ∈  O(n²), donde n es t.size() e y es j.size().
//Si bien no es cierto que siempre es acotable y por n² (es decir, una variable por la otra al cuadrado); en este caso sí
// se cumple, pues j.size() es más pequeño que t.size() al cuadrado (lo máximo que puede estar en j.size() es t.size()).


/******++++**************************** EJERCICIO jugarPlus ***********+++***********************/
void jugarPlus(tablero& t, banderitas& b, pos p, jugadas& j) {
    jugada a; //O(1)
    a.first = p; //O(1)
    a.second = minasAdyacentes(t,p); //O(1)
    j.push_back(a); //O(1)
// En un principio, agregamos la posición dada en la función con su cantidad de minas adyacentes, a jugadas
    int p_0 = p.first; //O(1)
    int p_1 = p.second; //O(1)

    if (minasAdyacentes(t,p)== 0 && !t[p_0][p_1] ){ //O(1)
        vector<jugada> v; //O(1)
        v.push_back(a); //O(1)
        vector<jugada> v_final = v; //O(1)
        vector<jugada> v_inicial; //O(1)
        vector<jugada> v_ady = v; //O(1)

        while (v_inicial != v_ady){ // t⁴, donde t es t.size(). Porque se multiplica la complejidad de la guarda
            // (t² en el peor caso, que es cuando el v_inicial tiene todos los elementos del tablero) y lo multiplicas
            // por la cantidad de ejecuciones del ciclo que tambien es t² por que el tablero esta vacio y hay la mayor
            // cantidad de posiciones que agregar.
            int i = v_final.size(); // me guarda el tamaño del vector nuevo (el que tiene los elementos últimos agregados O(1)
            v_inicial = v_final; // v_inicial toma el valor del vector que ingresa O(1)
            cumpleCondiciones (v_final, j, b, t, i); // O(b) + O(j)
            v_ady = v_final; // v_ady toma el valor del vector al que se le agregaron o no elementos // O(1)
            int k=0; // O(1)
            while (k < i){ // le saco a v_final los elementos que ya había agregado a mi lista de jugadas para no
                // agregarlos otra vez - para esto muevo la cantidad q saco de atras hacia adelante y dsp elimino los
                // que paso adelante para q no me queden repetidos --> se me achica el vector // O(1)
                v_final[k]=v_ady[v_ady.size() -1-k]; // O(1)
                v_final.pop_back();// O(1)
                k++;// O(1)
            }
            int r = 0; // O(1)
            while (r<v_final.size()){ // aca agrego los elementos agregados // O(v_final) donde |v_final| es t² en el peor caso
                jugada a = v_final[r]; // O(1)
                if (!esJugada(a.first, j)) { // O(j) donde j es j.size()
                    j.push_back(v_final[r]); // O(1)
                }
                r++; // O(1)
            }
        }

    }
}
//complejidad temporal: O(t⁴)*(O(1)+O(t²)) ∈  O(t⁶)
//No encontramos manera de hacerlo más eficiente. Lo intentamos hacer en un principio de manera recursiva pero cuando
//no nos funcionó, pensamos en otras formas de hacerlo (y esto fue lo primero en funcionar).

// En un principio, agregamos la posición dada en la función con su cantidad de minas adyacentes, a jugadas
// Lo que hace esta función es crear tres vectores: v_ady, v_final y v_inicial.
//Para comenzar, definimos una variable i, que es el tamaño de v_final al ingresar al while grande. Esto es así porque
// v_final contiene los últimos elementos que se agregan a jugadas (a partir de cumpleCondiciones). Luego, el primer while
// dentro del while más grande se encarga de pasar el valor del último elemento de v_final al inicio (para no perder el valor)
// y eliminar el último elemento. Realiza esto i-1 veces, hasta quitar todos los elementos que antes estaban en v_final
// (antes de que ocurriera el cambio, pues luego se somete a esta variable a la función cumpleCondiciones).
//Luego, para lo que reste del vector v_final, el segundo while dentro del while más grande se encargará de agregarlo a jugadas.
//En el while mas grande se guardan los valores de v_final en v_inicial al ingresar al ciclo. Esto es así porque v_final
// será cambiado luego en cumpleCondiciones.
//Además, v_ady se iguala v_final luego de haberse agregado (o no) los elementos, y sirve como copia de v_final a la hora de
// realizar el primer loop dentro del primer while.
// Finalmente, la comparación de v_inicial con v_ady en el while más grande sirve para que, en el caso en el que v_inicial
// sea igual a v_ady, se deje entrar, pues esto implicaría que no se agregó nada más.

/******++++**************************** EJERCICIO sugerirAutomatico121 ***********+++***********************/
bool sugerirAutomatico121(tablero& t, banderitas& b, jugadas& j, pos& p) {
    pos pes2; //O(1)
    if (hay121HorizontalLibre(t, b, j, pes2, p) || hay121VerticalLibre(t, b, j, pes2,p) ){ //O(j²) + O(j)*O(b) (ambos casos
        //tienen la misma complejidad)
        return true; //O(1)
    }else {
        return false; //O(1)
    }
}
//complejidad temporal: (O(j²) + O(j)*O(b)) + (O(j²) + O(j)*O(b)) ∈ O(j²) + O(j)*O(b)
// Esta función se fija si existe un 121 en algún sitio del tablero. En caso de que exista, devuelve true si tambien hay
// una posición sugerible para jugar, adyacente al 2 de ese 121.