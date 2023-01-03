# -*- coding: utf-8 -*-
from __future__ import print_function
import sys

UP, LEFT, DOWN, RIGHT = 0, 1, 2, 3

class Rompecabezas(object):

	###############################
	# Métodos públicos
	###############################

	def __init__(self, width, height, parent=None):
		self.parent = parent

		self._rompecabezas = []
		self._ancho = width
		self._alto = height
		self._espacio_vacio = (0, 0) # (alto, ancho) == (filas, columnas)


	def update(self):
		if self.parent is not None:
			self.parent.redraw()


	def cargar(self, fn):
		self._rompecabezas = []
		try:
			archivo = open(fn, 'r')
		except IOError:
			raise

		numero_fila = 0

		for fila in archivo.readlines():
			fila = fila.rstrip('\n')
			fila = fila.split('\t')
			for columna in range(len(fila)):
				if fila[columna] == ' ':
					fila[columna] = self._ancho * self._alto
					self._espacio_vacio = (numero_fila, columna)
				else:
					fila[columna] = int(fila[columna])

			self._rompecabezas.append(fila)
			numero_fila += 1

		if len(self._rompecabezas) != self._alto or len(self._rompecabezas[0]) != self._ancho:
			raise IOError("Formato incorrecto de archivo")
		archivo.close()


	def __str__(self):
		# Primero convierto todos los elementos de _rompecabezas a string.
		lista_aux = []
		for fila in self._rompecabezas:
			fila_aux = []

			for elem in fila:
				if elem == self._ancho * self._alto:
					fila_aux.append(' ')
					fila_aux.append('\t')
				else:
					fila_aux.append(str(elem))
					fila_aux.append('\t')

			fila_aux = fila_aux[:-1]
			fila_aux.append('\n')
			lista_aux.append(fila_aux)

		lista_aux = self._unirListas(lista_aux)
		return ''.join(lista_aux)		


	def get(self, i, j):
		return self._rompecabezas[i][j]


	def ancho(self):
		return self._ancho


	def alto(self):
		return self._alto


	def resuelto(self):
		lista_aux = self._unirListas(self._rompecabezas)
		return sorted(lista_aux) == lista_aux

	
	def mover(self, direccion):
		intercambio_realizado = False
		pos = self._espacio_vacio
		# Verifico que sea posible mover el espacio vacío en la dirección especificada previo a realizar
		# el intercambio.
		if direccion == 0 and pos[0]-1 >= 0:
			# Intercambio el espacio vacío con la posición de arriba.
			self._rompecabezas[pos[0]][pos[1]], self._rompecabezas[pos[0]-1][pos[1]] = self._rompecabezas[pos[0]-1][pos[1]], self._rompecabezas[pos[0]][pos[1]]
			self._espacio_vacio = (pos[0]-1, pos[1])
			intercambio_realizado = True

		elif direccion == 1 and pos[1]-1 >= 0:
			self._rompecabezas[pos[0]][pos[1]], self._rompecabezas[pos[0]][pos[1]-1] = self._rompecabezas[pos[0]][pos[1]-1], self._rompecabezas[pos[0]][pos[1]]
			self._espacio_vacio = (pos[0], pos[1]-1)
			intercambio_realizado = True

		elif direccion == 2 and pos[0]+1 < self._alto:
			self._rompecabezas[pos[0]][pos[1]], self._rompecabezas[pos[0]+1][pos[1]] = self._rompecabezas[pos[0]+1][pos[1]], self._rompecabezas[pos[0]][pos[1]]
			self._espacio_vacio = (pos[0]+1, pos[1])
			intercambio_realizado = True

		elif direccion == 3 and pos[1]+1 < self._ancho:
			self._rompecabezas[pos[0]][pos[1]], self._rompecabezas[pos[0]][pos[1]+1] = self._rompecabezas[pos[0]][pos[1]+1], self._rompecabezas[pos[0]][pos[1]]
			self._espacio_vacio = (pos[0], pos[1]+1)
			intercambio_realizado = True

		return intercambio_realizado		


	def guardar(self, fn):
		with open(fn, 'w') as archivo:
			archivo.write(str(self))
		

	def resolver(self, n):
		pos = self._espacio_vacio
		if self.resuelto() and n >= 0:
			return True

		elif n < 0:
			return False

		else:
			if pos[0]-1 >= 0:
				self.mover(UP)
				self.update()
				if self.resolver(n-1):
					return True
				self.mover(DOWN)
				self.update()

			if pos[1]-1 >= 0:
				self.mover(LEFT)
				self.update()
				if self.resolver(n-1):
					return True
				self.mover(RIGHT)
				self.update()

			if pos[0]+1 < self._alto:
				self.mover(DOWN)
				self.update()
				if self.resolver(n-1):
					return True
				self.mover(UP)
				self.update()

			if pos[1]+1 < self._ancho:
				self.mover(RIGHT)
				self.update()
				if self.resolver(n-1):
					return True
				self.mover(LEFT)
				self.update()

			return False

			
	###############################
	# Métodos privados
	###############################

	# Devuelve el resultado de concatenar los elementos de lista_de_listas. 
	def _unirListas(self, lista_de_listas):
		lista_aux = []
		for fila in lista_de_listas:
			lista_aux.extend(fila)
		return lista_aux


if __name__ == '__main__':

	x = Rompecabezas(6, 6)
	x.cargar('puzzle1.txt')
	print(x._rompecabezas)
	print(str(x))
	x.guardar('pruebita.txt')
	# print(x._unirListas(x._rompecabezas))
	# print(x.resuelto())
	# x.resolver(10)
	# print(x._rompecabezas)

