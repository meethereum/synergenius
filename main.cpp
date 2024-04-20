#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <chrono>
#include <thread>
#include "mysql_functions.h"

using namespace std;
bool flag=true;
std::string username = "";
std::string password = "";
connection_details mysql_details = {"localhost", "root", "root", "mydb"};
int userid=27;
int current_capital=1000000;
int initial_capital=900000;
struct ShapeWithText {
        sf::RectangleShape rectangle;
        sf::Text text;
    };

struct Feedback {
    string sender_username;
    string feedback_text;
};



void viewFeedback() {
    // Construct the SQL query to fetch feedback along with user information using JOIN
    string query = "SELECT tblUsers.uname, tblUsers.address, tblUsers.phone, Feedback.feedback_text "
                   "FROM Feedback "
                   "JOIN tblUsers ON tblUsers.userid = Feedback.sender_id"; // Assuming userid is the primary key in the Users table

    // Execute the query
    MYSQL* connection = mysql_init(NULL);
    if (connection == NULL) {
        cerr << "Error initializing MySQL connection." << endl;
        return;
    }

    if (mysql_real_connect(connection, "localhost", "root", "root", "mydb", 0, NULL, 0) == NULL) {
        cerr << "Error connecting to MySQL database: " << mysql_error(connection) << endl;
        mysql_close(connection);
        return;
    }

    if (mysql_query(connection, query.c_str())) {
        cerr << "MySQL Query Error: " << mysql_error(connection) << endl;
        mysql_close(connection);
        return;
    }

    // Get the result set
    MYSQL_RES* result = mysql_store_result(connection);
    if (result == NULL) {
        cerr << "Error fetching result set: " << mysql_error(connection) << endl;
        mysql_close(connection);
        return;
    }

    // Check if there are no feedback
    if (mysql_num_rows(result) == 0) {
        cout << "No feedback available." << endl;
    } else {
        // Print the feedback along with user information
        cout << "Feedback:" << endl;
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            cout << "Username: " << row[0] << endl;
            cout << "Address: " << row[1] << endl;
            cout << "Phone: " << row[2] << endl;
            cout << "Feedback: " << row[3] << endl;
            cout << "------------------------" << endl;
        }
    }

    // Free the result set
    mysql_free_result(result);

    mysql_close(connection);
}

void addFeedback(const Feedback& feedback) {
    // Construct the SQL insert query
    ostringstream query;
    query << "INSERT INTO Feedback (sender_id, feedback_text) SELECT userid, '" << feedback.feedback_text << "' FROM tblUsers WHERE uname = '" << feedback.sender_username << "'";

    // Execute the query
    MYSQL* connection = mysql_connection_setup(mysql_details);
    if (mysql_query(connection, query.str().c_str())) {
        cerr << "MySQL Query Error: " << mysql_error(connection) << std::endl;
        mysql_close(connection);
        return;
    }

    cout << "Feedback added successfully." << endl;

    mysql_close(connection);
}

class funtionality {
public:
    void Financials();
    void Stats();
    void Recommendations();
    void Inventory();
};
class Options:funtionality{
    public:
    int numSquares;
    std::vector<ShapeWithText> squares;
    Options(sf::RenderWindow& window, const std::vector<std::string>& texts);
     
};

