#include "Game.h"
#include "SDL_Plotter.h"
#include "Vec2.h"
#include "Color.h"
#include "Drawable.h"
#include <fstream>


int main(int argc, char ** argv) {
    Game evilHangman;
    return 0;
}

Game::Game() {
    // Load letter data from files
    for (char c = 'A'; c < 'Z'; c++) {
        try {
            letters[c] = Char(c, CHAR_SIZE);
        }
        catch (const string& fileName) {
            cerr << fileName << " could not be loaded!" << endl;
        }
    }
    cout << "Letters loaded!" << endl;
    
    state = MAIN_MENU;
    
    size = Vec2i(640, 480);
    g = new SDL_Plotter(size.y, size.x, false);
    
    //***************************Main Menu******************************
    //******************************************************************
    
    //lines
    Rectangle line1(7,7,618,3,RED);
    mainMenu.push_back(&line1);
    Rectangle line2(7,472,622,3,RED);
    mainMenu.push_back(&line2);

    Rectangle line3(7,7,3,467,RED);
    mainMenu.push_back(&line3);
    Rectangle line4(626,7,3,467,RED);
    mainMenu.push_back(&line4);
    
    //logo
    evil = new TextField ("Evil");
    evil->setFgColor(RED);
    evil->setLocation(Vec2i(20,16));
    evil->setScale(2);
    mainMenu.push_back(evil);
    hangman = new TextField ("HANGMAN");
    hangman->setFgColor(Color(200,0,0));
    hangman->setLocation(Vec2i(64,53));
    hangman->setScale(3);
    mainMenu.push_back(hangman);
    
    
    //Buttons
    playButton=new Button("PLAY", playAction);
    playButton->setScale(2);
    playButton->setLocation(Vec2i(345,145));
    playButton->setFgColor(_WHITE);
    optionsButton = new Button("OPTIONS", optionsAction);
    optionsButton->setScale(2);
    optionsButton->setLocation(Vec2i(310,280));
    optionsButton->setFgColor(_WHITE);
    quitButton = new Button("QUIT", quitAction);
    quitButton->setScale(2);
    quitButton->setLocation(Vec2i(340,350));
    quitButton->setFgColor(_WHITE);
    scoButton = new Button("HIGH SCORES", optionsAction);
    scoButton->setScale(2);
    scoButton->setLocation(Vec2i(260,210));
    scoButton->setFgColor(_WHITE);
    mainMenu.push_back(playButton);
    mainMenu.push_back(optionsButton);
    mainMenu.push_back(quitButton);
    mainMenu.push_back(scoButton);
    
    

    //STICKMAN
    Rectangle ground(40,400,550,9,BLACK);
    mainMenu.push_back(&ground);
    Rectangle comp1(80,150,5,250,BLACK);
    mainMenu.push_back(&comp1);
    Rectangle comp2(80,150,120,6,BLACK);
    mainMenu.push_back(&comp2);
    Rectangle comp3(200,150,2,30,BLACK);
    mainMenu.push_back(&comp3);
  
    
    stickMan = new StickMan(Vec2i(200,190),BLACK);
    stickMan->addPart();
    stickMan->addPart();
    stickMan->addPart();
    stickMan->addPart();
    stickMan->addPart();
    stickMan->addPart();
    mainMenu.push_back(stickMan);
    
    //***************************Option*********************************
    //******************************************************************
    //lines
    option.push_back(&line1);
    option.push_back(&line2);
    option.push_back(&line3);
    option.push_back(&line4);
    //title
    option.push_back(evil);
    option.push_back(hangman);
    
    //BOTTONS
    evilButton=new Button("EVIL", playAction);
    evilButton->setScale(2);
    evilButton->setLocation(Vec2i(300,190));
    evilButton->setFgColor(_WHITE);
    norButton = new Button("NORMAL",playAction);
    norButton->setScale(2);
    norButton->setLocation(Vec2i(280,290));
    norButton->setFgColor(_WHITE);
    menuButton = new Button("MENU", menuAction);
    menuButton->setScale(2);
    menuButton->setLocation(Vec2i(30,410));
    menuButton->setFgColor(_WHITE);
    quitButton = new Button("QUIT", quitAction);
    quitButton->setScale(2);
    quitButton->setLocation(Vec2i(500,410));
    quitButton->setFgColor(_WHITE);
    option.push_back(evilButton);
    option.push_back(norButton);
    option.push_back(menuButton);
    option.push_back(quitButton);
 
    //draw hangman
    option.push_back(&ground);
    option.push_back(&comp1);
    option.push_back(&comp2);
    option.push_back(&comp3);

    option.push_back(stickMan);

    
    //***************************PLAY***********************************
    //******************************************************************
    //lines
    playScreen.push_back(&line1);
    playScreen.push_back(&line2);
    playScreen.push_back(&line3);
    playScreen.push_back(&line4);
    
    
    //title
    playScreen.push_back(evil);
    playScreen.push_back(hangman);
    TextField stt("start");
    stt.setFgColor(Color(299,0,0));
    stt.setLocation(Vec2i(310,120));
    stt.setScale(3);
    playScreen.push_back(&stt);
    //draw "!"
    Rectangle markk(570,110,10,65,RED);
    playScreen.push_back(&markk);
    Circle cc(Vec2i(574,190),9,RED,true);
    playScreen.push_back(&cc);

    
    //bottons
    menuButton = new Button("MENU",menuAction);
    menuButton->setLocation(Vec2i(30,410));
    menuButton->setSize(Vec2i(100, 40));
    quitButton = new Button ("QUIT",quitAction);
    quitButton->setLocation(Vec2i(500,410));
    quitButton->setSize(Vec2i(100, 40));
    Button subButton ("SUBMIT",playAction);
    subButton.setLocation(Vec2i(400,310));
    subButton.setSize(Vec2i(150, 40));
    playScreen.push_back(menuButton);
    playScreen.push_back(quitButton);
    playScreen.push_back(&subButton);
    
   
    
    //draw hangman
    playScreen.push_back(&ground);
    playScreen.push_back(&comp1);
    playScreen.push_back(&comp2);
    playScreen.push_back(&comp3);

    stickMan =new StickMan(Vec2i(200,190));
    stickMan->addPart();
    stickMan->addPart();
    stickMan->addPart();
    stickMan->addPart();
    stickMan->addPart();
    stickMan->addPart();
    playScreen.push_back(stickMan);
    
    Rectangle block(240,220,340,80,RED,true);
    playScreen.push_back(&block);

    Rectangle aline(250,280,320,5,_WHITE, true);
    playScreen.push_back(&aline);
    
   
    
    
    //****************************Win***********************************
    //******************************************************************
   
    //lines
    win.push_back(&line1);
    win.push_back(&line2);
    win.push_back(&line3);
    win.push_back(&line4);

    
    //"YOU WON"
    TextField winn("YOU WON");
    winn.setFgColor(RED);
    winn.setScale(5);
    winn.setLocation(Vec2i(37,55));
    win.push_back(&winn);
    Circle c1(Vec2i(80,120),8,RED,true);
    Circle c2(Vec2i(560,120),8,RED,true);
    win.push_back(&c1);
    win.push_back(&c1);

    
    //bottons
    win.push_back(menuButton);
    win.push_back(quitButton);

    
    //draw hangman
    Rectangle ground3(40,380,550,9,BLACK);
    win.push_back(&ground3);
    Rectangle comp10(80,190,5,190,BLACK);
    win.push_back(&comp10);
    Rectangle comp11(80,190,100,6,BLACK);
    win.push_back(&comp11);
    Rectangle comp12(180,190,2,30,BLACK);
    win.push_back(&comp12);

    stickMan= new StickMan(Vec2i(180,230));
    stickMan->addPart();
    stickMan->addPart();
    stickMan->addPart();
    stickMan->addPart();
    stickMan->addPart();
    stickMan->addPart();
    win.push_back(stickMan);
    
    TextField urSco("YOUR SCORE:");
    urSco.setLocation(Vec2i(220,200));
    TextField hiscore("Current High:");
    hiscore.setLocation(Vec2i(220,250));
    TextField leave("LEAVE YOUR NAME:");
    leave.setLocation(Vec2i(220,300));
    win.push_back(&urSco);
    win.push_back(&hiscore);
    win.push_back(&leave);

    
    for(int x = 200;x<=580;x+=50)
    {
        line = new Rectangle(x,370,30,4,RED);
        win.push_back(line);
    }
        
   
    //**************************LOSE************************************
    //******************************************************************
    
    
    //lines
    win.push_back(&line1);
    win.push_back(&line2);
    win.push_back(&line3);
    win.push_back(&line4);
    
    //"YOU WON"
    TextField lose("LOSE");
    lose.setFgColor(RED);
    lose.setScale(6);
    lose.setLocation(Vec2i(150,55));
    loseScreen.push_back(&lose);
    
    //bottons
    loseScreen.push_back(menuButton);
    loseScreen.push_back(quitButton);
    
    //draw hangman
    loseScreen.push_back(&ground3);
    loseScreen.push_back(&comp10);
    loseScreen.push_back(&comp11);
    loseScreen.push_back(&comp12);
    loseScreen.push_back(stickMan);
    TextField leave1("LEAVE YOUR NAME:");
    leave1.setLocation(Vec2i(220,200));
    loseScreen.push_back(&leave1);
    
    //draw "!"
    Rectangle mark(200,200,8,60,RED);
    loseScreen.push_back(&mark);
    
    Circle c(Vec2i(204,270),5,RED,true);
    loseScreen.push_back(&c);
    
   
    line = new Rectangle(270,270,240,4,RED);
    loseScreen.push_back(line);

    playButton = new Button("TRY AGAIN",playAction);
    playButton->setScale(2);
    playButton->setLocation(Vec2i(220,310));
    loseScreen.push_back(playButton);
    
    Circle cir1(Vec2i(200,330),10,RED,true);
    loseScreen.push_back(&cir1);
    Circle cir2(Vec2i(535,330),10,RED,true);
    loseScreen.push_back(&cir2);
    
    
    mainLoop();
}




