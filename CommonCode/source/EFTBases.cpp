#include <cmath>
using namespace std;

#include "EFTBases.h"
#include "Constants.h"

AVVBasis::AVVBasis()
{
   A1ZZ = 0;   A2ZZ = 0;   A3ZZ = 0;   A4ZZ = 0;
   A1ZA = 0;   A2ZA = 0;   A3ZA = 0;   A4ZA = 0;
   A1AA = 0;   A2AA = 0;   A3AA = 0;   A4AA = 0;
}

AVVBasis::AVVBasis(double A[12])
{
   A1ZZ = A[0];   A2ZZ = A[1];   A3ZZ = A[2];   A4ZZ = A[3];
   A1ZA = A[4];   A2ZA = A[5];   A3ZA = A[6];   A4ZA = A[7];
   A1AA = A[8];   A2AA = A[9];   A3AA = A[10];  A4AA = A[11];
}

AVVBasis::AVVBasis(const HiggsBasis &H)
{
   double DeltaCZ = H.DeltaCZ;
   double CZB = H.CZB;
   double DeltaM = 0;
   double CZZ = H.CZZ;
   double CZZD = H.CZZD;
   double CZA = H.CZA;
   double CZAD = H.CZAD;
   double CAA = H.CAA;
   double CAAD = H.CAAD;

   double AlphaEM = CONST_ALPHA;
   double SW2 = CONST_SW2;
   double SW4 = SW2 * SW2;
   double CW2 = 1 - SW2;
   double CW4 = CW2 * CW2;
   double SW = sqrt(SW2);
   double CW = sqrt(CW2);
   double SW3 = SW * SW2;
   double PI = CONST_PI;

   // Older version with delta cw
   // A1ZZ = 2 * (1 + DeltaCZ);
   // A2ZZ = 4 * AlphaEM * CZZ * PI * pow(SW2 - SW4, -1);
   // A3ZZ = 4 * AlphaEM * CZZD * PI * pow(SW2 - SW4, -1);
   // A4ZZ = (1 / SW2 * (DeltaCW - DeltaCZ - 4 * DeltaM - 8 * AlphaEM * CZZ * PI + 8 * AlphaEM * CZA * PI * (1 - 2 * SW2) + 2 * (-DeltaCW + DeltaCZ + 4 * DeltaM + 4 * AlphaEM * CAA * PI * CW2) * SW2)) / 2;
   // A1ZA = 0;
   // A2ZA = 4 * AlphaEM * CZA * PI * pow(SW2 - SW4, -0.5);
   // A3ZA = 4 * AlphaEM * CZAD * PI * pow(SW2 - SW4, -0.5);
   // A4ZA = 1 / CW / SW * (-4 * AlphaEM * CZZ * PI + 4 * AlphaEM * CZA * PI * (1 - 2 * SW2) + CW2 * (DeltaCW - DeltaCZ - 4 * DeltaM + 4 * AlphaEM * CAA * PI * SW2));
   // A1AA = 0;
   // A2AA = 4 * AlphaEM * CAA * PI;
   // A3AA = 4 * AlphaEM * CAAD * PI;
   // A4AA = 0;

   // 1,4111
   A1ZZ = 2 * (1 + DeltaCZ);
   A2ZZ = 4 * AlphaEM * CZZ * PI / (SW2 - SW4);
   A3ZZ = 4 * AlphaEM * CZZD * PI / (SW2 - SW4);
   A4ZZ = 4 * AlphaEM * CZB * PI / SW2;
   A1ZA = 0;
   A2ZA = 4 * AlphaEM * CZA * PI / CW / SW;
   A3ZA = 4 * AlphaEM * CZAD * PI / CW / SW;
   A4ZA = 4 * AlphaEM * PI / CW * (-CZA + 2 * CZB + CZZ - (CAA - 2 * CZA + 2 * CZB) * SW2 + CAA * SW4) / (SW - 2 * SW3);
   A1AA = 0;
   A2AA = 4 * AlphaEM * CAA * PI;
   A3AA = 4 * AlphaEM * CAAD * PI;
   A4AA = 0;
}

