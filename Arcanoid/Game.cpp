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

int Game::run_game() {
    RenderWindow window(VideoMode(800, 600), "SFML works!", Style::Default);
    Game game = Game(window);
    //RectangleShape shape(Vector2f(100, 100));
    //shape.setFillColor(Color::Green);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        //window.draw(shape);
        game.draw();
        window.display();
    }

    return 0;
}
