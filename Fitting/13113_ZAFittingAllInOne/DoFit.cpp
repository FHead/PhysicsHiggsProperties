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
#include "CalculateZAME.h"

#include "FitClass.h"

#define USE_TIGHT_CUT
#define MAX_WEIGHT 4e-7

int main(int argc, char *argv[]);
double GetPhi(double x, double y);
bool PassLooseCut(ZALeptonVectors Event);
bool PassTightCut(ZALeptonVectors Event);
SingleEvent GiveMePoint(double Phis[3], double Phases[4]);
double GetWeight(double Phis[3], double Phases[4], ZAEventParameters &Event);
void ReadEvents(vector<SingleEvent> &Events, string FileName);

#define PI 3.14159265358979323846264338327950288479716939937510

// #define USE_LOOSE_CUT
#define USE_TIGHT_CUT

int main(int argc, char *argv[])
{
   int DatasetSize = 30;

   if(argc < 6)
   {
      cerr << "Usage: " << argv[0]
         << " SignalDatasetSize A2ZA A3ZA A2AA A3AA [Seed]"
         << endl;
      return -1;
   }

   DatasetSize = atoi(argv[1]);

   double A2ZA = atof(argv[2]);
   double A3ZA = atof(argv[3]);
   double A2AA = atof(argv[4]);
   double A3AA = atof(argv[5]);

   if(argc >= 7)
      srand(atoi(argv[6]));
   else
      srand(time(NULL));

   double AZA = sqrt(A2ZA * A2ZA + A3ZA * A3ZA);
   double AAA = sqrt(A2AA * A2AA + A3AA * A3AA);

   double PhiV = 0, PhiZA = 0, PhiAA = 0;
   PhiV = GetPhi(AZA, AAA);
   PhiZA = GetPhi(A2ZA, A3ZA);
   PhiAA = GetPhi(A2AA, A3AA);

   double Phis[3] = {PhiV, PhiZA, PhiAA};
   double Phases[4] = {0, 0, 0, 0};

   vector<FitResultSummary> Results;

   vector<FitConfiguration> Configurations;
   for(int i = 1; i <= 7; i++)
   {
      if(i != 7)
         continue;

      string Phis = "NNN";
      if((i / 1) % 2 == 1)    Phis[0] = 'Y';
      if((i / 2) % 2 == 1)    Phis[1] = 'Y';
      if((i / 4) % 2 == 1)    Phis[2] = 'Y';

      string Phases = "NNNN";

      vector<double> PhiValues = ListToVector(3, PhiV, PhiZA, PhiAA);

      Configurations.push_back(FitConfiguration(Phis, Phases, PhiValues, ListToVector(4, 0, 0, 0, 0)));
   }

   FitClass Fits;
   Fits.ClearPoints();
   int FitCount = 100;

   for(int iT = 0; iT < FitCount; iT++)
   {
      for(int iE = 0; iE < DatasetSize; iE++)
      {
         SingleEvent Event = GiveMePoint(Phis, Phases);
         Fits.AddPoint(Event);
      }

      for(int iC = 0; iC < (int)Configurations.size(); iC++)
      {
         FitResultSummary ResultTemp = Fits.DoFit(Configurations[iC]);
         Results.push_back(ResultTemp);
      }

      Fits.ClearPoints();
   }

   TFile OutputFile("OutputFile.root", "RECREATE");

   string BranchList = "";
   BranchList = BranchList + "PhiV:PhiZA:PhiAA";
   BranchList = BranchList + ":PhaseA2ZA:PhaseA3ZA:PhaseA2AA:PhaseA3AA";
   BranchList = BranchList + ":PhiVError:PhiZAError:PhiAAError";
   BranchList = BranchList + ":PhaseA2ZAError:PhaseA3ZAError:PhaseA2AAError:PhaseA3AAError";
   BranchList = BranchList + ":EDM:Status:DatasetSize:TruthNLL:BestNLL";

   TNtuple OutputTree("ResultTree", "", BranchList.c_str());

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[100];
      Array[0] = Results[i].Phi[0];       Array[7] = Results[i].PhiError[0];
      Array[1] = Results[i].Phi[1];       Array[8] = Results[i].PhiError[2];
      Array[2] = Results[i].Phi[2];       Array[9] = Results[i].PhiError[1];
      Array[3] = Results[i].Phase[0];     Array[10] = Results[i].PhaseError[0];
      Array[4] = Results[i].Phase[0];     Array[11] = Results[i].PhaseError[0];
      Array[5] = Results[i].Phase[0];     Array[12] = Results[i].PhaseError[0];
      Array[6] = Results[i].Phase[0];     Array[13] = Results[i].PhaseError[0];

      Array[14] = Results[i].EDM;
      Array[15] = Results[i].FitStatus;

      Array[16] = DatasetSize;

      Array[17] = Results[i].TruthNLL;    Array[18] = Results[i].BestNLL;
      
      OutputTree.Fill(Array);
   }

   OutputTree.SetMarkerStyle(20);

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