AVVBasis::AVVBasis(const WarsawBasis &W)
{
   double CT = W.CT;
   double CH = W.CH;
   double DeltaM = 0;
   double CWW = W.CWW;
   double CWWD = W.CWWD;
   double CWB = W.CWB;
   double CWBD = W.CWBD;
   double CBB = W.CBB;
   double CBBD = W.CBBD;

   double AlphaEM = CONST_ALPHA;
   double SW2 = CONST_SW2;
   double SW4 = SW2 * SW2;
   double CW2 = 1 - SW2;
   double CW4 = CW2 * CW2;
   double SW = sqrt(SW2);
   double CW = sqrt(CW2);
   double PI = CONST_PI;
   
   // Older version with delta cw
   // A1ZZ = -2 / SW2 * (-DeltaM - 4 * AlphaEM * CWB * PI + (-1 + CH + 2 * DeltaM) * SW2 + CT * (1 + SW2));
   // A2ZZ = 4 * AlphaEM * PI / CW2 / SW2 * (CWW - 2 * (-2 * CWB + CWW) * SW2 + (CBB - 4 * CWB + CWW) * SW4);
   // A3ZZ = 4 * AlphaEM * PI / CW2 / SW2 * (CWWD - 2 * (-2 * CWBD + CWWD) * SW2 + (CBBD - 4 * CWBD + CWWD) * SW4);
   // A4ZZ = 1 / SW2 * (CT - DeltaM - 8 * AlphaEM * CWB * PI - 2 * CT * SW2 + 2 * DeltaM * SW2);
   // A1ZA = 0;
   // A2ZA = 4 * AlphaEM * PI / CW / SW * (-2 * CWB + CWW - (CBB - 4 * CWB + CWW) * SW2);
   // A3ZA = 4 * AlphaEM * PI / CW / SW * (-2 * CWBD + CWWD - (CBBD - 4 * CWBD + CWWD) * SW2);
   // A4ZA = 2 / CW / SW * (-4 * AlphaEM * CWB * PI + CT * CW2 + DeltaM * (-1 + SW2));
   // A1AA = 0;
   // A2AA = 4 * AlphaEM * (CBB - 4 * CWB + CWW) * PI;
   // A3AA = 4 * AlphaEM * (CBBD - 4 * CWBD + CWWD) * PI;
   // A4AA = 0;
   
   // 1,4112
   A1ZZ = 2 / SW2 * (3 * (DeltaM + 4 * AlphaEM * CWB * PI) - 3 * CT * CW2 - (-1 + CH + 6 * DeltaM) * SW2);
   A2ZZ = 4 * AlphaEM * PI / CW2 / SW2 * (CWW - 2 * (-2 * CWB + CWW) * SW2 + (CBB - 4 * CWB + CWW) * SW4);
   A3ZZ = 4 * AlphaEM * PI / CW2 / SW2 * (CWWD - 2 * (-2 * CWBD + CWWD) * SW2 + (CBBD - 4 * CWBD + CWWD) * SW4);
   A4ZZ = 2 / SW2 * (-CT + DeltaM + 4 * AlphaEM * CWB * PI - 2 * DeltaM * SW2);
   A1ZA = 0;
   A2ZA = 4 * AlphaEM * PI / CW / SW * (-2 * CWB + CWW - (CBB - 4 * CWB + CWW) * SW2);
   A3ZA = 4 * AlphaEM * PI / CW / SW * (-2 * CWBD + CWWD - (CBBD - 4 * CWBD + CWWD) * SW2);
   A4ZA = -4 / CW / SW * (DeltaM - CT * CW2 + (-3 + 2 * SW2) * (-2 * AlphaEM * CWB * PI + DeltaM * SW2)) / (-1 + 2 * SW2);
   A1AA = 0;
   A2AA = 4 * AlphaEM * (CBB - 4 * CWB + CWW) * PI;
   A3AA = 4 * AlphaEM * (CBBD - 4 * CWBD + CWWD) * PI;
   A4AA = 0;
}

AVVBasis::AVVBasis(const LoopBasis &L)
{
   InterpretationCoefficients C;
   C.yt = L.YT;
   C.yta = L.YTA;
   C.mt = L.MT;
   C.gww = L.GWW;
   C.mw = L.MW;

   A1ZZ = 2;
   A2ZZ = L.A2ZZ;
   A3ZZ = L.A3ZZ;
   A4ZZ = L.A4ZZ;
   A1ZA = 0;
   A2ZA = InterpretedA2ZA_Roberto14167(C);
   A3ZA = InterpretedA3ZA_Roberto14167(C);
   A4ZA = 0;
   A1AA = 0;
   A2AA = InterpretedA2AA_Roberto14167(C);
   A3AA = InterpretedA3AA_Roberto14167(C);
   A4AA = 0;
}

AVVBasis::AVVBasis(const LoopBasis2 &L)
{
   InterpretationCoefficients C;
   C.yt = L.YT;
   C.yta = L.YTA;
   C.mt = L.MT;
   C.gww = L.GWW;

   A1ZZ = 2 * L.CZ;
   A2ZZ = L.A2ZZ;
   A3ZZ = L.A3ZZ;
   A4ZZ = L.A4ZZ;
   A1ZA = 0;
   A2ZA = InterpretedA2ZA_Roberto14167(C);
   A3ZA = InterpretedA3ZA_Roberto14167(C);
   A4ZA = 0;
   A1AA = 0;
   A2AA = InterpretedA2AA_Roberto14167(C);
   A3AA = InterpretedA3AA_Roberto14167(C);
   A4AA = 0;
}

void AVVBasis::Print(ostream &out)
{
   out << "(" << A1ZZ << ", " << A2ZZ << ", " << A3ZZ << ", " << A4ZZ << "; "
      << A1ZA << ", " << A2ZA << ", " << A3ZA << ", " << A4ZA << "; "
      << A1AA << ", " << A2AA << ", " << A3AA << ", " << A4AA << ")";
}

HiggsBasis::HiggsBasis()
{
   DeltaCZ = 0;   CZB = 0;
   CZZ = 0;       CZZD = 0;
   CZA = 0;       CZAD = 0;
   CAA = 0;       CAAD = 0;
}

HiggsBasis::HiggsBasis(double H[8])
{
   DeltaCZ = H[0];   CZB = H[1];
   CZZ = H[2];       CZZD = H[3];
   CZA = H[4];       CZAD = H[5];
   CAA = H[6];       CAAD = H[7];
}