void Game::mainLoop() {
    //cond = SDL_CreateCond();
    //SDL_Thread *updateThread = SDL_CreateThread(update, "Update Thread", this);
    
    while (!quit) {
        //draw();
        switch (state) {
            case MAIN_MENU:
                // Draw main menu
                for (Drawable* d : mainMenu) {
                    d->update(g, this);
                    if(state == MAIN_MENU) d->draw(g);
                }
                
                
            case PLAY:
                // Draw scene, word to guess
                for (Drawable* d : playScreen) {
                    d->update(g, this);
                    if(state == PLAY) d->draw(g);
                }
            case OPTIONS:
                // Draw OPTIONS - evil/mormal
                for (Drawable* d : option) {
                    d->update(g, this);
                    if(state == OPTIONS) d->draw(g);
                }
            case WIN:
                // Draw OPTIONS - evil/mormal
                for (Drawable* d : win) {
                    d->update(g, this);
                    if(state == WIN) d->draw(g);
                }
            case LOSE:
                // Draw OPTIONS - evil/mormal
                for (Drawable* d : loseScreen) {
                    d->update(g, this);
                    if(state == LOSE) d->draw(g);
                }
        }
        
        g->update();
        
        if (g->kbhit()) {
            g->getKey();
        }
        quit = g->getQuit();
    }
    
    //SDL_WaitThread(updateThread, NULL);
}

