#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TROOT.h"
#include "TCanvas.h"

#include "Code/DrawRandom.h"
#include "DataHelper.h"
#include "PlotHelper2.h"

#include "AngleConversion.h"

#include "ProjectionHelper.h"

struct FitResultSummary;
class FitClass;
int main(int argc, char *argv[]);
bool PassBaselineCut(EventParameters Event);

#define PI 3.14159265358979323846264338327950288479716939937510

struct FitResultSummary
{
public:
   double A2A1, A2A1Error;
   double A2Phase, A2PhaseError;
   double A3A1, A3A1Error;
   double A3Phase, A3PhaseError;
   double F, FError;
   double N1, N1Error;
   double N2, N2Error;
   double EDM;
   int FitStatus;
};

class FitClass
{
public:
   int SampleSize;
   vector<double> V[16][5];   // Background = 0, Signal = 1-15; second index = CUDWN
   vector<double> I[16][5];   // same as above
   vector<EventParameters> E;
   vector<string> S;
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihoodAll(const double *Parameters) const;

   void AddPoint(double v[16][5], double I[16][5], EventParameters &Event, string State);
   void ClearPoints();

   FitResultSummary DoFit();

   void PlotResult(PsFileHelper &PsFile, FitResultSummary Result);
};

int main(int argc, char *argv[])
{
   string FileName =  "EventF.root";
   int DatasetSize = 30;

   if(argc <= 2)
   {
      cerr << "Usage: " << argv[0] << " RootFile DatasetSize" << endl;
      return -1;
   }

   FileName = argv[1];
   DatasetSize = atoi(argv[2]);

   DataHelper DHFile("Normalization.dh");

   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("MCTree");

   int l1id, l3id;
   Tree->SetBranchAddress("l1id", &l1id);
   Tree->SetBranchAddress("l3id", &l3id);

   string SignalBranch[] = {"T26", "T3", "T5", "T7", "T9"};
   string BackgroundBranch[] = {"T2", "T4", "T6", "T8", "T10"};

   double Value[16][5] = {{0}};
   double Integral[16][5] = {{0}};

   string suffix[15] = {"A1RA1R", "A2RA2R", "A2IA2I", "A3RA3R", "A3IA3I",
      "A1RA2R", "A1RA2I", "A1RA3R", "A1RA3I", "A2RA2I",
      "A2RA3R", "A2RA3I", "A2IA3R", "A2IA3I", "A3RA3I"};
   vector<string> Suffix(suffix, suffix + 15);

   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B1_%s", Suffix[i].c_str()), &Value[i+1][0]);
   Tree->SetBranchAddress("B2", &Value[0][0]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B3_%s", Suffix[i].c_str()), &Value[i+1][1]);
   Tree->SetBranchAddress("B4", &Value[0][1]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B5_%s", Suffix[i].c_str()), &Value[i+1][2]);
   Tree->SetBranchAddress("B6", &Value[0][2]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B7_%s", Suffix[i].c_str()), &Value[i+1][3]);
   Tree->SetBranchAddress("B8", &Value[0][3]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B9_%s", Suffix[i].c_str()), &Value[i+1][4]);
   Tree->SetBranchAddress("B10", &Value[0][4]);

   float Weight;
   Tree->SetBranchAddress("weight", &Weight);

   float l1pt, l1eta, l1phi, l2pt, l2eta, l2phi;
   float l3pt, l3eta, l3phi, l4pt, l4eta, l4phi;
   Tree->SetBranchAddress("l1pt", &l1pt);
   Tree->SetBranchAddress("l1eta", &l1eta);
   Tree->SetBranchAddress("l1phi", &l1phi);
   Tree->SetBranchAddress("l2pt", &l2pt);
   Tree->SetBranchAddress("l2eta", &l2eta);
   Tree->SetBranchAddress("l2phi", &l2phi);
   Tree->SetBranchAddress("l3pt", &l3pt);
   Tree->SetBranchAddress("l3eta", &l3eta);
   Tree->SetBranchAddress("l3phi", &l3phi);
   Tree->SetBranchAddress("l4pt", &l4pt);
   Tree->SetBranchAddress("l4eta", &l4eta);
   Tree->SetBranchAddress("l4phi", &l4phi);

   FitClass Fits;
   int FitCount = 0;

   vector<FitResultSummary> Results;

   PsFileHelper PsFile("FitResult.ps");

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      if(DrawRandom(0, 1) > Weight)   // killed by efficiency
         continue;

      if(PassBaselineCut(Event) == false)
         continue;

      for(int j = 0; j < 5; j++)
      {
         Value[10][j] = 0;
         Value[15][j] = 0;
      }

      if(l1id < 0)   l1id = -l1id;
      if(l3id < 0)   l3id = -l3id;

      string State = "";
      // if(l1id == 11 && l3id == 11)   State = "ee";
      if(l1id == 11 && l3id == 13)   State = "em";
      if(l1id == 13 && l3id == 11)   State = "me";
      // if(l1id == 13 && l3id == 13)   State = "mm";

      if(State == "")   // WTF
         continue;
      else
      {
         for(int j = 0; j < 5; j++)
         {
            Integral[0][j] = DHFile[State][BackgroundBranch[j]].GetDouble();
            for(int i = 1; i < 16; i++)
            {
               char BranchSuffix[2] = "A";
               BranchSuffix[0] = char('A' + (i - 1));
               string Branch = SignalBranch[j] + BranchSuffix;
               Integral[i][j] = DHFile[State][Branch].GetDouble();

               if(i == 10 || i == 15)
                  Integral[i][j] = 0;
            }
         }
      }

      if(State == "em" || State == "me")   // bug fix of A2 cross terms!
      {
         for(int j = 0; j < 5; j++)
         {
            if(Integral[6][j] > 0)
            {
               Integral[6][j] = -Integral[6][j];
               Integral[7][j] = -Integral[7][j];
               Integral[11][j] = -Integral[11][j];
               Integral[12][j] = -Integral[12][j];
               Integral[13][j] = -Integral[13][j];
               Integral[14][j] = -Integral[14][j];
            }
         }
      }

      bool Good = true;
      for(int i = 0; i < 16; i++)
         for(int j = 0; j < 5; j++)
            if(Value[i][j] > 0.99 || (i <= 5 && Value[i][j] < 1e-35))
               Good = false;
      if(Good == false)
         continue;

      Fits.AddPoint(Value, Integral, Event, State);

      if(Fits.SampleSize < DatasetSize)
         continue;

      FitResultSummary ResultTemp = Fits.DoFit();
      Results.push_back(ResultTemp);
      FitCount = FitCount + 1;

      FitResultSummary RealResult;
      RealResult.A3A1 = sqrt(200);
      RealResult.A3Phase = PI / 4;
      RealResult.A2A1 = 6;
      RealResult.A2Phase = PI / 2;
      // RealResult.A3A1 = 0.99771079440301369;
      // RealResult.A3Phase = -0.14103275058429116;
      // RealResult.A2A1 = 1.0848176198295649;
      // RealResult.A2Phase = -0.14666649379719301;

      if(FitCount == 1)
      {
         PsFile.AddTextPage("Compared to fit result");
         Fits.PlotResult(PsFile, ResultTemp);
         PsFile.AddTextPage("Compared to truth");
         Fits.PlotResult(PsFile, RealResult);
      }

      Fits.ClearPoints();
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   File.Close();

   TFile OutputFile("OutputFile.root", "RECREATE");

   TNtuple OutputTree("ResultTree", "", "A2A1:A2Phase:A3A1:A3Phase:N1:N2:F:A2A1Error:A2PhaseError:A3A1Error:A3PhaseError:N1Error:N2Error:FError:EDM:Status");

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[100];
      Array[0] = Results[i].A2A1;      Array[7] = Results[i].A2A1Error;
      Array[1] = Results[i].A2Phase;   Array[8] = Results[i].A2PhaseError;
      Array[2] = Results[i].A3A1;      Array[9] = Results[i].A3A1Error;
      Array[3] = Results[i].A3Phase;   Array[10] = Results[i].A3PhaseError;
      Array[4] = Results[i].N1;        Array[11] = Results[i].N1Error;
      Array[5] = Results[i].N2;        Array[12] = Results[i].N2Error;
      Array[6] = Results[i].F;         Array[13] = Results[i].FError;

      Array[14] = Results[i].EDM;
      Array[15] = Results[i].FitStatus;
      
      OutputTree.Fill(Array);
   }

   OutputTree.SetAlias("A3Phase1", "(A3Phase+(A3A1<0)*3.1415926535)");
   OutputTree.SetAlias("A3Phase2", "(A3Phase1-int(A3Phase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A3PrimaryPhase", "(A3Phase2+(A3Phase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A2Phase1", "(A2Phase+(A2A1<0)*3.1415926535)");
   OutputTree.SetAlias("A2Phase2", "(A2Phase1-int(A2Phase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A2PrimaryPhase", "(A2Phase2+(A2Phase2<0)*2*3.1415926535)");

   OutputTree.SetAlias("A", "sqrt(A2A1*A2A1+A3A1*A3A1+1)");
   OutputTree.SetAlias("A1A", "1/sqrt(A2A1*A2A1+A3A1*A3A1+1)");
   OutputTree.SetAlias("A2A", "abs(A2A1)/sqrt(A2A1*A2A1+A3A1*A3A1+1)");
   OutputTree.SetAlias("A3A", "abs(A3A1)/sqrt(A2A1*A2A1+A3A1*A3A1+1)");
   OutputTree.SetAlias("As", "sqrt(A2A1*A2A1/3.125/3.125+A3A1*A3A1/5/5+1)");
   OutputTree.SetAlias("A1sAs", "1/sqrt(A2A1*A2A1/3.125/3.125+A3A1*A3A1/5/5+1)");
   OutputTree.SetAlias("A2sAs", "abs(A2A1/3.125)/sqrt(A2A1*A2A1/3.125/3.125+A3A1*A3A1/5/5+1)");
   OutputTree.SetAlias("A3sAs", "abs(A3A1/5)/sqrt(A2A1*A2A1/3.125/3.125+A3A1*A3A1/5/5+1)");

   OutputTree.SetMarkerStyle(20);

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   double A1R = 1;
   double A3R = Parameters[0] * cos(Parameters[1]);
   double A3I = Parameters[0] * sin(Parameters[1]);
   double A2R = Parameters[2] * cos(Parameters[3]);
   double A2I = Parameters[2] * sin(Parameters[3]);
   double F = Parameters[4];
   double N1 = Parameters[5];
   double N2 = Parameters[6];

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double Value[5] = {0}, Integral[5] = {0}, Likelihood[5] = {0};
      double LikelihoodB[5] = {0};

      for(int i = 0; i < 5; i++)
      {
         Value[i] = A1R * A1R * V[1][i][iS] + A2R * A2R * V[2][i][iS] + A2I * A2I * V[3][i][iS]
            + A3R * A3R * V[4][i][iS] + A3I * A3I * V[5][i][iS]
            + A1R * A2R * V[6][i][iS] + A1R * A2I * V[7][i][iS] + A1R * A3R * V[8][i][iS]
            + A1R * A3I * V[9][i][iS] + A2R * A2I * V[10][i][iS]
            + A2R * A3R * V[11][i][iS] + A2R * A3I * V[12][i][iS] + A2I * A3R * V[13][i][iS]
            + A2I * A3I * V[14][i][iS] + A3R * A3I * V[15][i][iS];
         Integral[i] = A1R * A1R * I[1][i][iS] + A2R * A2R * I[2][i][iS] + A2I * A2I * I[3][i][iS]
            + A3R * A3R * I[4][i][iS] + A3I * A3I * I[5][i][iS]
            + A1R * A2R * I[6][i][iS] + A1R * A2I * I[7][i][iS] + A1R * A3R * I[8][i][iS]
            + A1R * A3I * I[9][i][iS] + A2R * A2I * I[10][i][iS]
            + A2R * A3R * I[11][i][iS] + A2R * A3I * I[12][i][iS] + A2I * A3R * I[13][i][iS]
            + A2I * A3I * I[14][i][iS] + A3R * A3I * I[15][i][iS];
         Likelihood[i] = Value[i] / Integral[i];

         LikelihoodB[i] = V[0][i][iS] / I[0][i][iS];
      }

      bool Good = true;
      for(int i = 0; i < 5; i++)
         if(Likelihood[i] < 0)
            Good = false;
      if(Good == false)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }
      double LSa = Likelihood[0];
      double LSb1 = (N1 > 0) ? (Likelihood[1] - Likelihood[0]) : (Likelihood[0] - Likelihood[2]);
      double LSb2 = (N2 > 0) ? (Likelihood[3] - Likelihood[0]) : (Likelihood[0] - Likelihood[4]);
      double LBa = LikelihoodB[0];
      double LBb1 = (N1 > 0) ? (LikelihoodB[1] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[2]);
      double LBb2 = (N2 > 0) ? (LikelihoodB[3] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[4]);

      double SignalLikelihood = LSa + LSb1 * N1 + LSb2 * N2;
      double BackgroundLikelihood = LBa + LBb1 * N1 + LBb2 * N2;

      if(SignalLikelihood <= 0 || BackgroundLikelihood <= 0)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      LogTotal = LogTotal + log(SignalLikelihood * (1 - F) + BackgroundLikelihood * F) - N1 * N1 / 2 - N2 * N2 / 2;
   }

   return -LogTotal;
}

void FitClass::AddPoint(double v[16][5], double i[16][5], EventParameters &Event, string State)
{
   for(int i1 = 0; i1 < 16; i1++)
   {
      for(int i2 = 0; i2 < 5; i2++)
      {
         V[i1][i2].push_back(v[i1][i2]);
         I[i1][i2].push_back(i[i1][i2]);
      }
   }

   E.push_back(Event);
   S.push_back(State);

   SampleSize = SampleSize + 1;
}

void FitClass::ClearPoints()
{
   for(int i1 = 0; i1 < 16; i1++)
   {
      for(int i2 = 0; i2 < 5; i2++)
      {
         V[i1][i2].clear();
         I[i1][i2].clear();
      }
   }

   E.clear();
   S.clear();

   SampleSize = 0;
}

FitResultSummary FitClass::DoFit()
{
   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");

   Worker->SetPrintLevel(1);
   Worker->SetMaxFunctionCalls(1000000);
   Worker->SetMaxIterations(100000);
   Worker->SetTolerance(1e-3);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 7);
   Worker->SetFunction(Function);

   Worker->SetLimitedVariable(0, "A3A1", 1.02, 0.5, -100, 100);
   Worker->SetLimitedVariable(1, "A3Phase", -0.1, 0.1, -PI * 10, PI * 10);
   Worker->SetLimitedVariable(2, "A2A1", 1.1, 0.5, -100, 100);
   Worker->SetLimitedVariable(3, "A2Phase", -0.1, 0.1, -PI * 10, PI * 10);
   Worker->SetLimitedVariable(4, "F", 0, 0, 0, 1);
   Worker->SetLimitedVariable(5, "N1", 0, 0, -1, 1);
   Worker->SetLimitedVariable(6, "N2", 0, 0, -1, 1);
   
   Worker->Minimize();

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.A3A1 = Parameters[0];
   Result.A3A1Error = Errors[0];
   Result.A3Phase = Parameters[1];
   Result.A3PhaseError = Errors[1];
   Result.A2A1 = Parameters[2];
   
   Result.A2Phase = Parameters[3];
   Result.A2PhaseError = Errors[3];
   Result.F = Parameters[4];
   Result.FError = Errors[4];
   Result.N1 = Parameters[5];
   Result.N1Error = Errors[5];
   Result.N2 = Parameters[6];
   Result.N2Error = Errors[6];
   Result.EDM = Worker->Edm();
   Result.FitStatus = Worker->CovMatrixStatus();

   delete Worker;

   return Result;
}