double GetPhi(double x, double y)
{
   FourVector X;
   X[1] = x;
   X[2] = y;
   return X.GetPhi();
}

bool PassLooseCut(ZALeptonVectors Vectors)
{
   if(Vectors.Lepton1.GetPT() < 2)   return false;
   if(Vectors.Lepton2.GetPT() < 2)   return false;
   if(Vectors.Photon.GetPT() < 2)    return false;

   if(Vectors.Lepton1.GetAbsEta() > 2.4)   return false;
   if(Vectors.Lepton2.GetAbsEta() > 2.4)   return false;
   if(Vectors.Photon.GetAbsEta() > 2.4)    return false;

   double M1 = (Vectors.Lepton1 + Vectors.Lepton2).GetMass();
   if(M1 < 4)   return false;

   return true;
}

bool PassTightCut(ZALeptonVectors Vectors)
{
   double PT1 = Vectors.Lepton1.GetPT();
   double PT2 = Vectors.Lepton2.GetPT();

   if(max(PT1, PT2) < 20)            return false;
   if(min(PT1, PT2) < 10)            return false;
   if(Vectors.Photon.GetPT() < 15)   return false;
   
   if(Vectors.Lepton1.GetAbsEta() > 2.4)   return false;
   if(Vectors.Lepton2.GetAbsEta() > 2.4)   return false;
   if(Vectors.Photon.GetAbsEta() > 2.4)    return false;

   double M1 = (Vectors.Lepton1 + Vectors.Lepton2).GetMass();
   if(M1 < 50)   return false;

   return true;
}

