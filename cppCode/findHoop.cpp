#include "detect.h"

/**
 /**
 *  Find max overlap rect in all rects
 *  @param video path
 *  @param frame number
 *  @param hoop region
 *
 *  @return state of detect
 */
bool findHoop(vector<Rect>& allRects, vector<Rect>& nmsRects, int frameNum, Rect& hoop)
{
    //用来标记检测结果是否足够好
    bool flag = true;
    int centerPoints[nmsRects.size()][2];
    memset(centerPoints, 0, sizeof(centerPoints));

    int rectCount[nmsRects.size()];
    memset(rectCount, 0, sizeof(rectCount));

//    cout<<"=======center point======="<<endl;
    for (int i = 0; i<nmsRects.size() ; i++ )
    {
        centerPoints[i][0] = nmsRects[i].x + nmsRects[i].width / 2;
        centerPoints[i][1] = nmsRects[i].y + nmsRects[i].height / 2;
//        cout<<"center: "<<centerPoints[i][0]<<", "<<centerPoints[i][1]<<endl;
    }
    int n, c;
    for(n = 0; n<allRects.size(); n++)
    {
        for(c = 0; c<nmsRects.size(); c++)
        {
            if (allRects[n].x <= centerPoints[c][0]
                    &&allRects[n].y <= centerPoints[c][1]
                    &&centerPoints[c][0] <= allRects[n].x + allRects[n].width
                    &&centerPoints[c][1] <= allRects[n].y + allRects[n].height)
                rectCount[c]++;
        }
    }
    int maxCount = rectCount[0];
    int pos = 0;
    for(n = 1; n<nmsRects.size(); n++)
    {
        if (maxCount < rectCount[n])
        {
            maxCount = rectCount[n];
            pos = n;
        }
    }
    if (maxCount < frameNum/2 )
    {
        cout<<"Detection result is not good enough!!"<<endl;
        flag = false;
    }


//    cout<<"=======rect count======="<<endl;
//    for (n = 0; n<nmsRects.size() ;n++ )
//        cout<<"rect count"<<n<<": "<<rectCount[n]<<endl;

    hoop = nmsRects[pos];
    return flag;
}
