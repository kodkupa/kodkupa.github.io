#!/usr/bin/env python3
# 

def solv():
    board=[]
    for i in range(8):
        board.append(input())
    for x in range(64):
        i=x//8
        j=x%8
        if board[i][j]=='q':
            queenx,queeny=i,j
            break
    #Knight
    for x,y in [(1,2),(2,1),(-1,2),(2,-1),(1,-2),(-2,1),(-1,-2),(-2,-1)]:
        if 0<=x+queenx<=7 and 0<=y+queeny<=7:
            if board[x+queenx][y+queeny]=='N':
                print('YES')
                return
    #Pawn
    if 0<=1+queenx<=7 and 0<=1+queeny<=7:
        if board[1+queenx][1+queeny]=='P':
            print('YES')
            return
    if 0<=1+queenx<=7 and 0<=-1+queeny<=7:
        if board[1+queenx][-1+queeny]=='P':
            print('YES')
            return
    # horizontal/vertical
    for a,b in [(0,1),(1,0),(-1,0),(0,-1)]:
        x,y=queenx,queeny
        for c in range(1,8):
            x+=a
            y+=b
            if 0 <= y < 8 and 0 <= x < 8:
                if board[x][y] !='.':
                    if board[x][y] in ['R','Q']:
                        print('YES')
                        return
                    else:
                        break
            else:
                break
    # diagonal but not Pawns
    for a,b in [(1,1),(1,-1),(-1,1),(-1,-1)]:
        x,y=queenx,queeny
        for c in range(1,8):
            x+=a
            y+=b
            if 0 <= y < 8 and 0 <= x < 8:
                if board[x][y] !='.':
                    if board[x][y] in ['B','Q']:
                        print('YES')
                        return
                    else:
                        break
            else:
                break
    print('NO')



T = int(input().strip())
for _ in range(T):
    solv()
