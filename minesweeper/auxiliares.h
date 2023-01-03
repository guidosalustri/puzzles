
//
// Este archivo contiene las declaraciones de las funciones auxiliares
// que ustedes necesiten implementar. Tienen que coincidir con el código
// de esas mismas funciones, que estará en auxiliares.cpp
//

#pragma once   // esta línea es para que el archivo se incluya una sola vez

#include "definiciones.h"

bool esAdyacenteValida(pos p, int i, int j, tablero& t);
bool coordenadaValida(int c, int n);
void sacaBanderita (pos p, banderitas& b);
void plantaBanderita (pos p, banderitas& b);
bool esBanderita(pos p, banderitas& b);
//void esDescubiertaAuto (pos p, jugadas& j, banderitas& b, tablero& t);
void cumpleCondiciones (vector<jugada>& v, jugadas& j, banderitas& b, tablero& t, int tamano);
bool hay121HorizontalLibre(tablero& t, banderitas& b, jugadas& j, pos& pes2, pos& p);
bool hay121VerticalLibre(tablero& t, banderitas& b, jugadas& j, pos& pes2, pos& p);
bool libertadHorizontal (tablero& t,banderitas& b,jugadas& j,pos x, pos& p);
bool libertadVertical (tablero& t,banderitas& b,jugadas& j,pos x, pos& p);
bool esJugada(pos p, jugadas& j);
