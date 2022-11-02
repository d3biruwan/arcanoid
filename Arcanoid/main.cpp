#include"Game.hpp"

using namespace sf;
using namespace std;



int main()
{
    int run = 1;
    while (run == 1) {
        run=Game::run_game();
    }
    return 0;
}