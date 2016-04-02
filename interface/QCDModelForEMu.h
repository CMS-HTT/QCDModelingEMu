#ifndef HTT_QCDModelForEMu_h
#define HTT_QCDModelForEMu_h

//
//  QCDModelFoeEmu.hpp
//  
//
//  Created by Yiwen on 16/3/24.
//
//

#ifndef QCDModelForEMu_h
#define QCDModelForEMu_h

#include <stdio.h>
#include "TROOT.h"
#include "TFile.h"
#include "TH2.h"
#include <iostream>
#include <map>
#include <cmath>
#include <string>

#endif /* QCDModelFoeEmu_hpp */
class QCDModelForEMu
{
    private:
    TH2D * qcdHistWeightsCR1dRLt2H;
    TH2D * qcdHistWeightsCR1dR2to4H;
    TH2D * qcdHistWeightsCR1dRGt4H;
    
    TH2D * qcdHistWeightsCR2dRLt2H;
    TH2D * qcdHistWeightsCR2dR2to4H;
    TH2D * qcdHistWeightsCR2dRGt4H;
    
    int nBinsQCD;
    float qcdMin;
    float qcdMax;
    
    public:
    
    QCDModelForEMu(TString inputFile);
    ~QCDModelForEMu();
    
    float getWeight(float pt_1, float pt_2, float dr_tt);
    float getWeightUp(float pt_1, float pt_2, float dr_tt);
    float getWeightDown(float pt_1, float pt_2, float dr_tt);
    
};

#endif
