#!/usr/bin/env python
# -*- coding: utf-8 -*- 

"""
 Fuente: http://youtu.be/mdTeqiWyFnc
"""
from __future__ import print_function
import sys
import pygame
from imggrid import ImageGrid

# default params
PIECESIZE = 128
DEFAULT_SPEED = 500

class Screen(object):
    def __init__(self, name, width, height, piecesize=PIECESIZE):
        self.PIECESIZE = piecesize
        self.WIDTH = width
        self.HEIGHT = height
        self.WINDOW_SIZE = [self.PIECESIZE*self.WIDTH, self.PIECESIZE*self.HEIGHT]
        self.screen = pygame.display.set_mode(self.WINDOW_SIZE)
        pygame.display.set_caption("Ejercicio 3")
 
    def draw(self, grid):
        for y in range(self.HEIGHT):
            for x in range(self.WIDTH):
                p = grid.get(y, x)
                self.screen.blit(p, [x*self.PIECESIZE, y*self.PIECESIZE])

def usage():
    print("""Uso:

    {0} --generate archivotxt imagen ancho alto pasos [velocidad]
o bien:
    {0} archivotxt imagen [velocidad]

Si es especifica --generate, el programa generará una nueva instancia de rompecabezas de manera aleatoria. En otro caso, resolverá el rompecabezas indicado por archivotxt.

* imagen: indica el nombre de una imagen a rearmar en el rompecabezas.
* velocidad: opcional, solo para modo resolución, indica cuántos pasos se realizan por segundo (default: 500).
* ancho: solo para --generate indica el ancho en bloques del rompecabezas.
* alto: solo para --generate, indica el alto en bloques del rompecabezas.
* pasos: solo para --generate, indica la cantidad de pasos aleatorios utilizados en la generación del nuevo rompecabezas.
""".format(sys.argv[0]))

def runLoop():
    n = 0
    try:
        while not grid.solve(n):
            n += 1
        while True:
            grid.redraw()
    except StopIteration:
        pass

pygame.init()

name = "Ejercicio 3"

try:
    generate = False
    if '--generate' in sys.argv[1:]:
        sys.argv.pop(sys.argv.index('--generate'))
        generate = True

    fn = sys.argv[1]
    pic = sys.argv[2]

    if generate:
        width = int(sys.argv[3])
        height = int(sys.argv[4])
        steps = int(sys.argv[5])
        try:
            speed = int(sys.argv[6])
        except:
            speed = DEFAULT_SPEED
        screen = Screen(name, width, height)
        grid = ImageGrid(
                width=width,
                height=height,
                piecesize=PIECESIZE,
                speed=speed,
                draw=screen.draw)
        grid.initImg(pic)
        grid.shuffle(steps)
        grid.save(fn)
    else:
        try:
            speed = int(sys.argv[3])
        except:
            speed = DEFAULT_SPEED
        grid = ImageGrid(speed=speed,
                piecesize=PIECESIZE)
        grid.initGrid(fn)
        width = grid.width
        height = grid.height
        screen = Screen(name, width, height)
        grid.setDraw(screen.draw)
        grid.initImg(pic)
        runLoop()
except IndexError:
    usage()
    raise
except IOError as e:
    print("Error procesando archivo:", e)
    sys.exit(1)

pygame.quit()
