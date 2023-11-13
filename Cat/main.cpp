#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Cat {
public:

private:
};

class Stool {
public:
    RectangleShape stool;
    Stool(float x, float y, float width, float height) {
        stool.setSize(Vector2f(width, height));
        stool.setPosition(x, y);
        stool.setFillColor(Color::White);
    }

    // ���� ���� ����⸦ ��ġ�ϱ� ���� ��ġ�� ��ȯ�ϴ� �Լ�
    Vector2f getFishPosition(float fishRadius) const {
        float x = stool.getPosition().x + ((stool.getSize().x - fishRadius * 2) / 2); // ������ �߾�
        float y = stool.getPosition().y - 80; // ������ ���
        return Vector2f(x, y);
    }

private:

};

class Fish {
public:
    static Texture FishImg; // ��� ����� ��ü�� ������ static Texture ��ü
    CircleShape fish;
    bool isCollected;

    Fish(float x, float y) {
        if (!FishImgLoaded) { // �ؽ�ó�� �ε���� �ʾ����� �ε��մϴ�.
            if (!FishImg.loadFromFile("./resources/img/fish.png")) {
                cout << "����� �̹��� �ε� ����" << endl;
                exit(EXIT_FAILURE);
            }
            FishImgLoaded = true; // �̹��� �ε忡 �����ߴٴ� ǥ�ø� �մϴ�.
        }
        fish.setRadius(30.0f);
        fish.setPosition(x, y);
        fish.setTexture(&FishImg); // ��� ����Ⱑ ���� �ؽ�ó�� ����մϴ�.
        isCollected = false;
    }

    static bool FishImgLoaded; // �ؽ�ó �ε� ���θ� ��Ÿ���� static ����
};

bool Fish::FishImgLoaded = false; // �ʱ� ���´� false�� �����մϴ�.
Texture Fish::FishImg; // Static ��� ���� ����


