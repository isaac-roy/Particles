#include <iostream>
#include "Engine.h"

#define NUM_PARTICLES 5     // Number of particles created

using namespace std;

Engine::Engine()
{
    m_Window.create(VideoMode::getDesktopMode(), "Particles");
}

void Engine::run()
{
    Clock clock;

    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete. Starting engine..." << endl;

    while(m_Window.isOpen())
    {
        Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}

void Engine::input()
{
    int numPoints = 0;
    Event event;

    while(m_Window.pollEvent(event))
    {
        if(event.type == Event::Closed)
        {
            // Quit the game when the window is closed
            m_Window.close();
        }

        if(event.type == sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                for(int i = 0; i < NUM_PARTICLES; i++)
                {
                    numPoints = rand() % (50 - 25 + 1) + 25;

                    m_particles.push_back(
                        Particle(
                            m_Window,
                            numPoints,
                            Mouse::getPosition(m_Window)
                        )
                    );
                }
            }
        }
    }

    // Close the window when the escape key is pressed
    if(Keyboard::isKeyPressed(Keyboard::Escape))
    {
        m_Window.close();
    }
}

void Engine::update(float dtAsSeconds)
{
    // iterator-based for-loop
    for(auto it = m_particles.begin(); it != m_particles.end(); )
    {
        if(it->getTTL() > 0.0)
        {
            it->update(dtAsSeconds);
            it++;
        }
        else
        {
            it = m_particles.erase(it);
        }
    }
}

void Engine::draw()
{
    m_Window.clear();

    for(Particle particle : m_particles)
    {
        m_Window.draw(particle);
    }

    m_Window.display();
}
