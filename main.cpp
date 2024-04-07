#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

class Options {
public:
    Options(sf::RenderWindow& window, const std::vector<std::string>& texts) {
        numSquares = texts.size();
        squares.resize(numSquares);

        sf::Font font;
        if (!font.loadFromFile("Arial.ttf")) {
            std::cerr << "Error loading font file" << std::endl;
            return;
        }

        sf::RectangleShape homeContainer(sf::Vector2f(100.f, 50.f));
        homeContainer.setFillColor(sf::Color::Blue);
        homeContainer.setPosition(20.f, 20.f);

        sf::Text homeText("Home", font, 20);
        homeText.setFillColor(sf::Color::White);
        homeText.setPosition(30.f, 30.f);

        sf::Text headline("Choose from the following options", font, 40);
        headline.setFillColor(sf::Color::White);
        headline.setStyle(sf::Text::Bold);
        headline.setPosition((window.getSize().x - headline.getLocalBounds().width) / 2, 50.f);

        float x = (window.getSize().x - 200 * numSquares - 20 * (numSquares - 1)) / 2.f; // Center the row of squares

        for (int i = 0; i < numSquares; ++i) {
            squares[i].rectangle.setSize(sf::Vector2f(200.f, 100.f));
            squares[i].rectangle.setFillColor(sf::Color::Blue);
            squares[i].rectangle.setPosition(x, 250.f);

            squares[i].text.setString(texts[i]);
            squares[i].text.setFont(font);
            squares[i].text.setCharacterSize(20);
            squares[i].text.setFillColor(sf::Color::White);
            squares[i].text.setPosition(x + 30.f, 290.f);

            x += 220.f;
        }

        window.draw(homeContainer);
        window.draw(homeText);
        window.draw(headline);
        for (const auto& shape : squares) {
            window.draw(shape.rectangle);
            window.draw(shape.text);
        }
        window.display();
    }

    struct ShapeWithText {
        sf::RectangleShape rectangle;
        sf::Text text;
    };

    int numSquares;
    std::vector<ShapeWithText> squares;
};

class Tier1 {
public:
    Tier1(sf::RenderWindow& window) {
        std::vector<std::string> texts = {
            "Financials",
            "Stats",
            "Recommendations",
            "Inventory"
        };

        Options options(window, texts);
        handleEvents(window, options);
    }