int update(void* data) {
    Game* game = (Game*)data;
    
    while (!game->g->getQuit()) {
        for (int i = 0; i < game->drawables.size(); i++) {
            game->drawables[i]->update(game->g, game);
        }
    }
    
    return 0;
}

void Game::draw() {
    
}

Game::~Game() {
    delete g;
    for (int i = 0; i < drawables.size(); i++) {
        delete drawables[i];
    }
}

void plot(SDL_Plotter * g, const Vec2i & p, const Color& color) {
    if (p.x >= 0 && p.x < g->getCol() && p.y >= 0 && p.y < g->getRow()) {
        //cout << (int)color.r << " " << (int)color.g << " " << (int)color.b << endl;
        g->plotPixel(p.x, p.y, color.r, color.g, color.b);
    }
}

Vec2f::Vec2f() {
    x = y = 0;
}

Vec2f::Vec2f(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2f::Vec2f(int x, int y) : x(float(x)), y(float(y)) {}

Vec2f Vec2f::operator+(const Vec2f & other) {
    Vec2f result = Vec2f(other.x + x, other.y + y);
    return result;
}

Vec2f & Vec2f::operator+=(const Vec2f & other) {
    x += other.x;
    y += other.y;
    return *this;
}

Color::Color() {
    r = g = b = 0;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color Color::operator+(const Color & other) {
    Color result(other.r + r, other.g + g, other.b + b);
    return result;
}

Color & Color::operator+=(const Color & other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}

bool Color::operator==(const Color& other) {
    bool res = r == other.r && g == other.g && b == other.b;
    return res;
}

void drawLine(SDL_Plotter* g, const Vec2i& p1, const Vec2i& p2, const Color& color) {
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = p2.x - p1.x;
    dy = p2.y - p1.y;
    dx1 = fabs(dx);
    dy1 = fabs(dy);
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;
    
    if (dy1 <= dx1) {
        if (dx >= 0) {
            x = p1.x;
            y = p1.y;
            xe = p2.x;
        }
        else {
            x = p2.x;
            y = p2.y;
            xe = p1.x;
        }
        plot(g, Vec2f(x, y), color);
        for (i = 0; x < xe; i++) {
            x += 1;
            if (px < 0) {
                px += 2 * dy1;
            }
            else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    y += 1;
                }
                else {
                    y -= 1;
                }
                px += 2 * (dy1 - dx1);
            }
            plot(g, Vec2f(x, y), color);
        }
    }
    else {
        if (dy >= 0) {
            x = p1.x;
            y = p1.y;
            ye = p2.y;
        }
        else {
            x = p2.x;
            y = p2.y;
            ye = p1.y;
        }
        plot(g, Vec2f(x, y), color);
        for (i = 0; y < ye; i++) {
            y += 1;
            if (py <= 0) {
                py += 2 * dx1;
            }
            else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    x += 1;
                }
                else {
                    x -= 1;
                }
                py += 2 * (dx1 - dy1);
            }
            plot(g, Vec2f(x, y), color);
        }
    }
}

void drawRectangle(SDL_Plotter * g, const Rectangle& rect) {
    if (rect.getFilled()) {
        for (int y = 0; y < rect.getHeight(); y++) {
            drawLine(g, Vec2i(rect.getLocation().x, rect.getLocation().y + y), Vec2i(rect.getLocation().x + rect.getWidth(), rect.getLocation().y + y), rect.getColor());
        }
    }
    else {
        // Top line
        drawLine(g, rect.getLocation(), rect.getLocation() + Vec2i(rect.getWidth(), 0), rect.getColor());
        // Left line
        drawLine(g, rect.getLocation(), rect.getLocation() + Vec2i(0, rect.getHeight()), rect.getColor());
        // Right line
        drawLine(g, rect.getLocation() + Vec2i(rect.getWidth(), 0), rect.getLocation() + Vec2i(rect.getWidth(), rect.getHeight()), rect.getColor());
        // Bottom line
        drawLine(g, rect.getLocation() + Vec2i(0, rect.getHeight()), rect.getLocation() + Vec2i(rect.getWidth(), rect.getHeight()), rect.getColor());
    }
}

Line::Line() : p1(Vec2f()), p2(Vec2f()) {}

Line::Line(const Vec2i & p1, const Vec2i & p2) : p1(p1), p2(p2) {}

Line::Line(int x1, int y1, int x2, int y2) : p1(x1, y1), p2(x2, y2) {}

Vec2i Line::getP1() const {
    return p1;
}
Vec2i Line::getP2() const {
    return p2;
}
Color Line::getColor() const {
    return color;
}
void Line::setP1(const Vec2i& other) {
    p1 = other;
}
void Line::setP2(const Vec2i& other) {
    p2 = other;
}
void Line::setColor(const Color& color) {
    this->color = color;
}

void Line::draw(SDL_Plotter * g) {
    drawLine(g, p1, p2, color);
}

void Line::update(SDL_Plotter * g, Game* game) {}

Rectangle::Rectangle() {
    
}

Rectangle::Rectangle(const Vec2i & location, const Vec2i & size, const Color& color, bool filled) : location(location), size(size), color(color), fill(filled) {}

Rectangle::Rectangle(const Vec2i & location, int width, int height, const Color& color, bool filled) : Rectangle(location, Vec2i(width, height), color, filled) {}