HiggsBasis::HiggsBasis(const AVVBasis &A)
{
   double A1ZZR = A.A1ZZ;
   double A2ZZR = A.A2ZZ;
   double A3ZZR = A.A3ZZ;
   double A4ZZR = A.A4ZZ;
   double A1ZAR = A.A1ZA;
   double A2ZAR = A.A2ZA;
   double A3ZAR = A.A3ZA;
   double A4ZAR = A.A4ZA;
   double A1AAR = A.A1AA;
   double A2AAR = A.A2AA;
   double A3AAR = A.A3AA;
   double A4AAR = A.A4AA;
   double DeltaM = 0;

   double AlphaEM = CONST_ALPHA;
   double SW2 = CONST_SW2;
   double SW4 = SW2 * SW2;
   double CW2 = 1 - SW2;
   double CW4 = CW2 * CW2;
   double SW = sqrt(SW2);
   double CW = sqrt(CW2);
   double PI = CONST_PI;

   // Older version with DeltaCW
   // CZZ = (A2ZZR / AlphaEM * CW2 / PI * SW2) / 4;
   // CZZD = (A3ZZR / AlphaEM * CW2 / PI * SW2) / 4;
   // CZA = (A2ZAR * CW * SW / AlphaEM / PI) / 4;
   // CZAD = (A3ZAR * CW * SW / AlphaEM / PI) / 4;
   // CAA = (A2AAR / AlphaEM / PI) / 4;
   // CAAD = (A3AAR / AlphaEM / PI) / 4;
   // DeltaCW = (-2 + A1ZZR + A2AAR - A2ZZR - 2 * A4ZZR + 8 * DeltaM - 4 * A2ZAR * CW * SW + 2 * (-A2AAR + A2ZZR) * SW2 + (A2AAR - A2ZZR - 2 * A4ZZR) / (-1 + 2 * SW2)) / 2;
   // DeltaCZ = (-2 + A1ZZR) / 2;
   
   // 1,4111
   CZZ = (A2ZZR / AlphaEM * CW2 / PI * SW2) / 4;
   CZZD = (A3ZZR / AlphaEM * CW2 / PI * SW2) / 4;
   CZA = (A2ZAR * CW * SW / AlphaEM / PI) / 4;
   CZAD = (A3ZAR * CW * SW / AlphaEM / PI) / 4;
   CAA = (A2AAR / AlphaEM / PI) / 4;
   CAAD = (A3AAR / AlphaEM / PI) / 4;
   CZB = (A4ZZR / AlphaEM / PI * SW2) / 4;
   DeltaCZ = (-2 + A1ZZR) / 2;
}

HiggsBasis::HiggsBasis(const WarsawBasis &W)
{
   AVVBasis A(W);
   HiggsBasis H(A);

   DeltaCZ = H.DeltaCZ;
   CZB = H.CZB;
   CZZ = H.CZZ;
   CZZD = H.CZZD;
   CZA = H.CZA;
   CZAD = H.CZAD;
   CAA = H.CAA;
   CAAD = H.CAAD;
}

void HiggsBasis::Print(ostream &out)
{
   out << "(" << DeltaCZ << ", " << CZB << ", " << CZZ << ", " << CZZD << ", " << CZA << ", " << CZAD << ", " << CAA << ", " << CAAD << ")";
}

WarsawBasis::WarsawBasis()
{
   CT = 0;    CH = 0;
   CWW = 0;   CWWD = 0;
   CWB = 0;   CWBD = 0;
   CBB = 0;   CBBD = 0;
}

WarsawBasis::WarsawBasis(double W[8])
{
   CT = W[0];    CH = W[1];
   CWW = W[2];   CWWD = W[3];
   CWB = W[4];   CWBD = W[5];
   CBB = W[6];   CBBD = W[7];
}

WarsawBasis::WarsawBasis(const AVVBasis &A)
{
   double A1ZZR = A.A1ZZ;
   double A2ZZR = A.A2ZZ;
   double A3ZZR = A.A3ZZ;
   double A4ZZR = A.A4ZZ;
   double A1ZAR = A.A1ZA;
   double A2ZAR = A.A2ZA;
   double A3ZAR = A.A3ZA;
   double A4ZAR = A.A4ZA;
   double A1AAR = A.A1AA;
   double A2AAR = A.A2AA;
   double A3AAR = A.A3AA;
   double A4AAR = A.A4AA;
   double DeltaM = 0;

   double AlphaEM = CONST_ALPHA;
   double SW2 = CONST_SW2;
   double SW4 = SW2 * SW2;
   double SW6 = SW2 * SW2 * SW2;
   double CW2 = 1 - SW2;
   double CW4 = CW2 * CW2;
   double SW = sqrt(SW2);
   double CW = sqrt(CW2);
   double PI = CONST_PI;

   // Older version with delta cw
   // CWW = (1 / AlphaEM / PI * SW2 * (A2ZZR + SW * (2 * A2ZAR * CW + A2AAR * SW) - A2ZZR * SW2)) / 4;
   // CBB = (1 / AlphaEM * CW2 * (SW * (-2 * A2ZAR * CW + A2ZZR * SW) + A2AAR * CW2) / PI) / 4;
   // CWB = -(CW * SW / AlphaEM / PI * (A2ZAR + (A2AAR - A2ZZR) * CW * SW - 2 * A2ZAR * SW2)) / 8;
   // CWWD = (1 / AlphaEM / PI * SW2 * (A3ZZR + SW * (2 * A3ZAR * CW + A3AAR * SW) - A3ZZR * SW2)) / 4;
   // CBBD = (1 / AlphaEM * CW2 * (SW * (-2 * A3ZAR * CW + A3ZZR * SW) + A3AAR * CW2) / PI) / 4;
   // CWBD = -(CW * SW / AlphaEM / PI * (A3ZAR + (A3AAR - A3ZZR) * CW * SW - 2 * A3ZAR * SW2)) / 8;
   // CT = DeltaM - A2ZAR * CW * SW + (SW / CW * (-((A2ZAR + A4ZAR) * CW2) + (A2AAR - A2ZZR) * CW * SW * (-1 + 2 * CW2) + (A2ZAR + A4ZAR) * SW2) / (-1 + 2 * SW2)) / 2;
   // CH = (1 / CW / SW * (A4ZAR * (CW - SW) * (CW + SW) * (1 + SW2) + SW * (-(A2ZAR * SW * (1 + SW2)) + A2ZAR * SW * CW2 * (-1 + 8 * SW2) - CW * (-1 + 2 * SW2) * (-2 + A1ZZR + 6 * DeltaM + 2 * (-A2AAR + A2ZZR) * SW2))) / (-1 + 2 * SW2)) / 2;
   
   // 1,4112
   CWW = (1 / AlphaEM / PI * SW2 * (A2ZZR + SW * (2 * A2ZAR * CW + A2AAR * SW) - A2ZZR * SW2))/4;
   CWWD = (1 / AlphaEM / PI * SW2 * (A3ZZR + SW * (2 * A3ZAR * CW + A3AAR * SW) - A3ZZR * SW2))/4;
   CBB = (1 / AlphaEM * CW2 * (SW * (-2 * A2ZAR * CW + A2ZZR * SW) + A2AAR * CW2) / PI) / 4;
   CBBD = (1 / AlphaEM * CW2 * (SW * (-2 * A3ZAR * CW + A3ZZR * SW) + A3AAR * CW2) / PI) / 4;
   CWB = -(CW * SW / AlphaEM / PI * (A2ZAR + (A2AAR - A2ZZR) * CW * SW - 2 * A2ZAR * SW2)) / 8;
   CWBD = -(CW * SW / AlphaEM / PI * (A3ZAR + (A3AAR - A3ZZR) * CW * SW - 2 * A3ZAR * SW2)) / 8;
   CT = (2 * DeltaM - (A4ZZR + 4 * DeltaM + (A2AAR - A2ZZR) * CW2) * SW2 + A2ZAR * CW * SW * (-1 + 2 * SW2)) / 2;
   CH = (2 - A1ZZR + 6 * DeltaM + 3 * A4ZZR * CW2 - 3 * SW * (4 * DeltaM * SW + CW * (A2ZAR + (A2AAR - A2ZZR) * CW * SW - 2 * A2ZAR * SW2))) / 2;
}

