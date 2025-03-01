#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "svg.hpp"
using namespace std;

pos::pos(double x, double y) {
    this->x = x;
    this->y = y;
}
pos pos::operator+(pos &other) {
    return {this->x + other.x, this->y + other.y};
}
pos pos::operator-(pos &other) {
    return {this->x - other.x, this->y - other.y};
}

rgb::rgb() {
    r = 10;
    g = 10;
    b = 10;
}
rgb::rgb(uint r, uint g, uint b) {
    this->r = r;
    this->g = g;
    this->b = b;
}
string rgb::str() {
    stringstream ss;
    ss << '#';
    ss << setfill('0') << hex;
    ss << setw(2) << r << setw(2) << g << setw(2) << b;
    // cerr << r << ' ' << g << ' ' << b << endl; // debug
    return ss.str();
}
string to_string(rgb r) {
    return r.str();
}

color::color() {
    this->r = (rgb){3, 4, 5};
}
string color::str() {
    return r.str();
}
string to_string(color c) {
    return c.str();
}

svg::svg(string file_path, pos p1, pos p2, string unit) {
    fout = ofstream(file_path);
    start(p1, p2, unit);
}
svg::~svg() {
    finish();
    fout.close();
}

void svg::write_xml_tag(string tagname, map<string, string> attributes, bool shorttag) {
    fout << '<' << tagname << ' ';
    for (auto [key, value] : attributes) {
        fout << key << "=\"" << value << "\" ";
    }
    if (shorttag) {
        fout << "/>" << endl;
        return;
    }
    // !shorttag 未実装 #todo
    fout << '>';
    fout << "</" << tagname << '>' << endl;
}
void svg::start(pos pos1, pos pos2, string unit){
    fout << "<?xml version=\"1.0\" encoding=\"Shift-JIS\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg version=\"1.1\" width=\"" << pos2.x << unit << "\" height=\"" << pos2.y << unit << "\"\n  viewBox=\"" << pos1.x << ' ' << pos1.y << ' ' << pos2.x << ' ' << pos2.y << "\"\n  preserveAspectRatio=\"xMidYMid\"\n  fill-rule=\"evenodd\"\n  xmlns=\"http://www.w3.org/2000/svg\"\n  xmlns:xlink=\"http://www.w3.org/1999/xlink\">" << endl;
    // cout << pos1.x << ' ' << pos2.x << endl; // debug
    return;
}
void svg::finish(){
    fout << "</svg>" << endl;
    return;
}
void svg::text(pos pos, string str, rgb rgb, uint size, string optional_attributes){
    fout << "<text x=\"" << pos.x << "\" y=\"" << pos.y << "\" font-family=\"monospace\" font-size=\"" << size << "\" stroke=\"none\" fill=\"#" << hex << setw(2) << rgb.r << setw(2) << rgb.g << setw(2) << rgb.b << dec << "\" " << optional_attributes << ">\n  " << str << "\n</text>" << endl;
    return;
}
void svg::circle(pos pos1, pos pos2, rgb rgb){
    const double strokeWidth = 8.0;
    fout << "<circle cx=\"" << pos1.x << "\" cy=\"" << pos1.y << "\" r=\"" << pos2.x - pos1.x << "\" fill=\"none\" stroke=\"#" << hex << setw(2) << rgb.r << setw(2) << rgb.g << setw(2) << rgb.b << dec << "\" stroke-width=\"" << strokeWidth << "\" />" << endl;
    return;
}
void svg::rect(pos pos1, pos pos2, rgb r, map<string, string> optional_attributes){
    map<string, string> attributes;
    attributes["x"] = to_string(pos1.x);
    attributes["y"] = to_string(pos1.y);
    attributes["width"] = to_string(pos2.x - pos1.x);
    attributes["height"] = to_string(pos2.y - pos1.y);
    attributes["fill"] = r.str();
    attributes.merge(optional_attributes);
    write_xml_tag("rect", attributes, true);
    return;
}
// void svg::rect(pos pos1, pos pos2, rgb rgb, string optional_attributes){
//     fout << "<rect x=\"" << pos1.x << "\" y=\"" << pos1.y << "\" width=\"" << pos2.x - pos1.x << "\" height=\"" << pos2.y - pos1.y << "\" style=\" fill:#" << setw(2) << hex << rgb.r << setw(2) << rgb.g << setw(2) << rgb.b << dec << "\" " << optional_attributes << " />" << endl;
//     return;
// }
void svg::line(pos pos1, pos pos2, rgb rgb){
    fout << "<line x1=\"" << fixed << pos1.x << "\" y1=\"" << pos1.y << "\" x2=\"" << pos2.x << "\" y2=\"" << pos2.y << "\" stroke=\"#" << hex << setw(2) << rgb.r << setw(2) << rgb.g << setw(2) << rgb.b << dec << "\" stroke-width=\"" << 1 << "\" stroke-opacity=\"" << 1 << "\" stroke-linecap=\"round\" />" << endl;
    return;
}
// void svg::svg_line(string x1, string x2, string y1, string y2, map<string, string> global_attributes);
// type length, percentage, number
// https://developer.mozilla.org/ja/docs/Web/SVG/Element/line