    void Financials(sf::RenderWindow& window) {
        std::cout << "Financials function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Stats(sf::RenderWindow& window) {
        std::cout << "Stats function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Recommendations(sf::RenderWindow& window) {
        std::cout << "Recommendations function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Inventory(sf::RenderWindow& window) {
        std::cout << "Inventory function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void handleEvents(sf::RenderWindow& window, Options& options) {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    for (int i = 0; i < options.numSquares; ++i) {
                        if (options.squares[i].rectangle.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                            switch (i) {
                                case 0:
                                    window.clear();
                                    Financials(window);
                                    
                                    break;
                                case 1:
                                    window.clear();
                                    Stats(window);
                                    break;
                                case 2:
                                    window.clear();
                                    Recommendations(window);
                                    break;
                                case 3:
                                    window.clear();
                                    Inventory(window);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
};


class Tier2 {
public:
    Tier2(sf::RenderWindow& window) {
        std::vector<std::string> texts = {
            "Financials",
            "Stats",
            "Recommendations",
            "Inventory"
        };

        Options(window, texts);
    }

    void Financials(sf::RenderWindow& window) {
        std::cout << "Financials function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Stats(sf::RenderWindow& window) {
        std::cout << "Stats function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Recommendations(sf::RenderWindow& window) {
        std::cout << "Recommendations function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Inventory(sf::RenderWindow& window) {
        std::cout << "Inventory function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void handleEvents(sf::RenderWindow& window, Options& options) {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    for (int i = 0; i < options.numSquares; ++i) {
                        if (options.squares[i].rectangle.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                            switch (i) {
                                case 0:
                                    window.clear();
                                    Financials(window);
                                    
                                    break;
                                case 1:
                                    window.clear();
                                    Stats(window);
                                    break;
                                case 2:
                                    window.clear();
                                    Recommendations(window);
                                    break;
                                case 3:
                                    window.clear();
                                    Inventory(window);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

};

class Manufacturer {
public:
    Manufacturer(sf::RenderWindow& window) {
        std::vector<std::string> texts = {
            "Financials",
            "Stats",
            "Recommendations",
            "Inventory"
        };

        Options(window, texts);
    }

    void Financials(sf::RenderWindow& window) {
        std::cout << "Financials function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Stats(sf::RenderWindow& window) {
        std::cout << "Stats function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Recommendations(sf::RenderWindow& window) {
        std::cout << "Recommendations function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Inventory(sf::RenderWindow& window) {
        std::cout << "Inventory function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void handleEvents(sf::RenderWindow& window, Options& options) {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    for (int i = 0; i < options.numSquares; ++i) {
                        if (options.squares[i].rectangle.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                            switch (i) {
                                case 0:
                                    window.clear();
                                    Financials(window);
                                    
                                    break;
                                case 1:
                                    window.clear();
                                    Stats(window);
                                    break;
                                case 2:
                                    window.clear();
                                    Recommendations(window);
                                    break;
                                case 3:
                                    window.clear();
                                    Inventory(window);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

};

class Distributor {
public:
    Distributor(sf::RenderWindow& window) {
        std::vector<std::string> texts = {
            "Financials",
            "Stats",
            "Recommendations",
            "Inventory"
        };

        Options(window, texts);
    }

    void Financials(sf::RenderWindow& window) {
        std::cout << "Financials function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Stats(sf::RenderWindow& window) {
        std::cout << "Stats function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Recommendations(sf::RenderWindow& window) {
        std::cout << "Recommendations function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Inventory(sf::RenderWindow& window) {
        std::cout << "Inventory function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void handleEvents(sf::RenderWindow& window, Options& options) {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    for (int i = 0; i < options.numSquares; ++i) {
                        if (options.squares[i].rectangle.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                            switch (i) {
                                case 0:
                                    window.clear();
                                    Financials(window);
                                    
                                    break;
                                case 1:
                                    window.clear();
                                    Stats(window);
                                    break;
                                case 2:
                                    window.clear();
                                    Recommendations(window);
                                    break;
                                case 3:
                                    window.clear();
                                    Inventory(window);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

};

class Retailer {
public:
    Retailer(sf::RenderWindow& window) {
        std::vector<std::string> texts = {
            "Financials",
            "Stats",
            "Recommendations",
            "Inventory"
        };

        Options(window, texts);
    }

    void Financials(sf::RenderWindow& window) {
        std::cout << "Financials function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Stats(sf::RenderWindow& window) {
        std::cout << "Stats function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Recommendations(sf::RenderWindow& window) {
        std::cout << "Recommendations function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void Inventory(sf::RenderWindow& window) {
        std::cout << "Inventory function called." << std::endl;
        std::vector<std::string> texts = {
            "Show",
            "Add"
        };

        Options options(window,texts);
    }

    void handleEvents(sf::RenderWindow& window, Options& options) {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    for (int i = 0; i < options.numSquares; ++i) {
                        if (options.squares[i].rectangle.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                            switch (i) {
                                case 0:
                                    window.clear();
                                    Financials(window);
                                    
                                    break;
                                case 1:
                                    window.clear();
                                    Stats(window);
                                    break;
                                case 2:
                                    window.clear();
                                    Recommendations(window);
                                    break;
                                case 3:
                                    window.clear();
                                    Inventory(window);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

};

//........................................................................

void  Tier01(sf::RenderWindow& window){
    window.clear();
    Tier1 tire(window);
}
void  Tier02(sf::RenderWindow& window){
    window.clear();
    Tier2 tiree(window);
}
void  manu0(sf::RenderWindow& window){
    window.clear();
    Manufacturer Manu(window);
}
void  distri0(sf::RenderWindow& window){
    window.clear();
    Distributor Distri(window);
}
void  retail0(sf::RenderWindow& window){
    window.clear();
    Retailer Retail(window);
}

//...............................................................................................
class home
{
public:
    home(sf::RenderWindow& window) {
        // Load font
        sf::Font font;
        font.loadFromFile("Arial.ttf");

        const int numSquares = 5;
        std::vector<sf::RectangleShape> squares(numSquares);

        std::vector<std::string> texts = {
            "Tier1 Supplier",
            "Tier2 Supplier",
            "Manufacturer",
            "Distributor",
            "Retailer"
        };

        sf::Text headline("Choose from the following options", font, 40);
        headline.setFillColor(sf::Color::White);
        headline.setStyle(sf::Text::Bold);
        headline.setPosition((window.getSize().x - headline.getLocalBounds().width) / 2, 50.f);

        float x = (window.getSize().x - 200 * numSquares - 20 * (numSquares - 1)) / 2.f; // Center the row of squares

        for (int i = 0; i < numSquares; ++i) {
            squares[i].setSize(sf::Vector2f(200.f, 100.f));
            squares[i].setFillColor(sf::Color::Blue);
            squares[i].setPosition(x, 250.f);

            sf::Text text(texts[i], font, 20);
            text.setFillColor(sf::Color::White);
            text.setPosition(x + 30.f, 290.f);

            window.draw(squares[i]);
            window.draw(text);

            x += 220.f;
        }

        
        window.draw(headline);
        window.display();

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    for (int i = 0; i < numSquares; ++i) {
                        if (squares[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            switch (i) {
                                case 0:
                                    Tier01(window);
                                    break;
                                case 1:
                                    Tier02(window);
                                    break;
                                case 2:
                                    manu0(window);
                                    break;
                                case 3:
                                    distri0(window);
                                    break;
                                case 4:
                                    retail0(window);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
};

//......................................................................................

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Genesis trial", sf::Style::Fullscreen);
    home obj(window);
    return 0;
}
