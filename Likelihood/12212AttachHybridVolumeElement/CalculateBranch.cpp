#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <ctime>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "Code/TauHelperFunctions2.h"
#include "Code/DrawRandom.h"
#include "ProgressBar.h"

#include "AngleConversion.h"
#include "CalculateME.h"
#include "MEFunctions.h"

#include "LeptonResponse.h"
#include "HybridCalculator.h"
#include "PTYFunctions.h"

int main(int argc, char *argv[]);
bool CheckIfGood(vector<double> Single);
void AddToVector(vector<double> &Total, vector<double> Single, double Weight);
void PrintResult(string Identifier, vector<double> Total, int Count);
bool PassBaselineCut(EventParameters &Event);

int main(int argc, char *argv[])
{
   string FileName = "EventB.root";
   int StartEvent = 0;
   int EndEvent = 19;

   if(argc <= 3)
   {
      cerr << "Usage: " << argv[0] << " FileWithTree StartEvent EndEvent" << endl;
      return -1;
   }

   FileName = argv[1];
   StartEvent = atoi(argv[2]);
   EndEvent = atoi(argv[3]);

   // Read spectrum of Higgs
   ifstream in("HiggsFile_125");
   vector<double> HPT, HEta, HWeight;
   while(in)
   {
      char ch[10240] = "";
      in.getline(ch, 10239, '\n');
      if(ch[0] == '\0')
         continue;

      stringstream str(ch);

      double TempPT = -100, TempEta = -100, TempWeight = -100;
      str >> TempPT >> TempEta >> TempWeight;

      if(TempPT < 0 || TempEta < -99 || TempWeight < -99)
         continue;

      HPT.push_back(TempPT);
      HEta.push_back(TempEta);
      HWeight.push_back(TempWeight);
   }

   // Setup calculators
   HybridCalculator CalculatorEE, CalculatorME, CalculatorEM, CalculatorMM;

   CalculatorEM.SetEfficiency12(GetElectronEfficiencyPtEta);
   CalculatorEM.SetEfficiency34(GetMuonEfficiencyPtEta);
   CalculatorEM.SetSmear12(SmearElectronCentral);
   CalculatorEM.SetSmear34(SmearMuonCentral);
   CalculatorEM.SetToleranceF(1e-12);
   CalculatorEM.SetMaxDepthF(30);
   CalculatorEM.SetSimpleMassIntegralStep(180);
   CalculatorEM.SetExpansionOrder(2);
   CalculatorEM.SetDoDeltaMH(true, 125);
   CalculatorEM.SetIgnorePhi(true);
   CalculatorEM.SetApplyEfficiencyAtEnd(true);
   CalculatorEM.SetIntegralCRange(0.75, 1.25);
   CalculatorEM.SetPTYDensity(GetPTYDensity);
   // CalculatorEM.SetAttractorStrength(true, 2);
   CalculatorEM.SetIntegralCStep(20);
   CalculatorEM.SetSimpleMassIntegralWindow(true, 20);
   CalculatorEM.SetSimpleMassIntegralWindow(false, 30);
   CalculatorEM.SetFlatApproximation(false);
   CalculatorEM.SetIncludeSwapping(true);

   CalculatorEM.SetMECalculator(CalculateA1RA1RSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2RA2RSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2IA2ISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3RA3RSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3IA3ISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1RA2RSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1RA2ISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1RA3RSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA1RA3ISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2RA2ISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2RA3RSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2RA3ISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2IA3RSignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA2IA3ISignal2e2mu);
   CalculatorEM.SetMECalculator(CalculateA3RA3ISignal2e2mu);

   CalculatorME = CalculatorEM;
   CalculatorME.SetEfficiency12(GetMuonEfficiencyPtEta);
   CalculatorME.SetEfficiency34(GetElectronEfficiencyPtEta);
   CalculatorME.SetSmear12(SmearMuonCentral);
   CalculatorME.SetSmear34(SmearElectronCentral);

   CalculatorEE.SetEfficiency12(GetElectronEfficiencyPtEta);
   CalculatorEE.SetEfficiency34(GetElectronEfficiencyPtEta);
   CalculatorEE.SetSmear12(SmearElectronCentral);
   CalculatorEE.SetSmear34(SmearElectronCentral);
   CalculatorEE.SetToleranceF(1e-12);
   CalculatorEE.SetMaxDepthF(30);
   CalculatorEE.SetSimpleMassIntegralStep(180);
   CalculatorEE.SetExpansionOrder(2);
   CalculatorEE.SetDoDeltaMH(true, 125);
   CalculatorEE.SetIgnorePhi(true);
   CalculatorEE.SetApplyEfficiencyAtEnd(true);
   CalculatorEE.SetIntegralCRange(0.75, 1.25);
   CalculatorEE.SetPTYDensity(GetPTYDensity);
   // CalculatorEE.SetAttractorStrength(true, 2);
   CalculatorEE.SetIntegralCStep(20);
   CalculatorEE.SetSimpleMassIntegralWindow(true, 20);
   CalculatorEE.SetSimpleMassIntegralWindow(false, 30);
   CalculatorEE.SetFlatApproximation(false);
   CalculatorEE.SetIncludeSwapping(true);

   CalculatorEE.SetMECalculator(CalculateA1RA1RSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2RA2RSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2IA2ISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3RA3RSignal4e);
   CalculatorEE.SetMECalculator(CalculateA3IA3ISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1RA2RSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1RA2ISignal4e);
   CalculatorEE.SetMECalculator(CalculateA1RA3RSignal4e);
   CalculatorEE.SetMECalculator(CalculateA1RA3ISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2RA2ISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2RA3RSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2RA3ISignal4e);
   CalculatorEE.SetMECalculator(CalculateA2IA3RSignal4e);
   CalculatorEE.SetMECalculator(CalculateA2IA3ISignal4e);
   CalculatorEE.SetMECalculator(CalculateA3RA3ISignal4e);

   CalculatorMM = CalculatorEE;
   CalculatorMM.SetEfficiency12(GetMuonEfficiencyPtEta);
   CalculatorMM.SetEfficiency34(GetMuonEfficiencyPtEta);
   CalculatorMM.SetSmear12(SmearMuonCentral);
   CalculatorMM.SetSmear34(SmearMuonCentral);

   HybridCalculator CalculatorUpEM, CalculatorUpME, CalculatorUpEE, CalculatorUpMM;
   HybridCalculator CalculatorDownEM, CalculatorDownME, CalculatorDownEE, CalculatorDownMM;
   HybridCalculator CalculatorWideEM, CalculatorWideME, CalculatorWideEE, CalculatorWideMM;
   HybridCalculator CalculatorNarrowEM, CalculatorNarrowME, CalculatorNarrowEE, CalculatorNarrowMM;

   CalculatorUpEM = CalculatorEM;                     CalculatorDownEM = CalculatorEM;
   CalculatorUpEM.SetSmear12(SmearElectronUp);        CalculatorDownEM.SetSmear12(SmearElectronDown);
   CalculatorUpEM.SetSmear34(SmearMuonUp);            CalculatorDownEM.SetSmear34(SmearMuonDown);
   CalculatorUpME = CalculatorME;                     CalculatorDownME = CalculatorME;
   CalculatorUpME.SetSmear12(SmearMuonUp);            CalculatorDownME.SetSmear12(SmearMuonDown);
   CalculatorUpME.SetSmear34(SmearElectronUp);        CalculatorDownME.SetSmear34(SmearElectronDown);
   CalculatorUpEE = CalculatorEE;                     CalculatorDownEE = CalculatorEE;
   CalculatorUpEE.SetSmear12(SmearElectronUp);        CalculatorDownEE.SetSmear12(SmearElectronDown);
   CalculatorUpEE.SetSmear34(SmearElectronUp);        CalculatorDownEE.SetSmear34(SmearElectronDown);
   CalculatorUpMM = CalculatorMM;                     CalculatorDownMM = CalculatorMM;
   CalculatorUpMM.SetSmear12(SmearMuonUp);            CalculatorDownMM.SetSmear12(SmearMuonDown);
   CalculatorUpMM.SetSmear34(SmearMuonUp);            CalculatorDownMM.SetSmear34(SmearMuonDown);

   CalculatorWideEM = CalculatorEM;                   CalculatorNarrowEM = CalculatorEM;
   CalculatorWideEM.SetSmear12(SmearElectronWide);    CalculatorNarrowEM.SetSmear12(SmearElectronNarrow);
   CalculatorWideEM.SetSmear34(SmearMuonWide);        CalculatorNarrowEM.SetSmear34(SmearMuonNarrow);
   CalculatorWideME = CalculatorME;                   CalculatorNarrowME = CalculatorME;
   CalculatorWideME.SetSmear12(SmearMuonWide);        CalculatorNarrowME.SetSmear12(SmearMuonNarrow);
   CalculatorWideME.SetSmear34(SmearElectronWide);    CalculatorNarrowME.SetSmear34(SmearElectronNarrow);
   CalculatorWideEE = CalculatorEE;                   CalculatorNarrowEE = CalculatorEE;
   CalculatorWideEE.SetSmear12(SmearElectronWide);    CalculatorNarrowEE.SetSmear12(SmearElectronNarrow);
   CalculatorWideEE.SetSmear34(SmearElectronWide);    CalculatorNarrowEE.SetSmear34(SmearElectronNarrow);
   CalculatorWideMM = CalculatorMM;                   CalculatorNarrowMM = CalculatorMM;
   CalculatorWideMM.SetSmear12(SmearMuonWide);        CalculatorNarrowMM.SetSmear12(SmearMuonNarrow);
   CalculatorWideMM.SetSmear34(SmearMuonWide);        CalculatorNarrowMM.SetSmear34(SmearMuonNarrow);

   CalculatorEE.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorUpEE.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorDownEE.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorWideEE.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorNarrowEE.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorEM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorUpEM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorDownEM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorWideEM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorNarrowEM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorME.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorUpME.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorDownME.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorWideME.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorNarrowME.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorMM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorUpMM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorDownMM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorWideMM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);
   CalculatorNarrowMM.SetVerbosity(HybridCalculator::VerboseLevel_Quiet);

   // CalculatorEM.TestOutput();
   // CalculatorME.TestOutput();
   // CalculatorEE.TestOutput();
   // CalculatorMM.TestOutput();

   // Setup tree
   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("MCTree");

   float l1pt, l1eta, l1phi;   int l1id;
   float l2pt, l2eta, l2phi;   int l2id;
   float l3pt, l3eta, l3phi;   int l3id;
   float l4pt, l4eta, l4phi;   int l4id;
   Tree->SetBranchAddress("l1pt", &l1pt);
   Tree->SetBranchAddress("l1eta", &l1eta);
   Tree->SetBranchAddress("l1phi", &l1phi);
   Tree->SetBranchAddress("l1id", &l1id);
   Tree->SetBranchAddress("l2pt", &l2pt);
   Tree->SetBranchAddress("l2eta", &l2eta);
   Tree->SetBranchAddress("l2phi", &l2phi);
   Tree->SetBranchAddress("l2id", &l2id);
   Tree->SetBranchAddress("l3pt", &l3pt);
   Tree->SetBranchAddress("l3eta", &l3eta);
   Tree->SetBranchAddress("l3phi", &l3phi);
   Tree->SetBranchAddress("l3id", &l3id);
   Tree->SetBranchAddress("l4pt", &l4pt);
   Tree->SetBranchAddress("l4eta", &l4eta);
   Tree->SetBranchAddress("l4phi", &l4phi);
   Tree->SetBranchAddress("l4id", &l4id);

   // Start looping
   int EventCount = Tree->GetEntries();
   for(int iEvent = StartEvent; iEvent < EventCount && iEvent <= EndEvent; iEvent++)
   {
      Tree->GetEntry(iEvent);

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      EventParameters Angles = ConvertVectorsToAnglesRoberto(Leptons);

      LeptonVectors AlternativeLeptons;
      if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() > (Leptons.Lepton21 + Leptons.Lepton12).GetMass())
      {
         AlternativeLeptons.Lepton11 = Leptons.Lepton11;
         AlternativeLeptons.Lepton12 = Leptons.Lepton22;
         AlternativeLeptons.Lepton21 = Leptons.Lepton21;
         AlternativeLeptons.Lepton22 = Leptons.Lepton12;
      }
      else
      {
         AlternativeLeptons.Lepton11 = Leptons.Lepton21;
         AlternativeLeptons.Lepton12 = Leptons.Lepton12;
         AlternativeLeptons.Lepton21 = Leptons.Lepton11;
         AlternativeLeptons.Lepton22 = Leptons.Lepton22;
      }

      EventParameters AlternativeAngles = ConvertVectorsToAnglesRoberto(AlternativeLeptons);

      vector<double> Integral, IntegralUp, IntegralDown, IntegralWide, IntegralNarrow;
      vector<double> AlternativeIntegral, AlternativeIntegralUp, AlternativeIntegralDown,
         AlternativeIntegralWide, AlternativeIntegralNarrow;

      if(PassBaselineCut(Angles) == true)
      {
         if(l1id == 11 && l3id == 11)
         {
            Integral = CalculatorEE.SimpleMassIntegral(Angles);
            IntegralUp = CalculatorUpEE.SimpleMassIntegral(Angles);
            IntegralDown = CalculatorDownEE.SimpleMassIntegral(Angles);
            IntegralWide = CalculatorWideEE.SimpleMassIntegral(Angles);
            IntegralNarrow = CalculatorNarrowEE.SimpleMassIntegral(Angles);

            AlternativeIntegral = CalculatorEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralUp = CalculatorUpEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralDown = CalculatorDownEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralWide = CalculatorWideEE.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralNarrow = CalculatorNarrowEE.SimpleMassIntegral(AlternativeAngles);

            for(int i = 0; i < (int)Integral.size(); i++)
            {
               Integral[i] = (Integral[i] + AlternativeIntegral[i]);
               IntegralUp[i] = (IntegralUp[i] + AlternativeIntegralUp[i]);
               IntegralDown[i] = (IntegralDown[i] + AlternativeIntegralDown[i]);
               IntegralWide[i] = (IntegralWide[i] + AlternativeIntegralWide[i]);
               IntegralNarrow[i] = (IntegralNarrow[i] + AlternativeIntegralNarrow[i]);
            }
         }
         if(l1id == 11 && l3id == 13)
         {
            Integral = CalculatorEM.SimpleMassIntegral(Angles);
            IntegralUp = CalculatorUpEM.SimpleMassIntegral(Angles);
            IntegralDown = CalculatorDownEM.SimpleMassIntegral(Angles);
            IntegralWide = CalculatorWideEM.SimpleMassIntegral(Angles);
            IntegralNarrow = CalculatorNarrowEM.SimpleMassIntegral(Angles);
         }
         if(l1id == 13 && l3id == 11)
         {
            Integral = CalculatorME.SimpleMassIntegral(Angles);
            IntegralUp = CalculatorUpME.SimpleMassIntegral(Angles);
            IntegralDown = CalculatorDownME.SimpleMassIntegral(Angles);
            IntegralWide = CalculatorWideME.SimpleMassIntegral(Angles);
            IntegralNarrow = CalculatorNarrowME.SimpleMassIntegral(Angles);
         }
         if(l1id == 13 && l3id == 13)
         {
            Integral = CalculatorMM.SimpleMassIntegral(Angles);
            IntegralUp = CalculatorUpMM.SimpleMassIntegral(Angles);
            IntegralDown = CalculatorDownMM.SimpleMassIntegral(Angles);
            IntegralWide = CalculatorWideMM.SimpleMassIntegral(Angles);
            IntegralNarrow = CalculatorNarrowMM.SimpleMassIntegral(Angles);
            
            AlternativeIntegral = CalculatorMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralUp = CalculatorUpMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralDown = CalculatorDownMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralWide = CalculatorWideMM.SimpleMassIntegral(AlternativeAngles);
            AlternativeIntegralNarrow = CalculatorNarrowMM.SimpleMassIntegral(AlternativeAngles);

            for(int i = 0; i < (int)Integral.size(); i++)
            {
               Integral[i] = (Integral[i] + AlternativeIntegral[i]);
               IntegralUp[i] = (IntegralUp[i] + AlternativeIntegralUp[i]);
               IntegralDown[i] = (IntegralDown[i] + AlternativeIntegralDown[i]);
               IntegralWide[i] = (IntegralWide[i] + AlternativeIntegralWide[i]);
               IntegralNarrow[i] = (IntegralNarrow[i] + AlternativeIntegralNarrow[i]);
            }
         }
      }
      else
         cout << "Didn't pass baseline cut!" << endl;

      cout << setprecision(20);
      cout << FileName << " Central " << iEvent;
      for(int i = 0; i < (int)Integral.size(); i++)
         cout << " " << Integral[i];
      cout << endl;
      cout << FileName << " LeptonUp " << iEvent;
      for(int i = 0; i < (int)IntegralUp.size(); i++)
         cout << " " << IntegralUp[i];
      cout << endl;
      cout << FileName << " LeptonDown " << iEvent;
      for(int i = 0; i < (int)IntegralDown.size(); i++)
         cout << " " << IntegralDown[i];
      cout << endl;
      cout << FileName << " LeptonWide " << iEvent;
      for(int i = 0; i < (int)IntegralWide.size(); i++)
         cout << " " << IntegralWide[i];
      cout << endl;
      cout << FileName << " LeptonNarrow " << iEvent;
      for(int i = 0; i < (int)IntegralNarrow.size(); i++)
         cout << " " << IntegralNarrow[i];
      cout << endl;
   }

   // Cleanup
   File.Close();

   return 0;
}

