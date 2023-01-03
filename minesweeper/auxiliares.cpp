//
// Este archivo contiene las definiciones de las funciones auxiliares
// que ustedes necesiten implementar. Tienen que coincidir con las 
// declaraciones de auxiliares.h
//

#include <iostream>
#include <fstream>


#include "definiciones.h"
#include "ejercicios.h"
#include "auxiliares.h"

using namespace std;
//Ejercicio 1
bool esAdyacenteValida(pos p, int i, int j, tablero& t){
    int p_0 = p.first; //O(1)
    int p_1 = p.second; //O(1)
    if (coordenadaValida(p_0 + i, t.size()) && coordenadaValida(p_1 + j, t.size()) && (i!= 0 || j!=0)){ //O(1)
        return true; //O(1)
    } else{
        return false; //O(1)
    }
}

bool coordenadaValida(int c, int n){
    return (0 <= c && c < n); //O(1)
}

//Ejercicio 2

void sacaBanderita (pos p, banderitas& b){
    int i=0; //O(1)
    while (i<b.size() && p != b[i]){ //O(n)
        i++; //O(1)
    }
    pos a = b[i];//O(1)
    b[i] = b[b.size() -1];//O(1)
    b[b.size()-1] = a; //O(1)
    b.pop_back(); //O(1)
}

void plantaBanderita (pos p, banderitas& b){
    b.push_back(p); //O(1)
}

bool esBanderita(pos p, banderitas& b){
    int i = 0; //O(1)
    while (i < b.size() && p!=b[i]){ //O(n)
        i++; //O(1)
    }
    return i< b.size();//O(1)
}

// ejercicio 5
// O(1) * O(1) * ( O(1) + O(b) + O(j) + O(b) + O(j) ) = O(b) + O(j), donde b es b.size() y j es j.size().
// No las juntamos en una misma variable porque la longitud de las listas depende del juego.
void cumpleCondiciones (vector<jugada>& v, jugadas& j, banderitas& b, tablero& t, int tamano){
    int i; //O(1)
    int k; //O(1)
    int r = 0; //O(1)
    while (r<tamano){ //O(1) (tamaño es una constante)
        int p_0= v[r].first.first; //O(1)
        int p_1= v[r].first.second; //O(1)
        i=-1; //O(1)
        while (i<=1){ //O(1)
            k = -1; //O(1)
            while (k<=1){ //O(1)
                if (esAdyacenteValida(v[r].first,i,k,t)) { //O(1)
                    jugada z; //O(1)
                    z.first.first = p_0 + i; //O(1)
                    z.first.second = p_1 + k; //O(1)
                    z.second = minasAdyacentes(t, z.first); //O(1)
                    if (!t[p_0 + i][p_1 + k] && minasAdyacentes(t, z.first) == 0 && !esBanderita(z.first, b) && !esJugada(z.first, j)) { // O(b) + O(j), donde b es b.size() y j es j.size()
                        v.push_back(z); //O(1)
                    } else if (!t[p_0 + i][p_1 + k] && !esBanderita(z.first, b) && !esJugada(z.first, j)){ // O(b) + O(j), donde b es b.size() y j es j.size()
                        j.push_back(z); //O(1)
                    }
                }
                k++; //O(1)
            }
            i++; //O(1)
        }
        r++; //O(1)
    }
}

//La función anterior realiza la tarea de, para cada elemento del vector v ingresado, buscar los adyacentes válidos (adyacentes
// que no sean bombas ).
// Si estas casillas adyacentes no están en jugadas, y tampoco tienen bombas adyacentes (de manera tal que puede haber más camino libre,
// compuesto en parte por posibles adyacetnes a estas casillas), la función las agrega al vector v. En caso contrario, las agrega a jugadas.
// De esta manera, no se pierde tiempo buscando los adyacentes a los "bordes/costras" del camino libre (es decir, aquellas fichas que formarían
// el sendero de números que encerraría al camino libre).