class exits
{
    public:
    exits()
    {
        sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Genesis trial", sf::Style::Fullscreen);
        Options options(window,{"financials","recomendations","inventory"});
    }
};
class inputs{
    public:
    vector<string>database1={" Bread "," Toast "," Cake "};
        vector<string>database2={" 30 "," 50 "," 300 "};
        vector<string>database3={" 300 "," 500 "," 300 "};
    void add()
    {
        cout<<endl<<endl;
        cout<<".................................................................."<<endl<<endl;
        
        cout<<"Do you Want to continue? "<<endl<<"Yes/No"<<endl;
        string req;
        cin>>req;
        if(tolower(req[0])=='y')
        {
           cout << "\n1. Add to Inventory\n2. Dispatch Inventory\n 3.Show inventory \n Enter your choice (1-3): ";
                            int inventoryChoice;
                            cin >> inventoryChoice;
                            if (inventoryChoice == 1) {
                                int product, quantity;
                                cout << "Enter product price: ";
                                cin >> product;
                                cout << "Enter quantity: ";
                                cin >> quantity;

    // Construct the SQL update query
    ostringstream query;
    query << "UPDATE tblUsers SET current_capital = current_capital - " << product*quantity ;

    

    // Execute the query
    MYSQL *connection = mysql_connection_setup(mysql_details);
  

    if (mysql_query(connection, query.str().c_str())) {
        cerr << "MySQL Query Error: " << mysql_error(connection) << std::endl;
        mysql_close(connection);
        return;
    }

    cout << "Updated current_capital in tblUsers." << endl;

    mysql_close(connection);

                            } else if (inventoryChoice == 2) {
                                int product, quantity;
                                cout << "Enter product (1. Bread, 2. Toast, 3. Cake): ";
                                cin >> product;
                                cout << "Enter quantity: ";
                                cin >> quantity;
                                //inventory.dispatchInventory(product, quantity);

                                
                            } else {
                                cout << "showing inventory: " << endl;
                                display();
                            }
                          
            cout<<endl<<endl<<"Press any key and enter to exit ";
            string tempo;
            cin>>tempo;
            exits obj;
            //add data to sql database
        
        }
        else
        {
                exits obj;
        }
    }
        void display()
        {
        //sql command to display 
            for(int i=0;i<database1.size();i++)
            {
                cout<<endl<<endl;
                cout<<".................................................................."<<endl<<endl;
        
                cout<<"Name of the Product : "<<database1[i]<<endl;
                cout<<"Price of the Product : "<<database2[i]<<endl;
                cout<<"Quantity of the Product : "<<database3[i]<<endl;
                cout<<endl<<endl;
                cout<<".................................................................."<<endl<<endl;

            }
            char temp;
            cout<<"press any key to exit?  ";
            cin>>temp;
                exits obj;
            
        }
};


    void funtionality::Financials() {
        
        cout<<endl<<endl;
        cout<<".................................................................."<<endl<<endl;
        
        cout<<endl<<"1] Show financials "<<endl<<endl<<"2] exit "<<endl<<endl;
        
        int n;
        cin>>n;
        if(n==1)
        {
            char temp;
            cout << "Initial capital invested: " << current_capital << endl<<" capital remaining: " << initial_capital << endl<<" profit/loss: "<< -current_capital+initial_capital<<endl<<" profit/loss in %: "<<(current_capital-initial_capital)/(float)initial_capital<<endl;
            cout<<"press any key to exit ";
            cin>>temp;
            exits obj;
        }
        else
        {
            exits obj;
        }
        
    }

    void funtionality::Stats() {
        cout<<"............................................................."<<endl;
        cout<<endl<<"1] Show Stats "<<endl<<endl<<"2] exit "<<endl<<endl;
        cout<<"............................................................."<<endl<<endl;
        int n;
        cin>>n;
        if(n==1)
        {
            //mysql query
            char temp;
            cout<<"do you want to exit? (y,n) ";
            cin>>temp;
            if (temp=='y')
            {
                exits obj;
            }
        }
        else
        {
            exits obj;
        }
        
    }
    
