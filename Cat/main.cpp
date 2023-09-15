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
    catTexture.setSize(Vector2f(100, 50)); // 세로 크기를 200 픽셀로 설정

    // 중력 설정
    float gravity = 1000.0f; // 중력을 크게 설정
    float jumpStrength = -500.0f; // 점프력을 크게 설정
    Vector2f velocity(0.0f, 0.0f);

    // 바닥 높이 설정
    float groundHeight = 600.0f;

    // 이동 속도 설정
    float moveSpeed = 300.0f; // 초당 이동 픽셀 수로 변경

    // W 키를 눌렀을 때 점프 중인지 여부를 나타내는 변수
    bool isJumping = false;

    // 이동 방향을 나타내는 변수
    int moveDirection = 0; // 0: 정지, -1: 왼쪽, 1: 오른쪽

    // 시간을 추적하기 위한 clock 객체 초기화
    sf::Clock clock;

    // 게임 루프
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space && catTexture.getPosition().y >= groundHeight) {
                    // 점프
                    velocity.y = jumpStrength;
                }
                if (event.key.code == sf::Keyboard::W && !isJumping) {
                    // W 키를 누르면 점프 시작
                    velocity.y = jumpStrength;
                    isJumping = true;
                }
                if (event.key.code == sf::Keyboard::A) {
                    // A 키를 누르면 왼쪽으로 이동
                    moveDirection = -1;
                }
                if (event.key.code == sf::Keyboard::D) {
                    // D 키를 누르면 오른쪽으로 이동
                    moveDirection = 1;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W) {
                    // W 키를 놓으면 점프 중지
                    isJumping = false;
                }
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
                    // A 또는 D 키를 놓으면 이동 정지
                    moveDirection = 0;
                }
            }
        }

        // 중력 적용
        velocity.y += gravity * dt;

        // 이동 적용
        catTexture.move(moveSpeed * moveDirection * dt, 0);

        // 이동을 적용하기 위해 속도를 위치에 더함
        catTexture.move(0, velocity.y * dt);

        // 바닥과의 충돌 처리
        if (catTexture.getPosition().y >= groundHeight) {
            catTexture.setPosition(catTexture.getPosition().x, groundHeight);
            velocity.y = 0.0f;
            isJumping = false; // 바닥에 닿으면 점프 중지
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
