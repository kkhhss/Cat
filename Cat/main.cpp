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
    catTexture.setSize(Vector2f(100, 50)); // ���� ũ�⸦ 200 �ȼ��� ����

    // �߷� ����
    float gravity = 600.0f; // �߷��� ����
    float jumpStrength = -300.0f; // �������� ����
    Vector2f velocity(0.0f, 0.0f);

    // �ٴ� ���� ����
    float groundHeight = 600.0f;

    // �̵� �ӵ� ����
    float moveSpeed = 3000.0f; // �ʴ� �̵� �ȼ� ���� ����

    // W Ű�� ������ �� ���� ������ ���θ� ��Ÿ���� ����
    bool isJumping = false;

    // �ð��� �����ϱ� ���� clock ��ü �ʱ�ȭ
    sf::Clock clock;

    // ���� ����
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
                    // ����
                    velocity.y = jumpStrength;
                }
                if (event.key.code == sf::Keyboard::W && !isJumping) {
                    // W Ű�� ������ ���� ����
                    velocity.y = jumpStrength;
                    isJumping = true;
                }
                if (event.key.code == sf::Keyboard::A) {
                    // A Ű�� ������ �������� �̵�
                    catTexture.move(-moveSpeed * dt, 0);
                }
                if (event.key.code == sf::Keyboard::D) {
                    // D Ű�� ������ ���������� �̵�
                    catTexture.move(moveSpeed * dt, 0);
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
        velocity.y += gravity * dt;

        // �̵��� �����ϱ� ���� �ӵ��� ��ġ�� ����
        catTexture.move(velocity * dt);

        // �ٴڰ��� �浹 ó��
        if (catTexture.getPosition().y >= groundHeight) {
            catTexture.setPosition(catTexture.getPosition().x, groundHeight);
            velocity.y = 0.0f;
            isJumping = false; // �ٴڿ� ������ ���� ����
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
