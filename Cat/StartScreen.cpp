#include "StartScreen.h"

StartScreen::StartScreen() : isButtonHovered(false) {
    // 배경 이미지 로드
    if (!backgroundTexture.loadFromFile("./resource/img/StartScreen.png")) {
        // 에러 처리
    }
    backgroundSprite.setTexture(backgroundTexture);

    // 폰트 로드
    if (!font.loadFromFile("path/to/font.ttf")) {
        // 에러 처리
    }

    // '시작하기' 버튼 텍스트 설정
    startText.setFont(font);
    startText.setString(L"시작하기"); // 유니코드 문자열
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

        // 마우스 버튼 클릭 이벤트 처리
        if (event.type == sf::Event::MouseButtonPressed) {
            if (isButtonHovered) {
                // 게임 시작 로직
            }
        }

        // 마우스 호버 이벤트 처리
        if (event.type == sf::Event::MouseMoved) {
            if (startButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                isButtonHovered = true;
                startText.setFillColor(sf::Color::Red); // 호버 색상 변경
            }
            else {
                isButtonHovered = false;
                startText.setFillColor(sf::Color::White); // 기본 색상으로 변경
            }
        }
    }
}

void StartScreen::update(sf::Time dt) {
    // 필요한 업데이트 로직 (애니메이션 등)
}

void StartScreen::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite); // 배경 그리기
    window.draw(startText);        // '시작하기' 버튼 텍스트 그리기
}