Rectangle::Rectangle(int x, int y, int width, int height, const Color& color, bool filled) : Rectangle(Vec2i(x, y), Vec2i(width, height), color, filled) {}

Vec2i Rectangle::getLocation() const {
    return location;
}

Vec2i Rectangle::getSize() const {
    return size;
}

int Rectangle::getX() const {
    return location.x;
}

int Rectangle::getY() const {
    return location.y;
}

int Rectangle::getWidth() const {
    return size.x;
}

int Rectangle::getHeight() const {
    return size.y;
}

Color Rectangle::getColor() const {
    return color;
}

bool Rectangle::getFilled() const {
    return fill;
}

void Rectangle::setFilled(bool filled) {
    fill = filled;
}

void Rectangle::setColor(const Color & color) {
    this->color = color;
}

void Rectangle::setLocation(const Vec2i & location) {
    this->location = location;
}

void Rectangle::setSize(const Vec2i & size) {
    this->size = size;
}

void Rectangle::setX(int x) {
    location.x = x;
}

void Rectangle::setY(int y) {
    location.y = y;
}

void Rectangle::setWidth(int width) {
    size.x = width;
}

void Rectangle::setHeight(int height) {
    size.y = height;
}

void Rectangle::update(SDL_Plotter * g, Game* game) {
}

void Rectangle::draw(SDL_Plotter * g) {
    if(visible) drawRectangle(g, *this);
}

Pane::Pane(Pane * parent, Vec2i offset) {
    this->parent = parent;
    this->offset = offset;
}

Pane * Pane::getParent() const {
    return parent;
}

Vec2i Pane::getLocation() const {
    return location;
}

Vec2i Pane::getOffset() const {
    return offset;
}

Vec2i Pane::getSize() const {
    return size;
}

bool Pane::inside(const Vec2i & location) {
    if (parent == nullptr) {
        return (location.x > this->location.x &&
                location.x < this->location.x + size.x &&
                location.y > this->location.y &&
                location.y < this->location.y + size.y);
    }
    else {
        return (location.x > (parent->getLocation() + offset).x &&
                location.x < (parent->getLocation() + offset).x &&
                location.y >(parent->getLocation() + offset).y &&
                location.y < (parent->getLocation() + offset).y);
    }
}

void Pane::setParent(Pane * parent) {
    this->parent = parent;
}

void Pane::setLocation(const Vec2i & location) {
    this->location = location;
}

void Pane::setOffset(const Vec2i & offset) {
    this->offset = offset;
}

void Pane::setSize(const Vec2i & size) {
    this->size = size;
}

void Pane::draw(SDL_Plotter * g) {}

void Pane::update(SDL_Plotter * g, Game* game) {}

void drawCircle(SDL_Plotter* g, const Circle& circle) {
    Vec2i curLoc;
    for (int x = circle.getLocation().x - circle.getRadius(); x < circle.getLocation().x + circle.getRadius(); x++) {
        for (int y = circle.getLocation().y - circle.getRadius(); y < circle.getLocation().y + circle.getRadius(); y++) {
            curLoc = Vec2i(x, y);
            
            if (circle.getLocation().dist(curLoc) <= circle.getRadius()) {
                if (circle.getFilled()) {
                    plot(g, curLoc, circle.getColor());
                }
                else if (circle.getLocation().dist(curLoc) > circle.getRadius() - 1) {
                    plot(g, curLoc, circle.getColor());
                }
            }
        }
    }
}

Circle::Circle(const Vec2i& location, int radius, const Color& color, bool filled) {
    this->location = location;
    this->radius = radius;
    this->color = color;
    this->fill = filled;
}

Vec2i Circle::getLocation() const {
    return location;
}

int Circle::getRadius() const {
    return radius;
}

Color Circle::getColor() const {
    return color;
}

bool Circle::getFilled() const {
    return fill;
}

void Circle::setLocation(const Vec2i& location) {
    this->location = location;
}

void Circle::setRadius(int radius) {
    this->radius = radius;
}

void Circle::setColor(const Color& color) {
    this->color = color;
}

void Circle::setFilled(bool filled) {
    fill = filled;
}

void Circle::update(SDL_Plotter* g, Game* game) {
    
}

void Circle::draw(SDL_Plotter* g) {
    if(visible) drawCircle(g, *this);
}

Image::Image(const string & fileName) {
    load(string(SDL_GetBasePath()) + "res/img/" + fileName + ".txt");
}

void Image::load(const string & fileName) {
    ifstream file(fileName);
    if (!file) {
        throw fileName;
    }
    file >> size.y >> size.x;
    int r, g, b;
    
    for (int i = 0; i < size.x * size.y; i++) {
        file >> r >> g >> b;
        data.push_back(Color(r, g, b));
    }
}

void Image::draw(SDL_Plotter * g) {
    if (visible) {
        Vec2i drawLoc;
        if (parent == nullptr) {
            drawLoc = location;
        }
        else {
            drawLoc = parent->getLocation() + offset;
        }
        for (int r = 0; r < size.y; r++) {
            for (int c = 0; c < size.x; c++) {
                Color col = data[r * size.x + c];
                //cout << "(" << (int)col.r << "," << (int)col.g << "," << (int)col.b << ")" << endl;
                plot(g, drawLoc + Vec2i(c, r), data[r * size.x + c]);
            }
        }
    }
}

void Image::update(SDL_Plotter * g, Game* game) {}

Vec2i::Vec2i() : x(0), y(0) {}

Vec2i::Vec2i(int x, int y) : x(x), y(y) {}

Vec2i::Vec2i(float x, float y) : x(int(x)), y(int(y)) {}

