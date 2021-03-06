#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TProfile.h"

#include "Cuts.h"
#include "AngleConversion.h"

#include "ProgressBar.h"
#include "SetStyle.h"
#include "Code/DrawRandom.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main();
void ExportPlots(TH1D &H1, TH1D &H2, string FileBase);

int main()
{
   SetThesisStyle();

   TChain TreeToy("Tree", "Tree");
   for(int i = 10000; i < 10050; i++)
      TreeToy.AddFile(Form("Toys/Meow_%d.root", i));

   TFile FileMG("MG.root");
   TTree *TreeMG = (TTree *)FileMG.Get("Tree");

   TH1D HMHToy("HMHToy", "MH Toy;MH;", 100, 115, 135);                                 HMHToy.Sumw2();
   TH1D HMHMG("HMHMG", "MH MG;MH;", 100, 115, 135);                                    HMHMG.Sumw2();
   TH1D HM1Toy("HM1Toy", "M1 Toy;M1;", 100, 30, 120);                                  HM1Toy.Sumw2();
   TH1D HM1MG("HM1MG", "M1 MG;M1;", 100, 30, 120);                                     HM1MG.Sumw2();
   TH1D HM2Toy("HM2Toy", "M2 Toy;M2;", 100, 12, 90);                                   HM2Toy.Sumw2();
   TH1D HM2MG("HM2MG", "M2 MG;M2;", 100, 12, 90);                                      HM2MG.Sumw2();
   TH1D HCosTheta0Toy("HCosTheta0Toy", "CosTheta0 Toy;CosTheta0;", 100, -1, 1);        HCosTheta0Toy.Sumw2();
   TH1D HCosTheta0MG("HCosTheta0MG", "CosTheta0 MG;CosTheta0;", 100, -1, 1);           HCosTheta0MG.Sumw2();
   TH1D HPhi0Toy("HPhi0Toy", "Phi0 Toy;Phi0;", 100,  0, 2 * PI);                       HPhi0Toy.Sumw2();
   TH1D HPhi0MG("HPhi0MG", "Phi0 MG;Phi0;", 100,  0, 2 * PI);                          HPhi0MG.Sumw2();
   TH1D HCosTheta1Toy("HCosTheta1Toy", "CosTheta1 Toy;CosTheta1;", 100, -1, 1);        HCosTheta1Toy.Sumw2();
   TH1D HCosTheta1MG("HCosTheta1MG", "CosTheta1 MG;CosTheta1;", 100, -1, 1);           HCosTheta1MG.Sumw2();
   TH1D HCosTheta2Toy("HCosTheta2Toy", "CosTheta2 Toy;CosTheta2;", 100, -1, 1);        HCosTheta2Toy.Sumw2();
   TH1D HCosTheta2MG("HCosTheta2MG", "CosTheta2 MG;CosTheta2;", 100, -1, 1);           HCosTheta2MG.Sumw2();
   TH1D HPhiToy("HPhiToy", "Phi Toy;Phi;", 100,  0, 2 * PI);                           HPhiToy.Sumw2();
   TH1D HPhiMG("HPhiMG", "Phi MG;Phi;", 100,  0, 2 * PI);                              HPhiMG.Sumw2();
   TH1D HYHToy("HYHToy", "YH Toy;YH;", 100, -5, 5);                                    HYHToy.Sumw2();
   TH1D HYHMG("HYHMG", "YH MG;YH;", 100, -5, 5);                                       HYHMG.Sumw2();

   TProfile PM1MHToy("PM1MHToy", "M1 profile;MH;M1", 100, 115, 135);
   TProfile PM1MHMG("PM1MHMG", "M1 profile;MH;M1", 100, 115, 135);

   PM1MHToy.SetStats(0);
   PM1MHMG.SetStats(0);

   LeptonVectors LeptonToy;
   TreeToy.SetBranchAddress("L1PT",  &LeptonToy.Lepton11[1]);
   TreeToy.SetBranchAddress("L1Eta", &LeptonToy.Lepton11[2]);
   TreeToy.SetBranchAddress("L1Phi", &LeptonToy.Lepton11[3]);
   TreeToy.SetBranchAddress("L2PT",  &LeptonToy.Lepton12[1]);
   TreeToy.SetBranchAddress("L2Eta", &LeptonToy.Lepton12[2]);
   TreeToy.SetBranchAddress("L2Phi", &LeptonToy.Lepton12[3]);
   TreeToy.SetBranchAddress("L3PT",  &LeptonToy.Lepton21[1]);
   TreeToy.SetBranchAddress("L3Eta", &LeptonToy.Lepton21[2]);
   TreeToy.SetBranchAddress("L3Phi", &LeptonToy.Lepton21[3]);
   TreeToy.SetBranchAddress("L4PT",  &LeptonToy.Lepton22[1]);
   TreeToy.SetBranchAddress("L4Eta", &LeptonToy.Lepton22[2]);
   TreeToy.SetBranchAddress("L4Phi", &LeptonToy.Lepton22[3]);
   double Weight;
   TreeToy.SetBranchAddress("W", &Weight);
   double A1ZZA1ZZ;
   TreeToy.SetBranchAddress("B1_A1ZZR_A1ZZR", &A1ZZA1ZZ);

   double MaxWeight = 0;

   int EntryToy = TreeToy.GetEntries();
   ProgressBar BarToy(cout, EntryToy);
   for(int iE = 0; iE < EntryToy; iE++)
   {
      if((iE % (EntryToy / 500)) == 0)
      {
         BarToy.Update(iE);
         BarToy.Print();
      }
      
      TreeToy.GetEntry(iE);

      if(Weight != Weight)
         continue;
      if(A1ZZA1ZZ != A1ZZA1ZZ)
         continue;

      if(Weight > MaxWeight)
         MaxWeight = Weight;
      if(A1ZZA1ZZ > 0.1)
         continue;

      LeptonToy.Lepton11.SetPtEtaPhi(LeptonToy.Lepton11[1], LeptonToy.Lepton11[2], LeptonToy.Lepton11[3]);
      LeptonToy.Lepton12.SetPtEtaPhi(LeptonToy.Lepton12[1], LeptonToy.Lepton12[2], LeptonToy.Lepton12[3]);
      LeptonToy.Lepton21.SetPtEtaPhi(LeptonToy.Lepton21[1], LeptonToy.Lepton21[2], LeptonToy.Lepton21[3]);
      LeptonToy.Lepton22.SetPtEtaPhi(LeptonToy.Lepton22[1], LeptonToy.Lepton22[2], LeptonToy.Lepton22[3]);

      LeptonToy = LeptonToy.ReorderLeptons2e2mu();

      EventParameters Event = ConvertVectorsToAnglesRoberto(LeptonToy);

      vector<bool> PassCuts = PassPairingCuts(LeptonToy);

      HMHToy.Fill(Event.HMass, Weight * A1ZZA1ZZ * PassCuts[0]);
      HM1Toy.Fill(Event.ZMass, Weight * A1ZZA1ZZ * PassCuts[0]);
      HM2Toy.Fill(Event.Z2Mass, Weight * A1ZZA1ZZ * PassCuts[0]);
      HCosTheta0Toy.Fill(cos(Event.Theta0), Weight * A1ZZA1ZZ * PassCuts[0]);
      HPhi0Toy.Fill(Event.Phi0, Weight * A1ZZA1ZZ * PassCuts[0]);
      HCosTheta1Toy.Fill(cos(Event.Theta1), Weight * A1ZZA1ZZ * PassCuts[0]);
      HCosTheta2Toy.Fill(cos(Event.Theta2), Weight * A1ZZA1ZZ * PassCuts[0]);
      HPhiToy.Fill(Event.Phi, Weight * A1ZZA1ZZ * PassCuts[0]);
      HYHToy.Fill(Event.YH, Weight * A1ZZA1ZZ * PassCuts[0]);

      PM1MHToy.Fill(Event.HMass, Event.ZMass, Weight * A1ZZA1ZZ * PassCuts[0]);
   }
   BarToy.Update(EntryToy);
   BarToy.Print();
   BarToy.PrintLine();

   cout << MaxWeight << endl;

   LeptonVectors LeptonMG;
   double L1PT, L1Phi, L1Eta;
   double L2PT, L2Phi, L2Eta;
   double L3PT, L3Phi, L3Eta;
   double L4PT, L4Phi, L4Eta;
   TreeMG->SetBranchAddress("L1PT", &L1PT);
   TreeMG->SetBranchAddress("L1Eta", &L1Eta);
   TreeMG->SetBranchAddress("L1Phi", &L1Phi);
   TreeMG->SetBranchAddress("L2PT", &L2PT);
   TreeMG->SetBranchAddress("L2Eta", &L2Eta);
   TreeMG->SetBranchAddress("L2Phi", &L2Phi);
   TreeMG->SetBranchAddress("L3PT", &L3PT);
   TreeMG->SetBranchAddress("L3Eta", &L3Eta);
   TreeMG->SetBranchAddress("L3Phi", &L3Phi);
   TreeMG->SetBranchAddress("L4PT", &L4PT);
   TreeMG->SetBranchAddress("L4Eta", &L4Eta);
   TreeMG->SetBranchAddress("L4Phi", &L4Phi);

   int EntryMG = TreeMG->GetEntries();
   ProgressBar BarMG(cout, EntryMG);
   for(int iE = 0; iE < EntryMG; iE++)
   {
      if((iE % (EntryMG / 500)) == 0)
      {
         BarMG.Update(iE);
         BarMG.Print();
      }

      TreeMG->GetEntry(iE);

      LeptonMG.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      LeptonMG.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      LeptonMG.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
      LeptonMG.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

      LeptonMG = LeptonMG.ReorderLeptons2e2mu();

      double M4l = DrawGaussian(125, 2);
      LeptonMG.Lepton11 = LeptonMG.Lepton11 * M4l / 125;
      LeptonMG.Lepton12 = LeptonMG.Lepton12 * M4l / 125;
      LeptonMG.Lepton21 = LeptonMG.Lepton21 * M4l / 125;
      LeptonMG.Lepton22 = LeptonMG.Lepton22 * M4l / 125;

      EventParameters Event = ConvertVectorsToAnglesRoberto(LeptonMG);

      vector<bool> PassCuts = PassPairingCuts(LeptonMG);

      HMHMG.Fill(Event.HMass, PassCuts[0]);
      HM1MG.Fill(Event.ZMass, PassCuts[0]);
      HM2MG.Fill(Event.Z2Mass, PassCuts[0]);
      HCosTheta0MG.Fill(cos(Event.Theta0), PassCuts[0]);
      HPhi0MG.Fill(Event.Phi0, PassCuts[0]);
      HCosTheta1MG.Fill(cos(Event.Theta1), PassCuts[0]);
      HCosTheta2MG.Fill(cos(Event.Theta2), PassCuts[0]);
      HPhiMG.Fill(Event.Phi, PassCuts[0]);
      HYHMG.Fill(Event.YH, PassCuts[0]);

      PM1MHMG.Fill(Event.HMass, Event.ZMass, Weight * A1ZZA1ZZ * PassCuts[0]);
   }
   BarMG.Update(EntryMG);
   BarMG.Print();
   BarMG.PrintLine();

   ExportPlots(HMHToy, HMHMG, "MH");
   ExportPlots(HM1Toy, HM1MG, "M1");
   ExportPlots(HM2Toy, HM2MG, "M2");
   ExportPlots(HCosTheta0Toy, HCosTheta0MG, "CosTheta0");
   ExportPlots(HPhi0Toy, HPhi0MG, "Phi0");
   ExportPlots(HCosTheta1Toy, HCosTheta1MG, "CosTheta1");
   ExportPlots(HCosTheta2Toy, HCosTheta2MG, "CosTheta2");
   ExportPlots(HPhiToy, HPhiMG, "Phi");
   ExportPlots(HYHToy, HYHMG, "YH");

   HMHMG.Divide(&HMHToy);
   TCanvas C;
   HMHMG.SetMaximum(1.1);
   HMHMG.SetMinimum(0.9);
   HMHMG.Draw();
   HMHMG.GetYaxis()->SetTitle("Ratio MG / Toy");
   C.SaveAs("Ratio.png");
   C.SaveAs("Ratio.C");
   C.SaveAs("Ratio.eps");
   C.SaveAs("Ratio.pdf");

   HM1MG.Divide(&HM1Toy);
   HM1MG.SetMaximum(1.1);
   HM1MG.SetMinimum(0.9);
   HM1MG.Draw();
   HM1MG.GetYaxis()->SetTitle("Ratio MG / Toy");
   C.SaveAs("RatioM1.png");
   C.SaveAs("RatioM1.C");
   C.SaveAs("RatioM1.eps");
   C.SaveAs("RatioM1.pdf");

   HM2MG.Divide(&HM2Toy);
   HM2MG.SetMaximum(1.1);
   HM2MG.SetMinimum(0.9);
   HM2MG.Draw();
   HM2MG.GetYaxis()->SetTitle("Ratio MG / Toy");
   C.SaveAs("RatioM2.png");
   C.SaveAs("RatioM2.C");
   C.SaveAs("RatioM2.eps");
   C.SaveAs("RatioM2.pdf");

   PM1MHMG.SetMaximum(100);
   PM1MHMG.SetMinimum(70);
   PM1MHMG.Draw();
   PM1MHToy.SetMarkerColor(kRed);
   PM1MHToy.Draw("same");
   C.SaveAs("M1Profile.png");
   C.SaveAs("M1Profile.C");
   C.SaveAs("M1Profile.eps");
   C.SaveAs("M1Profile.pdf");

   FileMG.Close();

   return 0;
}

void ExportPlots(TH1D &H1, TH1D &H2, string FileBase)
{
   TCanvas C;

   H1.Scale(1 / H1.Integral());
   H2.Scale(1 / H2.Integral());

   H2.SetMinimum(0);

   H1.SetLineWidth(2);
   H1.SetLineColor(kRed);

   H2.SetLineWidth(2);
   H2.SetLineColor(kBlue);

   H1.SetStats(0);
   H2.SetStats(0);

   H1.SetTitle("");
   H2.SetTitle("");

   H2.Draw("hist");
   H1.Draw("error same");

   C.SaveAs((FileBase + ".png").c_str());
   C.SaveAs((FileBase + ".C").c_str());
   C.SaveAs((FileBase + ".pdf").c_str());
   C.SaveAs((FileBase + ".eps").c_str());
}