WarsawBasis::WarsawBasis(const HiggsBasis &H)
{
   AVVBasis A(H);
   WarsawBasis W(A);

   CT = W.CT;
   CH = W.CH;
   CWW = W.CWW;
   CWWD = W.CWWD;
   CWB = W.CWB;
   CWBD = W.CWBD;
   CBB = W.CBB;
   CBBD = W.CBBD;
}

void WarsawBasis::Print(ostream &out)
{
   out << "(" << CT << ", " << CH << ", " << CWW << ", " << CWWD << ", " << CWB << ", " << CWBD << ", " << CBB << ", " << CBBD << ")";
}

LoopBasis::LoopBasis()
{
   A2ZZ = 0;
   A3ZZ = 0;
   A4ZZ = 0;
   YT = 0;
   YTA = 0;
   MT = 0;
   GWW = 0;
   MW = 0;
}

LoopBasis::LoopBasis(double L[8])
{
   A2ZZ = L[0];
   A3ZZ = L[1];
   A4ZZ = L[2];
   YT = L[3];
   YTA = L[4];
   MT = L[5];
   GWW = L[6];
   MW = L[7];
}

LoopBasis::LoopBasis(const InterpretationCoefficients &C)
{
   A2ZZ = 0;
   A3ZZ = 0;
   A4ZZ = 0;
   YT = C.yt;
   YTA = C.yta;
   MT = C.mt;
   GWW = C.gww;
   MW = C.mw;
}

void LoopBasis::Print(std::ostream &out)
{
   out << "(" << A2ZZ << ", " << A3ZZ << ", " << A4ZZ << ", " << YT << ", " << YTA << ", " << MT << ", " << GWW << ", " << MW << ")";
}

LoopBasis2::LoopBasis2()
{
   A2ZZ = 0;
   A3ZZ = 0;
   A4ZZ = 0;
   YT = 0;
   YTA = 0;
   MT = 0;
   GWW = 0;
   CZ = 1;
}

LoopBasis2::LoopBasis2(double L[8])
{
   A2ZZ = L[0];
   A3ZZ = L[1];
   A4ZZ = L[2];
   YT = L[3];
   YTA = L[4];
   MT = L[5];
   GWW = L[6];
   CZ = L[7];
}

LoopBasis2::LoopBasis2(const InterpretationCoefficients &C)
{
   A2ZZ = 0;
   A3ZZ = 0;
   A4ZZ = 0;
   YT = C.yt;
   YTA = C.yta;
   MT = C.mt;
   GWW = C.gww;
   CZ = 1;
}

void LoopBasis2::Print(std::ostream &out)
{
   out << "(" << A2ZZ << ", " << A3ZZ << ", " << A4ZZ << ", " << YT << ", " << YTA << ", " << MT << ", " << GWW << ", " << CZ << ")";
}

ExtendedAVVBasis::ExtendedAVVBasis()
{
   A1ZZ = 0;   A2ZZ = 0;   A3ZZ = 0;   A4ZZ = 0;
   A1ZV = 0;   A2ZV = 0;   A3ZV = 0;   A4ZV = 0;
   A1ZA = 0;   A2ZA = 0;   A3ZA = 0;   A4ZA = 0;
   A1VV = 0;   A2VV = 0;   A3VV = 0;   A4VV = 0;
   A1VA = 0;   A2VA = 0;   A3VA = 0;   A4VA = 0;
   A1AA = 0;   A2AA = 0;   A3AA = 0;   A4AA = 0;
}