Vec2i::Vec2i(const Vec2f & other) : x(int(other.x)), y(int(other.y)) {}

Vec2i Vec2i::operator+(const Vec2i & other) {
    Vec2i result(other.x + x, other.y + y);
    return result;
}

Vec2i & Vec2i::operator+=(const Vec2i & other) {
    x += other.x;
    y += other.y;
    return *this;
}

ostream& operator<<(ostream& os, const Vec2i& vec2i) {
    os << "(" << vec2i.x << ", " << vec2i.y << ")";
    return os;
}

double Vec2i::dist(const Vec2i& other) {
    return sqrt(pow(x - other.x, 2.0) + pow(y - other.y, 2.0));
}

TextField::TextField() : Pane(nullptr) {
    this->canEdit = false;
}

TextField::TextField(const string & text) : Pane(nullptr) {
    setText(text);
}

string TextField::getText() const {
    return text;
}

bool TextField::getCanEdit() const {
    return canEdit;
}

void TextField::setText(const string & text) {
    this->text = text;
    field.clear();
    for (unsigned int i = 0; i < text.size(); i++) {
        Char tmp = letters[(char)toupper(text[i])];
        tmp.setParent(this);
        tmp.setOffset(Vec2i(i * CHAR_SIZE, 0));
        field.push_back(tmp);
    }
    size = Vec2i(text.size() * CHAR_SIZE, 16);
}

void TextField::setCanEdit(bool b) {
    this->canEdit = b;
}

void TextField::setFgColor(const Color& color) {
    fg = color;
    for (int i = 0; i < field.size(); i++) {
        field[i].setColor(fg);
    }
}

void TextField::draw(SDL_Plotter * g) {
    if (visible) {
        for (int i = 0; i < field.size(); i++) {
            field[i].draw(g);
        }
    }
}

void TextField::update(SDL_Plotter * g, Game* game) {
    char key = g->getKey();
    if (g->kbhit()) {
        if (key == '<') {
            setText(text.substr(0, text.size() - 1));
            g->clear();
        }
        else if(isalnum(key) || key == ' ' || key == '!') {
            setText(text + key);
            g->clear();
        }
    }
}

void TextField::setOffset(const Vec2i& offset) {
    for (int i = 0; i < field.size(); i++) {
        field[i].setOffset(field[i].getOffset() + offset);
    }
}

void TextField::setScale(int scale) {
    for (int i = 0; i < field.size(); i++) {
        field[i].setScale(scale);
        field[i].setOffset(Vec2i(i * CHAR_SIZE * scale, 0));
    }
}

Char::Char() {
    id = '\0';
    size = 0;
    scale = 0;
    color = BLACK;
}

Char::Char(char id, int size) : Pane(nullptr) {
    this->id = id;
    this->size = size;
    this->scale = 1;
    this->color = BLACK;
    string fileName = RES_CHAR + char(toupper(id)) + ".txt";
    loadChar(fileName);
}

char Char::getId() const {
    return id;
}

void Char::loadChar(const string & fileName) {
    ifstream file(fileName, ios::binary);
    if (!file) {
        throw fileName;
    }
    
    uint8_t tmp;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            file >> tmp;
            data.push_back(tmp);
        }
    }
}

void Char::setColor(const Color& color) {
    this->color = color;
}

void Char::draw(SDL_Plotter * g) {
    if (visible) {
        Vec2i drawLoc;
        if (parent == nullptr) {
            drawLoc = location;
        }
        else {
            drawLoc = parent->getLocation() + offset;
        }
        
        //cout << "Drawing " << this->id << " at " << drawLoc.x << ", " << drawLoc.y << endl;
        
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                /*
                 if (data[r * size + c] == uint8_t(49)) {
                 plot(g, drawLoc + Vec2i(c, r), color);
                 drawRectangle(g, Rectangle(0, 0, 0, 0));
                 }
                 */
                
                for (int _x = 0; _x < scale; _x++) {
                    for (int _y = 0; _y < scale; _y++) {
                        if (data[y * size + x] == uint8_t(49)) plot(g, Vec2i(drawLoc.x + _x + x * scale, drawLoc.y + _y + y * scale), color);
                    }
                }
            }
        }
    }
}

void Char::update(SDL_Plotter * g, Game* game) {}

void Char::setScale(int scale) {
    this->scale = scale;
}


void playAction(Game* game) {
    game->state = PLAY;
    game->g->clear();
    game->g->update();
}
void optionsAction(Game* game) {
    game->state = OPTIONS;
    game->g->clear();
    game->g->update();
}
void quitAction(Game* game) {
    game->g->setQuit(true);
}
void menuAction(Game* game)
{
    game->state = MAIN_MENU;
    game->g->clear();
    game->g->update();
}
void winAction(Game* game)              //
{
    game->state = WIN;
    game->g->clear();
    game->g->update();
}
void loseAction(Game* game)
{
    game->state = LOSE;
    game->g->clear();
    game->g->update();
}

Button::Button(const string & text, void (*action)(Game* game)) {
    tField = new TextField(text);
    tField->setParent(this);
    tField->setOffset(Vec2i(1, 1));
    leave = true;
    size = tField->getSize() + Vec2i(2, 2);
    cout << "Size: " << size << endl;
    this->action = action;
}

void Button::onHover(const Vec2i & location) {
    if (leave) {
        color = GRAY;
    }
    else {
        color = ORANGE;
    }
}

void Button::onClick(const Vec2i & location, Game* game) {
    action(game);
}

void Button::draw(SDL_Plotter * g) {
    if (visible) {
        if (parent == nullptr) {
            drawRectangle(g, Rectangle(location, size, color, true));
        }
        else {
            drawRectangle(g, Rectangle(parent->getLocation() + offset, size, color, true));
        }
        tField->draw(g);
    }
}

