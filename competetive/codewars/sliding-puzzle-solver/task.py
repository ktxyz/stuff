from queue import Queue, PriorityQueue, deque
from debug import ShowBoard


def is_puzzle_solvable(puzzle):
    flattened = [elem for row in puzzle for elem in row]

    inversions = 0
    N = len(flattened)
    for i in range(N - 1):
        for j in range(i + 1, N):
            if flattened[i] != 0 and flattened[j] != 0 and flattened[i] > flattened[j]:
                inversions += 1

    blank_row = 0
    for i in range(N):
        if flattened[i] == 0:
            blank_row = (N - i - 1) // len(puzzle[0])
            break

    if N % 2 == 1:
        return inversions % 2 == 0
    else:
        return (blank_row + inversions) % 2 == 0


def get_value_at(size, x, y):
    return y * size + x + 1


def get_x_y(size, value):
    value -= 1
    return value % size, value // size


def create_maze(puzzle, frozen, value, target_x, target_y):
    maze = [["." for _ in range(len(puzzle[0]))] for _ in range(len(puzzle))]
    if not frozen:
        frozen = [[False for _ in range(len(puzzle[0]))] for _ in range(len(puzzle))]
    for y in range(len(puzzle)):
        for x in range(len(puzzle[0])):
            if puzzle[y][x] == value:
                maze[y][x] = "B"
            elif frozen[y][x]:
                maze[y][x] = "X"
            elif puzzle[y][x] == 0:
                maze[y][x] = "S"
    return maze


class Node:
    DIR_STR = ["N", "E", "S", "W"]
    DIR = [(0, -1), (1, 0), (0, 1), (-1, 0)]

    def __init__(self, value_x, value_y, zero_x, zero_y, move=None, parent=None):
        self.value_x = value_x
        self.value_y = value_y
        self.zero_x = zero_x
        self.zero_y = zero_y
        self.move = move
        self.parent = parent

    def __lte__(self, other):
        return (
            self.value_x == other.value_x
            and self.value_y == other.value_y
            and self.zero_x == other.zero_x
            and self.zero_y == other.zero_y
        )


def solve_zero(maze, parent_node, target_x, target_y):
    N = len(maze)
    visited = [[False for _ in range(N)] for _ in range(N)]

    visited[parent_node.zero_y][parent_node.zero_x] = True

    queue = deque()
    queue.append(parent_node)

    while queue:
        node = queue.popleft()

        if node.zero_x == target_x and node.zero_y == target_y:
            return node

        for k in range(len(Node.DIR)):
            dx, dy = Node.DIR[k]
            new_x, new_y = node.zero_x + dx, node.zero_y + dy
            if new_x < 0 or new_x >= len(maze[0]) or new_y < 0 or new_y >= len(maze):
                continue
            if new_x == node.value_x and new_y == node.value_y:
                continue
            if maze[new_y][new_x] == "X" or maze[new_y][new_x] == "B":
                continue
            if visited[new_y][new_x]:
                continue

            visited[new_y][new_x] = True
            queue.append(
                Node(
                    node.value_x, node.value_y, new_x, new_y, (k, Node.DIR_STR[k]), node
                )
            )

    return None


def get_current_position(puzzle, value):
    for y in range(len(puzzle)):
        for x in range(len(puzzle[0])):
            if puzzle[y][x] == value:
                return x, y
    return None


def solve_value(maze, target_x, target_y):
    N = len(maze)
    for y in range(N):
        for x in range(N):
            if maze[y][x] == "B":
                start_x, start_y = x, y
            if maze[y][x] == "S":
                zero_x, zero_y = x, y

    visited = [[False for _ in range(N)] for _ in range(N)]
    visited[start_y][start_x] = True
    queue = deque()
    queue.append(Node(start_x, start_y, zero_x, zero_y))

    while queue:
        node = queue.popleft()

        if node.value_x == target_x and node.value_y == target_y:
            path = []
            while node.parent:
                path.append(node.move)
                node = node.parent
            return path[::-1]

        for k in range(len(Node.DIR)):
            dx, dy = Node.DIR[k]
            new_x, new_y = node.value_x + dx, node.value_y + dy
            if new_x < 0 or new_x >= N or new_y < 0 or new_y >= N:
                continue
            if maze[new_y][new_x] == "X":
                continue
            if visited[new_y][new_x]:
                continue

            zero_node = solve_zero(maze, node, new_x, new_y)
            if not zero_node:
                continue
            visited[new_y][new_x] = True

            queue.append(
                Node(
                    new_x,
                    new_y,
                    node.value_x,
                    node.value_y,
                    ((k + 2) % 4, Node.DIR_STR[(k + 2) % 4]),
                    zero_node,
                )
            )

    return None


