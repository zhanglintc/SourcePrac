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
            double lenght,lenght1,lenght2;
            count = 2;
            vector<Point>::reverse_iterator it1,it2,it3;
            it1 = points.rbegin();
            it2 = it1+1;
            it3 = it2+1;
            lenght = getdistance(it1->x,it1->y,it2->x,it2->y);
            distanceflag = (it1->x - it2->x)>>31;
            for( ;it2 != points.rend(); ++it2)
            {
                for( ; it3 != points.rend(); ++it3)
                {
                    lenght1 = getdistance(it1->x,it1->y,it3->x,it3->y);
                    lenght2 = getdistance(it2->x,it2->y,it3->x,it3->y);
                    if(isonline(lenght,lenght1,lenght2,checklenght(it3->x,it1->x,it2->x),distanceflag))
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
    inline int checklenght(int thispoint, int pointone, int pointtwo)
    {
        if((thispoint > pointone) && (thispoint > pointtwo))
            return 1;
        else if((thispoint < pointone) && (thispoint < pointtwo))
            return -1;
        else
            return 0;
    }
    double getdistance(int x1, int y1, int x2, int y2)
    {
        int temp1,temp2;
        temp1=square(x1-x2);
        temp2=square(y1-y2);
        return sqrt(temp1+temp2);
    }
    inline bool isonline(double &lenght,double &lenght1,double &lenght2,int lenghtflag, int flag)
    {
        bool rt;
        switch(lenghtflag)
        {
            case -1:
                if(flag == 0)
                    return doubleequal((lenght+lenght2),lenght1);
                else
                    return doubleequal((lenght+lenght1),lenght2);
            case 0:
                return doubleequal((lenght1+lenght2),lenght);
            case 1:
                if(flag ==0)
                    return doubleequal((lenght+lenght1),lenght2);
                else
                    return doubleequal((lenght+lenght2),lenght1);
            
            default:
                return false;
        }
    }
    inline void setmaxnum(int num)
    {
        if(num > maxnum)
            maxnum = num;
    }
    inline int square(int num)
    {
        return num*num;
    }
    inline bool doubleequal(double num1, double num2)
    {
        if((num1 - num2)< 0.005)
            return true;
        else return false;
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