bool CheckIfGood(vector<double> Single)
{
   for(int i = 0; i < (int)Single.size(); i++)
      if(Single[i] != Single[i])
         return false;
   return true;
}

void AddToVector(vector<double> &Total, vector<double> Single, double Weight)
{
   if(Single.size() > Total.size())
      Total.resize(Single.size());

   for(int i = 0; i < (int)Single.size(); i++)
      Total[i] = Total[i] + Single[i] * Weight;
}

void PrintResult(string Identifier, vector<double> Total, int Count)
{
   cout << Identifier << " " << Count;
   for(int i = 0; i < (int)Total.size(); i++)
      cout << setprecision(20) << " " << Total[i] / Count;
   cout << endl;
}

bool PassBaselineCut(EventParameters &Event)
{
   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

   if(fabs(Leptons.Lepton11.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.4)   return false;

   if(Event.ZMass < 40)    return false;
   if(Event.Z2Mass < 12)   return false;

   vector<double> LPTs;
   LPTs.push_back(Leptons.Lepton11.GetPT());
   LPTs.push_back(Leptons.Lepton12.GetPT());
   LPTs.push_back(Leptons.Lepton21.GetPT());
   LPTs.push_back(Leptons.Lepton22.GetPT());
   sort(LPTs.begin(), LPTs.end());
   if(LPTs[3] < 20)   return false;
   if(LPTs[2] < 10)   return false;
   if(LPTs[1] < 7)    return false;
   if(LPTs[0] < 7)    return false;

   if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton21).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton12 + Leptons.Lepton21).GetMass() < 4)   return false;
   if((Leptons.Lepton12 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   return true;
}













