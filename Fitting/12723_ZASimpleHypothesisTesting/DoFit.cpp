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
#include "ProgressBar.h"

#include "AngleConversion.h"

#include "FitClass.h"
// #include "ProjectionHelper.h"

int main(int argc, char *argv[]);
bool PassBaselineCutLoose(EventParameters Event);
bool PassBaselineCutTight(EventParameters Event);
void ReadEvents(vector<SingleEvent> &Events, string FileName);

#define PI 3.14159265358979323846264338327950288479716939937510

// #define USE_LOOSE_CUT
#define USE_TIGHT_CUT

int main(int argc, char *argv[])
{
   srand(time(NULL));

   string FileName =  "EventF.root";
   int DatasetSize = 30;
   string BackgroundFileName = "EventF.root";
   int BackgroundDatasetSize = 30;

   if(argc <= 10)
   {
      cerr << "Usage: " << argv[0]
         << " SignalRootFile SignalDatasetSize BackgroundRootFile BackgroundDatasetSize"
         << " A2ZZ A3ZZ A2ZA A3ZA A2AA A3AA"
         << endl;
      return -1;
   }

   FileName = argv[1];
   DatasetSize = atoi(argv[2]);
   BackgroundFileName = argv[3];
   BackgroundDatasetSize = atoi(argv[4]);

   double A2ZZ = atof(argv[5]);
   double A3ZZ = atof(argv[6]);
   double A2ZA = atof(argv[7]);
   double A3ZA = atof(argv[8]);
   double A2AA = atof(argv[9]);
   double A3AA = atof(argv[10]);

   FitClass Fits;
   Fits.ClearPoints();
   int FitCount = 0;

   vector<FitResultSummary> Results;

   // PsFileHelper PsFile("FitResult.ps");

   vector<SingleEvent> Signals, Backgrounds;
   ReadEvents(Signals, FileName);
   if(BackgroundDatasetSize > 0)
      ReadEvents(Backgrounds, BackgroundFileName);
   else
      Backgrounds = Signals;

   int BackgroundCounter = 0;

   ProgressBar Bar(cout, Signals.size());
   Bar.SetStyle(5);

   for(int iS = 0; iS < (int)Signals.size(); iS++)
   {
      if((iS % (Signals.size() / 300)) == 0)
      {
         Bar.Update(iS);
         Bar.Print();
      }

      Fits.AddPoint(Signals[iS]);

      if(Signals[iS].state == "em")   Fits.SignalStateCount[0] = Fits.SignalStateCount[0] + 1;
      if(Signals[iS].state == "me")   Fits.SignalStateCount[1] = Fits.SignalStateCount[1] + 1;
      if(Signals[iS].state == "ee")   Fits.SignalStateCount[2] = Fits.SignalStateCount[2] + 1;
      if(Signals[iS].state == "mm")   Fits.SignalStateCount[3] = Fits.SignalStateCount[3] + 1;
      
      if(Fits.SampleSize < DatasetSize)
         continue;

      while(Fits.SampleSize < DatasetSize + BackgroundDatasetSize)
      {
         Fits.AddPoint(Backgrounds[BackgroundCounter]);

         if(Backgrounds[BackgroundCounter].state == "em")
            Fits.BackgroundStateCount[0] = Fits.BackgroundStateCount[0] + 1;
         if(Backgrounds[BackgroundCounter].state == "me")
            Fits.BackgroundStateCount[1] = Fits.BackgroundStateCount[1] + 1;
         if(Backgrounds[BackgroundCounter].state == "ee")
            Fits.BackgroundStateCount[2] = Fits.BackgroundStateCount[2] + 1;
         if(Backgrounds[BackgroundCounter].state == "mm")
            Fits.BackgroundStateCount[3] = Fits.BackgroundStateCount[3] + 1;

         BackgroundCounter = BackgroundCounter + 1;
         if(BackgroundCounter >= Backgrounds.size())
            BackgroundCounter = 0;
      }

      Fits.I1ZZModificationFactor = 1;

      FitResultSummary ResultTemp;

      ResultTemp.Sem = Fits.SignalStateCount[0];
      ResultTemp.Sme = Fits.SignalStateCount[1];
      ResultTemp.See = Fits.SignalStateCount[2];
      ResultTemp.Smm = Fits.SignalStateCount[3];

      ResultTemp.Bem = Fits.BackgroundStateCount[0];
      ResultTemp.Bme = Fits.BackgroundStateCount[1];
      ResultTemp.Bee = Fits.BackgroundStateCount[2];
      ResultTemp.Bmm = Fits.BackgroundStateCount[3];

      double PlusParameters[] =
         {0, 0, 0, 0,
         0, 0, 0, 0,
         0.004, 0, 0, 0,
         0, 0, 0, 0, 0, 0};
      double ZeroParameters[] =
         {0, 0, 0, 0,
         0, 0, 0, 0,
         0, 0, 0, 0,
         0, 0, 0, 0, 0, 0};
      double MinusParameters[] =
         {0, 0, 0, 0,
         0, 0, 0, 0,
         -0.004, 0, 0, 0,
         0, 0, 0, 0, 0, 0};

      ResultTemp.PlusNLL = Fits.CalculateLogLikelihoodAll(PlusParameters);
      ResultTemp.ZeroNLL = Fits.CalculateLogLikelihoodAll(ZeroParameters);
      ResultTemp.MinusNLL = Fits.CalculateLogLikelihoodAll(MinusParameters);

      Results.push_back(ResultTemp);

      FitCount = FitCount + 1;

      Fits.ClearPoints();
   }

   Bar.Update(Signals.size());
   Bar.Print();
   Bar.PrintLine();

   // PsFile.AddTimeStampPage();
   // PsFile.Close();

   TFile OutputFile("OutputFile.root", "RECREATE");

   string BranchList = "";
   BranchList = BranchList + "Sem:Sme:See:Smm:Bem:Bme:Bee:Bmm:PlusNLL:ZeroNLL:MinusNLL";
   TNtuple OutputTree("ResultTree", "", BranchList.c_str());

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[100];

      Array[0] = Results[i].Sem;         Array[4] = Results[i].Bem;
      Array[1] = Results[i].Sme;         Array[5] = Results[i].Bme;
      Array[2] = Results[i].See;         Array[6] = Results[i].Bee;
      Array[3] = Results[i].Smm;         Array[7] = Results[i].Bmm;

      Array[8] = Results[i].MinusNLL;
      Array[9] = Results[i].ZeroNLL;
      Array[10] = Results[i].PlusNLL;

      OutputTree.Fill(Array);
   }

   OutputTree.SetMarkerStyle(20);

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

