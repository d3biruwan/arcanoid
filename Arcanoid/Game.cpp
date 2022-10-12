#include"Game.hpp"

Game::Game( RenderWindow& window) {
    parent = &window;

    player.set_window(window);
    player_texture.loadFromFile("player.png");
    player.set_position();
    player.set_texture(player_texture);
    player.set_game(*this);

    block_texture.loadFromFile("block.png");
    float offset_x = (float)(block_texture.getSize().x);
    float offset_y = (float)(block_texture.getSize().y);

    //Block block = Block();
    //block.set_window(window);
    //block.set_position(window.getSize().x / 2.f + 40.f, window.getSize().y / 2.f + 50.f);
    //block.set_texture(block_texture);
    //blocks.push_back(block);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Block block = Block(i*columns+j);
            block.set_blocks(blocks);
            block.set_window(window);
            block.set_position(border_x + offset_x * (j + 0.5f), border_y + offset_y * (i + 0.5f));
            block.set_texture(block_texture);
            block.set_game(*this);
            //block.set
            blocks.push_back(block);
        }
    }
    
    ball.set_blocks(blocks);
    ball.set_player(player);
    ball.set_window(window);
    ball_texture.loadFromFile("Ball.png");
    ball.set_position();
    ball.set_texture(ball_texture);
    ball.set_game(*this);
}


void Game::draw() {
    for (Block& block : blocks) {
        block.draw();
    }
    ball.draw();
    player.draw();
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

void Game::update_objects() {
    player.update_state();
    ball.update_state();
    ball.move();
}

int Game::run_game() {
    RenderWindow window(VideoMode(800, 600), "SFML works!", Style::Default);
    //window.setFramerateLimit(120);
    Game game = Game(window);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            game.move_player(Keyboard::Left);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            game.move_player(Keyboard::Right);
        }
        game.update_objects();
        window.clear();
        game.draw();
        window.display();
    }

    return 0;
}
