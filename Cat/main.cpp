#include <SFML/Graphics.hpp>
using namespace sf;

class Cat {
public:


private:
    int health;
};

int main() {
    // 창 생성
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Cat's Great Adventure");

    // 고양이 이미지
    // 고양이 스프라이트 생성
    RectangleShape catTexture;
    catTexture.setFillColor(Color::White);
    catTexture.setPosition(100, 400);
    catTexture.setSize(Vector2f(100, 50));

    // 중력 설정
    float gravity = 1.0f;
    float jumpStrength = -15.0f;
    Vector2f velocity(0.0f, 0.0f);

    // 바닥 높이 설정
    float groundHeight = 740.0f;

    // 이동 속도 설정
    float moveSpeed = 10.0f;

    // W 키를 눌렀을 때 점프 중인지 여부를 나타내는 변수
    bool isJumping = false;

    // 게임 루프
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A) {
                    // 왼쪽으로 이동
                    catTexture.move(-moveSpeed, 0);
                }
                if (event.key.code == sf::Keyboard::D) {
                    // 오른쪽으로 이동
                    catTexture.move(moveSpeed, 0);
                }
                if (event.key.code == sf::Keyboard::Space && catTexture.getPosition().y >= groundHeight) {
                    // 점프
                    velocity.y = jumpStrength;
                }
                if (event.key.code == sf::Keyboard::W && !isJumping) {
                    // W 키를 누르면 점프 시작
                    velocity.y = jumpStrength;
                    isJumping = true;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W) {
                    // W 키를 놓으면 점프 중지
                    isJumping = false;
                }
            }
        }

        // 중력 적용
        velocity.y += gravity;
        catTexture.move(0.0f, velocity.y);

        if (catTexture.getPosition().y >= groundHeight) {
            catTexture.setPosition(catTexture.getPosition().x, groundHeight);
            velocity.y = 0.0f;
        }

        // 화면 지우기
        window.clear();

        // 고양이 스프라이트 그리기
        window.draw(catTexture);

        // 화면 업데이트
        window.display();
    }

    return EXIT_SUCCESS;
}