void Button::update(SDL_Plotter * g, Game* game) {
    Vec2i mouseLoc;
    if (g->getMouseClick(mouseLoc.x, mouseLoc.y)) {
        if (inside(mouseLoc)) {
            onClick(mouseLoc, game);
        }
    }
    if (g->getMouseMotion(mouseLoc.x, mouseLoc.y)) {
        if (inside(mouseLoc)) {
            if (leave != false) {
                leave = false;
            }
        }
        else {
            if (leave != true) {
                leave = true;
            }
        }
        onHover(mouseLoc);
    }
}

void Button::setLocation(const Vec2i & location) {
    Pane::setLocation(location);
    tField->setLocation(location);
}

void Button::setOffset(const Vec2i& offset) {
    this->offset = offset;
    tField->setOffset(offset);
}

void Button::setFgColor(const Color& color) {
    tField->setFgColor(color);
}

void Button::setScale(int scale) {
    tField->setScale(scale);
    size = Vec2i(size.x * scale, size.y * scale);
}

TextField& Button::getField() {
    return *tField;
}

StickMan::StickMan(const Vec2i& location, const Color& color) {
    body.push_back(new Circle(location, 10, color, false));
    body.push_back(new Line(Vec2i(location.x, location.y + 10), Vec2i(location.x, location.y + 50)));
    body.push_back(new Line(((Line*)body[1])->getP2(), ((Line*)body[1])->getP2() + Vec2i(-18, 24)));
    body.push_back(new Line(((Line*)body[1])->getP2(), ((Line*)body[1])->getP2() + Vec2i(18, 24)));
    body.push_back(new Line(((Line*)body[1])->getP2() + Vec2i(0, -30), ((Line*)body[1])->getP2() + Vec2i(-12, -10)));
    body.push_back(new Line(((Line*)body[1])->getP2() + Vec2i(0, -30), ((Line*)body[1])->getP2() + Vec2i(12, -10)));
    for (int i = 0; i < body.size(); i++) {
        body[i]->visible = false;
    }
}
void StickMan::addPart() {
    bool added = false;
    int i = 0;
    while (i < body.size() && !added) {
        added = !body[i]->visible;
        if (added) {
            body[i]->visible = true;
        }
        else {
            i++;
        }
    }
}
void StickMan::removePart() {
    if (!body.empty()) {
        delete body.back();
        body.pop_back();
    }
}
bool StickMan::dead() const {
    return body.empty();
}

void StickMan::update(SDL_Plotter* g, Game* game) {
    for (int i = 0; i < body.size(); i++) {
        body[i]->update(g, game);
    }
}
void StickMan::draw(SDL_Plotter* g) {
    if (visible) {
        for (int i = 0; i < body.size(); i++) {
            if (body[i]->visible) body[i]->draw(g);
        }
    }
}

