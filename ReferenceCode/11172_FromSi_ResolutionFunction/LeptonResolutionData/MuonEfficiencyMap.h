UInt_t FindBinMuon( double value, double bins[], UInt_t nbins) {
  UInt_t nbinboundaries = nbins+1;
  UInt_t bin = 0;
  for (uint i=0; i < nbinboundaries; ++i) {
    if (i < nbinboundaries-1) {
      if (value >= bins[i] && value < bins[i+1]) {
        bin = i+1;
        break;
      }
    } else if (i == nbinboundaries-1) {
      if (value >= bins[i]) {
        bin = nbinboundaries;
        break;
      }
    }    
  }
  return bin;
}


Double_t GetMuonEfficiencyPtEtaPhi(Double_t Pt, Double_t Eta, Double_t Phi) {

  Double_t ptBins[16] = {5,6,7,8,9,10,12,14,16,18,20,25,30,35,40,50};
  Double_t etaBins[17] = {0,0.2,0.4,0.6,0.8,1,1.2,1.4442,1.566,1.8,2,2.1,2.2,2.3,2.4,2.5,2.6};
  Double_t phiBins[13] = {-3.2,-2.5,-2,-1.5,-1,-0.5,0,0.5,1,1.5,2,2.5,3.2};


  Double_t Efficiency[17][18][14]  = {
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.0134529,0.026393,0.039604,0.044164,0.0267857,0.0324484,0.0293333,0.0269461,0.0181818,0.0245232,0.0282486,0.042654,0},
      {0,0.0259434,0.0410557,0.0127389,0.0273556,0.0272727,0.0239521,0.0403727,0.0391566,0.0412979,0.00655738,0.0366972,0.034965,0},
      {0,0.0243309,0.0337423,0.0423453,0.0271903,0.0410557,0.0212121,0.0188679,0.0294118,0.0401146,0.0457143,0.0314465,0.0176768,0},
      {0,0.0248139,0.0299401,0.029703,0.01875,0.0340557,0.0311615,0.0135593,0.0369318,0.0285714,0.0443038,0.0406977,0.0369393,0},
      {0,0.0357143,0.0244648,0.0353698,0.0454545,0.01875,0.0126582,0.0174216,0.0420712,0.0172414,0.025,0.0204778,0.0154242,0},
      {0,0.0240385,0.0207612,0.041958,0.0301003,0.0327869,0.0182371,0.0320513,0.0294118,0.0197368,0.0222222,0.00857143,0.0305164,0},
      {0,0.0223124,0.0328767,0.0289157,0.0258398,0.0233161,0.0244565,0.010929,0.027027,0.0114943,0.0212766,0.0428954,0.0208768,0},
      {0,0.0305677,0.0217391,0.0335196,0.0426829,0.0343137,0.0358974,0.0301205,0.0163934,0.0175439,0.0107527,0.0104712,0.0202429,0},
      {0,0.0279188,0,0.0378549,0.015528,0.0153374,0.0280112,0.0125,0.0159151,0.0204678,0.027933,0.00543478,0.013986,0},
      {0,0.0273224,0.0436242,0.0259259,0.00729927,0.0273038,0.013289,0.00361011,0.0107914,0.0107143,0.0225564,0.0264151,0.0128205,0},
      {0,0.0131579,0.0390625,0.0144928,0.0148148,0.0212766,0.0166667,0.0423729,0.0222222,0.0357143,0,0.0149254,0.0167598,0},
      {0,0.0165746,0.025641,0.0222222,0.00787402,0.0138889,0.0243902,0,0.0325203,0.020979,0.0147059,0.030303,0,0},
      {0,0.0584795,0,0.0135135,0.0330579,0.0163934,0.023622,0.0222222,0,0.00884956,0.034965,0,0.0194805,0},
      {0,0,0,0,0.02,0.0172414,0.00869565,0.00840336,0.00793651,0.0183486,0.00769231,0,0.0177515,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.32766,0.348259,0.274194,0.361257,0.279188,0.367089,0.31694,0.310976,0.322368,0.375,0.269006,0.341346,0},
      {0,0.316583,0.305085,0.356725,0.278788,0.307692,0.285714,0.25625,0.325,0.375723,0.359116,0.322917,0.332016,0},
      {0,0.329949,0.308725,0.296089,0.347059,0.34058,0.398907,0.333333,0.348571,0.33557,0.365385,0.361582,0.340909,0},
      {0,0.337662,0.354286,0.275641,0.396341,0.412121,0.345324,0.357576,0.37037,0.442308,0.428571,0.37037,0.361991,0},
      {0,0.4,0.276596,0.350993,0.335526,0.29932,0.384106,0.395973,0.361702,0.356322,0.358621,0.360947,0.426396,0},
      {0,0.345946,0.359155,0.35119,0.358974,0.337838,0.387324,0.391608,0.349398,0.368794,0.322581,0.302326,0.374332,0},
      {0,0.398148,0.425743,0.364198,0.284884,0.40884,0.359116,0.294872,0.395722,0.382716,0.43956,0.434783,0.381579,0},
      {0,0.490741,0.358025,0.420455,0.317647,0.478873,0.533333,0.354839,0.423529,0.364865,0.391304,0.414286,0.441176,0},
      {0,0.406417,0.4,0.466667,0.355072,0.40411,0.459259,0.407143,0.366412,0.410959,0.456376,0.455224,0.475248,0},
      {0,0.490798,0.480392,0.451327,0.398148,0.352941,0.358491,0.424,0.403361,0.390909,0.411765,0.504587,0.418182,0},
      {0,0.411765,0.462963,0.40678,0.473684,0.348837,0.413043,0.555556,0.490909,0.425926,0.383333,0.348837,0.4375,0},
      {0,0.321429,0.307692,0.297872,0.240741,0.294118,0.403846,0.395833,0.354167,0.357143,0.45283,0.303571,0.41791,0},
      {0,0.241935,0.269231,0.181818,0.283019,0.172414,0.285714,0.311111,0.211538,0.382979,0.333333,0.2,0.344828,0},
      {0,0.264706,0.16,0.2,0.222222,0.212766,0.229167,0.1875,0.23913,0.186441,0.191489,0.266667,0.240741,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.382022,0.333333,0.376963,0.397129,0.369458,0.421801,0.461957,0.434783,0.373684,0.388601,0.415929,0.43913,0},
      {0,0.421687,0.443396,0.393035,0.368932,0.412088,0.428571,0.316583,0.456989,0.425,0.407583,0.419643,0.394531,0},
      {0,0.393574,0.442478,0.447761,0.435407,0.468421,0.447368,0.387665,0.402174,0.407407,0.43662,0.428571,0.408511,0},
      {0,0.417722,0.415459,0.358289,0.454082,0.469565,0.442922,0.43787,0.476923,0.440758,0.388889,0.428571,0.415686,0},
      {0,0.433071,0.457447,0.381503,0.425532,0.456989,0.424242,0.447059,0.408163,0.443182,0.448718,0.386935,0.442553,0},
      {0,0.40099,0.457286,0.402367,0.466667,0.527607,0.469697,0.469799,0.502703,0.411765,0.444444,0.454054,0.450216,0},
      {0,0.477778,0.479167,0.42487,0.530055,0.480583,0.492462,0.437186,0.446809,0.483412,0.44335,0.40566,0.457143,0},
      {0,0.478992,0.494737,0.56,0.489362,0.558824,0.45977,0.404255,0.411765,0.392857,0.45977,0.410526,0.519231,0},
      {0,0.526549,0.461538,0.5,0.515723,0.536458,0.467391,0.519231,0.426667,0.553191,0.489247,0.483412,0.528634,0},
      {0,0.526316,0.445455,0.529851,0.520833,0.558621,0.552448,0.492647,0.520661,0.597315,0.512605,0.43662,0.481283,0},
      {0,0.4,0.358491,0.37037,0.467742,0.422535,0.492537,0.507463,0.463768,0.445946,0.470588,0.426471,0.368421,0},
      {0,0.352113,0.34375,0.460317,0.410714,0.479167,0.387755,0.418919,0.444444,0.461538,0.442308,0.490196,0.40625,0},
      {0,0.408451,0.413793,0.4,0.359375,0.318182,0.387755,0.303571,0.36,0.306452,0.4,0.25,0.409836,0},
      {0,0.2,0.192982,0.217391,0.206897,0.276596,0.25,0.222222,0.181818,0.241935,0.352941,0.22449,0.273973,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.492308,0.42449,0.443548,0.493274,0.412017,0.444,0.470046,0.5,0.497835,0.44664,0.46988,0.425249,0},
      {0,0.413793,0.496124,0.385246,0.446009,0.431111,0.529126,0.511013,0.5,0.548246,0.506726,0.474419,0.484211,0},
      {0,0.493103,0.502304,0.459677,0.4329,0.515556,0.475207,0.481013,0.488764,0.475336,0.527523,0.443925,0.475728,0},
      {0,0.512727,0.448598,0.485437,0.427885,0.488688,0.532995,0.479798,0.564815,0.467593,0.495192,0.522936,0.48374,0},
      {0,0.449612,0.475728,0.40991,0.542056,0.451613,0.42268,0.519417,0.533981,0.471795,0.450704,0.480687,0.487179,0},
      {0,0.55036,0.515306,0.419192,0.45614,0.475138,0.538462,0.473404,0.446701,0.513228,0.474747,0.565217,0.490842,0},
      {0,0.508143,0.548544,0.462882,0.487395,0.478814,0.511312,0.533333,0.546729,0.513636,0.479638,0.527273,0.527027,0},
      {0,0.568182,0.575472,0.5,0.612245,0.589286,0.553719,0.49,0.58871,0.612903,0.574257,0.531915,0.512605,0},
      {0,0.504202,0.582418,0.508671,0.480874,0.58011,0.5,0.540698,0.514793,0.544974,0.504808,0.503145,0.524,0},
      {0,0.516667,0.538462,0.525,0.493333,0.455224,0.604839,0.532051,0.5,0.503497,0.522388,0.564286,0.564767,0},
      {0,0.5,0.564516,0.391304,0.416667,0.541667,0.576923,0.431034,0.515152,0.449275,0.633803,0.416667,0.541176,0},
      {0,0.4875,0.367647,0.396226,0.464286,0.384615,0.350877,0.636364,0.538462,0.428571,0.560606,0.402985,0.416667,0},
      {0,0.392857,0.297297,0.34,0.333333,0.564103,0.346939,0.423729,0.354839,0.5,0.47619,0.40678,0.492308,0},
      {0,0.227273,0.240741,0.295455,0.372881,0.354167,0.20339,0.266667,0.275862,0.363636,0.313725,0.333333,0.318841,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.494118,0.526316,0.456835,0.547244,0.491667,0.534545,0.517375,0.516484,0.490975,0.523207,0.530303,0.44795,0},
      {0,0.527331,0.475352,0.511538,0.482625,0.555556,0.477444,0.487903,0.468531,0.560345,0.536965,0.474638,0.529052,0},
      {0,0.524691,0.566406,0.54251,0.49187,0.53617,0.522267,0.505703,0.551587,0.549407,0.541667,0.517241,0.492308,0},
      {0,0.584229,0.518367,0.49569,0.53304,0.529412,0.51004,0.491803,0.497908,0.5,0.551587,0.594937,0.5,0},
      {0,0.543554,0.53304,0.506726,0.62069,0.541063,0.518182,0.511962,0.538462,0.519313,0.546559,0.544681,0.522648,0},
      {0,0.520446,0.524324,0.529412,0.545455,0.588542,0.511905,0.538813,0.543103,0.565611,0.564854,0.511737,0.544776,0},
      {0,0.520505,0.504545,0.505976,0.562212,0.595041,0.531746,0.560484,0.612319,0.520599,0.569106,0.507634,0.543253,0},
      {0,0.540323,0.53913,0.587156,0.491228,0.656863,0.513761,0.59292,0.531532,0.623077,0.546296,0.560976,0.512346,0},
      {0,0.539683,0.561224,0.527094,0.576037,0.577778,0.617021,0.55122,0.541872,0.56,0.619792,0.574468,0.587814,0},
      {0,0.59901,0.541401,0.612245,0.633333,0.539474,0.520958,0.632911,0.517986,0.586667,0.669173,0.640523,0.538889,0},
      {0,0.5625,0.533333,0.554054,0.418182,0.455696,0.536232,0.650794,0.518519,0.525641,0.5,0.583333,0.585106,0},
      {0,0.460784,0.431034,0.42029,0.6,0.422222,0.441176,0.485294,0.428571,0.466667,0.387097,0.467742,0.529412,0},
      {0,0.307692,0.345455,0.435484,0.54386,0.383333,0.447761,0.422535,0.42623,0.416667,0.468085,0.448276,0.384615,0},
      {0,0.302632,0.296296,0.293103,0.333333,0.245283,0.355263,0.285714,0.314286,0.28,0.196078,0.314815,0.2125,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.539432,0.535971,0.507194,0.49635,0.558394,0.529197,0.505882,0.485714,0.548387,0.562738,0.514599,0.534527,0},
      {0,0.521368,0.5625,0.576389,0.539792,0.523077,0.562044,0.559028,0.524648,0.554264,0.569892,0.544776,0.572308,0},
      {0,0.519231,0.573477,0.536965,0.568106,0.520661,0.546512,0.557143,0.514493,0.559184,0.571429,0.588235,0.537791,0},
      {0,0.561129,0.519685,0.582996,0.550218,0.514644,0.573705,0.514403,0.532567,0.605042,0.496212,0.626609,0.552632,0},
      {0,0.573477,0.532189,0.56015,0.545082,0.6,0.54321,0.573585,0.550388,0.575397,0.541322,0.580247,0.585443,0},
      {0,0.592105,0.526749,0.597561,0.585062,0.583673,0.581731,0.597561,0.603306,0.638889,0.62381,0.504673,0.55516,0},
      {0,0.585075,0.563636,0.576208,0.604545,0.561594,0.633065,0.551331,0.610039,0.556911,0.6,0.586345,0.604863,0},
      {0,0.49697,0.639535,0.465347,0.61157,0.57265,0.560606,0.492424,0.657658,0.614754,0.62037,0.598361,0.584416,0},
      {0,0.533784,0.579208,0.590244,0.502262,0.555024,0.568075,0.573333,0.570213,0.586735,0.538462,0.558685,0.558935,0},
      {0,0.582524,0.598592,0.574586,0.630872,0.481707,0.589595,0.569697,0.578947,0.596154,0.621469,0.59589,0.562814,0},
      {0,0.564356,0.477612,0.542857,0.643836,0.52381,0.552239,0.56962,0.56962,0.55814,0.652778,0.575342,0.56044,0},
      {0,0.549451,0.5,0.607595,0.5,0.467532,0.471429,0.390805,0.6,0.471429,0.588235,0.432432,0.5,0},
      {0,0.428571,0.353846,0.392857,0.421053,0.471698,0.508772,0.507692,0.485294,0.528302,0.470588,0.419753,0.426829,0},
      {0,0.388889,0.41791,0.470588,0.360656,0.435484,0.482759,0.387097,0.385965,0.362069,0.345455,0.346154,0.396825,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.589651,0.607431,0.590494,0.60034,0.594178,0.601695,0.569707,0.605634,0.587248,0.587522,0.571654,0.601064,0},
      {0,0.606258,0.599628,0.59965,0.572156,0.604414,0.618399,0.550622,0.648425,0.590444,0.594128,0.613767,0.596354,0},
      {0,0.585464,0.628676,0.559928,0.584642,0.592346,0.623987,0.587189,0.62543,0.605263,0.618375,0.596987,0.618158,0},
      {0,0.62804,0.6337,0.614,0.594406,0.590909,0.579585,0.568401,0.614695,0.621324,0.631387,0.627907,0.59751,0},
      {0,0.603318,0.612476,0.612167,0.634766,0.629964,0.645522,0.597043,0.636519,0.59725,0.566855,0.633911,0.608558,0},
      {0,0.614089,0.603306,0.57839,0.610101,0.594937,0.638776,0.637275,0.610075,0.615909,0.59309,0.650628,0.618182,0},
      {0,0.627346,0.60312,0.617706,0.652751,0.608779,0.620275,0.59292,0.596552,0.615248,0.616756,0.602612,0.638889,0},
      {0,0.627451,0.635338,0.596838,0.599206,0.68595,0.614545,0.657692,0.640496,0.673387,0.594017,0.669231,0.654952,0},
      {0,0.614726,0.567961,0.606335,0.615385,0.618056,0.623094,0.61215,0.639013,0.621749,0.658654,0.59719,0.656371,0},
      {0,0.592683,0.552381,0.566879,0.586885,0.611842,0.610169,0.557692,0.609231,0.634146,0.618785,0.631579,0.609756,0},
      {0,0.636364,0.583893,0.559701,0.563758,0.61039,0.580645,0.573864,0.606667,0.582734,0.609589,0.572289,0.629834,0},
      {0,0.567901,0.507246,0.529851,0.491803,0.541985,0.507692,0.553191,0.551471,0.522293,0.578947,0.561644,0.592814,0},
      {0,0.490683,0.455285,0.531469,0.5,0.47619,0.394737,0.546154,0.433566,0.530303,0.421053,0.452055,0.490446,0},
      {0,0.486111,0.364341,0.36,0.363636,0.472,0.336364,0.401575,0.380165,0.378641,0.371429,0.349206,0.411765,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.643939,0.645768,0.645212,0.667171,0.640489,0.617284,0.644845,0.653555,0.615756,0.667219,0.636066,0.63581,0},
      {0,0.672111,0.637562,0.64613,0.614035,0.656093,0.65247,0.641509,0.608379,0.634921,0.657143,0.599332,0.636245,0},
      {0,0.647453,0.615506,0.633851,0.641068,0.659459,0.623779,0.704013,0.653266,0.640323,0.654255,0.658031,0.649471,0},
      {0,0.677824,0.644366,0.640678,0.661017,0.635739,0.648557,0.634615,0.635209,0.680297,0.614983,0.647482,0.632391,0},
      {0,0.658209,0.678119,0.673721,0.653257,0.634652,0.64684,0.634652,0.663732,0.633028,0.652008,0.63879,0.666667,0},
      {0,0.651613,0.634298,0.637275,0.658537,0.685149,0.672,0.609856,0.685185,0.653631,0.626531,0.651805,0.682515,0},
      {0,0.665765,0.657559,0.612663,0.626923,0.679376,0.639932,0.659498,0.635135,0.628521,0.645338,0.65725,0.647646,0},
      {0,0.677215,0.668033,0.648536,0.628571,0.655738,0.620087,0.681275,0.683544,0.642023,0.669261,0.724,0.634868,0},
      {0,0.668459,0.678404,0.624444,0.619154,0.66309,0.603604,0.659864,0.617925,0.65808,0.635747,0.624424,0.68007,0},
      {0,0.603819,0.693009,0.678125,0.634615,0.669617,0.672515,0.60221,0.597101,0.644013,0.640127,0.654655,0.62844,0},
      {0,0.633136,0.664,0.629139,0.589404,0.607407,0.608434,0.598592,0.585526,0.595588,0.594595,0.591837,0.519774,0},
      {0,0.578947,0.571429,0.577922,0.562914,0.595588,0.556291,0.559211,0.533333,0.560811,0.574468,0.545455,0.60199,0},
      {0,0.555556,0.504065,0.454545,0.544776,0.488189,0.550388,0.520548,0.507692,0.539568,0.496644,0.476562,0.551282,0},
      {0,0.52071,0.523438,0.46,0.451613,0.472727,0.422764,0.496241,0.448598,0.460177,0.504762,0.406593,0.506494,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.675,0.704293,0.685252,0.671617,0.66877,0.668874,0.630435,0.699187,0.678788,0.680067,0.664912,0.683444,0},
      {0,0.67947,0.690141,0.686542,0.626786,0.618467,0.653501,0.631119,0.666102,0.661812,0.653974,0.670492,0.641611,0},
      {0,0.69407,0.67446,0.630691,0.657627,0.668942,0.658537,0.695652,0.652651,0.689531,0.6534,0.691126,0.687339,0},
      {0,0.699301,0.677419,0.671378,0.719178,0.684685,0.655417,0.650362,0.713514,0.663082,0.688213,0.691383,0.668079,0},
      {0,0.700599,0.724752,0.671154,0.678788,0.684701,0.697495,0.676245,0.672862,0.710526,0.642458,0.691849,0.682652,0},
      {0,0.667164,0.684783,0.667969,0.712274,0.64833,0.69428,0.644681,0.656315,0.674797,0.68705,0.670611,0.679104,0},
      {0,0.677037,0.654741,0.670157,0.680628,0.725217,0.662566,0.661626,0.693122,0.697297,0.683112,0.694946,0.70059,0},
      {0,0.613115,0.680451,0.645418,0.675277,0.675182,0.707317,0.653846,0.648536,0.651852,0.645038,0.710037,0.658621,0},
      {0,0.707965,0.649554,0.699301,0.647619,0.677346,0.69378,0.651885,0.653207,0.697039,0.708122,0.66055,0.668449,0},
      {0,0.636792,0.632107,0.625899,0.67541,0.636646,0.655629,0.66,0.674121,0.622291,0.627273,0.686869,0.692506,0},
      {0,0.578652,0.655629,0.634483,0.594771,0.548387,0.589147,0.625,0.609272,0.694268,0.745562,0.636364,0.531401,0},
      {0,0.554217,0.527778,0.556522,0.540146,0.616,0.625,0.558824,0.5625,0.625899,0.587413,0.593985,0.552083,0},
      {0,0.5125,0.546296,0.469697,0.554622,0.549296,0.59375,0.555556,0.555556,0.610619,0.547009,0.588235,0.586826,0},
      {0,0.517007,0.445545,0.541284,0.468468,0.412214,0.521368,0.394495,0.5,0.536585,0.462185,0.469027,0.428571,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.685185,0.676895,0.674242,0.692573,0.671614,0.688612,0.663176,0.681641,0.687398,0.69788,0.688073,0.662162,0},
      {0,0.684066,0.650995,0.696491,0.681739,0.689304,0.739962,0.726126,0.692737,0.710117,0.690432,0.661996,0.663539,0},
      {0,0.694767,0.676786,0.689531,0.695896,0.709343,0.676106,0.703154,0.661738,0.677596,0.664717,0.695971,0.69927,0},
      {0,0.694992,0.700422,0.686703,0.712042,0.737354,0.694553,0.672549,0.673428,0.72428,0.685817,0.712204,0.698738,0},
      {0,0.67713,0.700413,0.700197,0.696429,0.727096,0.696356,0.699387,0.693548,0.71673,0.682018,0.719745,0.681672,0},
      {0,0.670989,0.678571,0.666667,0.659341,0.707265,0.702882,0.690171,0.668354,0.699588,0.665227,0.685969,0.737896,0},
      {0,0.698198,0.680639,0.692946,0.671233,0.704331,0.668024,0.702,0.681729,0.665331,0.715139,0.714008,0.657321,0},
      {0,0.70997,0.693878,0.701681,0.665217,0.679654,0.702811,0.658009,0.700855,0.654028,0.647773,0.711712,0.667774,0},
      {0,0.689464,0.693002,0.628492,0.679724,0.651042,0.688222,0.683168,0.665829,0.708029,0.6875,0.67581,0.686025,0},
      {0,0.647202,0.678445,0.683453,0.614841,0.695167,0.711409,0.667785,0.622378,0.723776,0.655949,0.637324,0.666667,0},
      {0,0.672043,0.62963,0.65625,0.676923,0.597122,0.620155,0.607143,0.659574,0.618321,0.652893,0.622951,0.652632,0},
      {0,0.567251,0.5,0.58042,0.636364,0.567376,0.610294,0.610619,0.603053,0.617188,0.679688,0.682927,0.606061,0},
      {0,0.593496,0.468468,0.637363,0.575,0.477477,0.612245,0.504762,0.550388,0.587629,0.584746,0.6,0.622754,0},
      {0,0.445946,0.464286,0.545455,0.438095,0.466667,0.43956,0.506329,0.446602,0.534091,0.481818,0.495413,0.489655,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.685835,0.693548,0.661922,0.689981,0.692449,0.71063,0.716028,0.681467,0.654369,0.736538,0.661386,0.69163,0},
      {0,0.722944,0.710728,0.699387,0.654511,0.701149,0.676864,0.678571,0.71281,0.703777,0.712381,0.685714,0.715839,0},
      {0,0.732036,0.64991,0.662432,0.689453,0.684211,0.71,0.726236,0.707071,0.673956,0.716,0.643939,0.70687,0},
      {0,0.7031,0.747951,0.719262,0.728889,0.672764,0.722672,0.722642,0.681529,0.685259,0.733753,0.697495,0.697712,0},
      {0,0.689236,0.689507,0.727473,0.69379,0.727619,0.716518,0.677494,0.6875,0.664583,0.705215,0.724576,0.734007,0},
      {0,0.715789,0.7,0.690418,0.705128,0.737981,0.69697,0.722096,0.699519,0.691038,0.688053,0.68894,0.702422,0},
      {0,0.688817,0.681818,0.644211,0.728632,0.726891,0.708163,0.720497,0.726358,0.704104,0.716738,0.671739,0.71912,0},
      {0,0.72963,0.73913,0.682403,0.630542,0.676856,0.706422,0.673077,0.683258,0.643216,0.680203,0.71066,0.69112,0},
      {0,0.645514,0.674731,0.69837,0.704787,0.728863,0.639205,0.651948,0.619883,0.715447,0.67979,0.654391,0.654959,0},
      {0,0.655172,0.698182,0.645161,0.664207,0.715789,0.692857,0.700337,0.683636,0.704453,0.669145,0.658824,0.701408,0},
      {0,0.60119,0.641379,0.625,0.605263,0.6,0.645455,0.574803,0.653846,0.609756,0.686441,0.643564,0.598765,0},
      {0,0.540146,0.49505,0.574803,0.601695,0.598361,0.614815,0.620968,0.598361,0.62931,0.608696,0.518868,0.567568,0},
      {0,0.646154,0.699029,0.537736,0.622807,0.581818,0.59,0.525,0.5625,0.608696,0.619565,0.590476,0.596774,0},
      {0,0.490385,0.516484,0.511628,0.568807,0.478632,0.5,0.385542,0.528736,0.52439,0.517544,0.520408,0.508475,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.69142,0.706199,0.719388,0.712303,0.712489,0.705505,0.717995,0.704545,0.726625,0.707071,0.711312,0.681717,0},
      {0,0.71846,0.719816,0.705213,0.687674,0.691519,0.703601,0.696714,0.675455,0.703286,0.720952,0.710855,0.711029,0},
      {0,0.723221,0.704637,0.731822,0.725806,0.720862,0.736213,0.740631,0.678846,0.712077,0.737452,0.717493,0.703353,0},
      {0,0.712926,0.722449,0.684584,0.728088,0.707483,0.712598,0.70936,0.707411,0.71028,0.686782,0.6931,0.716881,0},
      {0,0.708714,0.709514,0.701461,0.70651,0.714443,0.736842,0.706653,0.731,0.72182,0.691478,0.722038,0.709887,0},
      {0,0.717728,0.70634,0.710983,0.697809,0.715708,0.684932,0.6678,0.680175,0.701342,0.700779,0.704651,0.711456,0},
      {0,0.717172,0.713089,0.716433,0.714889,0.721206,0.712185,0.705763,0.69969,0.693837,0.701566,0.691909,0.711918,0},
      {0,0.662432,0.669623,0.699387,0.655446,0.696703,0.681614,0.706638,0.716418,0.723404,0.707983,0.692308,0.689139,0},
      {0,0.708718,0.686869,0.704067,0.70202,0.716146,0.686352,0.735677,0.689258,0.713736,0.722365,0.70494,0.69332,0},
      {0,0.667626,0.683478,0.666081,0.68638,0.703448,0.677996,0.663866,0.721683,0.685455,0.67121,0.700917,0.69179,0},
      {0,0.66087,0.657258,0.719697,0.655039,0.699571,0.701299,0.717647,0.683486,0.632653,0.658824,0.66129,0.686007,0},
      {0,0.66436,0.598253,0.691983,0.597561,0.652893,0.64977,0.615063,0.669683,0.620853,0.670996,0.611814,0.619048,0},
      {0,0.620072,0.684492,0.602679,0.62069,0.627119,0.597222,0.582524,0.62212,0.679348,0.61165,0.645503,0.592593,0},
      {0,0.562016,0.52356,0.633166,0.609375,0.518135,0.560209,0.573171,0.515306,0.593137,0.486911,0.59116,0.57874,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.765475,0.771775,0.749458,0.752174,0.774411,0.735619,0.781427,0.790698,0.791246,0.791028,0.757327,0.795552,0},
      {0,0.771681,0.784615,0.758315,0.739326,0.753715,0.75772,0.766593,0.777262,0.780731,0.771619,0.775648,0.762976,0},
      {0,0.77866,0.789531,0.785633,0.765882,0.766704,0.764429,0.777268,0.783529,0.777393,0.760684,0.800691,0.762324,0},
      {0,0.763412,0.751908,0.746761,0.741935,0.788915,0.78961,0.747368,0.754624,0.761677,0.748466,0.78436,0.773077,0},
      {0,0.75835,0.736976,0.741307,0.772668,0.762599,0.747793,0.739744,0.749383,0.744125,0.74966,0.778226,0.766019,0},
      {0,0.726496,0.76,0.708389,0.743989,0.735744,0.749014,0.716755,0.719251,0.730135,0.714702,0.768194,0.772829,0},
      {0,0.730955,0.75,0.730424,0.704857,0.729974,0.757306,0.770471,0.761966,0.71195,0.757161,0.735369,0.740413,0},
      {0,0.708716,0.704478,0.746313,0.77957,0.775076,0.763006,0.740642,0.696602,0.72905,0.767263,0.749373,0.745247,0},
      {0,0.704244,0.721044,0.720893,0.754386,0.747994,0.75039,0.683409,0.714286,0.752756,0.728333,0.764151,0.752179,0},
      {0,0.737478,0.733485,0.686047,0.691943,0.747807,0.729911,0.744589,0.759574,0.747768,0.740476,0.739229,0.67121,0},
      {0,0.704453,0.759615,0.683962,0.699074,0.737991,0.638298,0.6875,0.684729,0.721154,0.70283,0.729258,0.745455,0},
      {0,0.691667,0.696629,0.646739,0.734694,0.69,0.734463,0.663043,0.708333,0.691099,0.708134,0.654255,0.697479,0},
      {0,0.668203,0.674847,0.715976,0.694581,0.677419,0.676647,0.617021,0.704918,0.690789,0.641975,0.642857,0.733668,0},
      {0,0.631579,0.586957,0.635294,0.617284,0.610063,0.634483,0.647436,0.628378,0.662069,0.631902,0.661972,0.663158,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.830556,0.850939,0.837775,0.857639,0.842645,0.856377,0.85244,0.839578,0.84589,0.848965,0.823804,0.841379,0},
      {0,0.833484,0.847554,0.850955,0.812287,0.834873,0.817241,0.83414,0.809467,0.82767,0.821641,0.830233,0.844643,0},
      {0,0.82668,0.839109,0.827711,0.803468,0.843554,0.819809,0.829091,0.831034,0.830035,0.813149,0.832536,0.843362,0},
      {0,0.813152,0.824781,0.810945,0.824798,0.85101,0.835938,0.837419,0.820352,0.831536,0.843137,0.810909,0.828794,0},
      {0,0.805825,0.84022,0.825503,0.79677,0.810512,0.841962,0.799736,0.813172,0.80083,0.811533,0.820621,0.813857,0},
      {0,0.809249,0.798165,0.799435,0.782032,0.811554,0.814016,0.804469,0.818182,0.807099,0.785075,0.779614,0.760234,0},
      {0,0.765,0.752604,0.798693,0.748092,0.792405,0.789407,0.784439,0.779452,0.780132,0.8125,0.789326,0.8,0},
      {0,0.78487,0.775449,0.770718,0.75,0.778075,0.764706,0.802326,0.755882,0.796089,0.796482,0.742775,0.773218,0},
      {0,0.797279,0.758621,0.761667,0.767888,0.784219,0.765891,0.76874,0.777778,0.764706,0.740132,0.778157,0.770964,0},
      {0,0.742424,0.734411,0.817308,0.745921,0.742981,0.780105,0.741419,0.795455,0.763098,0.724891,0.725,0.778547,0},
      {0,0.662281,0.689474,0.706468,0.781915,0.777778,0.774359,0.77193,0.736559,0.7625,0.71978,0.752427,0.75,0},
      {0,0.721461,0.68617,0.711656,0.723164,0.713514,0.710983,0.653333,0.66242,0.716578,0.72327,0.704918,0.746479,0},
      {0,0.643617,0.769231,0.698795,0.740506,0.653595,0.709677,0.6875,0.649635,0.715278,0.71519,0.698113,0.757447,0},
      {0,0.666667,0.674797,0.680272,0.736842,0.62069,0.617188,0.593333,0.689441,0.732484,0.651613,0.638298,0.63,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.892045,0.898104,0.873786,0.888078,0.877666,0.883352,0.87963,0.895054,0.878019,0.893643,0.882491,0.88657,0},
      {0,0.907834,0.879133,0.886199,0.885488,0.894253,0.87234,0.888,0.869312,0.883408,0.876443,0.900463,0.888993,0},
      {0,0.871847,0.866017,0.866508,0.874852,0.877301,0.860329,0.894118,0.880435,0.86715,0.889148,0.882635,0.874885,0},
      {0,0.871429,0.880299,0.864041,0.86375,0.853458,0.858396,0.862024,0.861214,0.866667,0.860294,0.871089,0.866351,0},
      {0,0.866034,0.848168,0.836364,0.852564,0.858073,0.85931,0.859249,0.854962,0.848787,0.85059,0.855967,0.856855,0},
      {0,0.835088,0.854223,0.819383,0.853372,0.840941,0.81997,0.809272,0.812779,0.850073,0.840108,0.846154,0.848929,0},
      {0,0.830421,0.818299,0.813765,0.797419,0.827725,0.81519,0.803109,0.799454,0.823607,0.813333,0.820779,0.822564,0},
      {0,0.820046,0.765244,0.756598,0.81694,0.81875,0.796923,0.81962,0.859195,0.815182,0.80112,0.83965,0.793319,0},
      {0,0.776353,0.777592,0.76699,0.786271,0.80303,0.773585,0.783471,0.773246,0.783276,0.769231,0.781086,0.807133,0},
      {0,0.760213,0.778509,0.751121,0.770787,0.765854,0.749431,0.708738,0.757303,0.759551,0.755448,0.742788,0.767925,0},
      {0,0.721992,0.748815,0.756219,0.734694,0.73224,0.735294,0.742515,0.704918,0.744792,0.772487,0.765258,0.738589,0},
      {0,0.753695,0.737705,0.706215,0.670588,0.759259,0.728261,0.714286,0.664179,0.717647,0.721854,0.738095,0.711009,0},
      {0,0.668067,0.639752,0.729167,0.675325,0.716312,0.72956,0.688742,0.730539,0.71519,0.629371,0.708075,0.671875,0},
      {0,0.654054,0.686567,0.641892,0.703125,0.699248,0.673759,0.655172,0.626761,0.679104,0.633803,0.637795,0.692308,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.893915,0.915192,0.907522,0.897522,0.921624,0.922911,0.919401,0.907395,0.907328,0.925141,0.911551,0.906001,0},
      {0,0.910304,0.911027,0.898955,0.886214,0.907261,0.921986,0.90935,0.894016,0.892157,0.892758,0.907827,0.908621,0},
      {0,0.907821,0.900442,0.914971,0.906755,0.905882,0.913978,0.918413,0.91021,0.911631,0.901244,0.913202,0.917808,0},
      {0,0.904337,0.900598,0.915373,0.899698,0.907823,0.897189,0.894377,0.896735,0.89214,0.900489,0.911988,0.910862,0},
      {0,0.889161,0.888798,0.881657,0.901653,0.893881,0.901195,0.886749,0.888152,0.900426,0.892027,0.891399,0.889825,0},
      {0,0.87661,0.86746,0.868733,0.873029,0.881701,0.867622,0.874219,0.892519,0.874573,0.858844,0.883806,0.879801,0},
      {0,0.856426,0.850829,0.835821,0.836393,0.849326,0.847165,0.862909,0.848214,0.832129,0.846854,0.857143,0.853349,0},
      {0,0.844828,0.858156,0.8473,0.834154,0.835088,0.832432,0.804159,0.789384,0.809695,0.829314,0.839864,0.820163,0},
      {0,0.809016,0.81828,0.823654,0.814689,0.812155,0.799569,0.786885,0.784228,0.828304,0.802313,0.794956,0.815975,0},
      {0,0.784795,0.774194,0.763889,0.757971,0.763524,0.773876,0.767267,0.766082,0.795322,0.797858,0.75942,0.807818,0},
      {0,0.731707,0.743056,0.76779,0.747604,0.726351,0.809187,0.695946,0.753754,0.72973,0.744409,0.726027,0.796069,0},
      {0,0.689024,0.71831,0.650735,0.70155,0.750973,0.737705,0.690909,0.770677,0.650909,0.668966,0.721805,0.673529,0},
      {0,0.660057,0.677043,0.74812,0.657778,0.692015,0.574766,0.62605,0.646512,0.67433,0.744186,0.686099,0.717718,0},
      {0,0.602076,0.61157,0.60274,0.655172,0.636364,0.676056,0.619512,0.663677,0.651282,0.574257,0.626923,0.664207,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.900116,0.885,0.916605,0.889203,0.892433,0.892286,0.887689,0.889787,0.904482,0.898217,0.900888,0.909703,0},
      {0,0.897276,0.896682,0.882266,0.892883,0.900442,0.885116,0.886598,0.886214,0.861813,0.882576,0.901773,0.902199,0},
      {0,0.890104,0.887538,0.906149,0.898974,0.905063,0.887982,0.887097,0.889799,0.895879,0.893263,0.902798,0.893931,0},
      {0,0.873317,0.894696,0.882793,0.888708,0.873459,0.898932,0.890101,0.874693,0.889331,0.882869,0.899533,0.891211,0},
      {0,0.868548,0.879965,0.876629,0.860051,0.862762,0.865254,0.89208,0.880543,0.873544,0.863946,0.871077,0.881777,0},
      {0,0.880089,0.88,0.884393,0.866731,0.859141,0.845552,0.872401,0.858782,0.865571,0.851521,0.881605,0.866904,0},
      {0,0.853138,0.842869,0.823638,0.85284,0.833618,0.849153,0.855839,0.833948,0.837788,0.8375,0.84827,0.834464,0},
      {0,0.808383,0.823308,0.837302,0.817006,0.831301,0.827038,0.842742,0.834382,0.808943,0.820327,0.826531,0.809023,0},
      {0,0.793785,0.817422,0.810191,0.780488,0.795328,0.794152,0.774233,0.806683,0.771218,0.797674,0.793765,0.825548,0},
      {0,0.731865,0.755319,0.744059,0.755027,0.771721,0.753555,0.744076,0.768224,0.756477,0.782906,0.804029,0.766839,0},
      {0,0.723127,0.677419,0.743494,0.743802,0.785425,0.661224,0.748899,0.758621,0.767717,0.697095,0.655738,0.767213,0},
      {0,0.634483,0.63964,0.722222,0.724138,0.709821,0.672727,0.651064,0.678414,0.731092,0.691542,0.757143,0.720257,0},
      {0,0.667984,0.678788,0.677273,0.601036,0.700599,0.645503,0.628272,0.696335,0.674312,0.625616,0.692308,0.61157,0},
      {0,0.641148,0.551724,0.560976,0.555556,0.659091,0.609929,0.551282,0.621795,0.578616,0.592814,0.540541,0.633466,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
}
};


  Int_t tmpPtBin = FindBinMuon( Pt , ptBins, 15);
  Int_t tmpEtaBin = FindBinMuon( Eta , etaBins, 16);
  Int_t tmpPhiBin = FindBinMuon( Phi , phiBins, 12);
  return Efficiency[tmpPtBin][tmpEtaBin][tmpPhiBin];
}




