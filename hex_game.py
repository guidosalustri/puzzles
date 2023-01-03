class Node:
    def __init__(self,r,c,tile):
        self.pos=(r,c)
        self.tile=tile
        self.contacts=[(1,-1),(1,0),(0,-1),(0,1),(-1,0),(-1,1)]
        self.finish_path=False


class ConnectGame:  

    def __init__(self, board):
        hexboard=[[Node(y,x, char)for x, char in enumerate(line.replace(' ', ''))] for y, line in enumerate(board.splitlines())]
        hexboardx=[[Node(x,y, char)for x, char in enumerate(line.replace(' ', ''))] for y, line in enumerate(board.splitlines())]
        self.board=hexboard
        hexboardx=list(zip(*hexboardx))
        self.boardt=hexboardx

    def get_winner(self):
        w=""
        if len(self.board)==1 and len(self.board[0])==1:
            return self.board[0][0].tile

        if ConnectGame.have_connection(self,self.board,"O"): w="O"
        elif ConnectGame.have_connection(self,self.boardt,"X"): w="X"
        return w

    def have_connection(self,board,player):
        paths=list(board[0])
        for tile in paths :
            if tile.tile==player:
                for contact in tile.contacts:
                    row = tile.pos[0] + contact[0]
                    col = tile.pos[1] + contact[1]
                    if row >= 0 and col >= 0:
                        try:
                            if board[row][col].tile==player:
                                if not board[row][col].finish_path:
                                    paths.append(board[row][col])
                                board[row][col].finish_path=True
                        except IndexError:
                            continue
        end=list(board[len(board)-1])
        for t in end:
            if t.finish_path: return t.finish_path