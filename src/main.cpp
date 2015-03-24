// SourceMain.cpp : Console application entry point

#include "headers.h"

#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

//#define printf(fmt, args...) myprintf(fmt, ##args)
//#define DEBUG_PRINT(x,...) wprintf(x,__VA_ARGS__)
//#define LOG(format, ...) printf(format,__VA_ARGS__)
//#define DEBUG_PRINT#(
#define DEBUG_PRINT minprintf

//2014.03.20 ZhangLin -S
//ADVANCED LEARNER'S English-Chinese Dictionary
//roll 2056 resulted 1830
//roll   16 resulted 5
//-----theodolite-----
//2014.03.20 ZhangLin -E
//Happy birthday!!! 2014.06.23 --Lane to myself
//Macbook Air!!! 2014.07.27 --Lane
////////////////////////////////////

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
    int maxPoints(vector<Point> &points) {
        int max_counter = 0;
        int cur_counter = 0;
        int this_point_max = 1;
        map<int, int> modifier;
        map<pair<int, int>, int> counter;
        pair<int, int> line;
        int slope = 0;

        if(points.size() == 1)
            return 1;

        if(points.size() == 2)
            return 2;

        for(int i = 0; i < points.size(); i++) {
            for(int j = 0; j < points.size(); j++) {
                if(i == j)
                    continue;

                if(points[i].x == points[j].x && points[i].y == points[j].y) {
                    modifier[i] = (modifier.find(i) == modifier.end() ? 1 : modifier.find(i)->second) + 1;
                    continue;
                }

                else if(points[i].x == points[j].x) {
                    slope = 0xffff;
                    line.first = i;
                    line.second  = slope;
                }

                else {
                    slope = float((points[i].y - points[j].y)) / float((points[i].x - points[j].x));
                    line.first = i;
                    line.second  = slope;
                }

                counter[line] = (counter.find(line) == counter.end() ? 0 : counter.find(line)->second) + 1;
                this_point_max = this_point_max > counter[line] ? this_point_max : counter[line];
            }

            cur_counter = this_point_max + (modifier.find(i) == modifier.end() ? 1 : modifier.find(i)->second);
            this_point_max = 1;

            max_counter = max_counter > cur_counter ? max_counter : cur_counter;

            counter.clear();
        }

        return max_counter;
    }
};
int main(int argc)
{
    //Initialize();
    //ControlDock();

    vector<Point> points;

    points.push_back(Point(1, 1));
    points.push_back(Point(1, 1));
    points.push_back(Point(2, 2));
    points.push_back(Point(2, 2));

    Solution s = Solution();
    cout << s.maxPoints(points) << endl;
    
    //SocketCaller();
/********************************************************************************************/
/********************************************************************************************/
/****************************  Below is the end mark  ***************************************/
/********************************************************************************************/
/********************************************************************************************/
    setTextColor(TEAL);
    printf("\n\n\n");
    printf("********Test over*********\n");
    printf("Press any key to exit...\n");
    printf("**************************\n");
    getchar();
    return 0;
}