ExtendedAVVBasis::ExtendedAVVBasis(double A[24])
{
   A1ZZ = A[0];   A2ZZ = A[1];   A3ZZ = A[2];   A4ZZ = A[3];
   A1ZV = A[4];   A2ZV = A[5];   A3ZV = A[6];   A4ZV = A[7];
   A1ZA = A[8];   A2ZA = A[9];   A3ZA = A[10];  A4ZA = A[11];
   A1VV = A[12];  A2VV = A[13];  A3VV = A[14];  A4VV = A[15];
   A1VA = A[16];  A2VA = A[17];  A3VA = A[18];  A4VA = A[19];
   A1AA = A[20];  A2AA = A[21];  A3AA = A[22];  A4AA = A[23];
}
   
void ExtendedAVVBasis::Print(std::ostream &out)
{
   out << "(" << A1ZZ << ", " << A2ZZ << ", " << A3ZZ << ", " << A4ZZ << "; "
      << A1ZV << ", " << A2ZV << ", " << A3ZV << ", " << A4ZV << "; "
      << A1ZA << ", " << A2ZA << ", " << A3ZA << ", " << A4ZA << "; "
      << A1VV << ", " << A2VV << ", " << A3VV << ", " << A4VV << "; "
      << A1VA << ", " << A2VA << ", " << A3VA << ", " << A4VA << "; "
      << A1AA << ", " << A2AA << ", " << A3AA << ", " << A4AA << ")";
}
   
FullAVVBasis::FullAVVBasis()
{
   for(int i = 0; i < 72; i++)
      A[i] = 0;
}

