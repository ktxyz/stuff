from enum import StrEnum

class Go:
    class Coords:
        def __init__(self, move):
            self.y = int(move[:-1])
            self.x = ord(move[-1]) - ord('A') - (1 if ord(move[-1]) >= ord('I') else 0)

    class Player(StrEnum):
        BLACK = 'black'
        WHITE = 'white'

    class PlayerStone(StrEnum):
        BLACK = 'x'
        WHITE = 'o'

    class Board:
        class Cell:
            def __init__(self, x, y):
                self.x = x
                self.y = y
                self.values = [('.', 0)]

            def set_value(self, value, time):
                self.values.append((value, time))
            
            def revert(self, to_time):
                while len(self.values) > 1 and self.values[-1][1] > to_time:
                    self.values.pop()

            def get_value(self):
                return self.values[-1][0]

        def __init__(self, width, height):
            self.width = width
            self.height = height

            self.cells = [[self.Cell(x, self.height - y) for x in range(width)] for y in range(height)]
            self.states = [self._gen_board()]

        def commit(self, override=False):
            if override:
                self.states = [self._gen_board()]
            else:
                self.states.append(self._gen_board())
            return self.states[-1]

        def _gen_board(self):
            return [[self.get_position(x, y).get_value() for x in range(self.width)] for y in range(1, self.height + 1)][::-1]

        def revert(self, time):
            for row in self.cells:
                for cell in row:
                    cell.revert(time)
            self.states = self.states[:time] + [self._gen_board()]
            return self.states[-1]

        def set_value(self, x, y, value, time):
            self.cells[self.height - y][x].set_value(value, time)

        def get_position(self, x, y):
            return self.cells[self.height - y][x]
        
        def _get_captured_stones(self, stone_type):
            # Connected components with flood fill
            captured_stones = []

            repr = dict([((y, x), (y, x)) for x in range(self.width) for y in range(self.height)])
            liberties = [[set() for x in range(self.width)] for y in range(self.height)]

            def find_repr(pos):
                if repr[pos] != pos:
                    repr[pos] = find_repr(repr[pos])
                return repr[pos]
            
            def union_repr(pos1, pos2):
                pos1 = find_repr(pos1)
                pos2 = find_repr(pos2)

                if pos1 == pos2:
                    return
                
                repr[pos1] = pos2
                liberties[pos2[0]][pos2[1]] |= liberties[pos1[0]][pos1[1]]

            # flood fill
            dx = [0, 1, 0, -1]
            dy = [1, 0, -1, 0]
            for y in range(self.height):
                for x in range(self.width):
                    if self.cells[y][x].get_value() != stone_type.value:
                        continue
                    for i in range(4):
                        nx = x + dx[i]
                        ny = y + dy[i]
                        if not (0 <= nx < self.width and 0 <= ny < self.height):
                            continue
                        if self.cells[ny][nx].get_value() == stone_type.value:
                            union_repr((y, x), (ny, nx))
                        elif self.cells[ny][nx].get_value() == '.':
                            ry, rx = find_repr((y, x))
                            liberties[ry][rx].add((ny, nx))

            for y in range(self.height):
                for x in range(self.width):
                    if self.cells[y][x].get_value() == stone_type.value:
                        ry, rx = find_repr((y, x))
                        if not liberties[ry][rx]:
                            captured_stones.append(self.cells[y][x])

            return captured_stones
        
        def is_valid(self, player, time):
            opponent_captured_stones = self._get_captured_stones(Go.PlayerStone.WHITE if player == Go.Player.BLACK else Go.PlayerStone.BLACK)
            for stone in opponent_captured_stones:
                stone.set_value('.', time)
            
            self_captured_stones = self._get_captured_stones(Go.PlayerStone.BLACK if player == Go.Player.BLACK else Go.PlayerStone.WHITE)
            if self_captured_stones and not opponent_captured_stones:
                return False
            
            # KO rule
            current_state = self._gen_board()

            if len(self.states) > 1 and current_state == self.states[-2]:
                return False
            else:
                self.states.append(current_state)
            
            return True
    
    def __init__(self, height, width=None):
        if width is None:
            width = height
        if not (0 < width < 25 and 0 < height < 25):
            raise ValueError("Board size must be less than 25 and greater than 0")
        
        self.size = {'height': height, 'width': width}
        
        self.width = width
        self.height = height
        
        self.reset()
    
    def _init_board(self):
        self.go_board = self.Board(self.width, self.height)
        self.board = self.go_board.states[-1]

    def _init_state(self):
        self.time = 0
        self.handicaped = False
        self._update_player()

    def get_position(self, pos):
        coords = self.Coords(pos)
        if not (0 <= coords.x < self.width and 0 < coords.y <= self.height):
            raise ValueError("Position out of board")
        return self.go_board.get_position(coords.x, coords.y).get_value()
    
    def reset(self):
        self._init_board()
        self._init_state()
    
    def _update_player(self):
        self.player = self.Player.BLACK if self.time % 2 == 0 else self.Player.WHITE
        self.turn = self.player.value

    def pass_turn(self):
        self.time += 1
        self._update_player()
    
    def move(self, *moves):
        for move in moves:
            coords = self.Coords(move)

            if not (0 <= coords.x < self.width and 0 < coords.y <= self.height):
                raise ValueError("Position out of board")
            
            if self.go_board.get_position(coords.x, coords.y).get_value() != '.': 
                raise ValueError("Position already occupied")
            
            self.go_board.set_value(coords.x, coords.y, self.PlayerStone.BLACK.value if self.player == self.Player.BLACK else self.PlayerStone.WHITE.value, self.time + 1)
            self.pass_turn()
            
            if not self.go_board.is_valid(self.Player.BLACK if self.player == self.Player.WHITE else self.Player.WHITE, self.time):
                self.rollback(1)
                raise ValueError("Invalid move")
            else:
                self.board = self.go_board.states[-1]

    def rollback(self, time):
        if self.time == 0 or self.time - time < 0:
            raise ValueError("Cannot rollback")
        
        self.time = self.time - time
        self.board = self.go_board.revert(self.time)
        self._update_player()
    
    def handicap_stones(self, stone_count):
        if self.handicaped:
            raise ValueError("Handicap stones already placed")
        if self.time > 0:
            raise ValueError("Handicap stones only available at the beginning of the game")
        valid_sizes = [9, 13, 19]
        if self.width not in valid_sizes or self.height not in valid_sizes or self.width != self.height:
            raise ValueError("Handicap stones only available for square board with size 9, 13, or 19")
        
        if stone_count == 0:
            return

        if self.width == 9 and stone_count > 5:
            raise ValueError("Handicap stones only available for 2 to 5 stones")
        if stone_count > 9:
            raise ValueError("Handicap stones only available for 2 to 9 stones")
        
        self.handicaped = True

        coordinates = [
            ["7G", "3C", "3G", "7C", "5E"],       # For 9x9 board
            ["10K", "4D", "4K", "10D", "7G", "7D", "7K", "10G", "4G"],       # For 13x13 board
            ["16Q", "4D", "4Q", "16D", "10K", "10D", "10Q", "16K", "4K"]     # For 19x19 board
        ]

        for coordinate in coordinates[valid_sizes.index(self.width)][:stone_count]:
            coords = self.Coords(coordinate)
            self.go_board.set_value(coords.x, coords.y, self.PlayerStone.BLACK.value, self.time)
        self.board = self.go_board.commit(True)
