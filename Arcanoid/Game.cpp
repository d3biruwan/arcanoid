#include"Game.hpp"

Game::Game( RenderWindow& window) {
    parent = &window;
    player_texture.loadFromFile("player.png");
    player.set_position(*parent);
    player.set_texture(player_texture);
    
}

void Game::draw() {
    player.draw(*parent);
}

void Game::move_player(Keyboard::Key key) {
    switch (key){
    case Keyboard::Left:
        player.move_left();
        break;
    case Keyboard::Right:
        player.move_right();
    }
}

int Game::run_game() {
    RenderWindow window(VideoMode(800, 600), "SFML works!", Style::Default);
    Game game = Game(window);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                game.move_player(event.key.code);
            }
        }

        window.clear();
        game.draw();
        window.display();
    }

    return 0;
}
