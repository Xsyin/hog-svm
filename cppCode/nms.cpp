#include <iostream>
#include <opencv2/opencv.hpp>
#include "detect.h"

/**
 *  Non Maximum Suppression to merge all detected region rectangles
 *  @param srcRects
 *  @param resRects
 *  @param thresh
 *
 *  @return
 */
void nonMaximumSuppression(const vector<Rect>& srcRects, vector<Rect>& resRects, float thresh)
{
    resRects.clear();
    const size_t size = srcRects.size();
    if (!size)
    {
        return;
    }
    // Sort the bounding boxes by the bottom - right y - coordinate of the bounding box
    multimap<int, size_t> idxs;
    for (size_t i = 0; i < size; ++i)
    {
        idxs.insert(pair<int, size_t>(srcRects[i].br().y, i));
    }
    // keep looping while some indexes still remain in the indexes list
    while (idxs.size() > 0)
    {
        // grab the last rectangle
        multimap<int, size_t>::iterator lastElem = --idxs.end();
        const Rect& rect1 = srcRects[lastElem->second];
        resRects.push_back(rect1);
        idxs.erase(lastElem);
        for (multimap<int, size_t>::iterator pos = idxs.begin(); pos != idxs.end(); )
        {
            // grab the current rectangle
            const Rect& rect2 = srcRects[pos->second];
            float intArea = (rect1 & rect2).area();
            float unionArea = rect1.area() + rect2.area() - intArea;
            float overlap = intArea / unionArea;
            // if there is sufficient overlap, suppress the current bounding box
            if (overlap > thresh)
            {
                idxs.erase(pos);
                pos++;
            }
            else
            {
                ++pos;
            }
        }
    }
}
