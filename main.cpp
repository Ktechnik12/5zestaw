#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

//klasa do obslugi canvy
class Canvas {
protected:
    int width;
    int height;
    std::vector<std::string> pixels;

public:
    Canvas(int w, int h) : width(w), height(h) {
        pixels.resize(height, std::string(width, ' '));
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    char getPixel(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return pixels[y][x];
        }
        return ' ';
    }

    void draw() const {
        std::cout << "|";
        for (int i = 0; i < width; ++i) {
            std::cout << "=";
        }
        std::cout << "|" << std::endl;
        int i = 1;
        for (const auto& row : pixels) {
            std::cout << i << "\t|" << row << "|" << std::endl;
            i++;
        }

        std::cout << "|";
        for (int i = 0; i < width; ++i) {
            std::cout << "=";
        }
        std::cout << "|" << std::endl;
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << "|";
            for (int i = 0; i < width; ++i) {
                file << "=";
            }
            file << "|" << std::endl;

            for (const auto& row : pixels) {
                file << "|" << row << "|" << std::endl;
            }

            file << "|";
            for (int i = 0; i < width; ++i) {
                file << "=";
            }
            file << "|" << std::endl;

            file.close();
        }
    }

    void setPixel(int x, int y, char symbol) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y][x] = symbol;
        }
    }
};

//klasa do obslugi figur
class Figure {
public:
    virtual ~Figure() {}
    virtual void draw(Canvas& canvas) = 0;
};

//kwadratu
class Square : public Figure {
private:
    int centerX;
    int centerY;
    int size;
    char symbol;

public:
    Square(int x, int y, int s, char sym) : centerX(x), centerY(y), size(s), symbol(sym) {}

    void draw(Canvas& canvas) override {
        int startX = centerX - size / 2;
        int startY = centerY - size / 2;

        for (int y = startY; y < startY + size; ++y) {
            for (int x = startX; x < startX + size; ++x) {
                canvas.setPixel(x, y, symbol);
            }
        }
    }
};

//kolo
class Circle : public Figure {
private:
    int centerX;
    int centerY;
    int radius;
    char symbol;

public:
    Circle(int x, int y, int r, char sym)
        : centerX(x), centerY(y), radius(r), symbol(sym) {}

    void draw(Canvas& canvas) override {
        for (int y = centerY - radius; y <= centerY + radius; ++y) {
            for (int x = centerX - radius; x <= centerX + radius; ++x) {
                if (isInside(x, y)) {
                    canvas.setPixel(x, y, symbol);
                }
            }
        }
    }

private:
    bool isInside(int x, int y) {
        int dx = x - centerX;
        int dy = y - centerY;
        return dx * dx + dy * dy <= radius * radius;
    }
};

//trojkat 1
class Triangle1 : public Figure {
private:
    int centerX;
    int centerY;
    int size;
    char symbol;

public:
    Triangle1(int x, int y, int r, char sym)
        : centerX(x), centerY(y), size(r), symbol(sym) {}

    void draw(Canvas& canvas) override {
        int startX = centerX - size / 2;
        int startY = centerY - size / 2;
        for (int y = startY; y < startY + size; ++y) {
            for (int x = 0; x < y - startY + 1; ++x) {
                canvas.setPixel(startX + x, y, symbol);
            }
        }
    }
};

//trojkat 2
class Triangle2 : public Figure {
private:
    int centerX;
    int centerY;
    int size;
    char symbol;

public:
    Triangle2(int x, int y, int r, char sym)
        : centerX(x), centerY(y), size(r), symbol(sym) {}

    void draw(Canvas& canvas) override {
        int startX = centerX - size / 2;
        int startY = centerY + size / 2;
        for (int y = startY; y > startY - size; --y) {
            for (int x = 0; x < startY - y + 1; ++x) {
                canvas.setPixel(startX + x, y, symbol);
            }
        }
    }
};

//trojkat 3
class Triangle3 : public Figure {
private:
    int centerX;
    int centerY;
    int size;
    char symbol;

public:
    Triangle3(int x, int y, int r, char sym)
        : centerX(x), centerY(y), size(r), symbol(sym) {}

    void draw(Canvas& canvas) override {
        int startX = centerX + size / 2;
        int startY = centerY - size / 2;
        for (int y = startY; y < startY + size; ++y) {
            for (int x = 0; x < y - startY + 1; ++x) {
                canvas.setPixel(startX - x, y, symbol);
            }
        }
    }
};

//trojkat 4
class Triangle4 : public Figure {
private:
    int centerX;
    int centerY;
    int size;
    char symbol;

public:
    Triangle4(int x, int y, int r, char sym)
        : centerX(x), centerY(y), size(r), symbol(sym) {}

