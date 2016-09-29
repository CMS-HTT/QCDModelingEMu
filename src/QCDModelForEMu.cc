//
//  QCDModelFoeEMu.cc
//  
//
//  Created by Yiwen on 16/3/24.
//
//

#include "HTT-utilities/QCDModelingEMu/interface/QCDModelForEMu.h"

QCDModelForEMu::QCDModelForEMu(TString inputFile)
{
  TString cmsswBase = TString( getenv ("CMSSW_BASE") );
  TString baseDir = cmsswBase + "/src/";
  TString fullPath = baseDir + inputFile;

  TFile *fileIn = new TFile(fullPath, "read");
  if (fileIn->IsZombie())
    { std::cout << "ERROR in QCDModelForEMu::initQCDModeling(TString inputRootFile) from HTT-utilities/QCDModelForEMu/QCDModelForEMu.cc : File " <<inputFile << " does not exist. Please check. " <<std::endl; 
      exit(-1);
    };
    
  qcdHistWeightsCR1dRLt2H=(TH2D*)fileIn->Get("QCDratio_CR1_dRLt2");
  qcdHistWeightsCR1dR2to4H=(TH2D*)fileIn->Get("QCDratio_CR1_dR2to4");
  qcdHistWeightsCR1dRGt4H=(TH2D*)fileIn->Get("QCDratio_CR1_dRGt4");
  
  qcdHistWeightsCR2dRLt2H=(TH2D *)fileIn->Get("QCDratio_CR2_dRLt2");
  qcdHistWeightsCR2dR2to4H=(TH2D *)fileIn->Get("QCDratio_CR2_dR2to4");
  qcdHistWeightsCR2dRGt4H=(TH2D *)fileIn->Get("QCDratio_CR2_dRGt4");
    
  nBinsQCD = qcdHistWeightsCR1dRLt2H->GetNbinsX();
  qcdMin = qcdHistWeightsCR1dRLt2H->GetXaxis()->GetBinLowEdge(1);
  qcdMax = qcdHistWeightsCR1dRLt2H->GetXaxis()->GetBinLowEdge(1+nBinsQCD);
  
  std::cout << "QCDModelForEMu::QCDModelForEMu() constructor : " << std::endl;
  std::cout << "nBins(QCD) = " << nBinsQCD
	    << "    min(QCD) = " << qcdMin
	    << "    max(QCD) = " << qcdMax << std::endl;
  std::cout << std::endl;


}

QCDModelForEMu::~QCDModelForEMu()
{
}

float QCDModelForEMu::getWeight(float pt_1, float pt_2,float dr_tt)
{
  float ptlead  = pt_1;
  float pttrail = pt_2;
  if (ptlead<pttrail)
    {
      ptlead  = pt_2;
      pttrail = pt_1;
    }
  
  if (ptlead>qcdMax)  ptlead = qcdMax-0.1;  
  if (ptlead<qcdMin)  ptlead = qcdMin+0.1; 
  if (pttrail>qcdMax) pttrail = qcdMax-0.1;  
  if (pttrail<qcdMin) pttrail = qcdMin+0.1; 

  float qcdweight = 1;
  
  if (dr_tt<2)
    qcdweight = qcdHistWeightsCR1dRLt2H->GetBinContent(qcdHistWeightsCR1dRLt2H->FindBin(pttrail,ptlead));
  else if (dr_tt>=2&&dr_tt<4)
    qcdweight = qcdHistWeightsCR1dR2to4H->GetBinContent(qcdHistWeightsCR1dR2to4H->FindBin(pttrail,ptlead));
  else
    qcdweight = qcdHistWeightsCR1dRGt4H->GetBinContent(qcdHistWeightsCR1dRGt4H->FindBin(pttrail,ptlead));
  
  return qcdweight;

}

float QCDModelForEMu::getWeightUp(float pt_1, float pt_2, float dr_tt)
{
    
  float ptlead  = pt_1;
  float pttrail = pt_2;
  if (ptlead<pttrail)
    {
      ptlead  = pt_2;
      pttrail = pt_1;
    }

  if (ptlead>qcdMax)  ptlead = qcdMax-0.1;  
  if (ptlead<qcdMin)  ptlead = qcdMin+0.1; 
  if (pttrail>qcdMax) pttrail = qcdMax-0.1;  
  if (pttrail<qcdMin) pttrail = qcdMin+0.1; 
    
  float qcdweight = 1;

  if (dr_tt<2)
    qcdweight = qcdHistWeightsCR2dRLt2H->GetBinContent(qcdHistWeightsCR2dRLt2H->FindBin(pttrail,ptlead));
  else if (dr_tt>=2&&dr_tt<4)
    qcdweight = qcdHistWeightsCR2dR2to4H->GetBinContent(qcdHistWeightsCR2dR2to4H->FindBin(pttrail,ptlead));
  else
    qcdweight = qcdHistWeightsCR2dRGt4H->GetBinContent(qcdHistWeightsCR2dRGt4H->FindBin(pttrail,ptlead));

  return qcdweight;

}

float QCDModelForEMu::getWeightDown(float pt_1, float pt_2, float dr_tt)
{
    
  float qcdweight   = getWeight(pt_1,pt_2,dr_tt);
  float qcdweightup = getWeightUp(pt_1,pt_2,dr_tt);
    
  float qcdweightdown=qcdweight*qcdweight/qcdweightup;
  
  return qcdweightdown;

}