SingleEvent GiveMePoint(double Phis[3], double Phases[4])
{
   ZAEventParameters Event;
   SingleEvent Result;

   static DataHelper DHFile("ZANormalization.dh");
   
   bool Good = false;
   while(Good == false)
   {
      Event.HMass = 125;
      Event.ZMass = DrawRandom(4, 125);
      Event.Phi0 = DrawRandom(0, 2 * PI);
      Event.Theta0 = DrawRandom(0, PI);
      Event.ThetaLL = DrawRandom(0, PI);
      Event.YH = 0;
      Event.PTH = 0;
      Event.PhiH = DrawRandom(0, 2 * PI);
      Event.PhiOffset = DrawRandom(0, 2 * PI);

      ZALeptonVectors Vectors = ConvertAnglesToVectorsRoberto(Event);

#ifdef USE_LOOSE_CUT
      if(PassLooseCut(Vectors) == false)
         continue;
#elif defined USE_TIGHT_CUT
      if(PassTightCut(Vectors) == false)
         continue;
#endif

      double CombinedWeight = GetWeight(Phis, Phases, Event);
      if(DrawRandom(0, 1) < CombinedWeight / MAX_WEIGHT)
         Good = true;
      if(Good == false)
         continue;

      if(CombinedWeight > MAX_WEIGHT)
         cerr << "ERROR!  Combined weight = " << CombinedWeight
            << ", greater than max weight (" << MAX_WEIGHT << ")" << endl;

      GeneralScalarParameters EmptyParameters;
      EmptyParameters.ahR = 0;     EmptyParameters.ahI = 0;   // ZZ Doesn't matter
      EmptyParameters.aZR = 0;     EmptyParameters.aZI = 0;   // ZZ Doesn't matter
      EmptyParameters.aZdR = 0;    EmptyParameters.aZdI = 0;  // ZZ Doesn't matter
      EmptyParameters.aZAR = 0;    EmptyParameters.aZAI = 0;
      EmptyParameters.aZAdR = 0;   EmptyParameters.aZAdI = 0;
      EmptyParameters.aAR = 0;     EmptyParameters.aAI = 0;
      EmptyParameters.aAdR = 0;    EmptyParameters.aAdI = 0;

      GeneralScalarParameters PA2ZAR = EmptyParameters;   PA2ZAR.aZAR = 1;
      GeneralScalarParameters PA2ZAI = EmptyParameters;   PA2ZAI.aZAI = 1;
      GeneralScalarParameters PA3ZAR = EmptyParameters;   PA3ZAR.aZAdR = 1;
      GeneralScalarParameters PA3ZAI = EmptyParameters;   PA3ZAI.aZAdI = 1;
      GeneralScalarParameters PA2AAR = EmptyParameters;   PA2AAR.aAR = 1;
      GeneralScalarParameters PA2AAI = EmptyParameters;   PA2AAI.aAI = 1;
      GeneralScalarParameters PA3AAR = EmptyParameters;   PA3AAR.aAdR = 1;
      GeneralScalarParameters PA3AAI = EmptyParameters;   PA3AAI.aAdI = 1;

      GeneralScalarParameters PA2ZARA2ZAI = PA2ZAR;   PA2ZARA2ZAI.aZAI = 1;
      GeneralScalarParameters PA2ZARA3ZAR = PA2ZAR;   PA2ZARA3ZAR.aZAdR = 1;
      GeneralScalarParameters PA2ZARA3ZAI = PA2ZAR;   PA2ZARA3ZAI.aZAdI = 1;
      GeneralScalarParameters PA2ZARA2AAR = PA2ZAR;   PA2ZARA2AAR.aAR = 1;
      GeneralScalarParameters PA2ZARA2AAI = PA2ZAR;   PA2ZARA2AAI.aAI = 1;
      GeneralScalarParameters PA2ZARA3AAR = PA2ZAR;   PA2ZARA3AAR.aAdR = 1;
      GeneralScalarParameters PA2ZARA3AAI = PA2ZAR;   PA2ZARA3AAI.aAdI = 1;

      GeneralScalarParameters PA2ZAIA3ZAR = PA2ZAI;   PA2ZAIA3ZAR.aZAdR = 1;
      GeneralScalarParameters PA2ZAIA3ZAI = PA2ZAI;   PA2ZAIA3ZAI.aZAdI = 1;
      GeneralScalarParameters PA2ZAIA2AAR = PA2ZAI;   PA2ZAIA2AAR.aAR = 1;
      GeneralScalarParameters PA2ZAIA2AAI = PA2ZAI;   PA2ZAIA2AAI.aAI = 1;
      GeneralScalarParameters PA2ZAIA3AAR = PA2ZAI;   PA2ZAIA3AAR.aAdR = 1;
      GeneralScalarParameters PA2ZAIA3AAI = PA2ZAI;   PA2ZAIA3AAI.aAdI = 1;

      GeneralScalarParameters PA3ZARA3ZAI = PA3ZAR;   PA3ZARA3ZAI.aZAdI = 1;
      GeneralScalarParameters PA3ZARA2AAR = PA3ZAR;   PA3ZARA2AAR.aAR = 1;
      GeneralScalarParameters PA3ZARA2AAI = PA3ZAR;   PA3ZARA2AAI.aAI = 1;
      GeneralScalarParameters PA3ZARA3AAR = PA3ZAR;   PA3ZARA3AAR.aAdR = 1;
      GeneralScalarParameters PA3ZARA3AAI = PA3ZAR;   PA3ZARA3AAI.aAdI = 1;

      GeneralScalarParameters PA3ZAIA2AAR = PA3ZAI;   PA3ZAIA2AAR.aAR = 1;
      GeneralScalarParameters PA3ZAIA2AAI = PA3ZAI;   PA3ZAIA2AAI.aAI = 1;
      GeneralScalarParameters PA3ZAIA3AAR = PA3ZAI;   PA3ZAIA3AAR.aAdR = 1;
      GeneralScalarParameters PA3ZAIA3AAI = PA3ZAI;   PA3ZAIA3AAI.aAdI = 1;

      GeneralScalarParameters PA2AARA2AAI = PA2AAR;   PA2AARA2AAI.aAI = 1;
      GeneralScalarParameters PA2AARA3AAR = PA2AAR;   PA2AARA3AAR.aAdR = 1;
      GeneralScalarParameters PA2AARA3AAI = PA2AAR;   PA2AARA3AAI.aAdI = 1;

      GeneralScalarParameters PA2AAIA3AAR = PA2AAI;   PA2AAIA3AAR.aAdR = 1;
      GeneralScalarParameters PA2AAIA3AAI = PA2AAI;   PA2AAIA3AAI.aAdI = 1;

      GeneralScalarParameters PA3AARA3AAI = PA3AAR;   PA3AARA3AAI.aAdI = 1;

      Result.v[0]  = GetSpin0ZAME(Event, PA2ZAR);
      Result.v[1]  = GetSpin0ZAME(Event, PA2ZAI);
      Result.v[2]  = GetSpin0ZAME(Event, PA3ZAR);
      Result.v[3]  = GetSpin0ZAME(Event, PA3ZAI);
      Result.v[4]  = GetSpin0ZAME(Event, PA2AAR);
      Result.v[5]  = GetSpin0ZAME(Event, PA2AAI);
      Result.v[6]  = GetSpin0ZAME(Event, PA3AAR);
      Result.v[7]  = GetSpin0ZAME(Event, PA3AAI);

      Result.v[8]  = GetSpin0ZAME(Event, PA2ZARA2ZAI) - Result.v[0] - Result.v[1];
      Result.v[9]  = GetSpin0ZAME(Event, PA2ZARA3ZAR) - Result.v[0] - Result.v[2];
      Result.v[10] = GetSpin0ZAME(Event, PA2ZARA3ZAI) - Result.v[0] - Result.v[3];
      Result.v[11] = GetSpin0ZAME(Event, PA2ZARA2AAR) - Result.v[0] - Result.v[4];
      Result.v[12] = GetSpin0ZAME(Event, PA2ZARA2AAI) - Result.v[0] - Result.v[5];
      Result.v[13] = GetSpin0ZAME(Event, PA2ZARA3AAR) - Result.v[0] - Result.v[6];
      Result.v[14] = GetSpin0ZAME(Event, PA2ZARA3AAI) - Result.v[0] - Result.v[7];
      
      Result.v[15] = GetSpin0ZAME(Event, PA2ZAIA3ZAR) - Result.v[1] - Result.v[2];
      Result.v[16] = GetSpin0ZAME(Event, PA2ZAIA3ZAI) - Result.v[1] - Result.v[3];
      Result.v[17] = GetSpin0ZAME(Event, PA2ZAIA2AAR) - Result.v[1] - Result.v[4];
      Result.v[18] = GetSpin0ZAME(Event, PA2ZAIA2AAI) - Result.v[1] - Result.v[5];
      Result.v[19] = GetSpin0ZAME(Event, PA2ZAIA3AAR) - Result.v[1] - Result.v[6];
      Result.v[20] = GetSpin0ZAME(Event, PA2ZAIA3AAI) - Result.v[1] - Result.v[7];

      Result.v[21] = GetSpin0ZAME(Event, PA3ZARA3ZAI) - Result.v[2] - Result.v[3];
      Result.v[22] = GetSpin0ZAME(Event, PA3ZARA2AAR) - Result.v[2] - Result.v[4];
      Result.v[23] = GetSpin0ZAME(Event, PA3ZARA2AAI) - Result.v[2] - Result.v[5];
      Result.v[24] = GetSpin0ZAME(Event, PA3ZARA3AAR) - Result.v[2] - Result.v[6];
      Result.v[25] = GetSpin0ZAME(Event, PA3ZARA3AAI) - Result.v[2] - Result.v[7];

      Result.v[26] = GetSpin0ZAME(Event, PA3ZAIA2AAR) - Result.v[3] - Result.v[4];
      Result.v[27] = GetSpin0ZAME(Event, PA3ZAIA2AAI) - Result.v[3] - Result.v[5];
      Result.v[28] = GetSpin0ZAME(Event, PA3ZAIA3AAR) - Result.v[3] - Result.v[6];
      Result.v[29] = GetSpin0ZAME(Event, PA3ZAIA3AAI) - Result.v[3] - Result.v[7];

      Result.v[30] = GetSpin0ZAME(Event, PA2AARA2AAI) - Result.v[4] - Result.v[5];
      Result.v[31] = GetSpin0ZAME(Event, PA2AARA3AAR) - Result.v[4] - Result.v[6];
      Result.v[32] = GetSpin0ZAME(Event, PA2AARA3AAI) - Result.v[4] - Result.v[7];

      Result.v[33] = GetSpin0ZAME(Event, PA2AAIA3AAR) - Result.v[5] - Result.v[6];
      Result.v[34] = GetSpin0ZAME(Event, PA2AAIA3AAI) - Result.v[5] - Result.v[7];

      Result.v[35] = GetSpin0ZAME(Event, PA3AARA3AAI) - Result.v[6] - Result.v[7];

      for(int i = 0; i < 36; i++)
      {
         char NumberString[10] = "";
         sprintf(NumberString, "X%02d", i + 1);

#ifdef USE_LOOSE_CUT
         Result.i[i] = DHFile["Loose"][NumberString].GetDouble();
#elif defined USE_TIGHT_CUT
         Result.i[i] = DHFile["Tight"][NumberString].GetDouble();
#endif
      }

      Result.event = Event;
   }

   return Result;
}

