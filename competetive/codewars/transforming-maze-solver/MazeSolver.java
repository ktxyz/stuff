import java.util.*;


public class MazeSolver {
    final private char[] dir_char = {'N', 'E', 'S', 'W'};
    final private int[] dir_x = {0, 1, 0, -1};
    final private int[] dir_y = {-1, 0, 1, 0};
    final private int[] dir_masks = {8, 1, 2, 4};
    private final int[][][] mazes;
    private int[][][] distance;
    private final int width;
    private final int height;
    private int start_x, start_y;
    private int end_x, end_y;

    private class Node implements Comparable<Node> {
        int x, y, m;

        // previous node
        Node prev;

        int cost;
        char move;

        Node(int x, int y, int m, char move, Node prev, int edge_cost) {
            this.x = x;
            this.y = y;
            this.m = m;
            this.move = move;
            this.prev = prev;

            if (this.prev != null) {
                this.cost = this.prev.cost + edge_cost;
            } else {
                this.cost = edge_cost;
            }
        }
        @Override
        public int compareTo(Node o) {
            return this.cost - o.cost;
        }
    };

    public MazeSolver(int[][] maze) {
        mazes = new int[4][maze.length][maze[0].length];
        distance = new int[4][maze.length][maze[0].length];

        height = maze.length;
        width = maze[0].length;
        mazes[0] = maze;

        for(int y = 0; y < height; ++y) {
            for(int x = 0; x < width; ++x) {
                distance[0][y][x] = Integer.MAX_VALUE;
                if (mazes[0][y][x] == -1) {
                    start_x = x;
                    start_y = y;
                    mazes[0][y][x] = 0;
                } else if (mazes[0][y][x] == -2) {
                    end_x = x;
                    end_y = y;
                    mazes[0][y][x] = 0;
                }

                for (int m = 1; m < 4; ++m) {
                    distance[m][y][x] = Integer.MAX_VALUE;
                    int old_val = mazes[m - 1][y][x];
                    int new_val = 0;
                    for (int i = 0; i < 4; ++i) {
                        if ((old_val & dir_masks[i]) != 0) {
                            new_val |= dir_masks[(i + 1) % 4];
                        }
                    }
                    mazes[m][y][x] = new_val;
                }
            }
        }
    }

    public void PrintMazes() {
        for(int m = 0; m < 4; ++m) {
            System.out.println("Maze " + m);
            for(int y = 0; y < height; ++y) {
                for(int x = 0; x < width; ++x) {
                    System.out.print(mazes[m][y][x] + " ");
                }
                System.out.println();
            }
            System.out.println();
        }
    }

    private List<String> GetSolution(Node node) {
        StringBuilder sb = new StringBuilder();
        while (node.prev != null) {
            sb.append(node.move);
            node = node.prev;
        }

        String[] arr = sb.reverse().toString().split("X");
        return new ArrayList<>(Arrays.asList(arr));
    }

    public List<String> solve() {
        distance[0][start_y][start_x] = 0;
        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.add(new Node(start_x, start_y, 0, 'X', null, 0));

        while (!pq.isEmpty()) {
            var node = pq.poll();

            if (node.cost > distance[node.m][node.y][node.x]) {
                continue;
            }

            if (node.x == end_x && node.y == end_y) {
                return GetSolution(node);
            }

            if (distance[(node.m + 1) % 4][node.y][node.x] > node.cost + 1) {
                distance[(node.m + 1) % 4][node.y][node.x] = node.cost + 1;
                pq.add(new Node(node.x, node.y, (node.m + 1) % 4, 'X', node, 1));
            }

            for (int dir = 0; dir < 4; ++dir) {
                int nx = node.x + dir_x[dir];
                int ny = node.y + dir_y[dir];
                int nm = node.m;

                if (nx < 0 || nx >= width || ny < 0 || ny >= height) {
                    continue;
                }

                if ((mazes[node.m][node.y][node.x] & dir_masks[dir] | mazes[node.m][ny][nx] & dir_masks[(dir + 2) % 4]) != 0) {
                    continue;
                }

                if (distance[nm][ny][nx] > node.cost) {
                    distance[nm][ny][nx] = node.cost;
                    pq.add(new Node(nx, ny, nm, dir_char[dir], node, 0));
                }
            }
        }

        return null;
    }
}

