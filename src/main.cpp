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

// code from wuhong...
class Solution {
public:
    int maxnum;

    int maxPoints(vector<Point> &points) {
        if(points.size() == 0)
            return 0;

        if(points.size() == 1)
            return 1;

        if(points.size() == 2)
            return 2;

        int count(0);
        maxnum = 0;

        while(1)
        {
            int distanceflag;
            double length, length1, length2;
            count = 2;
            vector<Point>::reverse_iterator it1, it2, it3;
            it1 = points.rbegin();
            it2 = it1 + 1;
            it3 = it2 + 1;

            length = getdistance(it1->x, it1->y, it2->x, it2->y);
            distanceflag = (it1->x - it2->x) >> 31;

            for( ; it2 != points.rend(); ++it2)
            {
                for( ; it3 != points.rend(); ++it3)
                {
                    length1 = getdistance(it1->x, it1->y, it3->x, it3->y);
                    length2 = getdistance(it2->x, it2->y, it3->x, it3->y);
                    if(isonline(length, length1, length2, checklength(it3->x, it1->x, it2->x), distanceflag))
                        ++count;
                }
            }

            points.pop_back();
            setmaxnum(count);
            if(points.size() == 2)
            break;
        }

        return maxnum;
    }

    /*
    return  1: this point in right
    return -1: this point in left
    return  0: this point in middle
    */
    inline int checklength(int thispoint, int pointone, int pointtwo)
    {
        if((thispoint > pointone) && (thispoint > pointtwo))
            return 1;
        else if((thispoint < pointone) && (thispoint < pointtwo))
            return -1;
        else
            return 0;
    }

    // distance of two point
    double getdistance(int x1, int y1, int x2, int y2)
    {
        double temp1, temp2;
        temp1 = square(x1 - x2);
        temp2 = square(y1 - y2);
        return (double)sqrt(temp1 + temp2);
    }

    // 
    inline bool isonline(double &length, double &length1, double &length2, int lengthType, int distanceflag)
    {
        switch(lengthType)
        {
            case -1:
                if(distanceflag == 0)
                    return doubleequal((length + length2), length1);
                else
                    return doubleequal((length + length1), length2);
            case 0:
                return doubleequal((length1 + length2), length);
            case 1:
                if(distanceflag == 0)
                    return doubleequal((length + length1), length2);
                else
                    return doubleequal((length + length2), length1);
            
            default:
                return false;
        }
    }

    inline void setmaxnum(int num)
    {
        if(num > maxnum)
            maxnum = num;
    }

    // square of two num
    inline double square(int num)
    {
        return (double)num * num;
    }

    // check two double equals or not
    inline bool doubleequal(double num1, double num2)
    {
        return ((num1 - num2) < 0.0000005 ? true : false);
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
    //cout << points.size() << endl;

    
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

