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
            auto block = make_unique<Block>(i*columns+j);
            block->set_game(*this);
            block->set_hp(3);
            block->set_position(border_x + offset_x * (j + 0.5f), border_y + offset_y * (i + 0.5f));
            block->set_texture(block_texture);
            if (i == j) {
                block->make_accelerating(block_acceleration,accelerating_block_texture);
            }
            blocks.push_back(move(block));
        }
    }
    auto ball = make_unique<Ball>(ball_velocity,*this);
    ball_texture.loadFromFile("ball.png");
    ball->set_position();
    ball->set_texture(ball_texture);
    balls.push_back(move(ball));

    bonus_texture.loadFromFile("question.png");

    font.loadFromFile("TNR.ttf");
    score_t.setFont(font);
    score_t.setCharacterSize(12);
    score_t.setPosition(0,this->window->getSize().y - 15);
    score_t.setString(to_string(0));

    heart_texture.loadFromFile("heart.png");

    for (int i = 0; i < player_hp; i++) {
        auto h=make_unique<Sprite>();
        h->setTexture(heart_texture);
        h->setPosition(this->window->getSize().x - (i + 1)* h->getLocalBounds().width, 0);
        hearts.push_back(move(h));
    }
}


void Game::draw() {
    for (auto& block : blocks) {
        block->draw();
    }
    for (auto& block : moving_blocks) {
        block->draw();
    }
    for (auto& ball : balls) {
        ball->draw();
    }
    for (auto& bonus : bonuses) {
        bonus->draw();
    }
    player->draw();
    window->draw(score_t);
    for (int i = 0; i < player->get_hp(); i++) {
        window->draw(*hearts.at(i));
    }
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
    for (auto& bonus : bonuses) {
        if (bonus) {
            bonus->update_state();
        }
        if (bonus) {
            bonus->move();
        }
    }
    for (auto& block : moving_blocks) {
        if (block) {
            block->update_state();
        }
        if (block) {
            block->move();
        }
    }
    for (auto& ball : balls) {
        if (ball) {
            ball->update_state();
        }
        if (ball) {
            ball->move();
        }
    }
}

void Game::add_ball() {
    auto new_ball = make_unique<Ball>(ball_velocity, *this);
    new_ball->set_position();
    new_ball->set_texture(ball_texture);
    for (auto& ball : balls) {
        float left = ball->get_global_bounds().getPosition().x;
        float top = ball->get_global_bounds().getPosition().y;
        float right = left + ball->get_global_bounds().width;
        float bottom = top + ball->get_global_bounds().height;

        if ((new_ball->get_global_bounds().left <= right) && (new_ball->get_global_bounds().left + new_ball->get_global_bounds().width >= left)) {
            if ((new_ball->get_global_bounds().top + new_ball->get_global_bounds().height >= top) && (new_ball->get_global_bounds().top <= bottom)) {
                new_ball->move(3.f / 2.f * new_ball->get_global_bounds().width, 0.f);
            }
        }
    }


    for (auto& block : moving_blocks) {
        float left = block->get_global_bounds().getPosition().x;
        float top = block->get_global_bounds().getPosition().y;
        float right = left + block->get_global_bounds().width;
        float bottom = top + block->get_global_bounds().height;

        if ((new_ball->get_global_bounds().left <= right) && (new_ball->get_global_bounds().left + new_ball->get_global_bounds().width >= left)) {
            if ((new_ball->get_global_bounds().top + new_ball->get_global_bounds().height >= top) && (new_ball->get_global_bounds().top <= bottom)) {
                new_ball->move(3.f / 2.f * new_ball->get_global_bounds().width, 0.f);
            }
        }
    }
    balls.push_back(move(new_ball));
    (balls.end() - 1)->get()->flash_animation();
}

void Game::add_block() {
    auto new_block = make_unique<Moving_Block>(block_velocity, *this);
    new_block->set_hp(3);
    new_block->set_position();
    new_block->set_texture(block_texture);
    for (auto& ball : balls) {
        float left = ball->get_global_bounds().getPosition().x;
        float top = ball->get_global_bounds().getPosition().y;
        float right = left + ball->get_global_bounds().width;
        float bottom = top + ball->get_global_bounds().height;

        if ((new_block->get_global_bounds().left <= right) && (new_block->get_global_bounds().left + new_block->get_global_bounds().width >= left)) {
            if ((new_block->get_global_bounds().top + new_block->get_global_bounds().height >= top) && (new_block->get_global_bounds().top <= bottom)) {
                new_block->move(3.f / 2.f * new_block->get_global_bounds().width, 0.f);
            }
        }
    }

    for (auto& block : moving_blocks) {
        float left = block->get_global_bounds().getPosition().x;
        float top = block->get_global_bounds().getPosition().y;
        float right = left + block->get_global_bounds().width;
        float bottom = top + block->get_global_bounds().height;

        if ((new_block->get_global_bounds().left <= right) && (new_block->get_global_bounds().left+ new_block->get_global_bounds().width >= left)) {
            if ((new_block->get_global_bounds().top+ new_block->get_global_bounds().height >= top) && (new_block->get_global_bounds().top <= bottom)) {
                new_block->move(3.f / 2.f * new_block->get_global_bounds().width, 0.f);
            }
        }
    }
    moving_blocks.push_back(move(new_block));

}

void Game::add_bonus() {
    if (moving_blocks.size() == max_moving_blocks) {
        add_ball();
        return;
    }
    if (balls.size() == max_balls_count) {
        add_block();
        return;
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100);
    if ((dist(gen) > 50) ) {
        add_block();
    }
    else {
        add_ball();
    } 
}

int Game::run_game() {
    auto window = make_unique<RenderWindow>(VideoMode(800, 600), "SFML works!", Style::Default);
    auto game = make_unique<Game>(move(window));
    srand(time(0));
    //Game game = Game(move(window));
    while (game->window->isOpen())
    {
        Event event;
        while (game->window->pollEvent(event))
        {
            if (event.type == Event::Closed) {
                game->window->close();
                return 0;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            game->move_player(Keyboard::Left);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            game->move_player(Keyboard::Right);
        }
        game->update_objects();
        if (game->player->get_hp() == 0) {
            return game->game_over_screen();
        }
        game->window->clear();
        game->draw();
        game->window->display();
    }

    return 0;
}

void Game::increase_score() {
    this->score++;
    score_t.setString(to_string(score));
}

int Game::game_over_screen() {
    RenderWindow screen=RenderWindow(VideoMode(800, 300), "POROSAD", Style::Default);
    Text text;
    Font old;
    old.loadFromFile("old.ttf");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(screen.getSize().x / 8, screen.getSize().y/2);
    string str=string("thy sc're is ");
    str += to_string(score);
    str += ".\nIf't be true thee wanteth to tryeth again, presseth the button ENTER,\noth'rwise presseth button ESC and the game shall endeth";
    text.setString(str);
    str== text.getString();
    //text.setFillColor(Color::Green);
    while (screen.isOpen()) {
        Event event;
        while (screen.pollEvent(event)) {
            if (event.type == Event::Closed) {
                return 0;
                screen.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                return 1;
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                return 0;
            }
            

        }
        screen.clear();
        screen.draw(text);
        screen.display();
    }
}