void  funtionality::Recommendations() {
        cout<<endl<<endl;
        cout<<".................................................................."<<endl<<endl;
        viewFeedback();
        char temp;
        
            cout<<"Do you Want to send a broadcast message? (y/n) "<<endl;
            cin>>temp;
        
        
        if(temp=='y')
        {
            //send message
            Feedback userFeedback;
            userFeedback.sender_username = username; // Replace with actual username
            userFeedback.feedback_text ;
            cout << "Enter your broadcast message: ";
            cin>>userFeedback.feedback_text;

    // Call addFeedback to insert the feedback
            addFeedback(userFeedback);
            cout<<endl<<endl;
            cout<<"Do You Want To add Another feedback? (y/n)" ;
            char ch;
            cin>>ch;
            if(ch=='y')
            {
                Recommendations();
            }
            else
            {
            cout<<"Do you want to exit? (press any key and enter ) ";

            string a;
            cin>>a;
            exits obj;
            }
        }
        else
        {
            exits obj;
        }
        
        
    }    void  funtionality::Inventory() {
        inputs obj;
        obj.add();
        
    }


    Options::Options(sf::RenderWindow& window, const std::vector<std::string>& texts) {
        numSquares = texts.size();
        squares.resize(numSquares);

        sf::Font font;
        if (!font.loadFromFile("Arial.ttf")) {
            std::cerr << "Error loading font file" << std::endl;
            return;
        }

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

        window.draw(headline);
        for (const auto& shape : squares) {
            window.draw(shape.rectangle);
            window.draw(shape.text);
        }
        window.display();

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    for (int i = 0; i < this->numSquares; ++i) {
                        if (this->squares[i].rectangle.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                            switch (i) {
                                case 0:
                                    window.clear(); 
                                    window.close();
                                    Financials();
                                    break;
                                case 1:
                                    window.clear();
                                    window.close();
                                    flag=true;
                                    Recommendations();
                                    break;
                                case 2:
                                    window.clear();
                                    window.close();
                                    Inventory();
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

//...............................................................................................

//......................................................................................


class LoginPage: public inputs, public funtionality{

public:
    LoginPage(sf::RenderWindow& window) {
        if (!font.loadFromFile("Arial.ttf")) {
            std::cerr << "Error loading font file" << std::endl;
            return;
        }

        // Set up text parameters
        setupTextParameters();

        // Set up input box parameters
        setupInputBoxParameters();

        // Set up cursor parameters
        setupCursorParameters();

        // Set up login button parameters
        setupLoginButtonParameters();

        // Start the main loop
        mainLoop(window);
    }

private:
    // Font
    sf::Font font;

    // Username
    sf::Text usernameLabel;
    sf::RectangleShape usernameInputBox;
    sf::Text usernameText;

    // Password
    sf::Text passwordLabel;
    sf::RectangleShape passwordInputBox;
    sf::Text passwordText;

    // Login button
    sf::RectangleShape loginButton;
    sf::Text loginButtonText;

    // Error message
    sf::Text errorText;

    // Cursor
    sf::RectangleShape cursor;
    bool cursorVisible = true;
    bool inputBoxActive = false;

    // Text parameters
    void setupTextParameters() {
        // Username label
        usernameLabel.setFont(font);
        usernameLabel.setString("Username:");
        usernameLabel.setCharacterSize(20);
        usernameLabel.setFillColor(sf::Color::White);
        usernameLabel.setPosition(100.f, 150.f);

        // Username text
        usernameText.setFont(font);
        usernameText.setCharacterSize(20);
        usernameText.setFillColor(sf::Color::Black);
        usernameText.setPosition(220.f, 150.f);

        // Password label
        passwordLabel.setFont(font);
        passwordLabel.setString("Password:");
        passwordLabel.setCharacterSize(20);
        passwordLabel.setFillColor(sf::Color::White);
        passwordLabel.setPosition(100.f, 200.f);

        // Password text
        passwordText.setFont(font);
        passwordText.setCharacterSize(20);
        passwordText.setFillColor(sf::Color::Black);
        passwordText.setPosition(220.f, 200.f);

        // Error text
        errorText.setFont(font);
        errorText.setCharacterSize(18);
        errorText.setFillColor(sf::Color::Red);
        errorText.setPosition(100.f, 350.f);
    }

    // Input box parameters
    void setupInputBoxParameters() {
        // Username input box
        usernameInputBox.setSize(sf::Vector2f(200.f, 30.f));
        usernameInputBox.setFillColor(sf::Color::White);
        usernameInputBox.setPosition(220.f, 150.f);
        usernameInputBox.setOutlineThickness(1.f);
        usernameInputBox.setOutlineColor(sf::Color::White);

        // Password input box
        passwordInputBox.setSize(sf::Vector2f(200.f, 30.f));
        passwordInputBox.setFillColor(sf::Color::White);
        passwordInputBox.setPosition(220.f, 200.f);
        passwordInputBox.setOutlineThickness(1.f);
        passwordInputBox.setOutlineColor(sf::Color::White);
    }

    // Cursor parameters
    void setupCursorParameters() {
        cursor.setSize(sf::Vector2f(1.f, 20.f));
        cursor.setFillColor(sf::Color::Black);
        cursor.setPosition(225.f, 175.f);
    }

    // Login button parameters
    void setupLoginButtonParameters() {
        loginButton.setSize(sf::Vector2f(100.f, 50.f));
        loginButton.setFillColor(sf::Color(30, 144, 255)); // Blue color
        loginButton.setPosition(220.f, 270.f);

        loginButtonText.setFont(font);
        loginButtonText.setString("Login");
        loginButtonText.setCharacterSize(20);
        loginButtonText.setFillColor(sf::Color::White);
        loginButtonText.setPosition(250.f, 280.f);
    }

    // Main loop
    void mainLoop(sf::RenderWindow& window) {
        while (window.isOpen()) {
            // Handle events
            handleEvents(window);

            // Update cursor visibility
            updateCursor();

            // Draw everything
            window.clear(sf::Color(30, 30, 30));
            drawElements(window);
            window.display();

            // Pause to control refresh rate
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    // Handle events
    void handleEvents(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::TextEntered:
                    handleTextInput(event);
                    break;
                case sf::Event::MouseButtonPressed:
                    handleMouseClick(window, event);
                    break;
                default:
                    break;
            }
        }
    }

    // Handle text input
    void handleTextInput(sf::Event& event) {
        if (inputBoxActive) {
            if (event.text.unicode == 8) { // Backspace
                if (activeInputBox == 0 && !usernameString.empty()) {
                    usernameString.pop_back();
                } else if (activeInputBox == 1 && !passwordString.empty()) {
                    passwordString.pop_back();
                }
            } else if (event.text.unicode < 128) {
                if (activeInputBox == 0 && usernameText.getGlobalBounds().width < 180.f) {
                    usernameString += static_cast<char>(event.text.unicode);
                } else if (activeInputBox == 1 && passwordText.getGlobalBounds().width < 180.f) {
                    passwordString += static_cast<char>(event.text.unicode);
                }
            }
        }
    }

    // Handle mouse click
    void handleMouseClick(sf::RenderWindow& window, sf::Event& event) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (usernameInputBox.getGlobalBounds().contains(mousePos)) {
            inputBoxActive = true;
            activeInputBox = 0;
        } else if (passwordInputBox.getGlobalBounds().contains(mousePos)) {
            inputBoxActive = true;
            activeInputBox = 1;
        } else {
            inputBoxActive = false;
        }

        if (loginButton.getGlobalBounds().contains(mousePos)) {
            // Perform login action
            loginAction(window);
        }
    }

    // Update cursor visibility
    void updateCursor() {
        static sf::Clock cursorTimer;
        if (cursorTimer.getElapsedTime().asMilliseconds() > 500) {
            cursorVisible = !cursorVisible;
            cursorTimer.restart();
        }
    }

    // Draw all elements
    void drawElements(sf::RenderWindow& window) {
        // Draw labels
        window.draw(usernameLabel);
        window.draw(passwordLabel);

        // Draw input boxes
        window.draw(usernameInputBox);
        window.draw(passwordInputBox);

        // Draw input text
        usernameText.setString(usernameString);
        window.draw(usernameText);
        passwordText.setString(passwordString);
        window.draw(passwordText);

        // Draw cursor if input box is active
        if (inputBoxActive && cursorVisible) {
            if (activeInputBox == 0) {
                cursor.setPosition(usernameText.getGlobalBounds().left + usernameText.getGlobalBounds().width, 175.f);
            } else if (activeInputBox == 1) {
                cursor.setPosition(passwordText.getGlobalBounds().left + passwordText.getGlobalBounds().width, 225.f);
            }
            window.draw(cursor);
        }

        // Draw login button
        window.draw(loginButton);
        window.draw(loginButtonText);

        // Draw error text
        window.draw(errorText);
    }

    // Track which input box is active (0 for username, 1 for password)
    int activeInputBox = 0;

    // Text entered in input boxes
    std::string usernameString;
    std::string passwordString;

    // Function to handle login action
    // Function to handle login action
void loginAction(sf::RenderWindow& window) {
    // Retrieve the username and password entered by the user
    username = usernameString;
    password = passwordString;

    // Define MySQL connection details
    struct connection_details mysql_details = {
        "localhost",
        "root",
        "root",
        "mydb"
    };

    // Set up MySQL connection
    MYSQL *connection = mysql_connection_setup(mysql_details);
    if (!connection) {
        errorText.setString("Failed to connect to MySQL server");
        return;
    }

    // Construct SQL query to retrieve user information
    std::ostringstream query;
    query << "SELECT * FROM tblUsers WHERE uname='" << username << "' AND password='" << password << "'";

    // Execute the query
    MYSQL_RES* res = mysql_perform_query(connection, query.str().c_str());
    if (!res) {
        errorText.setString("Failed to execute MySQL query");
        mysql_close(connection);
        return;
    }

    // Check if any rows were returned
    MYSQL_ROW row = mysql_fetch_row(res);

    if (row) {
        // User authenticated successfully
        initial_capital=atoi(row[4]);
        current_capital=atoi(row[5]);
        userid=atoi(row[0]);
        window.clear();
        Options Options(window,{"financials","recomendations","inventory"});
        //std::cout<<"give options to users";

    } else {
        // Invalid credentials
        errorText.setString("Invalid username or password");
    }

   

    // Free resources and close MySQL connection
    mysql_free_result(res);
    mysql_close(connection);
}


};
//......................................................................................
class introPage{
    public:
    introPage(){
    // Create the window
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Supply Chain Management System", sf::Style::Fullscreen);

    // Set background color to black
    window.clear(sf::Color::Black);

    // Create headline text
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error loading font file" << std::endl;
    }

    sf::Text headline("Supply Chain Management System", font, 42);
    headline.setFillColor(sf::Color::White);
    headline.setStyle(sf::Text::Bold);
    // Set position to center
    headline.setPosition((window.getSize().x - headline.getGlobalBounds().width) / 2, 50);

    // Create "get started" text inside a square shape
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setFillColor(sf::Color::Blue); // Dark blue color
    button.setPosition((window.getSize().x - button.getSize().x) / 2, 250);

    sf::Text buttonText("Get Started", font, 30);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setStyle(sf::Text::Bold);
    // Set position of text inside the button
    buttonText.setPosition(button.getPosition().x + (button.getSize().x - buttonText.getGlobalBounds().width) / 2, button.getPosition().y + (button.getSize().y - buttonText.getGlobalBounds().height) / 2);

    // Create "make it easy" text
    sf::Text footerText("Created By Synergenius", font, 27);
    footerText.setFillColor(sf::Color::White);
    footerText.setStyle(sf::Text::Bold);
    // Set position to center
    footerText.setPosition((window.getSize().x - footerText.getGlobalBounds().width) / 2, 500);

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Check if the left mouse button is pressed and the mouse cursor is within the button's area
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                    // Call the emp function
                    LoginPage loginPage(window);
                }
            }
        }

        // Clear the window
        window.clear();

        // Draw elements
        window.draw(headline);
        window.draw(button);
        window.draw(buttonText);
        window.draw(footerText);

        // Display content
        window.display();
    }
    }

};






//......................................................................................
int main() {
    introPage obj1;
    return 0;
}