def solve_manually(puzzle, offset_x, offset_y):
    print(puzzle, offset_x, offset_y)

    class ANode:
        def __init__(self, zx, zy, cost, moves, puzzle):
            self.moves = moves
            self.puzzle = [row.copy() for row in puzzle]
            self.zx = zx
            self.zy = zy
            self.cost = cost
            self.price = self._calc_heur() + self.cost
            self.hash = self._calc_hash()

        def _calc_hash(self):
            return hash(self.puzzle.__str__() + str(self.zx) + str(self.zy))

        def _calc_heur(self):
            N = len(self.puzzle)
            M = len(self.puzzle[0])
            h = 0
            for y in range(N):
                for x in range(M):
                    if self.puzzle[y][x] == 0:
                        continue
                    vx, vy = get_x_y(N + offset_y, self.puzzle[y][x])
                    off_x = offset_x + x
                    off_y = offset_y + y
                    h += abs(vx - off_x) + abs(vy - off_y)
            return h

        def __lt__(self, other):
            return self.price < other.price

    N = len(puzzle)
    M = len(puzzle[0])
    for y in range(N):
        for x in range(M):
            if puzzle[y][x] == 0:
                zx, zy = x, y
                break

    PQ = PriorityQueue()
    PQ.put(ANode(zx, zy, 0, [], puzzle))
    visited = set()
    visited.add(PQ.queue[0].hash)

    while not PQ.empty():
        node = PQ.get()

        if node._calc_heur() == 0:
            return node.moves

        for k in range(len(Node.DIR)):
            dx, dy = Node.DIR[k]
            new_x, new_y = node.zx + dx, node.zy + dy
            if new_x < 0 or new_x >= M or new_y < 0 or new_y >= N:
                continue

            new_puzzle = [row.copy() for row in node.puzzle]
            new_puzzle[new_y][new_x], new_puzzle[node.zy][node.zx] = (
                new_puzzle[node.zy][node.zx],
                new_puzzle[new_y][new_x],
            )
            new_node = ANode(
                new_x,
                new_y,
                node.cost + 1,
                node.moves + [(k, Node.DIR_STR[k])],
                new_puzzle,
            )
            if new_node.hash in visited:
                continue
            visited.add(new_node.hash)
            PQ.put(new_node)
    return None


class SolveRequest:
    def __init__(self, value, target_x, target_y, froze_add=[], froze_remove=[]):
        self.value = value
        self.target_x = target_x
        self.target_y = target_y
        self.froze_add = froze_add
        self.froze_remove = froze_remove


def recover_values(puzzle, moves):
    N = len(puzzle)
    values = []
    for move in moves:
        dx, dy = Node.DIR[move[0]]
        for y in range(N):
            for x in range(N):
                if puzzle[y][x] == 0:
                    vx, vy = x, y
                    break
        values.append(puzzle[vy + dy][vx + dx])
        puzzle[vy][vx], puzzle[vy + dy][vx + dx] = (
            puzzle[vy + dy][vx + dx],
            puzzle[vy][vx],
        )
    return values


