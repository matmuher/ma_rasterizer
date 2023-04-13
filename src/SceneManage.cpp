#include <MaRasterizer.hpp>


// [SCENE MANAGING]

void MaRasterizer::clear_scene()
{
    for (int y = 0; y < camera.get_height(); ++y)
        for (int x = 0; x < camera.get_width(); ++x)
        {
            setPixel(x, y, sf::Color::White);
        }
}

sf::Vector3f create_shift_vec(float angle, float len)
{
    return sf::Vector3f{
                        sinf(deg2rad(angle)),
                        0.,
                        -cosf(deg2rad(angle))
                        } * len;
}

void MaRasterizer::process_key(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::D)
    {
        camera.change_rotation(-StdRotateAngle);
    }            

    if (key == sf::Keyboard::A)
    {
        camera.change_rotation(StdRotateAngle);
    }

    if (key == sf::Keyboard::W)
    {
        camera.change_position(create_shift_vec(camera.get_angle(), StdShiftLen));
    }

    if (key == sf::Keyboard::S)
    {
        camera.change_position(create_shift_vec(camera.get_angle(), -StdShiftLen));
    }
}

void MaRasterizer::render_scene()
{
    if (m_mode == RenderMode::Picture)
    {
        info() << "MEOW\n";
        update_scene();
        save_scene();
        return;
    }

    sf::Texture texture;
    sf::Sprite sprite;

    bool is_pressed = true;
    sf::Keyboard::Key key;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    info() << "Pressed\n";
                    is_pressed = true;
                    key = event.key.code;
                    break;

                case sf::Event::KeyReleased:
                    info() << "Unpressed\n";
                    is_pressed = false;
                    break;
            
                default:
                    break;
            }
        }

        if (is_pressed)
        {
            process_key(key);
        }

        clear_scene();
        update_scene(); // specigy objects
        // update all
        // draw all

        texture.loadFromImage(image);
        sprite.setTexture(texture);

        window.clear();
        window.draw(sprite);
        window.display();
    }
}

void MaRasterizer::save_scene() const
{
    image.saveToFile(file_name);
}