//Ejercicio 6
bool esJugada(pos p, jugadas& j){
    int i = 0; //O(1)
    while (i < j.size() && p!=j[i].first){ //O(j), donde j es j.size()
        i++; //O(1)
    }
    return i< j.size(); //O(1)
}
// Esta función se fija si la posición que inserto está en la lista de jugadas.

bool hay121HorizontalLibre(tablero& t, banderitas& b, jugadas& j, pos& pes2, pos& p){
    int i = 0; //O(1)
    bool siHay = false; //O(1)
    while (i < j.size() && !siHay){ //O(j) donde j es j.size()
        if (j[i].second == 2 ){ //O(1)
            pos x = j[i].first; //O(1)
            int x_0 = x.first; //O(1)
            int x_1 = x.second; //O(1)
            pos a; //O(1)
            a.first = x_0; //O(1)
            a.second = x_1 -1; //O(1)
            pos c; //O(1)
            c.first = x_0; //O(1)
            c.second = x_1 +1; //O(1)
            if (esJugada(a,j) && esJugada(c,j)) { //O(j) donde j es j.size()
                if (minasAdyacentes(t, a) == 1 && minasAdyacentes(t, c) == 1){ //O(1)
                    if (libertadHorizontal (t, b, j, x, p)){ //O(b)+O(j)
                        siHay = true; //O(1)
                        pes2 = x; //O(1)
                    }
                }
            }
        }
        i++; //O(1)
    }
    return siHay; //O(1)
}
//complejidad temporal: O(j)*(O(1)+O(j)+O(1)+O(b)+O(j)) ∈ O(j²) + O(j)*O(b)
//esta función busca en la lista de jugadas, una posición que tenga 2 bombas adyacentes. Una vez que la encuentra, busca
// que las dos posiciones que comparten la fila pero se encuentran en distintas columnas (una está en la columna anterior
//y la otra en la siguiente al 2) estén en la lista de jugadas y tengan solo 1 bomba adyacente. Definimos a estas dos posiciones
//como "a" y "c". con la posicion del 2, ejecutamos libertadHorizontal. Si en libertadHorizontal encontramos una posición
//sugerible, cambiamos pes2 por x, y hacemos que el bool que se devuelve sea true.
//Cabe aclarar que nuestra función se queda con el primer 121 (con una posición jugable adyacente al 2) que encuentra.


bool libertadHorizontal (tablero& t,banderitas& b,jugadas& j,pos x, pos& p) {
    int i = -1; //O(1)
    bool res = false; //O(1)
    while (i <= 1 && !res) { //O(1)
        pos z; //O(1)
        z.first = x.first + i; //O(1)
        z.second = x.second; //O(1)
        if (coordenadaValida(z.first, t.size()) && coordenadaValida(z.second, t.size()) && !t[z.first][z.second]) { //O(1)
            if (!esBanderita(z, b)){ //O(b) donde b es b.size()
                if (!esJugada(z, j)){ //O(j) donde j es j.size()
                    p = z; //O(1)
                    res = true; //O(1)
                }
            }
        }
        i=i+2; //O(1)
    }
    return  res; //O(1)
}
//complejidad temporal: O(1)*(O(1)+O(b)+O(j)) ∈ O(b) + O(j)
//Esta función se fija si, para un 121 horizontal, existe alguna posicion jugable (que no haya estado jugada, que no sea
// una bomba, y que no sea una banderita) que esté en la misma columna que el 2 del 121 pero en la fila anterior o siguiente
// (que sea adyacente). Para hacer esto, definimos un numero i que en el inicio es -1, y una posición z en la misma columna
//que la posición ingresada pero distinta fila (la fila se calcula sumando "i" a la fila de la posición ingresada). Luego,
//al terminar la primera ejecución de este ciclo, se le suma 2 a i, de manera que i= 1. El ciclo deja de ejecutarse cuando
// se encuentra una posición jugable (de manera tal que el booleano res sea true) o cuando i es mayor a 1.