def slide_puzzle(original_puzzle):
    puzzle = original_puzzle.copy()

    if not is_puzzle_solvable(puzzle):
        print("Puzzle is not solvable")
        return None
    print("Solving puzzle:")
    print(puzzle)

    N = len(puzzle)
    solve_requests = []
    for k in range(N - 2):
        # row then column
        for x in range(k, N - 2):
            solve_requests.append(SolveRequest(get_value_at(N, x, k), x, k, [(x, k)]))
        # move last piece to far away row
        solve_requests.append(SolveRequest(get_value_at(N, N - 1, k), N - 1, N - 1))
        # move second last piece to last column in row
        solve_requests.append(
            SolveRequest(get_value_at(N, N - 2, k), N - 1, k, [(N - 1, k)])
        )
        # move last piece below it
        solve_requests.append(
            SolveRequest(
                get_value_at(N, N - 1, k), N - 1, k + 1, [(N - 1, k + 1)], [(N - 1, k)]
            )
        )
        # move second last piece to its place
        solve_requests.append(
            SolveRequest(
                get_value_at(N, N - 2, k), N - 2, k, [(N - 2, k)], [(N - 1, k + 1)]
            )
        )
        # move last piece to its place
        solve_requests.append(
            SolveRequest(get_value_at(N, N - 1, k), N - 1, k, [(N - 1, k)])
        )

        for y in range(k + 1, N - 2):
            solve_requests.append(SolveRequest(get_value_at(N, k, y), k, y, [(k, y)]))
        # move last piece to far away column
        solve_requests.append(SolveRequest(get_value_at(N, k, N - 1), N - 1, k + 1))
        # move second to last piece on last row
        solve_requests.append(
            SolveRequest(get_value_at(N, k, N - 2), k, N - 1, [(k, N - 1)])
        )
        # move last piece before it
        solve_requests.append(
            SolveRequest(
                get_value_at(N, k, N - 1), k + 1, N - 1, [(k + 1, N - 1)], [(k, N - 1)]
            )
        )
        # move second to last piece to correct place
        solve_requests.append(
            SolveRequest(
                get_value_at(N, k, N - 2), k, N - 2, [(k, N - 2)], [(k + 1, N - 1)]
            )
        )
        # move last piece to correct place
        solve_requests.append(
            SolveRequest(get_value_at(N, k, N - 1), k, N - 1, [(k, N - 1)])
        )

    frozen = [[False for _ in range(N)] for _ in range(N)]
    full_path = []
    for target in solve_requests:
        value, target_x, target_y = target.value, target.target_x, target.target_y

        t_x, t_y = get_x_y(N, value)
        if (t_x >= N - 3) and (t_y >= N - 2):
            print("We got to 3x2 area, solving manually")
            break

        if get_current_position(puzzle, value) == (target_x, target_y):
            for x, y in target.froze_add:
                frozen[y][x] = True
            for x, y in target.froze_remove:
                frozen[y][x] = False
            continue

        maze = create_maze(puzzle, frozen, value, target_x, target_y)

        path = solve_value(maze, target_x, target_y)
        if path is None:
            return None

        visualized = [row.copy() for row in puzzle]
        full_path.extend(path)
        for m in path:
            dx, dy = Node.DIR[m[0]]
            for y in range(N):
                for x in range(N):
                    if visualized[y][x] == 0:
                        vx, vy = x, y
                        break
            visualized[vy][vx], visualized[vy + dy][vx + dx] = (
                visualized[vy + dy][vx + dx],
                visualized[vy][vx],
            )
            ShowBoard([visualized, visualized])

        puzzle = visualized.copy()
        for x, y in target.froze_add:
            frozen[y][x] = True
        for x, y in target.froze_remove:
            frozen[y][x] = False

    print("Finishing manually")
    manual_path = solve_manually(
        [row.copy()[N - 3 :] for row in puzzle[N - 2 :]], N - 3, N - 2
    )
    if manual_path is None:
        print("Manual failed")
        return None
    for m in manual_path:
        dx, dy = Node.DIR[m[0]]
        for y in range(N):
            for x in range(N):
                if visualized[y][x] == 0:
                    vx, vy = x, y
                    break
        visualized[vy][vx], visualized[vy + dy][vx + dx] = (
            visualized[vy + dy][vx + dx],
            visualized[vy][vx],
        )
        ShowBoard([visualized, visualized])
    full_path.extend(manual_path)
    print("Recovering values")
    values = recover_values([row.copy() for row in original_puzzle], full_path)
    return values