int main() {
    // â ����
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Cat's Great Adventure");

    // �̹��� �ε�
    Texture CityImg;
    if (!CityImg.loadFromFile("./resources/img/cityImg.jpg")) {
        return EXIT_FAILURE;
    }
    Sprite backgroundSprite(CityImg);

    Texture catImg1;
    catImg1.loadFromFile("./resources/img/Cat_Img3.png");
    Texture catImg2;
    catImg2.loadFromFile("./resources/img/Cat_Img3_1.png");

    // �⺻ �� ����
    sf::View defaultView = window.getDefaultView();

    Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/H2GTRE.TTF")) {
        cout << "��Ʈ �ε� �ȵ�" << endl;
        return EXIT_FAILURE;
    }

    // ������ ���� �ؽ�Ʈ ��ü �ʱ�ȭ
    Text scoreText;
    scoreText.setFont(font);          // ��Ʈ ����
    scoreText.setCharacterSize(24);   // �ؽ�Ʈ ũ�� ����
    scoreText.setFillColor(Color::White);  // �ؽ�Ʈ �� ����
    scoreText.setPosition(10, 10);    // �ؽ�Ʈ ��ġ ����

    // ����� ��������Ʈ ����
    RectangleShape catTexture;
    catTexture.setTexture(&catImg1);
    catTexture.setPosition(100, 400);
    catTexture.setSize(Vector2f(100, 55)); // ���� ũ�⸦ 200 �ȼ��� ����

    // ���� ��������Ʈ ����
    std::vector<Stool> stools;

    stools.push_back(Stool(100, 700, 100, 10));
    stools.push_back(Stool(300, 600, 100, 10));
    stools.push_back(Stool(500, 500, 100, 10));
    stools.push_back(Stool(700, 400, 100, 10));
    stools.push_back(Stool(900, 300, 100, 10));
    stools.push_back(Stool(1100, 500, 100, 10));
    stools.push_back(Stool(1300, 400, 100, 10));
    stools.push_back(Stool(1500, 300, 100, 10));
    stools.push_back(Stool(1700, 200, 100, 10));
    stools.push_back(Stool(1900, 100, 100, 10));
    stools.push_back(Stool(400, 730, 100, 10));
    stools.push_back(Stool(600, 630, 100, 10));
    stools.push_back(Stool(800, 580, 100, 10));
    stools.push_back(Stool(1100, 230, 100, 10));
    stools.push_back(Stool(1400, 130, 100, 10));


    // �߷� ����
    float gravity = 1000.0f; // �߷��� ũ�� ����
    float jumpStrength = -500.0f; // �������� ũ�� ����
    Vector2f velocity(0.0f, 0.0f);

    // ���� ���� �ʱ�ȭ
    int score = 0;
    scoreText.setString("Score: " + to_string(score)); // �ʱ� ���� ���ڿ� ����

    // ����� ����
    std::vector<Fish> fishes;
    for (auto& stool : stools) {
        Vector2f fishPos = stool.getFishPosition(30.0f); // 30.0f�� ����� CircleShape�� �������Դϴ�.
        fishes.emplace_back(fishPos.x, fishPos.y);
    }

    // �ٴ� ���� ����
    float groundHeight = 1200.0f;

    // �̵� �ӵ� ����
    float moveSpeed = 300.0f; // �ʴ� �̵� �ȼ� ���� ����

    // W Ű�� ������ �� ���� ������ ���θ� ��Ÿ���� ����
    bool isJumping = false;

    // �� �� ���� ������ �����ϵ��� �� ����
    bool canJump = true;

    float scrollSpeed = 0.0f; // ��ũ�� �ӵ�

    // �̵� ������ ��Ÿ���� ����
    int moveDirection = 0; // 0: ����, -1: ����, 1: ������

    // ����̰� ���� ���� �ִ����� Ȯ���ϴ� ����
    bool onStool = false;


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
                if (event.key.code == sf::Keyboard::W && !isJumping && canJump) {
                    // W Ű�� ������ ���� ����
                    velocity.y = jumpStrength;
                    isJumping = true;
                    canJump = false; // �� �̻� �������� ���ϵ��� ����
                }
                if (event.key.code == sf::Keyboard::A) {
                    // A Ű�� ������ �������� �̵�
                    moveDirection = -1;
                }
                if (event.key.code == sf::Keyboard::D) {
                    // D Ű�� ������ ���������� �̵�
                    moveDirection = 1;
                }

            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W) {
                    // W Ű�� ������ ���� ����
                    isJumping = false;
                }
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
                    // A �Ǵ� D Ű�� ������ �̵� ����
                    moveDirection = 0;
                }
            }
        }




        // �߷� ����
        velocity.y += gravity * dt;

        // �̵� ����
        float moveDirectionX = moveSpeed * moveDirection * dt;
        catTexture.move(moveDirectionX, 0);

        // �̵� ���⿡ ���� ��������Ʈ�� ������
        if (moveDirectionX > 0) {
            catTexture.setTexture(&catImg1);
        }
        else if (moveDirectionX < 0) {
            catTexture.setTexture(&catImg2);
        }

        // �̵��� �����ϱ� ���� �ӵ��� ��ġ�� ����
        catTexture.move(0, velocity.y * dt);

        // ���ǰ��� �浹 ó��
        for (Stool& stool : stools) {
            if (catTexture.getGlobalBounds().intersects(stool.stool.getGlobalBounds())) {
                // ���� ���� �ִ��� Ȯ��
                float catBottom = catTexture.getPosition().y + catTexture.getSize().y;
                float stoolTop = stool.stool.getPosition().y;
                // �緯���� ���� �߰��Ͽ� '�Ѿ��' ������ �ذ�
                if (velocity.y > 0 && catBottom < stoolTop + 10) { // 10�� �緯���� ���Դϴ�
                    velocity.y = 0; // �߷��� �缳��
                    catTexture.setPosition(catTexture.getPosition().x, stoolTop - catTexture.getSize().y); // ����̸� ���� ���� ��ġ��Ŵ
                    onStool = true;
                    canJump = true; // �ٽ� ������ �� �ְ� ����
                }
            }
        }

        // ������ ������� �浹 ó��
        for (Fish& fish : fishes) {
            if (!fish.isCollected && catTexture.getGlobalBounds().intersects(fish.fish.getGlobalBounds())) {
                fish.isCollected = true; // ����⸦ �����ߴٰ� ǥ��
                score += 100; // ������ �߰�
                scoreText.setString("Score: " + to_string(score)); // ���� ������Ʈ
            }
        }

        // ������� ���� ��ġ�� ����ϴ�.
        sf::Vector2f catPosition = catTexture.getPosition();

        // �並 �����ϰ� ������� ��ġ�� �߽��� ����ϴ�.
        sf::View view;
        view.setCenter(catPosition);
        view.setSize(1600, 800);

        // �����쿡 �並 �����մϴ�.
        window.setView(view);

        // �並 ������Ʈ�ϱ� ���� ����� ��ġ�� ���� �߽ɿ� ����ϴ�.
        backgroundSprite.setPosition(view.getCenter().x - window.getSize().x / 2, view.getCenter().y - window.getSize().y / 2);

        // ������ �並 ������Ʈ
        view.setCenter(catTexture.getPosition()); // ����̸� �߽����� �並 �����մϴ�.
        window.setView(view);


        // ȭ�� �����
        window.clear();

        // ��� ��������Ʈ �׸���
        window.draw(backgroundSprite);

        // ����� ��������Ʈ �׸���
        window.draw(catTexture);

        // ���� ��������Ʈ �׸���
        for (const Stool& stool : stools)
            window.draw(stool.stool);

        // ����� �׸���
        for (const Fish& fish : fishes) {
            if (!fish.isCollected) {
                window.draw(fish.fish);
            }
        }
        // �⺻ ��� ��ȯ�Ͽ� ���� �ؽ�Ʈ �׸���
        window.setView(defaultView);
        window.draw(scoreText);

        // ȭ�� ������Ʈ
        window.display();
    }

    return EXIT_SUCCESS;
}