#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

const char OUR_MARK = 'x';
const char OPP_MARK = 'o';
const char EMPTY = '.';

void readBoard(char board[3][3]) {
    string line;
    for (int i = 0; i < 3; ++i) {
        cin >> line;
        for (int j = 0; j < 3; ++j) {
            board[i][j] = line[j];
        }
    }
}

void writeBoard(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

bool isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == EMPTY)
                return false;
    return true;
}

bool checkWin(char board[3][3], char player) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0]==player && board[i][1]==player && board[i][2]==player)
            return true;
        if (board[0][i]==player && board[1][i]==player && board[2][i]==player)
            return true;
    }
    if (board[0][0]==player && board[1][1]==player && board[2][2]==player)
        return true;
    if (board[0][2]==player && board[1][1]==player && board[2][0]==player)
        return true;
    return false;
}

int evaluate(char board[3][3]) {
    if (checkWin(board, OUR_MARK))
        return +10;
    else if (checkWin(board, OPP_MARK))
        return -10;
    else
        return 0;
}

int minimax(char board[3][3], int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);

    if (score == 10)
        return score - depth;
    if (score == -10)
        return score + depth;

    if (isBoardFull(board))
        return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = OUR_MARK;
                    best = max(best, minimax(board, depth + 1, !isMax, alpha, beta));
                    board[i][j] = EMPTY;
                    alpha = max(alpha, best);

                    if (beta <= alpha)
                        break;
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = OPP_MARK;
                    best = min(best, minimax(board, depth + 1, !isMax, alpha, beta));
                    board[i][j] = EMPTY;
                    beta = min(beta, best);

                    if (beta <= alpha)
                        break;
                }
            }
        }
        return best;
    }
}

void findBestMove(char board[3][3], int &bestRow, int &bestCol) {
    int bestVal = numeric_limits<int>::min();
    bestRow = -1;
    bestCol = -1;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                board[i][j] = OUR_MARK;
                int moveVal = minimax(board, 0, false, numeric_limits<int>::min(), numeric_limits<int>::max());
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
}

int main() {
    string turnStr;
    cin >> turnStr;
    bool isOurTurn = true;
    char board[3][3];

    readBoard(board);

    while (true) {
        if (!isOurTurn) {
            readBoard(board);

            if (checkWin(board, OPP_MARK)) {
                return 0;
            }
            if (isBoardFull(board)) {
                return 0;
            }
        }

        int bestRow, bestCol;
        findBestMove(board, bestRow, bestCol);

        if (bestRow != -1 && bestCol != -1) {
            board[bestRow][bestCol] = OUR_MARK;
        } else {
            return 0;
        }

        writeBoard(board);

        if (checkWin(board, OUR_MARK)) {
            return 0;
        }

        if (isBoardFull(board)) {
            return 0;
        }

        isOurTurn = false;
    }

    return 0;
}
