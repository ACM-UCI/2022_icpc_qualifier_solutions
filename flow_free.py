board = [[cell for cell in input().rstrip()] for _ in range(4)]

starts = dict()
colors = list()
for r in range(4):
    for c in range(4):
        col = board[r][c]
        if col != 'W' and col not in starts:
            starts[col] = (r,c)
            colors.append(col)

needed = 16 - 2*len(colors)

# col_index keeps track of the current color we are looking for
# r,c is the current cell search is on
# use_cnt is so we know if we've used all cells on the board
def dfs(col_index, r, c, use_cnt):

    curr_col = colors[col_index]

    for nr,nc in ((r-1,c),(r,c+1),(r+1,c),(r,c-1)):
        if nr < 0 or nc < 0 or nr >= 4 or nc >= 4: # unreachable cell
            continue
        if board[nr][nc] == curr_col and (nr,nc) != starts[curr_col]:
            if col_index+1 == len(colors):
                return use_cnt == needed
            elif dfs(col_index+1, *starts[colors[col_index+1]], use_cnt):
                return True
        elif board[nr][nc] == 'W':
            board[nr][nc] = 'A' # must make cell unreachable so it is not reused
            if dfs(col_index, nr, nc, use_cnt+1):
                return True
            board[nr][nc] = 'W' # search failed so can make cell usable again
    return False

if dfs(0, *starts[colors[0]], 0):
    print('solvable')
else:
    print('not solvable')