FullAVVBasis::FullAVVBasis(PolarSymmetricFullAVVBasis &P)
{
   double AD = P.V.A * cos(P.V.Theta);
   double AO = P.V.A * sin(P.V.Theta);

   double A1234ZZ = AD * cos(P.V.ThetaD);
   double A1234VV = AD * sin(P.V.ThetaD) * cos(P.V.PhiD);
   double A1234AA = AD * sin(P.V.ThetaD) * sin(P.V.PhiD);
   double A1234ZV = AO * cos(P.V.ThetaO);
   double A1234ZA = AO * sin(P.V.ThetaO) * cos(P.V.PhiO);
   double A1234VA = AO * sin(P.V.ThetaO) * sin(P.V.PhiO);

   double A12ZZ = A1234ZZ * cos(P.V.ThetaZZ);   double A34ZZ = A1234ZZ * sin(P.V.ThetaZZ);
   double A12VV = A1234VV * cos(P.V.ThetaVV);   double A34VV = A1234VV * sin(P.V.ThetaVV);
   double A12AA = A1234AA * cos(P.V.ThetaAA);   double A34AA = A1234AA * sin(P.V.ThetaAA);
   double A12ZV = A1234ZV * cos(P.V.ThetaZV);   double A34ZV = A1234ZV * sin(P.V.ThetaZV);
   double A12ZA = A1234ZA * cos(P.V.ThetaZA);   double A34ZA = A1234ZA * sin(P.V.ThetaZA);
   double A12VA = A1234VA * cos(P.V.ThetaVA);   double A34VA = A1234VA * sin(P.V.ThetaVA);

   double A1ZZ = A12ZZ * cos(P.V.Psi12ZZ);   double A2ZZ = A12ZZ * sin(P.V.Psi12ZZ);
   double A3ZZ = A34ZZ * cos(P.V.Psi34ZZ);   double A4ZZ = A34ZZ * sin(P.V.Psi34ZZ);
   double A1VV = A12VV * cos(P.V.Psi12VV);   double A2VV = A12VV * sin(P.V.Psi12VV);
   double A3VV = A34VV * cos(P.V.Psi34VV);   double A4VV = A34VV * sin(P.V.Psi34VV);
   double A1AA = A12AA * cos(P.V.Psi12AA);   double A2AA = A12AA * sin(P.V.Psi12AA);
   double A3AA = A34AA * cos(P.V.Psi34AA);   double A4AA = A34AA * sin(P.V.Psi34AA);
   double A1ZV = A12ZV * cos(P.V.Psi12ZV);   double A2ZV = A12ZV * sin(P.V.Psi12ZV);
   double A3ZV = A34ZV * cos(P.V.Psi34ZV);   double A4ZV = A34ZV * sin(P.V.Psi34ZV);
   double A1ZA = A12ZA * cos(P.V.Psi12ZA);   double A2ZA = A12ZA * sin(P.V.Psi12ZA);
   double A3ZA = A34ZA * cos(P.V.Psi34ZA);   double A4ZA = A34ZA * sin(P.V.Psi34ZA);
   double A1VA = A12VA * cos(P.V.Psi12VA);   double A2VA = A12VA * sin(P.V.Psi12VA);
   double A3VA = A34VA * cos(P.V.Psi34VA);   double A4VA = A34VA * sin(P.V.Psi34VA);

   AVV.A1ZZR = A1ZZ * cos(P.V.ThetaA1ZZ);   AVV.A1ZZI = A1ZZ * sin(P.V.ThetaA1ZZ);
   AVV.A2ZZR = A2ZZ * cos(P.V.ThetaA2ZZ);   AVV.A2ZZI = A2ZZ * sin(P.V.ThetaA2ZZ);
   AVV.A3ZZR = A3ZZ * cos(P.V.ThetaA3ZZ);   AVV.A3ZZI = A3ZZ * sin(P.V.ThetaA3ZZ);
   AVV.A4ZZR = A4ZZ * cos(P.V.ThetaA4ZZ);   AVV.A4ZZI = A4ZZ * sin(P.V.ThetaA4ZZ);
   AVV.A1VVR = A1VV * cos(P.V.ThetaA1VV);   AVV.A1VVI = A1VV * sin(P.V.ThetaA1VV);
   AVV.A2VVR = A2VV * cos(P.V.ThetaA2VV);   AVV.A2VVI = A2VV * sin(P.V.ThetaA2VV);
   AVV.A3VVR = A3VV * cos(P.V.ThetaA3VV);   AVV.A3VVI = A3VV * sin(P.V.ThetaA3VV);
   AVV.A4VVR = A4VV * cos(P.V.ThetaA4VV);   AVV.A4VVI = A4VV * sin(P.V.ThetaA4VV);
   AVV.A1AAR = A1AA * cos(P.V.ThetaA1AA);   AVV.A1AAI = A1AA * sin(P.V.ThetaA1AA);
   AVV.A2AAR = A2AA * cos(P.V.ThetaA2AA);   AVV.A2AAI = A2AA * sin(P.V.ThetaA2AA);
   AVV.A3AAR = A3AA * cos(P.V.ThetaA3AA);   AVV.A3AAI = A3AA * sin(P.V.ThetaA3AA);
   AVV.A4AAR = A4AA * cos(P.V.ThetaA4AA);   AVV.A4AAI = A4AA * sin(P.V.ThetaA4AA);
   AVV.A1ZVR = A1ZV * cos(P.V.ThetaA1ZV);   AVV.A1ZVI = A1ZV * sin(P.V.ThetaA1ZV);
   AVV.A2ZVR = A2ZV * cos(P.V.ThetaA2ZV);   AVV.A2ZVI = A2ZV * sin(P.V.ThetaA2ZV);
   AVV.A3ZVR = A3ZV * cos(P.V.ThetaA3ZV);   AVV.A3ZVI = A3ZV * sin(P.V.ThetaA3ZV);
   AVV.A4ZVR = A4ZV * cos(P.V.ThetaA4ZV);   AVV.A4ZVI = A4ZV * sin(P.V.ThetaA4ZV);
   AVV.A1ZAR = A1ZA * cos(P.V.ThetaA1ZA);   AVV.A1ZAI = A1ZA * sin(P.V.ThetaA1ZA);
   AVV.A2ZAR = A2ZA * cos(P.V.ThetaA2ZA);   AVV.A2ZAI = A2ZA * sin(P.V.ThetaA2ZA);
   AVV.A3ZAR = A3ZA * cos(P.V.ThetaA3ZA);   AVV.A3ZAI = A3ZA * sin(P.V.ThetaA3ZA);
   AVV.A4ZAR = A4ZA * cos(P.V.ThetaA4ZA);   AVV.A4ZAI = A4ZA * sin(P.V.ThetaA4ZA);
   AVV.A1VAR = A1VA * cos(P.V.ThetaA1VA);   AVV.A1VAI = A1VA * sin(P.V.ThetaA1VA);
   AVV.A2VAR = A2VA * cos(P.V.ThetaA2VA);   AVV.A2VAI = A2VA * sin(P.V.ThetaA2VA);
   AVV.A3VAR = A3VA * cos(P.V.ThetaA3VA);   AVV.A3VAI = A3VA * sin(P.V.ThetaA3VA);
   AVV.A4VAR = A4VA * cos(P.V.ThetaA4VA);   AVV.A4VAI = A4VA * sin(P.V.ThetaA4VA);

   AVV.A1VZR = AVV.A1ZVR;   AVV.A1VZI = AVV.A1ZVI;
   AVV.A2VZR = AVV.A2ZVR;   AVV.A2VZI = AVV.A2ZVI;
   AVV.A3VZR = AVV.A3ZVR;   AVV.A3VZI = AVV.A3ZVI;
   AVV.A4VZR = AVV.A4ZVR;   AVV.A4VZI = AVV.A4ZVI;
   AVV.A1AZR = AVV.A1ZAR;   AVV.A1AZI = AVV.A1ZAI;
   AVV.A2AZR = AVV.A2ZAR;   AVV.A2AZI = AVV.A2ZAI;
   AVV.A3AZR = AVV.A3ZAR;   AVV.A3AZI = AVV.A3ZAI;
   AVV.A4AZR = AVV.A4ZAR;   AVV.A4AZI = AVV.A4ZAI;
   AVV.A1AVR = AVV.A1VAR;   AVV.A1AVI = AVV.A1VAI;
   AVV.A2AVR = AVV.A2VAR;   AVV.A2AVI = AVV.A2VAI;
   AVV.A3AVR = AVV.A3VAR;   AVV.A3AVI = AVV.A3VAI;
   AVV.A4AVR = AVV.A4VAR;   AVV.A4AVI = AVV.A4VAI;
}
   
PolarSymmetricFullAVVBasis::PolarSymmetricFullAVVBasis()
{
   for(int i = 0; i < 48; i++)
      P[i] = 0;
}

