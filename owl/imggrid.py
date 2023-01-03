import pygame
import random

from slidingpuzzle import Rompecabezas

# para usar xrange/range independientemente de cual esta disponible en la version de python en uso
try:
    xrange(10)
except:
    pass
else:
    range = xrange

UP, LEFT, DOWN, RIGHT = 0, 1, 2, 3

WHITE = (255, 255, 255)

class EmptyBlock(object):
    def __init__(self, sizex, sizey):
        self.sizex, self.sizey = sizex, sizey

        self.block = pygame.Surface((sizex, sizey))
        self.block.fill(WHITE)

    def get(self):
        return self.block

class ImageGrid(object):
    def __init__(self, width=4, height=4, piecesize=128, speed=500, draw=None):
        self.width = width
        self.height = height
        self.piecesize = piecesize
        self.draw = draw
        self.speed = speed
        self.clock = pygame.time.Clock()
        self.grid = Rompecabezas(self.width, self.height, parent=self)
        self.empty = EmptyBlock(self.piecesize, self.piecesize)

    def initGrid(self, fn):
        self.grid = Rompecabezas(self.width, self.height, parent=self)
        self.grid.cargar(fn)
        self.width = self.grid.ancho()
        self.height = self.grid.alto()

    def initImg(self, imgfn):
        img = pygame.image.load(imgfn)
        self.img = pygame.transform.smoothscale(img, (self.width*self.piecesize, self.height*self.piecesize))
        self.tiles = []
        for y in range(self.height):
            for x in range(self.width):
                start_x = x*self.piecesize
                size_x = self.piecesize
                start_y = y*self.piecesize
                size_y = self.piecesize
                subsurf = self.img.subsurface([start_x, start_y, size_x, size_y]).copy()
                pygame.draw.rect(subsurf, WHITE, (0, 0, self.piecesize, self.piecesize), 2)
                self.tiles.append(subsurf)
        self.tiles[-1] = self.empty.get()
    
    def getTile(self, n):
        return self.tiles[int(n)-1] if n != ' ' else self.tiles[-1]

    def get(self, i, j):
        return self.getTile(self.grid.get(i, j))

    def move(self, direction):
        self.grid.mover(direction)

    def shuffle(self, n=15):
        for i in range(n):
            direction = random.randint(0, 3)
            self.move(direction)

    def save(self, fn):
        self.grid.guardar(fn)

    def solve(self, n):
        return self.grid.resolver(n)

    def setDraw(self, fn):
        self.draw = fn

    def redraw(self):
        self.draw(self)
        self.clock.tick(self.speed)
        pygame.display.flip()

        for event in pygame.event.get():  # User did something
            if event.type == pygame.QUIT or event.type == pygame.MOUSEBUTTONDOWN:  # If user clicked close
                raise StopIteration()  # Flag that we are done so we exit this loop
 