/*
void mainmenu(SDL_Plotter& background)
{
    while(!background.getQuit())
    {
        
        //lines
        for(int x = 10;x<=630;x+=10)
        {
            Rectangle line1(x,10,3,3,RED);
            drawRectangle(&background, line1);
            Rectangle line2(x,460,3,3,RED);
            drawRectangle(&background, line2);
        }
        for(int x = 10;x<470;x+=10)
        {
            Rectangle line3(10,x,3,3,RED);
            drawRectangle(&background, line3);
            Rectangle line4(630,x,3,3,RED);
            drawRectangle(&background, line4);
        }
        
        //buttons
        loadFont("font.txt");
        Button playButton ("PLAY");
        playButton.setLocation(Vec2i(340,140));
        playButton.setSize(Vec2i(100, 40));
        playButton.draw(&background);
        myString play("PLAY",Vec2i(345,145),4,_WHITE);
        drawString(background, play);
        
        Button highSButton ("HIGH SCORES");
        highSButton.setLocation(Vec2i(260,210));
        highSButton.setSize(Vec2i(270, 40));
        highSButton.draw(&background);
        myString highScore("HIGH SCORES",Vec2i(265,215),4,_WHITE);
        drawString(background, highScore);
        
        Button optionsBt ("OPTIONS");
        optionsBt.setLocation(Vec2i(310,280));
        optionsBt.setSize(Vec2i(175, 40));
        optionsBt.draw(&background);
        myString option("OPTIONS",Vec2i(315,285),4,_WHITE);
        drawString(background, option);
        
        Button quitButton ("QUIT");
        quitButton.setLocation(Vec2i(340,350));
        quitButton.setSize(Vec2i(100, 40));
        quitButton.draw(&background);
        myString quit("QUIT",Vec2i(345,355),4,_WHITE);
        drawString(background, quit);
        
        //logo
        myString evil("EVIL",Vec2i(40,30),3,RED);
        drawString(background, evil);
        const Color hang(200, 0, 0);
        myString HangMan("HANGMAN",Vec2i(100,50),6,hang);
        drawString(background, HangMan);
        
        
        
        //chage size??????????????
        
         for (char c = 'A'; c < 'Z'; c++) {
         try {
         letters[c] = Char(c, CHAR_SIZE);
         }
         catch (const string& fileName) {
         cerr << fileName << " could not be loaded!" << endl;
         }
         }
         TextField evil("EVIL");
         evil.setLocation(Vec2i(25,40));
         evil.setFgColor(RED);
         evil.setSize(Vec2i(200,100));
         evil.draw(&background);
         TextField hman("HANGMAN");
         hman.setLocation(Vec2i(200,40));
         hman.setFgColor(RED);
         hman.setSize(Vec2i(200,100));
         hman.draw(&background);
 
        
        
        
        
        
        Rectangle ground(40,400,550,9,BLACK);
        drawRectangle(&background, ground);
        Rectangle comp1(80,150,5,250,BLACK);
        drawRectangle(&background, comp1);
        Rectangle comp2(80,150,120,6,BLACK);
        drawRectangle(&background, comp2);
        Rectangle comp3(200,150,2,30,BLACK);
        drawRectangle(&background, comp3);
        
        StickMan man(Vec2i(200,190));
        man.draw(&background);
        if(background.kbhit()){
            background.getKey();
        }
        
        background.update();
    }
    
}

void win(SDL_Plotter& background)
{
    while(!background.getQuit())
    {
        
        //lines
        for(int x = 10;x<=630;x+=10)
        {
            Rectangle line1(x,10,3,3,RED);
            drawRectangle(&background, line1);
            Rectangle line2(x,460,3,3,RED);
            drawRectangle(&background, line2);
        }
        for(int x = 10;x<470;x+=10)
        {
            Rectangle line3(10,x,3,3,RED);
            drawRectangle(&background, line3);
            Rectangle line4(630,x,3,3,RED);
            drawRectangle(&background, line4);
        }
        //"YOU WON"
        loadFont("font.txt");
        myString win("YOU WON",Vec2i(110,90),10,BLACK);
        drawString(background, win);
        Circle c1(Vec2i(80,120),8,RED,true);
        Circle c2(Vec2i(560,120),8,RED,true);
        c1.draw(&background);
        c2.draw(&background);
        
        //bottons
        Button menuButton ("MENU");
        menuButton.setLocation(Vec2i(30,410));
        menuButton.setSize(Vec2i(100, 40));
        menuButton.draw(&background);
        myString menu("MENU",Vec2i(35,415),4,_WHITE);
        drawString(background, menu);
        
        Button quitButton ("QUIT");
        quitButton.setLocation(Vec2i(500,410));
        quitButton.setSize(Vec2i(100, 40));
        quitButton.draw(&background);
        myString quit("QUIT",Vec2i(505,415),4,_WHITE);
        drawString(background, quit);
        
        //draw hangman
        Rectangle ground(40,380,550,9,BLACK);
        drawRectangle(&background, ground);
        Rectangle comp1(80,190,5,190,BLACK);
        drawRectangle(&background, comp1);
        Rectangle comp2(80,190,100,6,BLACK);
        drawRectangle(&background, comp2);
        Rectangle comp3(180,190,2,30,BLACK);
        drawRectangle(&background, comp3);
        
        StickMan man(Vec2i(180,230));
        man.draw(&background);
        
        myString score("YOUR SCORE:",Vec2i(220,200),3,BLACK);
        drawString(background, score);
        myString hiscore("Current High:",Vec2i(220,250),3,BLACK);
        drawString(background, hiscore);
        myString leave("LEAVE YOUR NAME:",Vec2i(220,300),3,BLACK);
        drawString(background, leave);
        
        for(int x = 200;x<=580;x+=50)
        {
            Rectangle line1(x,370,30,4,RED);
            drawRectangle(&background, line1);
        }
        
        
        if(background.kbhit()){
            background.getKey();
        }
        if(background.kbhit()){
            background.getKey();
        }
        
        background.update();
    }
}
void lose(SDL_Plotter& background)
{
    while(!background.getQuit())
    {
        
        //lines
        for(int x = 10;x<=630;x+=10)
        {
            Rectangle line1(x,10,3,3,RED);
            drawRectangle(&background, line1);
            Rectangle line2(x,460,3,3,RED);
            drawRectangle(&background, line2);
        }
        for(int x = 10;x<470;x+=10)
        {
            Rectangle line3(10,x,3,3,RED);
            drawRectangle(&background, line3);
            Rectangle line4(630,x,3,3,RED);
            drawRectangle(&background, line4);
        }
        //"GAME OVER"
        loadFont("font.txt");
        myString win("GAME OVER",Vec2i(85,80),9,BLACK);
        drawString(background, win);
        Circle c1(Vec2i(60,110),8,RED,true);
        Circle c2(Vec2i(580,110),8,RED,true);
        c1.draw(&background);
        c2.draw(&background);
        
        //bottons
        Button menuButton ("MENU");
        menuButton.setLocation(Vec2i(30,410));
        menuButton.setSize(Vec2i(100, 40));
        menuButton.draw(&background);
        myString menu("MENU",Vec2i(35,415),4,_WHITE);
        drawString(background, menu);
        
        Button quitButton ("QUIT");
        quitButton.setLocation(Vec2i(500,410));
        quitButton.setSize(Vec2i(100, 40));
        quitButton.draw(&background);
        myString quit("QUIT",Vec2i(505,415),4,_WHITE);
        drawString(background, quit);
        
        //draw hangman
        Rectangle ground(40,380,550,9,BLACK);
        drawRectangle(&background, ground);
        Rectangle comp1(80,190,5,190,BLACK);
        drawRectangle(&background, comp1);
        Rectangle comp2(80,190,100,6,BLACK);
        drawRectangle(&background, comp2);
        Rectangle comp3(180,190,2,30,BLACK);
        drawRectangle(&background, comp3);
        
        StickMan man(Vec2i(180,230));
        man.draw(&background);
        
        myString score("YOUR SCORE:",Vec2i(220,200),3,BLACK);
        drawString(background, score);
        myString hiscore("Current High:",Vec2i(220,250),3,BLACK);
        drawString(background, hiscore);
        myString leave("LEAVE YOUR NAME:",Vec2i(220,300),3,BLACK);
        drawString(background, leave);
        
        for(int x = 200;x<=580;x+=50)
        {
            Rectangle line1(x,370,30,4,RED);
            drawRectangle(&background, line1);
        }
        
        
        if(background.kbhit()){
            background.getKey();
        }
        if(background.kbhit()){
            background.getKey();
        }
        
        background.update();
    }
}

void play(SDL_Plotter& background)
{
    loadFont("font.txt");
    while(!background.getQuit())
    {
        //lines
        for(int x = 10;x<=630;x+=10)
        {
            Rectangle line1(x,10,3,3,RED);
            drawRectangle(&background, line1);
            Rectangle line2(x,460,3,3,RED);
            drawRectangle(&background, line2);
        }
        for(int x = 10;x<470;x+=10)
        {
            Rectangle line3(10,x,3,3,RED);
            drawRectangle(&background, line3);
            Rectangle line4(630,x,3,3,RED);
            drawRectangle(&background, line4);
        }
        //title
        myString evil("EVIL",Vec2i(40,30),3,RED);
        drawString(background, evil);
        const Color hang(200, 0, 0);
        myString HangMan("HANGMAN",Vec2i(100,50),6,hang);
        drawString(background, HangMan);
        
        //bottons
        Button menuButton ("MENU");
        menuButton.setLocation(Vec2i(30,410));
        menuButton.setSize(Vec2i(100, 40));
        menuButton.draw(&background);
        myString menu("MENU",Vec2i(35,415),4,_WHITE);
        drawString(background, menu);
        
        Button quitButton ("QUIT");
        quitButton.setLocation(Vec2i(500,410));
        quitButton.setSize(Vec2i(100, 40));
        quitButton.draw(&background);
        myString quit("QUIT",Vec2i(505,415),4,_WHITE);
        drawString(background, quit);
        Button subButton ("SUBMIT");
        subButton.setLocation(Vec2i(400,310));
        subButton.setSize(Vec2i(150, 40));
        subButton.draw(&background);
        myString subm("SUBMIT",Vec2i(405,315),4,_WHITE);
        drawString(background, subm);
        
        //draw hangman
        Rectangle ground(40,380,550,9,BLACK);
        drawRectangle(&background, ground);
        Rectangle comp1(80,150,5,230,BLACK);
        drawRectangle(&background, comp1);
        Rectangle comp2(80,150,120,6,BLACK);
        drawRectangle(&background, comp2);
        Rectangle comp3(200,150,2,30,BLACK);
        drawRectangle(&background, comp3);
        
        StickMan man(Vec2i(200,190));
        man.draw(&background);
        
        
        for(int x = 240;x<=580;x+=50)
        {
            Rectangle line1(x,280,40,5,RED);
            drawRectangle(&background, line1);
        }
        
        if(background.kbhit()){
            background.getKey();
        }
        if(background.kbhit()){
            background.getKey();
        }
        
        background.update();
    }
}
void options(SDL_Plotter& background)
{
    while(!background.getQuit())
    {
        
        //lines
        for(int x = 10;x<=630;x+=10)
        {
            Rectangle line1(x,10,3,3,RED);
            drawRectangle(&background, line1);
            Rectangle line2(x,460,3,3,RED);
            drawRectangle(&background, line2);
        }
        for(int x = 10;x<470;x+=10)
        {
            Rectangle line3(10,x,3,3,RED);
            drawRectangle(&background, line3);
            Rectangle line4(630,x,3,3,RED);
            drawRectangle(&background, line4);
        }
        //"GAME OVER"
        loadFont("font.txt");
        myString win("OPTIONS",Vec2i(120,80),10,BLACK);
        drawString(background, win);
        Circle c1(Vec2i(80,110),8,RED,true);
        Circle c2(Vec2i(560,110),8,RED,true);
        c1.draw(&background);
        c2.draw(&background);
        
        //bottons
        Button  evilButton ("EVIL");
        evilButton.setLocation(Vec2i(300,190));
        evilButton.setSize(Vec2i(150,50));
        evilButton.draw(&background);
        myString evil("EVIL",Vec2i(305,195),6,_WHITE);
        drawString(background, evil);
        
        Button norButton ("NORMAL");
        norButton.setLocation(Vec2i(280,290));
        norButton.setSize(Vec2i(220,50));
        norButton.draw(&background);
        myString normal("NORMAL",Vec2i(285,295),6,_WHITE);
        drawString(background, normal);
        
        
        
        Button menuButton ("MENU");
        menuButton.setLocation(Vec2i(30,410));
        menuButton.setSize(Vec2i(100, 40));
        menuButton.draw(&background);
        myString menu("MENU",Vec2i(35,415),4,_WHITE);
        drawString(background, menu);
        
        Button quitButton ("QUIT");
        quitButton.setLocation(Vec2i(500,410));
        quitButton.setSize(Vec2i(100, 40));
        quitButton.draw(&background);
        myString quit("QUIT",Vec2i(505,415),4,_WHITE);
        drawString(background, quit);
        
        //draw hangman
        Rectangle ground(40,380,550,9,BLACK);
        drawRectangle(&background, ground);
        Rectangle comp1(80,190,5,190,BLACK);
        drawRectangle(&background, comp1);
        Rectangle comp2(80,190,100,6,BLACK);
        drawRectangle(&background, comp2);
        Rectangle comp3(180,190,2,30,BLACK);
        drawRectangle(&background, comp3);
        
        StickMan man(Vec2i(180,230));
        man.draw(&background);
        
        if(background.kbhit()){
            background.getKey();
        }
        if(background.kbhit()){
            background.getKey();
        }
        
        background.update();
    }
}

*/
