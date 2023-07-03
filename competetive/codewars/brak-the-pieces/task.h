#pragma once

#include "util.h"
#include <string>
#include <limits>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#ifndef DEBUG
    #define DEBUG(x)
#endif


using Pos = std::pair<int, int>;
using Board = std::vector<std::vector<int>>;

int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[] = {1, -1, 0, 0, -1, 1, 1, -1};

struct BoundingBox {
    int top, left, bottom, right;
};

Board fill(const std::vector<std::string> &pieces) {
    Board board;
    for(auto i = 0; i < pieces.size(); ++i) {
        board.push_back(std::vector<int>(pieces[i].size()));
    }

    for(int i = 0; i < pieces.size(); i++) {
        for(int j = 0; j < pieces[i].size(); j++) {
            if(pieces[i][j] == ' ') {
                board[i][j] = 0;
            } else {
                board[i][j] = -1;
            }
        }
    }

    int idx = 1;
    std::queue<Pos> Q;

    for(auto y = 0; y < board.size() - 1; ++y) {
        for(auto x = 0; x < board[y].size() - 1; ++x) {
            switch(pieces[y][x]) {
                case '+':
                    break;
                default:
                    continue;
            }

            int yx = y + 1;
            int xx = x + 1;

            if (pieces[yx][xx] != ' ' || pieces[y][xx] != '-' || pieces[yx][x] != '|')
                continue;

            if(board[yx][xx])
                continue;
            
            board[yx][xx] = idx;
            Q.push({yx, xx});

            while(!Q.empty()) {
                auto curr = Q.front(); Q.pop();

                for(auto i = 0; i < 4; ++i) {
                    auto ny = curr.first + dy[i];
                    auto nx = curr.second + dx[i];

                    if(ny < 0 || ny >= board.size() || nx < 0 || nx >= board[ny].size())
                        continue;

                    if(!board[ny][nx]) {
                        board[ny][nx] = idx;
                        Q.push({ny, nx});
                    }
                }
            }

            idx++;
        }
    }

    DEBUG("FILL\n");
    for(auto &r : board) {
        for(auto &c : r) {
            DEBUG(c << ' ');
        }
        DEBUG('\n');
    }

    return board;
}

std::vector<std::vector<std::string>> breakPieces(const Board &board) {
    std::vector<std::vector<std::string>> pieces;

    int pieceCount = 0;
    for(auto &r : board) {
        for(auto &c : r) {
            pieceCount = std::max(pieceCount, c);
        }
    }

    std::vector<BoundingBox> boundingBoxes(pieceCount + 1, {std::numeric_limits<int>::max(), std::numeric_limits<int>::max(),  
                                                            std::numeric_limits<int>::min(),  std::numeric_limits<int>::min()});
    for(int y = 0; y < board.size(); ++y) {
        for(int x = 0; x < board[y].size(); ++x) {
            if(board[y][x] < 1)
                continue;

            auto &bb = boundingBoxes[board[y][x]];
            bb.top = std::min(bb.top, y);
            bb.left = std::min(bb.left, x);
            bb.bottom = std::max(bb.bottom, y);
            bb.right = std::max(bb.right, x);
        }
    }

    boundingBoxes.erase(boundingBoxes.begin());
    for(auto &bb : boundingBoxes) {
        auto height = bb.bottom - bb.top + 1;
        auto width = bb.right - bb.left + 1;

        auto piece(std::vector<std::string>(height + 2, std::string(width + 2, ' ')));

        for(int y = bb.top; y <= bb.bottom; ++y) {
            for(int x = bb.left; x <= bb.right; ++x) {
                if(board[y][x] != pieces.size() + 1)
                    continue;
                
                for(int i = 0; i < 4; ++i) {
                    auto ny = y + dy[i];
                    auto nx = x + dx[i];

                    if(ny < 0 || ny >= board.size() || nx < 0 || nx >= board[ny].size())
                        continue;

                    if (board[ny][nx] != board[y][x]) {
                        int nyy = y - bb.top + dy[i] + 1;
                        int nxx = x - bb.left + dx[i] + 1;
                        piece[nyy][nxx] = (i > 1 ? '|' : '-');
                    }
                }

                for(int i = 4; i < 8; ++i) {
                    auto ny = y + dy[i];
                    auto nx = x + dx[i];

                    if(ny < 0 || ny >= board.size() || nx < 0 || nx >= board[ny].size())
                        continue;

                    if(board[y][nx] != board[y][x] && board[ny][x] != board[y][x]) {
                        int nyy = y - bb.top + dy[i] + 1;
                        int nxx = x - bb.left + dx[i] + 1;
                        piece[nyy][nxx] = '+';
                    }
                }
            }
        }

        for(int y = 1; y < piece.size() - 1; ++y) {
            for(int x = 1; x < piece[0].size() - 1; ++x) {
                if(piece[y][x] == '-') {
                    if (piece[y - 1][x] == '|' || piece[y + 1][x] == '|') {
                        piece[y][x] = '+';
                    }
                } else if (piece[y][x] == '|') {
                    if (piece[y][x - 1] == '-' || piece[y][x + 1] == '-') {
                        piece[y][x] = '+';
                    }
                }
            }
        }

        for(auto &s : piece)
            while(!s.empty() && s.back() == ' ')
                s.pop_back();

        pieces.push_back(piece);
    }


    return pieces;
}

std::vector<std::string> break_piece(const std::string &pieces) {
    if (pieces.empty())
        return {};
    
    auto splitPieces = split_lines(pieces);
    auto board = fill(splitPieces);
    auto brokenPieces = breakPieces(board);
    
    std::vector<std::string> result;
    for(auto &piece : brokenPieces) {
        result.push_back(join("\n", piece));
    }
    return result;
}