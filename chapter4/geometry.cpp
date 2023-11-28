#include <iostream>

class Point {
    int x, y;
public:
    Point(int pos_x, int pos_y) {
        x =  pos_x;
        y = pos_y;
    }
    int getX() const{
        return x;
    }
    int getY() const{
        return y;
    }
};

class Geometry {
    int arrNum = 0;
    // 점100 개를보관하는배열.
    Point* point_array[100];
public:
    Geometry(Point **point_list) {
        point_list = point_list;
    }
    Geometry() {
        
    }
    void AddPoint(const Point &point);
    
    // 모든점들간의거리를출력하는함수입니다.
    void PrintDistance();
    
    // 모든점들을잇는직선들간의교점의수를출력해주는함수입니다.
    // 참고적으로 임의의 두 점을 잇는 직선의 방정식을 f(x,y) = ax+by+c = 0
    // 이라고할때임의의다른두점(x1, y1) 과(x2, y2) 가f(x,y)=0 을기준으로
    // 서로다른부분에있을조건은f(x1, y1) * f(x2, y2) <= 0 이면됩니다.
    void PrintNumMeets();
};

void Geometry::AddPoint(const Point &point) {
    point_array[arrNum++] = new Point(point.getX(), point.getY());
}

void Geometry::PrintDistance() {
    for(int i=0; i<arrNum; i++) {
        for(int j=i+1; j<arrNum; j++) {
            std::cout<<"("<<point_array[i]->getX()<<", "<<point_array[i]->getY()<<")와 ("<<point_array[j]->getX()<<", "<<point_array[j]->getY()<<")의 거리"<<std::endl;
            float x = (point_array[i]->getX()-point_array[j]->getX()) * (point_array[i]->getX()-point_array[j]->getX());
            float y = (point_array[i]->getY()-point_array[j]->getY()) * (point_array[i]->getY()-point_array[j]->getY());
            float distance = sqrt(x+y);
            std::cout<<"Distance : "<<distance<<std::endl;
        }
    }
}

void Geometry::PrintNumMeets() {
    std::vector<float> slope;
    for(int i=0; i<arrNum; i++) {
        for(int j=i+1; j<arrNum; j++) {
            float s = (float)(point_array[i]->getY() - point_array[j]->getY()) / (point_array[i]->getX() - point_array[j]->getX());
            slope.push_back(s);
        }
    }
    int count = slope.size();
    for(int i=0; i<slope.size(); i++) {
        for(int j=0; j<slope.size(); j++){
            if(i > j && slope[i] == slope[j])
                break;
            else if(i != j && slope[i] == slope[j])
                count--;
        }
    }
    
    std::cout<<"모든 점들을 잇는 직선들 간의 교점의 수 : "<<count<<std::endl;
}

int main() {
    
    Geometry geometry;
    
    Point point(0, 0);
    geometry.AddPoint(point);
    
    Point point2(3, 4);
    geometry.AddPoint(point2);
    
    Point point3(-3, -4);
    geometry.AddPoint(point3);
    
    Point point4(-5, 5);
    geometry.AddPoint(point4);
    
    Point point5(6, 8);
    geometry.AddPoint(point5);
    
    Point point6(1, 1);
    geometry.AddPoint(point6);
    
    geometry.PrintDistance();
    geometry.PrintNumMeets();
    
    return 0;
}
