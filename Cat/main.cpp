#include <SFML/Graphics.hpp>
using namespace sf;

class Cat {
public:


private:
    int health;
};

int main() {
    // â ����
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Cat's Great Adventure");

    // ����� �̹���
    // ����� ��������Ʈ ����
    RectangleShape catTexture;
    catTexture.setFillColor(Color::White);
    catTexture.setPosition(100, 400);
    catTexture.setSize(Vector2f(100, 50));

    // �߷� ����
    float gravity = 1.0f;
    float jumpStrength = -15.0f;
    Vector2f velocity(0.0f, 0.0f);

    // �ٴ� ���� ����
    float groundHeight = 740.0f;

    // �̵� �ӵ� ����
    float moveSpeed = 10.0f;

    // W Ű�� ������ �� ���� ������ ���θ� ��Ÿ���� ����
    bool isJumping = false;

    // ���� ����
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A) {
                    // �������� �̵�
                    catTexture.move(-moveSpeed, 0);
                }
                if (event.key.code == sf::Keyboard::D) {
                    // ���������� �̵�
                    catTexture.move(moveSpeed, 0);
                }
                if (event.key.code == sf::Keyboard::Space && catTexture.getPosition().y >= groundHeight) {
                    // ����
                    velocity.y = jumpStrength;
                }
                if (event.key.code == sf::Keyboard::W && !isJumping) {
                    // W Ű�� ������ ���� ����
                    velocity.y = jumpStrength;
                    isJumping = true;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W) {
                    // W Ű�� ������ ���� ����
                    isJumping = false;
                }
            }
        }

        // �߷� ����
        velocity.y += gravity;
        catTexture.move(0.0f, velocity.y);

        if (catTexture.getPosition().y >= groundHeight) {
            catTexture.setPosition(catTexture.getPosition().x, groundHeight);
            velocity.y = 0.0f;
        }

        // ȭ�� �����
        window.clear();

        // ����� ��������Ʈ �׸���
        window.draw(catTexture);

        // ȭ�� ������Ʈ
        window.display();
    }

    return EXIT_SUCCESS;
}