PolarSymmetricFullAVVBasis::PolarSymmetricFullAVVBasis(FullAVVBasis &AVV)
{
   for(int i = 0; i < 48; i++)
      P[i] = 0;
   
   V.ThetaA1ZZ = GetAngle(AVV.AVV.A1ZZR, AVV.AVV.A1ZZI);
   V.ThetaA2ZZ = GetAngle(AVV.AVV.A2ZZR, AVV.AVV.A2ZZI);
   V.ThetaA3ZZ = GetAngle(AVV.AVV.A3ZZR, AVV.AVV.A3ZZI);
   V.ThetaA4ZZ = GetAngle(AVV.AVV.A4ZZR, AVV.AVV.A4ZZI);
   V.ThetaA1VV = GetAngle(AVV.AVV.A1VVR, AVV.AVV.A1VVI);
   V.ThetaA2VV = GetAngle(AVV.AVV.A2VVR, AVV.AVV.A2VVI);
   V.ThetaA3VV = GetAngle(AVV.AVV.A3VVR, AVV.AVV.A3VVI);
   V.ThetaA4VV = GetAngle(AVV.AVV.A4VVR, AVV.AVV.A4VVI);
   V.ThetaA1AA = GetAngle(AVV.AVV.A1AAR, AVV.AVV.A1AAI);
   V.ThetaA2AA = GetAngle(AVV.AVV.A2AAR, AVV.AVV.A2AAI);
   V.ThetaA3AA = GetAngle(AVV.AVV.A3AAR, AVV.AVV.A3AAI);
   V.ThetaA4AA = GetAngle(AVV.AVV.A4AAR, AVV.AVV.A4AAI);
   V.ThetaA1ZV = GetAngle(AVV.AVV.A1ZVR, AVV.AVV.A1ZVI);
   V.ThetaA2ZV = GetAngle(AVV.AVV.A2ZVR, AVV.AVV.A2ZVI);
   V.ThetaA3ZV = GetAngle(AVV.AVV.A3ZVR, AVV.AVV.A3ZVI);
   V.ThetaA4ZV = GetAngle(AVV.AVV.A4ZVR, AVV.AVV.A4ZVI);
   V.ThetaA1ZA = GetAngle(AVV.AVV.A1ZAR, AVV.AVV.A1ZAI);
   V.ThetaA2ZA = GetAngle(AVV.AVV.A2ZAR, AVV.AVV.A2ZAI);
   V.ThetaA3ZA = GetAngle(AVV.AVV.A3ZAR, AVV.AVV.A3ZAI);
   V.ThetaA4ZA = GetAngle(AVV.AVV.A4ZAR, AVV.AVV.A4ZAI);
   V.ThetaA1VA = GetAngle(AVV.AVV.A1VAR, AVV.AVV.A1VAI);
   V.ThetaA2VA = GetAngle(AVV.AVV.A2VAR, AVV.AVV.A2VAI);
   V.ThetaA3VA = GetAngle(AVV.AVV.A3VAR, AVV.AVV.A3VAI);
   V.ThetaA4VA = GetAngle(AVV.AVV.A4VAR, AVV.AVV.A4VAI);

   double A1ZZ = sqrt(AVV.AVV.A1ZZR * AVV.AVV.A1ZZR + AVV.AVV.A1ZZI * AVV.AVV.A1ZZI);
   double A2ZZ = sqrt(AVV.AVV.A2ZZR * AVV.AVV.A2ZZR + AVV.AVV.A2ZZI * AVV.AVV.A2ZZI);
   double A3ZZ = sqrt(AVV.AVV.A3ZZR * AVV.AVV.A3ZZR + AVV.AVV.A3ZZI * AVV.AVV.A3ZZI);
   double A4ZZ = sqrt(AVV.AVV.A4ZZR * AVV.AVV.A4ZZR + AVV.AVV.A4ZZI * AVV.AVV.A4ZZI);
   double A1VV = sqrt(AVV.AVV.A1VVR * AVV.AVV.A1VVR + AVV.AVV.A1VVI * AVV.AVV.A1VVI);
   double A2VV = sqrt(AVV.AVV.A2VVR * AVV.AVV.A2VVR + AVV.AVV.A2VVI * AVV.AVV.A2VVI);
   double A3VV = sqrt(AVV.AVV.A3VVR * AVV.AVV.A3VVR + AVV.AVV.A3VVI * AVV.AVV.A3VVI);
   double A4VV = sqrt(AVV.AVV.A4VVR * AVV.AVV.A4VVR + AVV.AVV.A4VVI * AVV.AVV.A4VVI);
   double A1AA = sqrt(AVV.AVV.A1AAR * AVV.AVV.A1AAR + AVV.AVV.A1AAI * AVV.AVV.A1AAI);
   double A2AA = sqrt(AVV.AVV.A2AAR * AVV.AVV.A2AAR + AVV.AVV.A2AAI * AVV.AVV.A2AAI);
   double A3AA = sqrt(AVV.AVV.A3AAR * AVV.AVV.A3AAR + AVV.AVV.A3AAI * AVV.AVV.A3AAI);
   double A4AA = sqrt(AVV.AVV.A4AAR * AVV.AVV.A4AAR + AVV.AVV.A4AAI * AVV.AVV.A4AAI);
   double A1ZV = sqrt(AVV.AVV.A1ZVR * AVV.AVV.A1ZVR + AVV.AVV.A1ZVI * AVV.AVV.A1ZVI);
   double A2ZV = sqrt(AVV.AVV.A2ZVR * AVV.AVV.A2ZVR + AVV.AVV.A2ZVI * AVV.AVV.A2ZVI);
   double A3ZV = sqrt(AVV.AVV.A3ZVR * AVV.AVV.A3ZVR + AVV.AVV.A3ZVI * AVV.AVV.A3ZVI);
   double A4ZV = sqrt(AVV.AVV.A4ZVR * AVV.AVV.A4ZVR + AVV.AVV.A4ZVI * AVV.AVV.A4ZVI);
   double A1ZA = sqrt(AVV.AVV.A1ZAR * AVV.AVV.A1ZAR + AVV.AVV.A1ZAI * AVV.AVV.A1ZAI);
   double A2ZA = sqrt(AVV.AVV.A2ZAR * AVV.AVV.A2ZAR + AVV.AVV.A2ZAI * AVV.AVV.A2ZAI);
   double A3ZA = sqrt(AVV.AVV.A3ZAR * AVV.AVV.A3ZAR + AVV.AVV.A3ZAI * AVV.AVV.A3ZAI);
   double A4ZA = sqrt(AVV.AVV.A4ZAR * AVV.AVV.A4ZAR + AVV.AVV.A4ZAI * AVV.AVV.A4ZAI);
   double A1VA = sqrt(AVV.AVV.A1VAR * AVV.AVV.A1VAR + AVV.AVV.A1VAI * AVV.AVV.A1VAI);
   double A2VA = sqrt(AVV.AVV.A2VAR * AVV.AVV.A2VAR + AVV.AVV.A2VAI * AVV.AVV.A2VAI);
   double A3VA = sqrt(AVV.AVV.A3VAR * AVV.AVV.A3VAR + AVV.AVV.A3VAI * AVV.AVV.A3VAI);
   double A4VA = sqrt(AVV.AVV.A4VAR * AVV.AVV.A4VAR + AVV.AVV.A4VAI * AVV.AVV.A4VAI);

   V.Psi12ZZ = GetAngle(A1ZZ, A2ZZ);
   V.Psi12VV = GetAngle(A1VV, A2VV);
   V.Psi12AA = GetAngle(A1AA, A2AA);
   V.Psi12ZV = GetAngle(A1ZV, A2ZV);
   V.Psi12ZA = GetAngle(A1ZA, A2ZA);
   V.Psi12VA = GetAngle(A1VA, A2VA);
   V.Psi34ZZ = GetAngle(A3ZZ, A4ZZ);
   V.Psi34VV = GetAngle(A3VV, A4VV);
   V.Psi34AA = GetAngle(A3AA, A4AA);
   V.Psi34ZV = GetAngle(A3ZV, A4ZV);
   V.Psi34ZA = GetAngle(A3ZA, A4ZA);
   V.Psi34VA = GetAngle(A3VA, A4VA);

   double A12ZZ = sqrt(A1ZZ * A1ZZ + A2ZZ * A2ZZ);
   double A12VV = sqrt(A1VV * A1VV + A2VV * A2VV);
   double A12AA = sqrt(A1AA * A1AA + A2AA * A2AA);
   double A12ZV = sqrt(A1ZV * A1ZV + A2ZV * A2ZV);
   double A12ZA = sqrt(A1ZA * A1ZA + A2ZA * A2ZA);
   double A12VA = sqrt(A1VA * A1VA + A2VA * A2VA);
   double A34ZZ = sqrt(A1ZZ * A1ZZ + A2ZZ * A2ZZ);
   double A34VV = sqrt(A1VV * A1VV + A2VV * A2VV);
   double A34AA = sqrt(A1AA * A1AA + A2AA * A2AA);
   double A34ZV = sqrt(A1ZV * A1ZV + A2ZV * A2ZV);
   double A34ZA = sqrt(A1ZA * A1ZA + A2ZA * A2ZA);
   double A34VA = sqrt(A1VA * A1VA + A2VA * A2VA);

   V.ThetaZZ = GetAngle(A12ZZ, A34ZZ);
   V.ThetaVV = GetAngle(A12VV, A34VV);
   V.ThetaAA = GetAngle(A12AA, A34AA);
   V.ThetaZV = GetAngle(A12ZV, A34ZV);
   V.ThetaZA = GetAngle(A12ZA, A34ZA);
   V.ThetaVA = GetAngle(A12VA, A34VA);

   double A1234ZZ = sqrt(A12ZZ * A12ZZ + A34ZZ * A34ZZ);
   double A1234VV = sqrt(A12VV * A12VV + A34VV * A34VV);
   double A1234AA = sqrt(A12AA * A12AA + A34AA * A34AA);
   double A1234ZV = sqrt(A12ZV * A12ZV + A34ZV * A34ZV);
   double A1234ZA = sqrt(A12ZA * A12ZA + A34ZA * A34ZA);
   double A1234VA = sqrt(A12VA * A12VA + A34VA * A34VA);

   V.PhiD = GetAngle(A1234VV, A1234AA);
   V.PhiO = GetAngle(A1234ZA, A1234VA);

   double ADPartial = sqrt(A1234VV * A1234VV + A1234AA * A1234AA);
   double AOPartial = sqrt(A1234ZA * A1234ZA + A1234VA * A1234VA);

   V.ThetaD = GetAngle(A1234ZZ, ADPartial);
   V.ThetaO = GetAngle(A1234ZV, AOPartial);

   double AD = sqrt(A1234ZZ * A1234ZZ + A1234VV * A1234VV + A1234AA * A1234AA);
   double AO = sqrt(A1234ZV * A1234ZV + A1234ZA * A1234ZA + A1234VA * A1234VA);

   V.Theta = GetAngle(AD, AO);
   V.A = sqrt(AD * AD + AO * AO);
}

double PolarSymmetricFullAVVBasis::GetAngle(double X, double Y)
{
   double R = sqrt(X * X + Y * Y);
   if(R == 0)
      return 0;

   double Theta = acos(X / R);
   if(Y < 0)
      Theta = -Theta;

   return Theta;
}

std::ostream &operator <<(std::ostream &out, AVVBasis &A)
{
   A.Print(out);
   return out;
}

std::ostream &operator <<(std::ostream &out, HiggsBasis &H)
{
   H.Print(out);
   return out;
}

std::ostream &operator <<(std::ostream &out, WarsawBasis &W)
{
   W.Print(out);
   return out;
}

std::ostream &operator <<(std::ostream &out, LoopBasis &L)
{
   L.Print(out);
   return out;
}

std::ostream &operator <<(std::ostream &out, LoopBasis2 &L)
{
   L.Print(out);
   return out;
}




