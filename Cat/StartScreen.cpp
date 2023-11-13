#include "StartScreen.h"

StartScreen::StartScreen() : isButtonHovered(false) {
    // ��� �̹��� �ε�
    if (!backgroundTexture.loadFromFile("./resource/img/StartScreen.png")) {
        // ���� ó��
    }
    backgroundSprite.setTexture(backgroundTexture);

    // ��Ʈ �ε�
    if (!font.loadFromFile("path/to/font.ttf")) {
        // ���� ó��
    }

    // '�����ϱ�' ��ư �ؽ�Ʈ ����
    startText.setFont(font);
    startText.setString(L"�����ϱ�"); // �����ڵ� ���ڿ�
    startText.setCharacterSize(24);
    startText.setFillColor(sf::Color::White);
    // startText.setPosition("./resource/img/StartScreen.png");
}

void StartScreen::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // ���콺 ��ư Ŭ�� �̺�Ʈ ó��
        if (event.type == sf::Event::MouseButtonPressed) {
            if (isButtonHovered) {
                // ���� ���� ����
            }
        }

        // ���콺 ȣ�� �̺�Ʈ ó��
        if (event.type == sf::Event::MouseMoved) {
            if (startButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                isButtonHovered = true;
                startText.setFillColor(sf::Color::Red); // ȣ�� ���� ����
            }
            else {
                isButtonHovered = false;
                startText.setFillColor(sf::Color::White); // �⺻ �������� ����
            }
        }
    }
}

void StartScreen::update(sf::Time dt) {
    // �ʿ��� ������Ʈ ���� (�ִϸ��̼� ��)
}

void StartScreen::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite); // ��� �׸���
    window.draw(startText);        // '�����ϱ�' ��ư �ؽ�Ʈ �׸���
}