//
// Created by iridescent on 27.04.22.
//

#include "AUI/Platform/AWindow.h"
#include "AUI/View/AButton.h"
#include "view/AGraphView.h"
#include "thread"
#include "view/AHistogramView.h"

class MainWindow : public AWindow {
public:
    static std::pair<int, int> windowSize;
    MainWindow();
    ~MainWindow();
private:
    std::thread mThread;
    std::thread sThread;
    _<AGraphView> rawSignal;
    _<AGraphView> fftSpectrum;
    _<AHistogramView> histogram;
    _<AButton> recordButton;
    DataFlow dataFlow;
    void getSpectrogram();
    //_<ALabel> test;

};