Double_t GetMuonEfficiencyPtEta(Double_t Pt, Double_t Eta) {

  Double_t ptBins[16] = {5,6,7,8,9,10,12,14,16,18,20,25,30,35,40,50};
  Double_t etaBins[17] = {0,0.2,0.4,0.6,0.8,1,1.2,1.4442,1.566,1.8,2,2.1,2.2,2.3,2.4,2.5,2.6};


  Double_t Efficiency[17][18] = {
    {0,0.0290807,0.0300533,0.0308597,0.0309636,0.0259027,0.0256541,0.0243335,0.0252284,0.0183616,0.0195402,0.0207697,0.0170628,0.0201588,0.00874243,0,0,0    },
    {0,0.324482,0.319722,0.342552,0.369756,0.360081,0.354997,0.38319,0.417709,0.423961,0.426093,0.432392,0.346875,0.269297,0.218371,0,0,0    },
    {0,0.398962,0.407097,0.424254,0.429198,0.430203,0.454093,0.462934,0.472055,0.501146,0.515698,0.434509,0.421203,0.36,0.236967,0,0,0    },
    {0,0.459728,0.47549,0.480579,0.492947,0.474403,0.495751,0.509936,0.559598,0.523726,0.526846,0.498762,0.45443,0.406548,0.296407,0,0,0    },
    {0,0.504753,0.506617,0.527469,0.525429,0.53662,0.540183,0.544218,0.556338,0.569164,0.584746,0.538095,0.461538,0.415144,0.287062,0,0,0    },
    {0,0.526718,0.55064,0.548759,0.551923,0.564276,0.582182,0.586261,0.5724,0.558647,0.581095,0.566775,0.50348,0.449032,0.398329,0,0,0    },
    {0,0.59226,0.599752,0.602319,0.608436,0.614736,0.613834,0.616592,0.637575,0.61983,0.599051,0.594096,0.544289,0.477032,0.392688,0,0,0    },
    {0,0.642676,0.638867,0.648071,0.646218,0.6534,0.655112,0.647093,0.661243,0.645762,0.6415,0.599778,0.569536,0.51764,0.477008,0,0,0    },
    {0,0.67616,0.657084,0.671827,0.681963,0.686349,0.674088,0.683732,0.663204,0.676509,0.65232,0.618622,0.573684,0.554557,0.474965,0,0,0    },
    {0,0.680502,0.689305,0.687628,0.699324,0.698443,0.687144,0.687303,0.683502,0.679358,0.666302,0.640071,0.603321,0.568953,0.478161,0,0,0    },
    {0,0.689676,0.698681,0.692606,0.708931,0.703915,0.703441,0.703262,0.688376,0.671541,0.682586,0.622165,0.581917,0.598479,0.505532,0,0,0    },
    {0,0.70734,0.704192,0.719124,0.707993,0.713122,0.70068,0.708506,0.690969,0.705059,0.684974,0.677336,0.638438,0.622318,0.562552,0,0,0    },
    {0,0.771762,0.766592,0.775936,0.762969,0.754254,0.7376,0.739908,0.741391,0.73278,0.726705,0.709813,0.693311,0.678955,0.634635,0,0,0    },
    {0,0.843744,0.830654,0.828383,0.827343,0.814767,0.797021,0.782645,0.77473,0.770152,0.757542,0.739112,0.707985,0.704926,0.661264,0,0,0    },
    {0,0.88579,0.886454,0.875253,0.86501,0.854202,0.836181,0.815955,0.808441,0.782235,0.756273,0.741429,0.719828,0.690706,0.664931,0,0,0    },
    {0,0.910634,0.903612,0.910331,0.902906,0.891953,0.874939,0.848367,0.828799,0.807793,0.777312,0.748468,0.700447,0.678364,0.631693,0,0,0    },
    {0,0.897457,0.890116,0.894617,0.886484,0.873075,0.867882,0.842102,0.822961,0.797287,0.760274,0.728479,0.693243,0.657377,0.594426,0,0,0}
  };


  Int_t tmpPtBin = FindBinMuon( Pt , ptBins, 15);
  Int_t tmpEtaBin = FindBinMuon( Eta , etaBins, 16);
  return Efficiency[tmpPtBin][tmpEtaBin];
}