double GetWeight(double Phis[3], double Phases[4], ZAEventParameters &Event)
{
   double AZA = cos(Phis[0]);
   double AAA = sin(Phis[0]);

   double A2ZA = AZA * cos(Phis[1]);
   double A3ZA = AZA * sin(Phis[1]);
   double A2AA = AAA * cos(Phis[2]);
   double A3AA = AAA * sin(Phis[2]);

   double A2ZAR = A2ZA * cos(Phases[0]);
   double A2ZAI = A2ZA * sin(Phases[0]);
   double A3ZAR = A3ZA * cos(Phases[1]);
   double A3ZAI = A3ZA * sin(Phases[1]);
   double A2AAR = A2AA * cos(Phases[2]);
   double A2AAI = A2AA * sin(Phases[2]);
   double A3AAR = A3AA * cos(Phases[3]);
   double A3AAI = A3AA * sin(Phases[3]);

   GeneralScalarParameters Parameters;
   Parameters.ahR = 0;         Parameters.ahI = 0;
   Parameters.aZR = 0;         Parameters.aZI = 0;
   Parameters.aZdR = 0;        Parameters.aZdI = 0;
   Parameters.aZAR = A2ZAR;    Parameters.aZAI = A2ZAI;
   Parameters.aZAdR = A3ZAR;   Parameters.aZAdI = A3ZAI;
   Parameters.aAR = A2AAR;     Parameters.aAI = A2AAI;
   Parameters.aAdR = A3AAR;    Parameters.aAdI = A3AAI;

   double Weight = GetSpin0ZAME(Event, Parameters);

   return Weight * Event.HMass * Event.ZMass * sin(Event.Theta0) * sin(Event.ThetaLL);
}



