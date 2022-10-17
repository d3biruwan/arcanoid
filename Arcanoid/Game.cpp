#include"Game.hpp"

Game::Game( unique_ptr<RenderWindow> window) {
    this->window = move(window);

    player->set_game(*this);
    player_texture.loadFromFile("player.png");
    player->set_position();
    player->set_texture(player_texture);

    block_texture.loadFromFile("block.png");
    accelerating_block_texture.loadFromFile("speed_block.png");
    float offset_x = (float)(block_texture.getSize().x);
    float offset_y = (float)(block_texture.getSize().y);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Block block = Block(block_colors,i*columns+j);
            block.set_game(*this);
            block.set_hp(3);
            block.set_position(border_x + offset_x * (j + 0.5f), border_y + offset_y * (i + 0.5f));
            block.set_texture(block_texture);
            if (i == j) {
                block.make_accelerating(block_acceleration,accelerating_block_texture);
            }
            blocks.push_back(block);
        }
    }
    auto ball = make_unique<Ball>(ball_velocity,*this);
    ball_texture.loadFromFile("ball.png");
    ball->set_position();
    ball->set_texture(ball_texture);
    balls.push_back(move(ball));
}


void Game::draw() {
    for (Block& block : blocks) {
        block.draw();
    }
    for (auto& ball : balls) {
        ball->draw();
    }
    player->draw();
}

void Game::move_player(Keyboard::Key key) {
    switch (key){
    case Keyboard::Left:
        player->move_left();
        break;
    case Keyboard::Right:
        player->move_right();
    }
}

void Game::update_objects() {
    player->update_state();
    for (auto& ball : balls) {
        ball->update_state();
        ball->move();
    }
}

void Game::add_bonus() {
    auto new_ball = make_unique<Ball>(ball_velocity, *this);
    new_ball->set_position();
    new_ball->set_texture(ball_texture);
    new_ball->set_game(*this);
    balls.push_back(move(new_ball));
    //(balls.end()-1)->flash_animation();
    
}

int Game::run_game() {
    auto window = make_unique<RenderWindow>(VideoMode(800, 600), "SFML works!", Style::Default);
    Game game = Game(move(window));
    while (game.window->isOpen())
    {
        Event event;
        while (game.window->pollEvent(event))
        {
            if (event.type == Event::Closed) {
                game.window->close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            game.move_player(Keyboard::Left);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            game.move_player(Keyboard::Right);
        }
        game.update_objects();
        game.window->clear();
        game.draw();
        game.window->display();
    }

    return 0;
}
