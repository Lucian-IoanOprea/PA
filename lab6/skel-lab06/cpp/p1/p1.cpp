#include <iostream>
#include <vector>
#include <utility>

#include "nim.h"

using namespace std;

Move::Move(int amount = 0, int heap = -1): amount(amount), heap(heap)
{
}

Nim::Nim()
{
    heaps[0] = 3;
    heaps[1] = 4;
    heaps[2] = 5;
}


std::vector<Move>
Nim::get_moves(int player)
{
    std::vector<Move> ret;
    for (int i = 0; i < 3; i++)
        for (int k = 1; k <= 3; k++)
            if (k <= heaps[i])
                ret.push_back(Move(k, i));
    return ret;
}


bool Nim::ended()
{
    
    for (int i = 0; i < 3; ++i) {
        if (heaps[i] != 0)
            return false;
    }
    return true;
}


int Nim::eval(int player)
{
    
    if (ended())
        return Inf;
    if ((heaps[0] ^ heaps[1] ^ heaps[2]) == 0)
            return (-1) * Inf;
    return Inf;
}


bool Nim::apply_move(const Move &move)
{
    
    if (move.amount <= heaps[move.heap]) {
        heaps[move.heap] -= move.amount;
        return true;
    }
    return false;
}


void Nim::print()
{
    for (int i = 0; i < 3; i++)
    {
        std::cout << i << ":";
        for (int j = 0; j < heaps[i]; j++)
            std::cout << " *";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


pair<int, Move> minimax(Nim init, int player, int depth)
{
    
    if (init.ended() || depth == 0)
        return make_pair(init.eval(player), NULL); 
    vector<Move> moves = init.get_moves(player);
    int maximum = (-1) * Inf; 
  
    Move result = moves[0];
    for (auto move: moves) {
        if (init.apply_move(move)) {
            int score = (-1) * minimax(init, player, depth - 1).first;
            if (score > maximum) {
                maximum = score;
                result = move;
            }
        }
    }
    return pair<int, Move>(maximum, result);
}


int main()
{
    Nim nim;

    nim.heaps[0] = 5;
    nim.heaps[1] = 10;
    nim.heaps[2] = 20;

    nim.print();

    /* Choose here if you want COMP vs HUMAN or COMP vs COMP */
    bool HUMAN_PLAYER = false;
    int player = 1;

    while (!nim.ended())
    {
        std::pair<int, Move> p;
        if (player == 1)
        {
            p = minimax(nim, player, 6);
            //p = minimax_abeta(nim, player, 13, -Inf, Inf);

            std::cout << "Player " << player << " evaluates to " << p.first << std::endl;
            nim.apply_move(p.second);
        }
        else
        {
            if (!HUMAN_PLAYER)
            {
                p = minimax(nim, player, 6);
                //p = minimax_abeta(nim, player, 13, -Inf, Inf);

                std::cout << "Player " << player << " evaluates to " << p.first << std::endl;
                nim.apply_move(p.second);
            }
            else
            {
                bool valid = false;
                while (!valid)
                {
                    int am, h;
                    std::cout << "Insert amount [1, 2 or 3] and heap [0, 1 or 2]: ";
                    std::cin >> am >> h;
                    valid = nim.apply_move(Move(am, h));
                }
            }
        }

        nim.print();
        player *= -1;
    }

    int w = nim.heaps[0] + nim.heaps[1] + nim.heaps[2];
    if (w == 0)
        std::cout << "Player " << player << " WON!" << std::endl;
    else
        std::cout << "Player " << player << " LOST!" << std::endl;
}