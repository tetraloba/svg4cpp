#include <fstream>
#include <string>
#include <map>

class pos {
    public:
        double x;
        double y;
        pos(double x, double y);
        pos operator+(pos &other);
        pos operator-(pos &other);
};

class rgb {
    public:
        uint r;
        uint g;
        uint b;
        rgb();
        rgb(uint r, uint g, uint b);
        std::string str();
};
std::string to_string(rgb);

class color {
    public:
        rgb r;
        color();
        std::string str();
};
std::string to_string(color c);

class svg {
    private:
        void write_xml_tag(std::string tagname, std::map<std::string, std::string> attributes, bool shorttag);
        void start(pos, pos, std::string); //SVGのヘッダを出力 指定座標でキャンバスサイズとビューポイント
        void finish(); //SVGタグを閉じる
    public:
        std::ofstream fout;
        color default_fill;
        color default_stroke;
        svg(std::string file_path, pos p1, pos p2, std::string unit);
        ~svg();
        void line(pos, pos, rgb); //直線を出力
        void rect(pos, pos, rgb, std::map<std::string, std::string> optional_attributes = std::map<std::string, std::string>()); //矩形(長方形)を出力
        void circle(pos, pos, rgb); //円を出力
        void text(pos, std::string, rgb, uint, std::string optional_attributes); //文字を出力
};