    void draw(Canvas& canvas) override {
        int startX = centerX + size / 2;
        int startY = centerY + size / 2;
        for (int y = startY; y > startY - size; --y) {
            for (int x = 0; x < startY - y + 1; ++x) {
                canvas.setPixel(startX - x, y, symbol);
            }
        }
    }
};

//klasa do cienia
class Light {
private:
    int posX;
    int posY;
    char symbol;
    char placeSymbol;

public:
    Light(int x, int y, char sym, char ps) : posX(x), posY(y), symbol(sym), placeSymbol(ps) {}
    void applyShadow(Canvas& canvas, const std::vector<Figure*>& figures){
        canvas.setPixel(posX,posY,placeSymbol);
        for (int i = 0; i < canvas.getHeight(); ++i) {
            for (int j = 0; j < canvas.getWidth(); ++j) {
                if (isInShadow(j, i, canvas)&& canvas.getPixel(j, i) == ' ') {
                    canvas.setPixel(j, i, symbol);
                }
            }
        }
    };

private:
    bool isInShadow(int x, int y, const Canvas& canvas) const{
        int dx = posX - x;
        int dy = posY - y;

        int distance = std::sqrt(dx * dx + dy * dy);

        if (distance > 0 && distance < canvas.getWidth()) {
            int stepX = (dx > 0) ? 1 : -1;
            int stepY = (dy > 0) ? 1 : -1;

            int absDx = std::abs(dx);
            int absDy = std::abs(dy);

            int currX = x;
            int currY = y;

            int error = absDx - absDy;

            while (currX != posX || currY != posY) {
                if (canvas.getPixel(currX, currY) != ' ') {
                    return true;
                }

                int error2 = error * 2;

                if (error2 > -absDy) {
                    error -= absDy;
                    currX += stepX;
                }

                if (error2 < absDx) {
                    error += absDx;
                    currY += stepY;
                }
            }
        }

        return false;
    };
};

//main
int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Podaj nazwę pliku konfiguracyjnego jako argument." << std::endl;
        return 1;
    }

    std::string configFilename = argv[1];
    std::ifstream configFile(configFilename);
    if (!configFile.is_open()) {
        std::cout << "Nie można otworzyć pliku konfiguracyjnego: " << configFilename << std::endl;
        return 1;
    }

    int canvasWidth = 0;
    int canvasHeight = 0;
    std::string outputFilename;
    char emptySymbol;
    std::vector<Figure*> figures;
    Light* light = nullptr;

    std::string line;
    while (std::getline(configFile, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::string key;
        std::istringstream iss(line);
        iss >> key;

        if (key == "canvas_width") {
            iss >> canvasWidth;
        } else if (key == "canvas_height") {
            iss >> canvasHeight;
        } else if (key == "output_filename") {
            iss >> outputFilename;
        } else if (key == "empty_symbol") {
            iss >> emptySymbol;
        } else if (key == "figure") {
            std::string figureType;
            int x, y, size;
            char symbol;
            iss >> figureType >> x >> y >> size >> symbol;
            std::cout << figureType << x << y << size << symbol << std::endl;
            Figure* figure = nullptr;
            if (figureType == "square") {
                figure = new Square(x, y, size, symbol);
            } else if (figureType == "circle") {
                figure = new Circle(x, y, size, symbol);
            }else if (figureType == "triangle1") {
                figure = new Triangle1 (x, y, size, symbol);;
            }else if (figureType == "triangle2") {
                figure = new Triangle2 (x, y, size, symbol);;
            }else if (figureType == "triangle3") {
                figure = new Triangle3 (x, y, size, symbol);;
            }else if (figureType == "triangle4") {
                figure = new Triangle4 (x, y, size, symbol);;
            }

            if (figure) {
                figures.push_back(figure);
            }
        }else if (key == "light") {
            int x, y;
            char symbol;
            char placeSymbol;
            iss >> x >> y >> placeSymbol >> symbol;
            std::cout << x << y << symbol << std::endl;
            light = new Light(x, y, symbol, placeSymbol);
            std::cout << x << y << symbol << std::endl;
        }
    }

    configFile.close();

    if (canvasWidth <= 0 || canvasHeight <= 0) {
        std::cout << "Niepoprawne wymiary płótna." << std::endl;
        return 1;
    }

    Canvas canvas(canvasWidth, canvasHeight);

    for (const auto& figure : figures) {
        figure->draw(canvas);
    }

    if (light != nullptr) {
        light->applyShadow(canvas, figures);
    }

    canvas.draw();

    if (!outputFilename.empty()) {
        canvas.saveToFile(outputFilename);
        std::cout << "Zapisano obraz do pliku: " << outputFilename << std::endl;
    }

    for (const auto& figure : figures) {
        delete figure;
    }

    delete light;

    return 0;
}
