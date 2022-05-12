//
// Created by iridescent on 27.04.22.
//
#include <numeric>
#include "AUI/ASS/ASS.h"
#include "AGraphView.h"

AGraphView::AGraphView(int pointsNum) :  data(pointsNum, {0,0}) {
    this->pointsNum = pointsNum;
    //setExpanding();
    setExpanding();
    std::cout<<getSize()[0] << " " << getSize()[1]<<std::endl;

}

void AGraphView::setData(std::vector<glm::vec2> d) {

    maxY = (*std::max_element(d.begin(), d.end(),
                              [](glm::vec2 &a, glm::vec2 &b) {
                                  return a[1] < b[1];
                              }))[1];
    minY = (*std::min_element(d.begin(), d.end(),
                              [](glm::vec2 &a, glm::vec2 &b) {
                                  return a[1] < b[1];
                              }))[1];
    //std::cout << maxY << " " << minY << std::endl;
    minX = d[0][0];
    maxX = d[pointsNum-1][0];
    auto height = getSize()[1];
    auto weight = getSize()[0];
    double coef = 1;
    if (maxY != minY ) coef = height / 2 / (fabs(maxY) + fabs(minY));
    for (int i = 0; i < pointsNum; i++) {
        data[i] = {i*weight/pointsNum, -(d[i][1] * coef) + (height/2+(maxY+minY) / 2) * coef};

    }
    this->delta = (height/2+(maxY+minY) / 2) * coef;
    redraw();
}


void AGraphView::render() {
    std::cout << getSize()[0] << " " << getSize()[1] << std::endl;
    AView::render();
    //Render::rect(ASolidBrush{0x009999_rgb}, {0,0}, getSize());
    Render::line(ASolidBrush{0x0020202_rgb}, {0,0}, {getSize()[0],0});
    Render::lines(ASolidBrush{0x000000_rgb}, data);
    Render::line(ASolidBrush{0x0020202_rgb}, {0,0}, {0,getSize()[1]});
    renderCoordinatesX();
    renderCoordinatesY();
}

/**
 *
 */
void AGraphView::renderCoordinatesX() {
    unsigned int wight = getSize()[0];
    //10 - min number of pixels between divisions, should be calculated
    /**/
    std::cout << wight << std::endl;
    unsigned int numOfDivisions = std::min(pointsNum, (int)(wight / 20));
    std::cout << wight << std::endl;
    unsigned int divisionsLength = wight / numOfDivisions;
    Render::line(ASolidBrush{0x0020202_rgb}, {0,delta}, {wight,delta});
    for (int i = 0; i < numOfDivisions; i++) {
        Render::line(ASolidBrush{0x0020202_rgb}, {i*divisionsLength,delta + 1},
                     {i*divisionsLength,delta - 1});
        Render::string({i*divisionsLength,delta + 3},
                       std::to_string((int)std::round(minX + (maxX-minX)/numOfDivisions)*i));
    }
}

void AGraphView::renderCoordinatesY() {
    auto maxYg = (*std::max_element(data.begin(), data.end(),
                                  [](glm::vec2 &a, glm::vec2 &b) {
                                      return a[1] > b[1];
                                  }))[1];
    auto minYg = (*std::min_element(data.begin(), data.end(),
                                  [](glm::vec2 &a, glm::vec2 &b) {
                                      return a[1] > b[1];
                                  }))[1];
    if (minYg<0) Render::string({2,delta}, std::to_string(0));
    Render::line(ASolidBrush{0x0020202_rgb}, {0,maxYg}, {2,maxYg});
    Render::string({2,maxYg}, std::to_string((int)std::ceil(maxY)));
    Render::line(ASolidBrush{0x0020202_rgb}, {0,minYg}, {2,minYg});
    Render::string({2,minYg}, std::to_string((int)std::round(minY)));
}

