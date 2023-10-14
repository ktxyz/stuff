#include <stdio.h>
#include <queue>
#include <cstring>
#include <string>
#define MAXN 20

struct State {
    int box_x, box_y;
    int player_x, player_y;
    std::string path;

    State() {
        box_x = box_y = player_x = player_y = 0;
        path = "";
    }
};

char buffer[MAXN + 1][MAXN + 1];
const int dir[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // N, E, S, W
const char u_dir[] = {'N', 'E', 'S', 'W'};
const char l_dir[] = {'n', 'e', 's', 'w'};
State answer_state;
State player_state;
int r, c;

int target_x, target_y;

bool is_valid(int x, int y) {
    return x >= 0 && x < r && y >= 0 && y < c && buffer[x][y] != '#';
}

bool find_player_path(State init_state, int target_x, int target_y) {
    bool visited[MAXN + 1][MAXN + 1] = {false};
    memset(visited, false, sizeof(visited));

    std::queue<State> q;
    init_state.path = "";
    q.push(init_state);
    visited[init_state.box_x][init_state.box_y] = true;
    visited[init_state.player_x][init_state.player_y] = true;

    while (!q.empty()) {
        State state = q.front();
        q.pop();

        if (state.player_x == target_x && state.player_y == target_y) {
            player_state = state;
            return true;
        }

        for (int k = 0; k < 4; ++k) {
            int npx = state.player_x + dir[k][0];
            int npy = state.player_y + dir[k][1];

            if (!is_valid(npx, npy) || visited[npx][npy]) {
                continue;
            }

            visited[npx][npy] = true;

            State new_state;
            new_state.box_x = state.box_x;
            new_state.box_y = state.box_y;
            new_state.player_x = npx;
            new_state.player_y = npy;
            new_state.path = state.path + l_dir[k];

            q.push(new_state);
        }
    }

    return false;
}

bool find_path(State init_state) 
{
    bool visited[MAXN + 1][MAXN + 1] = {false};
    memset(visited, false, sizeof(visited));

    std::queue<State> q;
    q.push(init_state);
    visited[init_state.box_x][init_state.box_y] = true;

    while (!q.empty()) {
        State state = q.front();
        q.pop();

        for (int k = 0; k < 4; ++k) {
            int nbx = state.box_x + dir[k][0];
            int nby = state.box_y + dir[k][1];
            int npx = state.box_x - dir[k][0];
            int npy = state.box_y - dir[k][1];

            if (!is_valid(nbx, nby) || !is_valid(npx, npy) || visited[nbx][nby]) {
                continue;
            }

            if (!find_player_path(state, npx, npy)) {
                continue;
            }
            
            visited[nbx][nby] = true;

            State new_state;
            new_state.box_x = nbx;
            new_state.box_y = nby;
            new_state.player_x = state.box_x;
            new_state.player_y = state.box_y;
            new_state.path = state.path + player_state.path + u_dir[k];

            if (nbx == target_x && nby == target_y) {
                answer_state = new_state;
                return true;
            }

            q.push(new_state);
        }
    }

    return false;
}


int main() {
    int i = 0;
    while(scanf("%d%d", &r, &c) && (r || c)) {
        State init_state;
        for (int i = 0; i < r; i++) {
            scanf("%s\n", buffer[i]);

            for (int j = 0; j < c; ++j) {
                switch (buffer[i][j]) {
                    case 'S':
                        init_state.player_x = i;
                        init_state.player_y = j;
                        break;
                    case 'B':
                        init_state.box_x = i;
                        init_state.box_y = j;
                        break;
                    case 'T':
                        target_x = i;
                        target_y = j;
                        break;
                    default:
                        break;
                }
            }
        }

        // for(int i = 0; i < r; i++) {
        //     printf("%s\n", buffer[i]);
        // }

        // printf("Target: (%d, %d)\n", target_x, target_y);
        // printf("Player: (%d, %d)\n", init_state.player_x, init_state.player_y);
        // printf("Box: (%d, %d)\n", init_state.box_x, init_state.box_y);

        printf("Maze #%d\n", ++i);
        if (!find_path(init_state)) {
            printf("Impossible.\n");
        } else {
            printf("%s\n", answer_state.path.c_str());
        }
        printf("\n");
    }

    return 0;
}