void FitClass::PlotResult(PsFileHelper &PsFile, FitResultSummary Result)
{
   TFile File("ProjectionTree.root");
   TTree *Tree = (TTree *)File.Get("Tree");

   GeneralScalarParameters Parameters;
   Parameters.ahR = 1;                                     Parameters.ahI = 0;
   Parameters.aZR = Result.A2A1 * cos(Result.A2Phase);     Parameters.aZI = Result.A2A1 * sin(Result.A2Phase);
   Parameters.aZdR = Result.A3A1 * cos(Result.A3Phase);    Parameters.aZdI = Result.A3A1 * sin(Result.A3Phase);

   ProjectionHelper Projection(Tree);

   TH1D HHMass("HHMass", "Projection of HMass", 40, 115, 135);
   TH1D HZMass("HZMass", "Projection of ZMass", 40, 40, 120);
   TH1D HZ2Mass("HZ2Mass", "Projection of Z2Mass", 40, 12, 80);
   TH1D HPhi0("HPhi0", "Projection of Phi0", 25, -PI, PI);
   TH1D HCosTheta0("HCosTheta0", "Projection of CosTheta0", 25, -1, 1);
   TH1D HPhi("HPhi", "Projection of Phi", 20, -PI, PI);
   TH1D HCosTheta1("HCosTheta1", "Projection of CosTheta1", 25, -1, 1);
   TH1D HCosTheta2("HCosTheta2", "Projection of CosTheta2", 25, -1, 1);

   int EMCount = 0, MECount = 0, EECount = 0, MMCount = 0;

   for(int i = 0; i < (int)E.size(); i++)
   {
      if(E[i].Phi0 > PI)   E[i].Phi0 = E[i].Phi0 - 2 * PI;
      if(E[i].Phi > PI)    E[i].Phi = E[i].Phi - 2 * PI;

      HHMass.Fill(E[i].HMass);
      HZMass.Fill(E[i].ZMass);
      HZ2Mass.Fill(E[i].Z2Mass);
      HPhi0.Fill(E[i].Phi0);
      HCosTheta0.Fill(cos(E[i].Theta0));
      HPhi.Fill(E[i].Phi);
      HCosTheta1.Fill(cos(E[i].Theta1));
      HCosTheta2.Fill(cos(E[i].Theta2));

      if(S[i] == "ee")   EECount = EECount + 1;
      if(S[i] == "em")   EMCount = EMCount + 1;
      if(S[i] == "me")   MECount = MECount + 1;
      if(S[i] == "mm")   MMCount = MMCount + 1;
   }
   
   TH1D HPDFHMass("HPDFHMass", "Projection of HMass", 60, 115, 135);
   TH1D HPDFZMass("HPDFZMass", "Projection of ZMass", 60, 40, 120);
   TH1D HPDFZ2Mass("HPDFZ2Mass", "Projection of Z2Mass", 60, 12, 80);
   TH1D HPDFPhi0("HPDFPhi0", "Projection of Phi0", 40, -PI, PI);
   TH1D HPDFCosTheta0("HPDFCosTheta0", "Projection of CosTheta0", 40, -1, 1);
   TH1D HPDFPhi("HPDFPhi", "Projection of Phi", 30, -PI, PI);
   TH1D HPDFCosTheta1("HPDFCosTheta1", "Projection of CosTheta1", 40, -1, 1);
   TH1D HPDFCosTheta2("HPDFCosTheta2", "Projection of CosTheta2", 40, -1, 1);

   Projection.FillProjection(HPDFHMass, ProjectionHelper::DimensionMH, HHMass.Integral() * (135 - 115) / 40,
      Parameters, EECount, MMCount, EMCount, MECount);
   Projection.FillProjection(HPDFZMass, ProjectionHelper::DimensionM1, HZMass.Integral() * (120 - 40) / 40,
      Parameters, EECount, MMCount, EMCount, MECount);
   Projection.FillProjection(HPDFZ2Mass, ProjectionHelper::DimensionM2, HZ2Mass.Integral() * (80 - 12) / 40,
      Parameters, EECount, MMCount, EMCount, MECount);
   Projection.FillProjection(HPDFPhi0, ProjectionHelper::DimensionPhi0, HPhi0.Integral() * (2 * PI) / 25,
      Parameters, EECount, MMCount, EMCount, MECount);
   Projection.FillProjection(HPDFCosTheta0, ProjectionHelper::DimensionCosTheta0, HCosTheta0.Integral() * 2 / 25,
      Parameters, EECount, MMCount, EMCount, MECount);
   Projection.FillProjection(HPDFPhi, ProjectionHelper::DimensionPhi, HPhi.Integral() * (2 * PI) / 20,
      Parameters, EECount, MMCount, EMCount, MECount);
   Projection.FillProjection(HPDFCosTheta1, ProjectionHelper::DimensionCosTheta1, HCosTheta1.Integral() * 2 / 25,
      Parameters, EECount, MMCount, EMCount, MECount);
   Projection.FillProjection(HPDFCosTheta2, ProjectionHelper::DimensionCosTheta2, HCosTheta2.Integral() * 2 / 25,
      Parameters, EECount, MMCount, EMCount, MECount);

   HHMass.SetStats(0);
   HZMass.SetStats(0);
   HZ2Mass.SetStats(0);
   HPhi0.SetStats(0);
   HCosTheta0.SetStats(0);
   HPhi.SetStats(0);
   HCosTheta1.SetStats(0);
   HCosTheta2.SetStats(0);
   
   HHMass.SetMinimum(0);
   HZMass.SetMinimum(0);
   HZ2Mass.SetMinimum(0);
   HPhi0.SetMinimum(0);
   HCosTheta0.SetMinimum(0);
   HPhi.SetMinimum(0);
   HCosTheta1.SetMinimum(0);
   HCosTheta2.SetMinimum(0);
   
   HHMass.SetMarkerStyle(20);
   HZMass.SetMarkerStyle(20);
   HZ2Mass.SetMarkerStyle(20);
   HPhi0.SetMarkerStyle(20);
   HCosTheta0.SetMarkerStyle(20);
   HPhi.SetMarkerStyle(20);
   HCosTheta1.SetMarkerStyle(20);
   HCosTheta2.SetMarkerStyle(20);
   
   HHMass.SetLineWidth(2);
   HZMass.SetLineWidth(2);
   HZ2Mass.SetLineWidth(2);
   HPhi0.SetLineWidth(2);
   HCosTheta0.SetLineWidth(2);
   HPhi.SetLineWidth(2);
   HCosTheta1.SetLineWidth(2);
   HCosTheta2.SetLineWidth(2);

   HPDFHMass.SetLineWidth(2);
   HPDFZMass.SetLineWidth(2);
   HPDFZ2Mass.SetLineWidth(2);
   HPDFPhi0.SetLineWidth(2);
   HPDFCosTheta0.SetLineWidth(2);
   HPDFPhi.SetLineWidth(2);
   HPDFCosTheta1.SetLineWidth(2);
   HPDFCosTheta2.SetLineWidth(2);

   TCanvas C;

   HHMass.Draw("error");
   HPDFHMass.Draw("same");
   PsFile.AddCanvas(C);

   HZMass.Draw("error");
   HPDFZMass.Draw("same");
   PsFile.AddCanvas(C);

   HZ2Mass.Draw("error");
   HPDFZ2Mass.Draw("same");
   PsFile.AddCanvas(C);

   HPhi0.Draw("error");
   HPDFPhi0.Draw("same");
   PsFile.AddCanvas(C);

   HCosTheta0.Draw("error");
   HPDFCosTheta0.Draw("same");
   PsFile.AddCanvas(C);

   HPhi.Draw("error");
   HPDFPhi.Draw("same");
   PsFile.AddCanvas(C);

   HCosTheta1.Draw("error");
   HPDFCosTheta1.Draw("same");
   PsFile.AddCanvas(C);

   HCosTheta2.Draw("error");
   HPDFCosTheta2.Draw("same");
   PsFile.AddCanvas(C);

   File.Close();
}

bool PassBaselineCut(EventParameters Event)
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



