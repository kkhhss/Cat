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

    // 발판 위에 물고기를 배치하기 위한 위치를 반환하는 함수
    Vector2f getFishPosition(float fishRadius) const {
        float x = stool.getPosition().x + ((stool.getSize().x - fishRadius * 2) / 2); // 발판의 중앙
        float y = stool.getPosition().y - 80; // 발판의 상단
        return Vector2f(x, y);
    }

private:

};

class Fish {
public:
    static Texture FishImg; // 모든 물고기 객체가 공유할 static Texture 객체
    CircleShape fish;
    bool isCollected;

    Fish(float x, float y) {
        if (!FishImgLoaded) { // 텍스처가 로드되지 않았으면 로드합니다.
            if (!FishImg.loadFromFile("./resources/img/fish.png")) {
                cout << "물고기 이미지 로드 실패" << endl;
                exit(EXIT_FAILURE);
            }
            FishImgLoaded = true; // 이미지 로드에 성공했다는 표시를 합니다.
        }
        fish.setRadius(30.0f);
        fish.setPosition(x, y);
        fish.setTexture(&FishImg); // 모든 물고기가 같은 텍스처를 사용합니다.
        isCollected = false;
    }

    static bool FishImgLoaded; // 텍스처 로드 여부를 나타내는 static 변수
};

bool Fish::FishImgLoaded = false; // 초기 상태는 false로 설정합니다.
Texture Fish::FishImg; // Static 멤버 변수 정의


int main() {
    // 창 생성
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Cat's Great Adventure");

    // 이미지 로드
    Texture CityImg;
    if (!CityImg.loadFromFile("./resources/img/cityImg.jpg")) {
        return EXIT_FAILURE;
    }
    Sprite backgroundSprite(CityImg);

    Texture catImg1;
    catImg1.loadFromFile("./resources/img/Cat_Img3.png");
    Texture catImg2;
    catImg2.loadFromFile("./resources/img/Cat_Img3_1.png");

    // 기본 뷰 저장
    sf::View defaultView = window.getDefaultView();

    Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/H2GTRE.TTF")) {
        cout << "폰트 로드 안됨" << endl;
        return EXIT_FAILURE;
    }

    // 점수를 위한 텍스트 객체 초기화
    Text scoreText;
    scoreText.setFont(font);          // 폰트 설정
    scoreText.setCharacterSize(24);   // 텍스트 크기 설정
    scoreText.setFillColor(Color::White);  // 텍스트 색 설정
    scoreText.setPosition(10, 10);    // 텍스트 위치 설정

    // 고양이 스프라이트 생성
    RectangleShape catTexture;
    catTexture.setTexture(&catImg1);
    catTexture.setPosition(100, 400);
    catTexture.setSize(Vector2f(100, 55)); // 세로 크기를 200 픽셀로 설정

    // 발판 스프라이트 생성
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


    // 중력 설정
    float gravity = 1000.0f; // 중력을 크게 설정
    float jumpStrength = -500.0f; // 점프력을 크게 설정
    Vector2f velocity(0.0f, 0.0f);

    // 점수 변수 초기화
    int score = 0;
    scoreText.setString("Score: " + to_string(score)); // 초기 점수 문자열 설정

    // 물고기 생성
    std::vector<Fish> fishes;
    for (auto& stool : stools) {
        Vector2f fishPos = stool.getFishPosition(30.0f); // 30.0f는 물고기 CircleShape의 반지름입니다.
        fishes.emplace_back(fishPos.x, fishPos.y);
    }

    // 바닥 높이 설정
    float groundHeight = 1200.0f;

    // 이동 속도 설정
    float moveSpeed = 300.0f; // 초당 이동 픽셀 수로 변경

    // W 키를 눌렀을 때 점프 중인지 여부를 나타내는 변수
    bool isJumping = false;

    // 딱 한 번만 점프가 가능하도록 할 변수
    bool canJump = true;

    float scrollSpeed = 0.0f; // 스크롤 속도

    // 이동 방향을 나타내는 변수
    int moveDirection = 0; // 0: 정지, -1: 왼쪽, 1: 오른쪽

    // 고양이가 발판 위에 있는지를 확인하는 변수
    bool onStool = false;


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
                if (event.key.code == sf::Keyboard::W && !isJumping && canJump) {
                    // W 키를 누르면 점프 시작
                    velocity.y = jumpStrength;
                    isJumping = true;
                    canJump = false; // 더 이상 점프하지 못하도록 설정
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
        float moveDirectionX = moveSpeed * moveDirection * dt;
        catTexture.move(moveDirectionX, 0);

        // 이동 방향에 따라 스프라이트를 뒤집음
        if (moveDirectionX > 0) {
            catTexture.setTexture(&catImg1);
        }
        else if (moveDirectionX < 0) {
            catTexture.setTexture(&catImg2);
        }

        // 이동을 적용하기 위해 속도를 위치에 더함
        catTexture.move(0, velocity.y * dt);

        // 발판과의 충돌 처리
        for (Stool& stool : stools) {
            if (catTexture.getGlobalBounds().intersects(stool.stool.getGlobalBounds())) {
                // 발판 위에 있는지 확인
                float catBottom = catTexture.getPosition().y + catTexture.getSize().y;
                float stoolTop = stool.stool.getPosition().y;
                // 톨러런스 값을 추가하여 '넘어서는' 문제를 해결
                if (velocity.y > 0 && catBottom < stoolTop + 10) { // 10은 톨러런스 값입니다
                    velocity.y = 0; // 중력을 재설정
                    catTexture.setPosition(catTexture.getPosition().x, stoolTop - catTexture.getSize().y); // 고양이를 발판 위에 위치시킴
                    onStool = true;
                    canJump = true; // 다시 점프할 수 있게 설정
                }
            }
        }

        // 물고기와 고양이의 충돌 처리
        for (Fish& fish : fishes) {
            if (!fish.isCollected && catTexture.getGlobalBounds().intersects(fish.fish.getGlobalBounds())) {
                fish.isCollected = true; // 물고기를 수집했다고 표시
                score += 100; // 점수를 추가
                scoreText.setString("Score: " + to_string(score)); // 점수 업데이트
            }
        }

        // 고양이의 현재 위치를 얻습니다.
        sf::Vector2f catPosition = catTexture.getPosition();

        // 뷰를 생성하고 고양이의 위치에 중심을 맞춥니다.
        sf::View view;
        view.setCenter(catPosition);
        view.setSize(1600, 800);

        // 윈도우에 뷰를 적용합니다.
        window.setView(view);

        // 뷰를 업데이트하기 전에 배경의 위치를 뷰의 중심에 맞춥니다.
        backgroundSprite.setPosition(view.getCenter().x - window.getSize().x / 2, view.getCenter().y - window.getSize().y / 2);

        // 게임의 뷰를 업데이트
        view.setCenter(catTexture.getPosition()); // 고양이를 중심으로 뷰를 설정합니다.
        window.setView(view);


        // 화면 지우기
        window.clear();

        // 배경 스프라이트 그리기
        window.draw(backgroundSprite);

        // 고양이 스프라이트 그리기
        window.draw(catTexture);

        // 발판 스프라이트 그리기
        for (const Stool& stool : stools)
            window.draw(stool.stool);

        // 물고기 그리기
        for (const Fish& fish : fishes) {
            if (!fish.isCollected) {
                window.draw(fish.fish);
            }
        }
        // 기본 뷰로 전환하여 점수 텍스트 그리기
        window.setView(defaultView);
        window.draw(scoreText);

        // 화면 업데이트
        window.display();
    }

    return EXIT_SUCCESS;
}