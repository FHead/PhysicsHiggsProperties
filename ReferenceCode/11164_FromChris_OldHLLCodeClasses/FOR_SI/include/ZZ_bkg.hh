#ifndef ZZ_bkg_HH
#define ZZ_bkg_HH

#include <SmearingFunction.cc>

class ZZ_bkg {
public:
  ZZ_bkg();
  ~ZZ_bkg();

  void SetSmearingFunction(SmearingFunction* smear);
  void LoadEvent(TLorentzVector p1p, TLorentzVector p1m, 
		 TLorentzVector p2p, TLorentzVector p2m);
  void LoadEvent(double M, double cosTHETA, double PHI, 
		 double c1, double c2, double phi);
    
  void CalcGenMomenta();
  void CalcGenKinematics();
  void SmearMomenta(int type);  
  void CalcRecoKinematics(bool ID);
  bool PassCuts(double eta_cut, double pt_cut);
  void SwitchZ();
  void SetBoostDist(string filename);
  void GenBoost(double mH);
  double BreitWigner(double mstar, double m, double w);
  double Prob(double mH, double cosTHETA, double PHI, 
	      double c1, double c2, double phi);

  double Get_c1() {return _c1;}
  double Get_c2() {return _c2;}
  double Get_phi() {return _phi;}
  double Get_PHI() {return _PHI;}
  double Get_cosTHETA() {return _cosTHETA;}
  double Get_c1GEN() {return _c1GEN;}
  double Get_c2GEN() {return _c2GEN;}
  double Get_phiGEN() {return _phiGEN;}
  double Get_PHIGEN() {return _PHIGEN;}
  double Get_cosTHETAGEN() {return _cosTHETAGEN;}
  
  TLorentzVector Get_HGEN() {return _HGEN;}
  TLorentzVector Get_Z1GEN() {return _Z1GEN;}
  TLorentzVector Get_Z2GEN() {return _Z2GEN;}
  TLorentzVector Get_H() {return _H;}
  TLorentzVector Get_Z1() {return _Z1;}
  TLorentzVector Get_Z2() {return _Z2;}
  TLorentzVector Get_p1p() {return _p1p;}
  TLorentzVector Get_p1m() {return _p1m;}
  TLorentzVector Get_p2p() {return _p2p;}
  TLorentzVector Get_p2m() {return _p2m;}
  TLorentzVector Get_p1pGEN() {return _p1pGEN;}
  TLorentzVector Get_p1mGEN() {return _p1mGEN;}
  TLorentzVector Get_p2pGEN() {return _p2pGEN;}
  TLorentzVector Get_p2mGEN() {return _p2mGEN;}
 

protected:
  void Init();
  TRandom3* random;
  // Event-by-event kinematics
  TLorentzVector _p1pGEN;
  TLorentzVector _p1mGEN;
  TLorentzVector _p2pGEN;
  TLorentzVector _p2mGEN;

  TLorentzVector _HGEN;
  TLorentzVector _Z1GEN;
  TLorentzVector _Z2GEN;
  TLorentzVector _H;
  TLorentzVector _Z1;
  TLorentzVector _Z2;

  double _c1GEN;
  double _c2GEN;
  double _phiGEN;
  double _PHIGEN;
  double _cosTHETAGEN;
  double _massHGEN;
  double _massZ1GEN;
  double _massZ2GEN;

  TLorentzVector _p1p;
  TLorentzVector _p1m;
  TLorentzVector _p2p;
  TLorentzVector _p2m;

  double _c1;
  double _c2;
  double _phi;
  double _PHI;
  double _cosTHETA;
  double _massH;
  double _massZ1;
  double _massZ2;

  SmearingFunction* _cmsSmear;
  TH1D* _mZPDF;
  double _mZ;
  double _wZ;
  double _mMu;

  vector<TH2D*> _BoostDist;
  double _etaH;
  double _phiH;
  double _pTH;

  int N_M;
  double min_M;
  double max_M;
  int N_pt;
  double min_pt;
  double max_pt;
  int N_eta;
  double min_eta;
  double max_eta;

};
#endif
