#include <iostream>
using namespace std;

#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH2D.h"

#include "PlotHelper3.h"
#include "DataHelper.h"
#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   string ModelList[8] =
   {
      "A1UU",
      "A2UU",
      "A3UU",
      "A2UA",
      "A2UZ",
      "A1UUpA3UU",
      "A1UURpA1UZR",
      "A1UURIpA1UZRI"
   };

   bool Present[8] =
   {
      true,
      true,
      false,
      true,
      true,
      true,
      false,
      false
   };

   string Cuts[2] = {"F", "P"};

   double Events[10] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000};

   DataHelper DHFile("ResultDatabase.dh");

   PdfFileHelper PdfFile("SummaryPlots.pdf");
   PdfFile.AddTextPage("Some summary plots");

   for(int iC = 0; iC < 2; iC++)
   {
      for(int iM1 = 0; iM1 < 8; iM1++)
      {
         if(Present[iM1] == false)
            continue;

         for(int iM2 = iM1 + 1; iM2 < 8; iM2++)
         {
            if(Present[iM2] == false)
               continue;

            PdfFile.AddTextPage(Form("Models %s vs %s, Cut %s", ModelList[iM1].c_str(), ModelList[iM2].c_str(), Cuts[iC].c_str()));

            TGraphAsymmErrors GLD1, GLD1Plus, GLD1Minus;
            TGraphAsymmErrors GLD2, GLD2Plus, GLD2Minus;
            TGraph GModelP;
            TGraphAsymmErrors GLD1B, GLD1PlusB, GLD1MinusB;
            TGraphAsymmErrors GLD2B, GLD2PlusB, GLD2MinusB;
            TGraph GModelPB;
            TGraphAsymmErrors GLD1B2, GLD1PlusB2, GLD1MinusB2;
            TGraphAsymmErrors GLD2B2, GLD2PlusB2, GLD2MinusB2;
            TGraph GModelPB2;
            TGraphAsymmErrors GLD1BS, GLD1PlusBS, GLD1MinusBS;
            TGraphAsymmErrors GLD2BS, GLD2PlusBS, GLD2MinusBS;
            TGraph GModelPBS;

            GLD1.SetNameTitle("GLD1", Form("LD1, Model %d vs %d", iM1, iM2));
            GLD1Plus.SetNameTitle("GLD1Plus", Form("LD1 (+), Model %d vs %d", iM1, iM2));
            GLD1Minus.SetNameTitle("GLD1Minus", Form("LD1 (-), Model %d vs %d", iM1, iM2));
            GLD2.SetNameTitle("GLD2", Form("LD2, Model %d vs %d", iM1, iM2));
            GLD2Plus.SetNameTitle("GLD2Plus", Form("LD2 (+), Model %d vs %d", iM1, iM2));
            GLD2Minus.SetNameTitle("GLD2Minus", Form("LD2 (-), Model %d vs %d", iM1, iM2));
            GModelP.SetNameTitle("GModelP", Form("Model p-value, Model %d vs %d", iM1, iM2));
            GLD1B.SetNameTitle("GLD1B", Form("LD1, Model %d vs %d, S+B", iM1, iM2));
            GLD1PlusB.SetNameTitle("GLD1PlusB", Form("LD1 (+), Model %d vs %d, S+B", iM1, iM2));
            GLD1MinusB.SetNameTitle("GLD1MinusB", Form("LD1 (-), Model %d vs %d, S+B", iM1, iM2));
            GLD2B.SetNameTitle("GLD2B", Form("LD2, Model %d vs %d, S+B", iM1, iM2));
            GLD2PlusB.SetNameTitle("GLD2PlusB", Form("LD2 (+), Model %d vs %d, S+B", iM1, iM2));
            GLD2MinusB.SetNameTitle("GLD2MinusB", Form("LD2 (-), Model %d vs %d, S+B", iM1, iM2));
            GModelPB.SetNameTitle("GModelPB", Form("Model p-value, Model %d vs %d, S+B", iM1, iM2));
            GLD1B2.SetNameTitle("GLD1B2", Form("LD1, Model %d vs %d, S+B (float)", iM1, iM2));
            GLD1PlusB2.SetNameTitle("GLD1PlusB2", Form("LD1 (+), Model %d vs %d, S+B (float)", iM1, iM2));
            GLD1MinusB2.SetNameTitle("GLD1MinusB2", Form("LD1 (-), Model %d vs %d, S+B (float)", iM1, iM2));
            GLD2B2.SetNameTitle("GLD2B2", Form("LD2, Model %d vs %d, S+B (float)", iM1, iM2));
            GLD2PlusB2.SetNameTitle("GLD2PlusB2", Form("LD2 (+), Model %d vs %d, S+B (float)", iM1, iM2));
            GLD2MinusB2.SetNameTitle("GLD2MinusB2", Form("LD2 (-), Model %d vs %d, S+B (float)", iM1, iM2));
            GModelPB2.SetNameTitle("GModelPB2", Form("Model p-value, Model %d vs %d, S+B (float)", iM1, iM2));
            GLD1BS.SetNameTitle("GLD1BS", Form("LD1, Model %d vs %d, S+B (A2UV)", iM1, iM2));
            GLD1PlusBS.SetNameTitle("GLD1PlusBS", Form("LD1 (+), Model %d vs %d, S+B (A2UV)", iM1, iM2));
            GLD1MinusBS.SetNameTitle("GLD1MinusBS", Form("LD1 (-), Model %d vs %d, S+B (A2UV)", iM1, iM2));
            GLD2BS.SetNameTitle("GLD2BS", Form("LD2, Model %d vs %d, S+B (A2UV)", iM1, iM2));
            GLD2PlusBS.SetNameTitle("GLD2PlusBS", Form("LD2 (+), Model %d vs %d, S+B (A2UV)", iM1, iM2));
            GLD2MinusBS.SetNameTitle("GLD2MinusBS", Form("LD2 (-), Model %d vs %d, S+B (A2UV)", iM1, iM2));
            GModelPBS.SetNameTitle("GModelPBS", Form("Model p-value, Model %d vs %d, S+B (A2UV)", iM1, iM2));

            string StatePrefix = ModelList[iM1] + " " + ModelList[iM2] + " Cut" + Cuts[iC] + " ";
            string StateSuffix = Form(" [%d %d]", iM1, iM2);

            if(ModelList[iM1] > ModelList[iM2])
               StatePrefix = ModelList[iM2] + " " + ModelList[iM1] + " Cut" + Cuts[iC] + " ";
            
            for(int iS = 0; iS < 10; iS++)
            {
               string State = StatePrefix + Form("S%d", iS + 10) + StateSuffix + " 00";
               
               GLD1.SetPoint(iS, Events[iS], DHFile[State]["L1DMedian Center"].GetDouble());
               GLD1.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DMedian Center"].GetDouble() - DHFile[State]["L1DMedian Low"].GetDouble(),
                  DHFile[State]["L1DMedian High"].GetDouble() - DHFile[State]["L1DMedian Center"].GetDouble());
               GLD1Plus.SetPoint(iS, Events[iS]*1.05, DHFile[State]["L1DPlus Center"].GetDouble());
               GLD1Plus.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DPlus Center"].GetDouble() - DHFile[State]["L1DPlus Low"].GetDouble(),
                  DHFile[State]["L1DPlus High"].GetDouble() - DHFile[State]["L1DPlus Center"].GetDouble());
               GLD1Minus.SetPoint(iS, Events[iS]*0.95, DHFile[State]["L1DMinus Center"].GetDouble());
               GLD1Minus.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DMinus Center"].GetDouble() - DHFile[State]["L1DMinus Low"].GetDouble(),
                  DHFile[State]["L1DMinus High"].GetDouble() - DHFile[State]["L1DMinus Center"].GetDouble());
               GLD2.SetPoint(iS, Events[iS], DHFile[State]["L2DMedian Center"].GetDouble());
               GLD2.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DMedian Center"].GetDouble() - DHFile[State]["L2DMedian Low"].GetDouble(),
                  DHFile[State]["L2DMedian High"].GetDouble() - DHFile[State]["L2DMedian Center"].GetDouble());
               GLD2Plus.SetPoint(iS, Events[iS]*1.05, DHFile[State]["L2DPlus Center"].GetDouble());
               GLD2Plus.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DPlus Center"].GetDouble() - DHFile[State]["L2DPlus Low"].GetDouble(),
                  DHFile[State]["L2DPlus High"].GetDouble() - DHFile[State]["L2DPlus Center"].GetDouble());
               GLD2Minus.SetPoint(iS, Events[iS]*0.95, DHFile[State]["L2DMinus Center"].GetDouble());
               GLD2Minus.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DMinus Center"].GetDouble() - DHFile[State]["L2DMinus Low"].GetDouble(),
                  DHFile[State]["L2DMinus High"].GetDouble() - DHFile[State]["L2DMinus Center"].GetDouble());
               GModelP.SetPoint(iS, Events[iS], DHFile[State]["Model PValue"].GetDouble());
               
               State = StatePrefix + Form("S%d", iS + 20) + StateSuffix + " 00";
               
               GLD1B.SetPoint(iS, Events[iS], DHFile[State]["L1DMedian Center"].GetDouble());
               GLD1B.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DMedian Center"].GetDouble() - DHFile[State]["L1DMedian Low"].GetDouble(),
                  DHFile[State]["L1DMedian High"].GetDouble() - DHFile[State]["L1DMedian Center"].GetDouble());
               GLD1PlusB.SetPoint(iS, Events[iS]*1.05, DHFile[State]["L1DPlus Center"].GetDouble());
               GLD1PlusB.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DPlus Center"].GetDouble() - DHFile[State]["L1DPlus Low"].GetDouble(),
                  DHFile[State]["L1DPlus High"].GetDouble() - DHFile[State]["L1DPlus Center"].GetDouble());
               GLD1MinusB.SetPoint(iS, Events[iS]*0.95, DHFile[State]["L1DMinus Center"].GetDouble());
               GLD1MinusB.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DMinus Center"].GetDouble() - DHFile[State]["L1DMinus Low"].GetDouble(),
                  DHFile[State]["L1DMinus High"].GetDouble() - DHFile[State]["L1DMinus Center"].GetDouble());
               GLD2B.SetPoint(iS, Events[iS], DHFile[State]["L2DMedian Center"].GetDouble());
               GLD2B.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DMedian Center"].GetDouble() - DHFile[State]["L2DMedian Low"].GetDouble(),
                  DHFile[State]["L2DMedian High"].GetDouble() - DHFile[State]["L2DMedian Center"].GetDouble());
               GLD2PlusB.SetPoint(iS, Events[iS]*1.05, DHFile[State]["L2DPlus Center"].GetDouble());
               GLD2PlusB.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DPlus Center"].GetDouble() - DHFile[State]["L2DPlus Low"].GetDouble(),
                  DHFile[State]["L2DPlus High"].GetDouble() - DHFile[State]["L2DPlus Center"].GetDouble());
               GLD2MinusB.SetPoint(iS, Events[iS]*0.95, DHFile[State]["L2DMinus Center"].GetDouble());
               GLD2MinusB.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DMinus Center"].GetDouble() - DHFile[State]["L2DMinus Low"].GetDouble(),
                  DHFile[State]["L2DMinus High"].GetDouble() - DHFile[State]["L2DMinus Center"].GetDouble());
               GModelPB.SetPoint(iS, Events[iS], DHFile[State]["Model PValue"].GetDouble());
               
               State = StatePrefix + Form("S%d", iS + 20) + StateSuffix + " 10";
               
               GLD1B2.SetPoint(iS, Events[iS], DHFile[State]["L1DMedian Center"].GetDouble());
               GLD1B2.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DMedian Center"].GetDouble() - DHFile[State]["L1DMedian Low"].GetDouble(),
                  DHFile[State]["L1DMedian High"].GetDouble() - DHFile[State]["L1DMedian Center"].GetDouble());
               GLD1PlusB2.SetPoint(iS, Events[iS]*1.05, DHFile[State]["L1DPlus Center"].GetDouble());
               GLD1PlusB2.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DPlus Center"].GetDouble() - DHFile[State]["L1DPlus Low"].GetDouble(),
                  DHFile[State]["L1DPlus High"].GetDouble() - DHFile[State]["L1DPlus Center"].GetDouble());
               GLD1MinusB2.SetPoint(iS, Events[iS]*0.95, DHFile[State]["L1DMinus Center"].GetDouble());
               GLD1MinusB2.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DMinus Center"].GetDouble() - DHFile[State]["L1DMinus Low"].GetDouble(),
                  DHFile[State]["L1DMinus High"].GetDouble() - DHFile[State]["L1DMinus Center"].GetDouble());
               GLD2B2.SetPoint(iS, Events[iS], DHFile[State]["L2DMedian Center"].GetDouble());
               GLD2B2.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DMedian Center"].GetDouble() - DHFile[State]["L2DMedian Low"].GetDouble(),
                  DHFile[State]["L2DMedian High"].GetDouble() - DHFile[State]["L2DMedian Center"].GetDouble());
               GLD2PlusB2.SetPoint(iS, Events[iS]*1.05, DHFile[State]["L2DPlus Center"].GetDouble());
               GLD2PlusB2.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DPlus Center"].GetDouble() - DHFile[State]["L2DPlus Low"].GetDouble(),
                  DHFile[State]["L2DPlus High"].GetDouble() - DHFile[State]["L2DPlus Center"].GetDouble());
               GLD2MinusB2.SetPoint(iS, Events[iS]*0.95, DHFile[State]["L2DMinus Center"].GetDouble());
               GLD2MinusB2.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DMinus Center"].GetDouble() - DHFile[State]["L2DMinus Low"].GetDouble(),
                  DHFile[State]["L2DMinus High"].GetDouble() - DHFile[State]["L2DMinus Center"].GetDouble());
               GModelPB2.SetPoint(iS, Events[iS], DHFile[State]["Model PValue"].GetDouble());
               
               State = StatePrefix + Form("S%d", iS + 20) + StateSuffix + " 11";
               
               GLD1BS.SetPoint(iS, Events[iS], DHFile[State]["L1DMedian Center"].GetDouble());
               GLD1BS.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DMedian Center"].GetDouble() - DHFile[State]["L1DMedian Low"].GetDouble(),
                  DHFile[State]["L1DMedian High"].GetDouble() - DHFile[State]["L1DMedian Center"].GetDouble());
               GLD1PlusBS.SetPoint(iS, Events[iS]*1.05, DHFile[State]["L1DPlus Center"].GetDouble());
               GLD1PlusBS.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DPlus Center"].GetDouble() - DHFile[State]["L1DPlus Low"].GetDouble(),
                  DHFile[State]["L1DPlus High"].GetDouble() - DHFile[State]["L1DPlus Center"].GetDouble());
               GLD1MinusBS.SetPoint(iS, Events[iS]*0.95, DHFile[State]["L1DMinus Center"].GetDouble());
               GLD1MinusBS.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DMinus Center"].GetDouble() - DHFile[State]["L1DMinus Low"].GetDouble(),
                  DHFile[State]["L1DMinus High"].GetDouble() - DHFile[State]["L1DMinus Center"].GetDouble());
               GLD2BS.SetPoint(iS, Events[iS], DHFile[State]["L2DMedian Center"].GetDouble());
               GLD2BS.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DMedian Center"].GetDouble() - DHFile[State]["L2DMedian Low"].GetDouble(),
                  DHFile[State]["L2DMedian High"].GetDouble() - DHFile[State]["L2DMedian Center"].GetDouble());
               GLD2PlusBS.SetPoint(iS, Events[iS]*1.05, DHFile[State]["L2DPlus Center"].GetDouble());
               GLD2PlusBS.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DPlus Center"].GetDouble() - DHFile[State]["L2DPlus Low"].GetDouble(),
                  DHFile[State]["L2DPlus High"].GetDouble() - DHFile[State]["L2DPlus Center"].GetDouble());
               GLD2MinusBS.SetPoint(iS, Events[iS]*0.95, DHFile[State]["L2DMinus Center"].GetDouble());
               GLD2MinusBS.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DMinus Center"].GetDouble() - DHFile[State]["L2DMinus Low"].GetDouble(),
                  DHFile[State]["L2DMinus High"].GetDouble() - DHFile[State]["L2DMinus Center"].GetDouble());
               GModelPBS.SetPoint(iS, Events[iS], DHFile[State]["Model PValue"].GetDouble());
            }

            TCanvas C;
            C.SetLogx();
            C.SetLogy();

            TGraph GUp;
            GUp.SetPoint(0, 0, 0.5);
            GUp.SetPoint(1, 1000000000, 0.5);

            TH2D HWorld("HWorld", ";N_{S};p-value", 100, 2.5, 20000, 100, 1e-5, 1);
            HWorld.SetStats(0);

            GModelP.SetMarkerColor(kBlue);
            GModelPB.SetMarkerColor(kRed);
            GModelPB2.SetMarkerColor(kGreen);
            GModelPBS.SetMarkerColor(kYellow + 3);

            HWorld.SetTitle("Model p (S [blue] vs. S+B (fix B) [red] vs. S+B (float B) [green] vs. S+B (float B, A2UV) [yellow])");
            HWorld.Draw();
            GModelP.Draw("p");
            GModelPB.Draw("p");
            GModelPB2.Draw("p");
            GModelPBS.Draw("p");
            GUp.Draw("l");

            PdfFile.AddCanvas(C);

            // HWorld.SetTitle("LD1 (S)");
            // HWorld.Draw();
            // GLD1.Draw("pl");
            // GLD1Plus.Draw("pl");
            // GLD1Minus.Draw("pl");
            // GUp.Draw("l");

            // PdfFile.AddCanvas(C);

            // HWorld.SetTitle("LD2 (S)");
            // HWorld.Draw();
            // GLD2.Draw("pl");
            // GLD2Plus.Draw("pl");
            // GLD2Minus.Draw("pl");
            // GUp.Draw("l");

            // PdfFile.AddCanvas(C);

            // HWorld.SetTitle("LD1 (S+B fix)");
            // HWorld.Draw();
            // GLD1B.Draw("pl");
            // GLD1PlusB.Draw("pl");
            // GLD1MinusB.Draw("pl");
            // GUp.Draw("l");

            // PdfFile.AddCanvas(C);

            // HWorld.SetTitle("LD2 (S+B fix)");
            // HWorld.Draw();
            // GLD2B.Draw("pl");
            // GLD2PlusB.Draw("pl");
            // GLD2MinusB.Draw("pl");
            // GUp.Draw("l");

            // PdfFile.AddCanvas(C);

            // HWorld.SetTitle("LD1 (S+B float)");
            // HWorld.Draw();
            // GLD1B2.Draw("pl");
            // GLD1PlusB2.Draw("pl");
            // GLD1MinusB2.Draw("pl");
            // GUp.Draw("l");

            // PdfFile.AddCanvas(C);

            // HWorld.SetTitle("LD2 (S+B float)");
            // HWorld.Draw();
            // GLD2B2.Draw("pl");
            // GLD2PlusB2.Draw("pl");
            // GLD2MinusB2.Draw("pl");
            // GUp.Draw("l");

            // PdfFile.AddCanvas(C);

            // HWorld.SetTitle("LD1 (S+B float, A2UV)");
            // HWorld.Draw();
            // GLD1BS.Draw("pl");
            // GLD1PlusBS.Draw("pl");
            // GLD1MinusBS.Draw("pl");
            // GUp.Draw("l");

            // PdfFile.AddCanvas(C);

            // HWorld.SetTitle("LD2 (S+B float, A2UV)");
            // HWorld.Draw();
            // GLD2BS.Draw("pl");
            // GLD2PlusBS.Draw("pl");
            // GLD2MinusBS.Draw("pl");
            // GUp.Draw("l");

            // PdfFile.AddCanvas(C);
         }
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}