bool PassBaselineCutLoose(EventParameters Event)
{
   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

   if(fabs(Leptons.Lepton11.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.4)   return false;

   if(max(Event.ZMass, Event.Z2Mass) < 4)    return false;
   if(min(Event.ZMass, Event.Z2Mass) < 4)   return false;

   if(Event.ZMass < Event.Z2Mass) return false;
   
   vector<double> LPTs;
   LPTs.push_back(Leptons.Lepton11.GetPT());
   LPTs.push_back(Leptons.Lepton12.GetPT());
   LPTs.push_back(Leptons.Lepton21.GetPT());
   LPTs.push_back(Leptons.Lepton22.GetPT());
   sort(LPTs.begin(), LPTs.end());
   if(LPTs[3] < 2)    return false;
   if(LPTs[2] < 2)    return false;
   if(LPTs[1] < 2)    return false;
   if(LPTs[0] < 2)    return false;

   return true;
}

bool PassBaselineCutTight(EventParameters Event)
{
   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);
   double M1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   if(fabs(Leptons.Lepton11.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.4)   return false;

   if(max(M1, M2) < 40)   return false;
   if(min(M1, M2) < 12)   return false;

   vector<double> LPTs;
   LPTs.push_back(Leptons.Lepton11.GetPT());
   LPTs.push_back(Leptons.Lepton12.GetPT());
   LPTs.push_back(Leptons.Lepton21.GetPT());
   LPTs.push_back(Leptons.Lepton22.GetPT());
   sort(LPTs.begin(), LPTs.end());
   if(LPTs[3] < 20)    return false;
   if(LPTs[2] < 10)    return false;
   if(LPTs[1] < 7)    return false;
   if(LPTs[0] < 7)    return false;

   return true;
}

void ReadEvents(vector<SingleEvent> &Events, string FileName)
{
   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("MCTree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("Tree");
   if(Tree == NULL)
      return;

   DataHelper DHFile("Normalization.dh");

   int l1id, l3id;
   Tree->SetBranchAddress("l1id", &l1id);
   Tree->SetBranchAddress("l3id", &l3id);

#ifdef USE_LOOSE_CUT
   string SignalBranch[] = {"t1", "t3", "t5", "t7", "t9"};
   string BackgroundBranch[] = {"t2", "t4", "t6", "t8", "t10"};
#else
   string SignalBranch[] = {"T1", "T3", "T5", "T7", "T9"};
   string BackgroundBranch[] = {"T2", "T4", "T6", "T8", "T10"};
#endif

   double Value[92][5] = {{0}};
   double Integral[92][5] = {{0}};

   string suffix[91] = {
      "A1ZZRA1ZZR",
      "A2ZZRA2ZZR",
      "A2ZZIA2ZZI",
      "A3ZZRA3ZZR",
      "A3ZZIA3ZZI",
      "A2ZARA2ZAR",
      "A2ZAIA2ZAI",
      "A3ZARA3ZAR",
      "A3ZAIA3ZAI",
      "A2AARA2AAR",
      "A2AAIA2AAI",
      "A3AARA3AAR",
      "A3AAIA3AAI",
      "A1ZZRA2ZZR",
      "A1ZZRA2ZZI",
      "A1ZZRA3ZZR",
      "A1ZZRA3ZZI",
      "A1ZZRA2ZAR",
      "A1ZZRA2ZAI",
      "A1ZZRA3ZAR",
      "A1ZZRA3ZAI",
      "A1ZZRA2AAR",
      "A1ZZRA2AAI",
      "A1ZZRA3AAR",
      "A1ZZRA3AAI",
      "A2ZZRA2ZZI",
      "A2ZZRA3ZZR",
      "A2ZZRA3ZZI",
      "A2ZZRA2ZAR",
      "A2ZZRA2ZAI",
      "A2ZZRA3ZAR",
      "A2ZZRA3ZAI",
      "A2ZZRA2AAR",
      "A2ZZRA2AAI",
      "A2ZZRA3AAR",
      "A2ZZRA3AAI",
      "A2ZZIA3ZZR",
      "A2ZZIA3ZZI",
      "A2ZZIA2ZAR",
      "A2ZZIA2ZAI",
      "A2ZZIA3ZAR",
      "A2ZZIA3ZAI",
      "A2ZZIA2AAR",
      "A2ZZIA2AAI",
      "A2ZZIA3AAR",
      "A2ZZIA3AAI",
      "A3ZZRA3ZZI",
      "A3ZZRA2ZAR",
      "A3ZZRA2ZAI",
      "A3ZZRA3ZAR",
      "A3ZZRA3ZAI",
      "A3ZZRA2AAR",
      "A3ZZRA2AAI",
      "A3ZZRA3AAR",
      "A3ZZRA3AAI",
      "A3ZZIA2ZAR",
      "A3ZZIA2ZAI",
      "A3ZZIA3ZAR",
      "A3ZZIA3ZAI",
      "A3ZZIA2AAR",
      "A3ZZIA2AAI",
      "A3ZZIA3AAR",
      "A3ZZIA3AAI",
      "A2ZARA2ZAI",
      "A2ZARA3ZAR",
      "A2ZARA3ZAI",
      "A2ZARA2AAR",
      "A2ZARA2AAI",
      "A2ZARA3AAR",
      "A2ZARA3AAI",
      "A2ZAIA3ZAR",
      "A2ZAIA3ZAI",
      "A2ZAIA2AAR",
      "A2ZAIA2AAI",
      "A2ZAIA3AAR",
      "A2ZAIA3AAI",
      "A3ZARA3ZAI",
      "A3ZARA2AAR",
      "A3ZARA2AAI",
      "A3ZARA3AAR",
      "A3ZARA3AAI",
      "A3ZAIA2AAR",
      "A3ZAIA2AAI",
      "A3ZAIA3AAR",
      "A3ZAIA3AAI",
      "A2AARA2AAI",
      "A2AARA3AAR",
      "A2AARA3AAI",
      "A2AAIA3AAR",
      "A2AAIA3AAI",
      "A3AARA3AAI"
   };
   vector<string> Suffix(suffix, suffix + 91);

   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B1_%s", Suffix[i].c_str()), &Value[i+1][0]);
   Tree->SetBranchAddress("B2", &Value[0][0]);
   /*
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B3_%s", Suffix[i].c_str()), &Value[i+1][1]);
   Tree->SetBranchAddress("B4", &Value[0][1]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B5_%s", Suffix[i].c_str()), &Value[i+1][2]);
   Tree->SetBranchAddress("B6", &Value[0][2]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B7_%s", Suffix[i].c_str()), &Value[i+1][3]);
   Tree->SetBranchAddress("B8", &Value[0][3]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B9_%s", Suffix[i].c_str()), &Value[i+1][4]);
   Tree->SetBranchAddress("B10", &Value[0][4]);
   */

   double l1pt, l1eta, l1phi, l2pt, l2eta, l2phi;
   double l3pt, l3eta, l3phi, l4pt, l4eta, l4phi;
   double Weight;
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
   Tree->SetBranchAddress("Weight", &Weight);

   int EntryCount = Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(1);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 1000 || (iE % (EntryCount / 1000) == 0))
      {
         Bar.Update(iE);
         Bar.Print();
      }

      Tree->GetEntry(iE);

      // if(DrawRandom(0, 1) > Weight)
      //    continue;

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      if(l1id < 0)   l1id = -l1id;
      if(l3id < 0)   l3id = -l3id;

      if(l1id == l3id)
         Leptons = Leptons.ReorderLeptons4e();
      else
         Leptons = Leptons.ReorderLeptons2e2mu();

      EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      if(Event.HMass > 135 || Event.HMass < 115)
         continue;
#ifdef USE_LOOSE_CUT
      if(PassBaselineCutLoose(Event) == false)
         continue;
#else
      if(PassBaselineCutTight(Event) == false)
         continue;
#endif

      string State = "";
      if(l1id == 11 && l3id == 11)   State = "ee";
      if(l1id == 11 && l3id == 13)   State = "em";
      if(l1id == 13 && l3id == 11)   State = "me";
      if(l1id == 13 && l3id == 13)   State = "mm";

      if(l1id == l3id)
      {
         if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)
            continue;
         if((Leptons.Lepton12 + Leptons.Lepton21).GetMass() < 4)
            continue;
      }
      
      string DHState = State;
#ifdef USE_LOOSE_CUT
      if(State[0] != State[1])   // em, me
         DHState = "LooseCutEM";
      if(State[0] == State[1])   // ee, mm
         DHState = "LooseCutEE";
#else
      if(State[0] != State[1])   // em, me
         DHState = "TightCutEM";
      if(State[0] == State[1])   // ee, mm
         DHState = "TightCutEE";
#endif

      if(State == "")   // WTF
         continue;
      else
      {
         for(int j = 0; j < 5; j++)
         {
#ifdef USE_LOOSE_CUT
            if(State[0] != State[1])
               BackgroundBranch[j][0] = 't';
            else
               BackgroundBranch[j][0] = 'v';
#else
            if(State[0] != State[1])
               BackgroundBranch[j][0] = 'T';
            else
               BackgroundBranch[j][0] = 'V';
#endif

            Integral[0][j] = DHFile[DHState][BackgroundBranch[j]].GetDouble();
            for(int i = 1; i < 92; i++)
            {
#ifdef USE_LOOSE_CUT
               if(State[0] != State[1])
                  SignalBranch[j][0] = 't';
               else
                  SignalBranch[j][0] = 'v';
#else
               if(State[0] != State[1])
                  SignalBranch[j][0] = 'T';
               else
                  SignalBranch[j][0] = 'V';
#endif

               char BranchSuffix[100] = "";
               sprintf(BranchSuffix, "_%02d", i);
               string Branch = SignalBranch[j] + BranchSuffix;
               Integral[i][j] = DHFile[DHState][Branch].GetDouble();
            }

            Value[0][j] = 0.5;
            Integral[0][j] = 1;
         }
      }

      for(int i = 0; i < 92; i++)
      {
         for(int j = 1; j < 5; j++)
         {
            Value[i][j] = Value[i][0];
            Integral[i][j] = Integral[i][0];
         }
      }

      bool Good = true;
      for(int i = 0; i < 92; i++)
         for(int j = 0; j < 5; j++)
            if(Value[i][j] > 0.99 || (i < 14 && Value[i][j] < 1e-50))
               Good = false;
      if(Good == false)
         continue;

      SingleEvent NewEvent;

      for(int i = 0; i < 92; i++)
         for(int j = 0; j < 5; j++)
            NewEvent.v[i][j] = Value[i][j];
      for(int i = 0; i < 92; i++)
         for(int j = 0; j < 5; j++)
            NewEvent.i[i][j] = Integral[i][j];
      NewEvent.event = Event;
      NewEvent.state = State;

      Events.push_back(NewEvent);
   }
   
   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   File.Close();

   random_shuffle(Events.begin(), Events.end());

   cout << "Events read: " << Events.size() << endl;
}



