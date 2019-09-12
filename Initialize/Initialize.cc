#include "Initialize.h"


// Konstruktor
Initialize::Initialize()
{
    //Clear window
    window.clear(sf::Color::White);

    //Skapa musik
    music.openFromFile("resources/Scooter-Fire.ogg");
    music.setLoop(true);

    //Initiera font
    font.loadFromFile("resources/sansation.ttf");
    input.setFont(font);
    input.setCharacterSize(70);
    input.setColor(sf::Color::White);

    //Ladda texturer
    texture1.loadFromFile("resources/background2.png");
    texture2.loadFromFile("resources/lavatexture.png");

    //Initiera sprites
    sprite1.setTexture(texture1);
    sprite1.setPosition(0, 0);
    sprite2.setTexture(texture2);
    sprite2.setPosition(0, 0);
    sprite3.setTexture(texture2);
    sprite3.setPosition(1300, 0);

    //Lägg in powerups i world
    world.addPowerup(inversion);
    world.addPowerup(quickprojectile);
    world.addPowerup(invincibility);
    world.addPowerup(slowrotation);

    //Lägg in obstacles i world
    world.addObstacle(obstacle1);
    world.addObstacle(obstacle2);
    world.addObstacle(obstacle3);
    world.addObstacle(obstacle4);

    //Färga ballen
    ball1.setFillColor(sf::Color::Red);
    ball2.setFillColor(sf::Color(0, 128, 255, 255));
    ball3.setFillColor(sf::Color::Green);
    ball4.setFillColor(sf::Color(255, 128, 0, 255));

    //Initiera obstacles
    wall1.setFillColor(sf::Color::Black);
    wall1.setPosition(centerdiff, 0);
    wall2.setFillColor(sf::Color::Black);
    wall2.setPosition(centerdiff, 980);
    wall3.setFillColor(sf::Color::Black);
    wall3.setPosition(980 + centerdiff, 0);
    wall4.setFillColor(sf::Color::Black);
    wall4.setPosition(centerdiff, 0);

    //Färga powerups
    power1.setFillColor(sf::Color::Magenta);
    power2.setFillColor(sf::Color::Magenta);
    power3.setFillColor(sf::Color::Magenta);
    power4.setFillColor(sf::Color::Magenta);


}


void Initialize::run()
{
    //Print startimage
    game.printStartImage(window, input, sprite1);


    //Initialize loop: Number of players
    if (!game.initializePlayers(window, world, player1, player2, player3, player4))
    {
        return;
    }
    Points points{game.getNumberOfPlayers()};

    // Number of players chosen
    game.printNumberOfPlayers(window, input);

    // Initialize loop: Controller keys
    if (!game.initializeControls(window, input))
    {
        return;
    }

    //All init done! Countdown!
    game.countdown(window, input, music);

    //Game loop
    while (game.getRunning())
    {
        //Player colors
        game.setColor(player1, ball1);
        game.setColor(player2, ball2);
        game.setColor(player3, ball3);
        game.setColor(player4, ball4);

        //Player positions in graphics
        ball1.setPosition(player1->getXPosition() + 320 - game.getPlayerRadius(),
            player1->getYPosition() + 20 - game.getPlayerRadius());
        ball2.setPosition(player2->getXPosition() + 320 - game.getPlayerRadius(),
            player2->getYPosition() + 20 - game.getPlayerRadius());
        ball3.setPosition(player3->getXPosition() + 320 - game.getPlayerRadius(),
            player3->getYPosition() + 20 - game.getPlayerRadius());
        ball4.setPosition(player4->getXPosition() + 320 - game.getPlayerRadius(),
            player4->getYPosition() + 20 - game.getPlayerRadius());

        //Powerup positions in graphics
        power1.setPosition(inversion->getXPosition() + 320 - game.getPowerupRadius(),
                inversion->getYPosition() + 20 - game.getPowerupRadius());
        power2.setPosition(quickprojectile->getXPosition() + 320 - game.getPowerupRadius(),
                quickprojectile->getYPosition() + 20 - game.getPowerupRadius());
        power3.setPosition(invincibility->getXPosition() + 320 - game.getPowerupRadius(),
                invincibility->getYPosition() + 20 - game.getPowerupRadius());
        power4.setPosition(slowrotation->getXPosition() + 320 - game.getPowerupRadius(),
                slowrotation->getYPosition() + 20 - game.getPowerupRadius());


        game.powerupDeactivation(world);
        game.powerupSpawn(world);
        game.handleKeyEvents(window, world);

        //Draw graphics
        window.clear(sf::Color::White);
        window.draw(sprite2);
        window.draw(sprite3);
        window.draw(ball1);
        window.draw(ball2);

        if (game.getNumberOfPlayers() >= 3)
        {
            window.draw(ball3);
        }
        if (game.getNumberOfPlayers() == 4)
        {
            window.draw(ball4);
        }

        //Draw guns
        game.drawGuns(window, world);

        //Draw walls
        window.draw(wall1);
        window.draw(wall2);
        window.draw(wall3);
        window.draw(wall4);

        //Draw powerups
        window.draw(power1);
        window.draw(power2);
        window.draw(power3);
        window.draw(power4);

        //Draw projectiles
        game.drawProjectiles(window, world);

        //Draw powerup bar
        game.drawPowerupBar(window, world);

        //Points table
        game.drawPoints(window, points, font);

        world.updateAllPositions(physics, game);
        world.checkAllCollisions(collision, physics, points, game);

        // show the newly drawn things
        window.display();

        //End game if playerpoints reach 15
        game.endGame(window, font, points);

        // wait before drawing the next frame
        sf::sleep(sf::milliseconds(50/3));
        }
}
