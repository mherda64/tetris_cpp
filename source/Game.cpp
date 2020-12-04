//
// Created by musiek on 11/21/20.
//

#include "../header/Game.h"
#include <iostream>

bool Game::run() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tetris");
    window.setVerticalSyncEnabled(true);

    if (!gameBoard.init("tileset.png", 32))
        return false;

    sf::Texture backgroundText;
    backgroundText.loadFromFile("background.png");
    sf::Sprite background;
    background.setTexture(backgroundText);

//    sf::Texture nextFieldText;
//    nextFieldText.loadFromFile("next_field.png");
//    sf::Sprite nextField;
//    nextField.setTexture(nextFieldText);
//    nextField.setPosition(16 * 32, 8 * 32);

    Piece* currentPiece = pieceFactory.getPiece();
    Piece* nextPiece = pieceFactory.getPiece();
    nextPiece->setPiecePosition(X_OFFSET / 32 + BOARD_WIDTH + 2, 10, false);
    Piece* ghostPiece = pieceFactory.getGhostPiece(currentPiece);
    setGhostPosition(currentPiece, ghostPiece);


    bool deltaFlag = false;
    float deltaTime = 0;

    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();


    while (window.isOpen()) {

        if (gameOver) {
            break;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                //todo jedna funkcja
                if (event.key.code == sf::Keyboard::Left)
                    moveLeft(currentPiece, ghostPiece);
                else if (event.key.code == sf::Keyboard::Right)
                    moveRight(currentPiece, ghostPiece);
//                else if (event.key.code == sf::Keyboard::Up)
//                    (*currentPiece).setPiecePosition((*currentPiece).getPiecePosition().getX(), (*currentPiece).getPiecePosition().getY() - 1);
                else if (event.key.code == sf::Keyboard::Down)
                    fallDown(currentPiece);
                else if (event.key.code == sf::Keyboard::Z)
                    rotateLeft(currentPiece, ghostPiece);
                else if (event.key.code == sf::Keyboard::X)
                    rotateRight(currentPiece, ghostPiece);
            }
        }

        window.clear();
        window.draw(background);
//        window.draw(nextField);
        window.draw(gameBoard);
        window.draw(*currentPiece);
        window.draw(*nextPiece);
        window.draw(*ghostPiece);
        window.display();

        time = clock.getElapsedTime();
        if (time.asSeconds() - deltaTime > 0.5) {
            clock.restart();
            if (!fallDown(currentPiece)) {
                gameOver = gameBoard.add(currentPiece);

                delete currentPiece;
                delete ghostPiece;

                //swap pieces
                currentPiece = nextPiece;
                currentPiece->setPiecePosition(DEFAULT_X, DEFAULT_Y);
                //get new piece as the next piece
                nextPiece = pieceFactory.getPiece();
                nextPiece->setPiecePosition(X_OFFSET / 32 + BOARD_WIDTH + 2, 10, false);
                //get new ghost piece and update it's position
                ghostPiece = pieceFactory.getGhostPiece(currentPiece);
                setGhostPosition(currentPiece, ghostPiece);

                //getting number of cleared rows
                int clearedRows = gameBoard.updateBoard();
                totalRows += gameBoard.updateBoard();

//                updateScore(clearedRows);
//                updateLevel();



                //TODO score updating here i guess
            }

        }
    }

    return true;
}

Game::Game() {}

bool Game::moveLeft(Piece *piece, Piece* ghostPiece) {
    if (!gameBoard.collidesWith(
            piece->getPiecePosition().getX() - 1,
            piece->getPiecePosition().getY(),
            piece->getCurrentShape())
            ) {
        piece->setPiecePosition(piece->getPiecePosition().getX() - 1, piece->getPiecePosition().getY());
        setGhostPosition(piece, ghostPiece);
        return true;
    }
    return false;
}

bool Game::moveRight(Piece *piece, Piece* ghostPiece) {
    if (!gameBoard.collidesWith(
            piece->getPiecePosition().getX() + 1,
            piece->getPiecePosition().getY(),
            piece->getCurrentShape())
            ) {
        piece->setPiecePosition(piece->getPiecePosition().getX() + 1, piece->getPiecePosition().getY());
        setGhostPosition(piece, ghostPiece);
        return true;
    }
    return false;
}

bool Game::rotateLeft(Piece *piece, Piece* ghostPiece) {
    if (!gameBoard.collidesWith(
            piece->getPiecePosition().getX(),
            piece->getPiecePosition().getY(),
            piece->getLeftRotationShape())
            ) {
        piece->rotateLeft();
        setGhostPosition(piece, ghostPiece);
        return true;
    }
    return false;
}

bool Game::rotateRight(Piece *piece, Piece* ghostPiece) {
    if (!gameBoard.collidesWith(
            piece->getPiecePosition().getX(),
            piece->getPiecePosition().getY(),
            piece->getRightRotationShape())
            ) {
        piece->rotateRight();
        setGhostPosition(piece, ghostPiece);
        return true;
    }
    return false;
}

bool Game::fallDown(Piece *piece) {
    if (!gameBoard.collidesWith(
            piece->getPiecePosition().getX(),
            piece->getPiecePosition().getY() + 1,
            piece->getCurrentShape())
            ) {
        piece->setPiecePosition(piece->getPiecePosition().getX(), piece->getPiecePosition().getY() + 1);
        return true;
    }
    return false;
}

void Game::setGhostPosition(Piece *currentPiece, Piece* ghostPiece) {
    //set current ghost rotation the same as the current piece rotation
    ghostPiece->setRotation(currentPiece->getRotation());
    //set current ghost position the same as the current piece position
    ghostPiece->setPiecePosition(currentPiece->getPiecePosition());

    //find lowest free ghost piece position
    while (!gameBoard.collidesWith(ghostPiece->getPiecePosition().getX(),
                                   ghostPiece->getPiecePosition().getY() + 1,
                                   ghostPiece->getCurrentShape())) {
        ghostPiece->setPiecePosition(ghostPiece->getPiecePosition().getX(),
                                     ghostPiece->getPiecePosition().getY() + 1);
    }
}