//Nosotros antes habíamos tenido errores con los tests de la cursada en este ejercicio porque considerábamos también
// sugeribles a las posiciones que compartían un vértice (o lado) con los 1s del 121.

bool hay121VerticalLibre(tablero& t, banderitas& b, jugadas& j, pos& pes2, pos& p){
    int i = 0; //O(1)
    bool siHay = false; //O(1)
    while (i < j.size() && !siHay){ //O(j) donde j es j.size()
        if (j[i].second == 2 ){ //O(1)
            pos x = j[i].first; //O(1)
            int x_0 = x.first; //O(1)
            int x_1 = x.second; //O(1)
            pos a; //O(1)
            a.first = x_0 -1; //O(1)
            a.second = x_1 ; //O(1)
            pos c; //O(1)
            c.first = x_0 + 1; //O(1)
            c.second = x_1 ; //O(1)
            if (esJugada(a,j) && esJugada(c,j)) { //O(j)
                if (minasAdyacentes(t, a) == 1 && minasAdyacentes(t, c) == 1){ //O(1)
                    if (libertadVertical(t, b, j, x, p)){ //O(b) + O(j)
                        siHay = true; //O(1)
                        pes2 = x; //O(1)
                    }
                }
            }
        }
        i++; //O(1)
    }
    return siHay; //O(1)
}
//comnplejidad temporal: O(j)*(O(1)+O(j)+O(1)+O(b)+O(j)) ∈ O(j²) + O(j)*O(b)

//esta función busca en la lista de jugadas, una posición que tenga 2 bombas adyacentes. Una vez que la encuentra, busca
// que las dos posiciones que comparten la columna pero se encuentran en distintas filas (una está en la fila anterior
//y la otra en la siguiente al 2) estén en la lista de jugadas y tengan solo 1 bomba adyacente. Definimos a estas dos posiciones
//como "a" y "c". Con la posicion del 2, ejecutamos libertadVertical. Si en libertadVertical encontramos una posición
//sugerible, cambiamos pes2 por x, y hacemos que el bool que se devuelve sea true.
//Cabe aclarar que nuestra función se queda con el primer 121 (con una posición jugable adyacente al 2) que encuentra.

bool libertadVertical (tablero& t,banderitas& b,jugadas& j,pos x, pos& p) {
    int k = - 1; //O(1)
    bool res = false; //O(1)
    while (k <= 1 && !res) { //O(1)
        pos z; //O(1)
        z.first = x.first; //O(1)
        z.second = x.second + k; //O(1)
        if (coordenadaValida(z.first, t.size()) && coordenadaValida(z.second, t.size()) && !t[z.first][z.second]) { //O(1)
            if (!esBanderita(z, b)){ //O(b) donde b es b.size()
                if (!esJugada(z, j)){ //O(j) donde j es j.size()
                    p = z; //O(1)
                    res = true; //O(1)
                }
            }
        }
        k = k + 2; //O(1)
    }
    return  res; //O(1)
}
//complejidad temporal: O(1)*(O(1)+O(b)+O(j)) ∈ O(b) + O(j)

//Esta función se fija si, para un 121 vertical, existe alguna posicion jugable (que no haya estado jugada, que no sea
// una bomba, y que no sea una banderita) que esté en la misma fila que el 2 del 121 pero en la columna anterior o siguiente
// (que sea adyacente). Para hacer esto, definimos un numero i que en el inicio es -1, y una posición z en la misma fila
//que la posición ingresada pero distinta columna (la columna se calcula sumando "i" a la columna de la posición ingresada).
// Luego, al terminar la primera ejecución de este ciclo, se le suma 2 a i, de manera que i= 1. El ciclo deja de ejecutarse
// cuando se encuentra una posición jugable (de manera tal que el booleano res sea true) o cuando i es mayor a 1.

//Nosotros antes habíamos tenido errores con los tests de la cursada en este ejercicio porque considerábamos también
// sugeribles a las posiciones que compartían un vértice (o lado) con los 1s del 121.
