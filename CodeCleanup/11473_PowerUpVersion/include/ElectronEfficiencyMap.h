unsigned int FindElectronEfficiencyBin( double value, double bins[], unsigned int nbins) {
  unsigned int nbinboundaries = nbins+1;
  unsigned int bin = 0;
  for (unsigned int i=0; i < nbinboundaries; ++i) {
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


double GetElectronEfficiencyPtEtaPhi(double Pt, double Eta, double Phi) {

  double ptBins[16] = {5,6,7,8,9,10,12,14,16,18,20,25,30,35,40,50};
  double etaBins[17] = {0,0.2,0.4,0.6,0.8,1,1.2,1.4442,1.566,1.8,2,2.1,2.2,2.3,2.4,2.5,2.6};
  double phiBins[13] = {-3.2,-2.5,-2,-1.5,-1,-0.5,0,0.5,1,1.5,2,2.5,3.2};


  double Efficiency[17][18][14]  = {
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.0508475,0.0930233,0.0625,0.0517241,0.04,0,0.0769231,0.0540541,0.0188679,0.08,0,0.0138889,0},
      {0,0.0285714,0.0377358,0.0491803,0.0526316,0.0204082,0.0204082,0.05,0.047619,0.0425532,0.0508475,0.0652174,0.0151515,0},
      {0,0,0,0.0677966,0.037037,0.1,0.0238095,0,0.046875,0.0425532,0.037037,0,0.0757576,0},
      {0,0.047619,0.0408163,0,0.04,0.0555556,0.02,0.15873,0.0196078,0.0727273,0.0392157,0.0384615,0.0555556,0},
      {0,0.0980392,0.0444444,0.0263158,0.047619,0.0727273,0.0816327,0.0222222,0.0196078,0.0465116,0.0606061,0.0178571,0.0377358,0},
      {0,0.0645161,0.108696,0.0243902,0.05,0,0.0681818,0.0344828,0.0465116,0.047619,0.0222222,0.0512821,0.0508475,0},
      {0,0.025974,0,0,0.0454545,0.037037,0.0273973,0.0350877,0.0465116,0,0.05,0.0754717,0.0447761,0},
      {0,0.027027,0,0,0.0526316,0,0.05,0,0.0333333,0,0.0625,0,0,0},
      {0,0.0394737,0.0833333,0.0384615,0.02,0,0.0392157,0.0178571,0.0454545,0,0,0.0263158,0,0},
      {0,0.04,0,0.04,0,0.030303,0.05,0.0238095,0.0444444,0.027027,0.0227273,0.0196078,0.0338983,0},
      {0,0.0606061,0.0909091,0,0.0454545,0.04,0,0,0,0,0,0.05,0,0},
      {0,0,0,0,0.0526316,0,0,0,0.05,0.047619,0.047619,0,0,0},
      {0,0,0.047619,0,0.0833333,0,0,0,0,0,0,0,0,0},
      {0,0.0833333,0,0,0,0,0,0,0.0555556,0,0,0.0526316,0,0},
      {0,0,0.0416667,0,0.0526316,0,0.0555556,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0.0666667,0.03125,0.0625,0,0.0416667,0.111111,0,0.115385,0,0.0294118,0.025,0},
      {0,0.0645161,0.0454545,0.0322581,0.0606061,0,0.03125,0,0.047619,0.0434783,0.05,0.0833333,0.030303,0},
      {0,0.0731707,0.121212,0,0.0384615,0,0.04,0,0.0322581,0,0,0.0434783,0.0740741,0},
      {0,0,0.0952381,0.111111,0,0.0416667,0.047619,0,0,0,0,0.0416667,0,0},
      {0,0,0,0.0625,0,0.08,0.0555556,0,0.0952381,0.0666667,0,0.0833333,0,0},
      {0,0.0588235,0.0526316,0.0434783,0,0.0869565,0.0322581,0.0909091,0,0.0952381,0.0416667,0.0588235,0.0322581,0},
      {0,0.0967742,0.0416667,0,0.0769231,0.0588235,0,0.129032,0.0416667,0.05,0,0.0512821,0.0571429,0},
      {0,0,0.125,0,0.111111,0.25,0,0,0,0,0.153846,0,0.0666667,0},
      {0,0.1,0.037037,0,0.047619,0.08,0,0,0,0.0666667,0.04,0,0.04,0},
      {0,0.0645161,0,0,0.1,0.0588235,0.0526316,0,0.05,0.047619,0,0,0.0555556,0},
      {0,0.0666667,0.111111,0.0666667,0.125,0,0,0.333333,0,0,0.142857,0,0.0833333,0},
      {0,0,0.0909091,0,0,0.363636,0,0.0714286,0,0,0,0.125,0,0},
      {0,0,0,0,0,0.1,0,0,0,0,0,0,0,0},
      {0,0.222222,0,0,0,0.285714,0,0,0,0.230769,0.25,0,0,0},
      {0,0,0,0.25,0,0,0,0,0.1,0,0.125,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.0810811,0.0625,0.0666667,0.1,0.189189,0.111111,0.0540541,0.128205,0.0416667,0.0967742,0.16,0.03125,0},
      {0,0.0526316,0.0666667,0.15625,0.166667,0,0.133333,0.0645161,0.133333,0.152174,0.0909091,0.212121,0.025641,0},
      {0,0.186047,0.0740741,0.25,0.0967742,0.153846,0.0909091,0,0.0645161,0.172414,0.16129,0.142857,0.15,0},
      {0,0.0882353,0.03125,0.0454545,0.142857,0.0384615,0.125,0.15625,0.0322581,0.0909091,0.0571429,0,0.135135,0},
      {0,0.03125,0.037037,0.0909091,0.230769,0.0571429,0.0882353,0.115385,0.107143,0.08,0.0869565,0.12,0.142857,0},
      {0,0.111111,0.0740741,0.0952381,0.206897,0.04,0.0333333,0.047619,0.0666667,0.08,0.25,0.0384615,0.0882353,0},
      {0,0.102564,0.133333,0.12,0.15,0.0571429,0.04,0.131579,0.0384615,0,0.0769231,0,0.0638298,0},
      {0,0.0526316,0,0.105263,0.15,0.117647,0,0.153846,0,0.105263,0,0,0.133333,0},
      {0,0.233333,0.111111,0.277778,0.142857,0.172414,0,0.0588235,0.0769231,0.12,0.129032,0.272727,0.0666667,0},
      {0,0.173913,0.24,0.133333,0.2,0.148148,0.0588235,0.142857,0.1,0.333333,0.0769231,0.157895,0.173913,0},
      {0,0.307692,0,0.222222,0.25,0.181818,0.25,0.4,0.0833333,0,0,0,0.0769231,0},
      {0,0,0.142857,0,0.142857,0,0.111111,0.125,0.2,0.285714,0,0.166667,0.1,0},
      {0,0.1,0.272727,0.2,0,0.307692,0.125,0,0.25,0.0769231,0.0769231,0.2,0.153846,0},
      {0,0.125,0,0.0833333,0,0,0,0.25,0.142857,0,0.285714,0.166667,0,0},
      {0,0.333333,0,0.222222,0,0.25,0,0,0,0,0.133333,0.25,0.125,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.463415,0.424242,0.459459,0.444444,0.560976,0.558824,0.428571,0.384615,0.566667,0.475,0.514286,0.410256,0},
      {0,0.564103,0.538462,0.522727,0.461538,0.47619,0.62069,0.545455,0.575758,0.457143,0.517241,0.540541,0.333333,0},
      {0,0.673913,0.55,0.424242,0.658537,0.714286,0.606061,0.6,0.45,0.609756,0.45,0.666667,0.638889,0},
      {0,0.617647,0.483871,0.608696,0.5,0.567568,0.594595,0.705882,0.685714,0.592593,0.535714,0.5,0.622222,0},
      {0,0.519231,0.423077,0.447368,0.391304,0.527778,0.377778,0.577778,0.47619,0.571429,0.547619,0.685714,0.479167,0},
      {0,0.473684,0.575758,0.53125,0.347826,0.47619,0.448276,0.387097,0.419355,0.421053,0.48,0.363636,0.363636,0},
      {0,0.513514,0.25,0.371429,0.346154,0.4,0.357143,0.583333,0.294118,0.375,0.272727,0.230769,0.45,0},
      {0,0.25,0.3125,0.176471,0.230769,0.166667,0.166667,0.32,0.230769,0.2,0.4,0.272727,0.117647,0},
      {0,0.47619,0.390244,0.4,0.344828,0.304348,0.242424,0.296296,0.333333,0.3,0.21875,0.454545,0.424242,0},
      {0,0.193548,0.388889,0.484848,0.290323,0.416667,0.44,0.5,0.333333,0.7,0.444444,0.518519,0.6,0},
      {0,0.416667,0.4,0,0.3,0.75,0.25,0.25,0.222222,0.461538,0.454545,0.538462,0.285714,0},
      {0,0.0909091,0.0909091,0.428571,0.363636,0.285714,0.166667,0.6,0.545455,0.4,0.375,0.454545,0.3,0},
      {0,0.214286,0.1,0.25,0.0909091,0.2,0.2,0.222222,0.5,0.142857,0.375,0.375,0.214286,0},
      {0,0,0,0,0.2,0.571429,0.0909091,0,0.375,0.166667,0.142857,0.285714,0.125,0},
      {0,0,0,0,0.3,0,0,0.2,0,0.333333,0.142857,0.375,0.363636,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.590909,0.619048,0.564103,0.722222,0.6,0.613636,0.653846,0.530612,0.552632,0.727273,0.648649,0.684211,0},
      {0,0.657895,0.666667,0.68,0.714286,0.705882,0.769231,0.757576,0.636364,0.615385,0.634146,0.611111,0.824561,0},
      {0,0.769231,0.818182,0.682927,0.690476,0.627451,0.705882,0.772727,0.837209,0.694444,0.529412,0.818182,0.636364,0},
      {0,0.714286,0.727273,0.659091,0.625,0.777778,0.818182,0.693878,0.793103,0.787879,0.62963,0.685714,0.85,0},
      {0,0.722222,0.72973,0.615385,0.677419,0.647059,0.7,0.658537,0.85,0.588235,0.636364,0.634146,0.679245,0},
      {0,0.690476,0.666667,0.703704,0.578947,0.736842,0.529412,0.653846,0.6,0.709677,0.631579,0.638889,0.722222,0},
      {0,0.613636,0.590909,0.5,0.5,0.606061,0.705882,0.578947,0.741935,0.435897,0.46875,0.578947,0.574074,0},
      {0,0.192308,0.380952,0.3,0.230769,0.133333,0.294118,0.384615,0.26087,0.0833333,0.153846,0.444444,0.291667,0},
      {0,0.393939,0.444444,0.392857,0.470588,0.472222,0.615385,0.444444,0.512821,0.45,0.6,0.394737,0.481481,0},
      {0,0.5,0.555556,0.625,0.517241,0.548387,0.5,0.380952,0.346154,0.571429,0.5,0.333333,0.652174,0},
      {0,0.266667,0.454545,0.421053,0.545455,0.6,0.8,0.7,0.571429,0.666667,0.307692,0.5,0.571429,0},
      {0,0.5,0.416667,0.0909091,0.181818,0.333333,0.357143,0.357143,0.384615,0.571429,0.266667,0.769231,0.714286,0},
      {0,0.2,0.375,0.1,0.181818,0.3,0.666667,0.285714,0.25,0.625,0.384615,0.7,0.272727,0},
      {0,0.375,0,0.125,0.222222,0.222222,0.272727,0.2,0.375,0.6,0.625,0.333333,0.1,0},
      {0,0.2,0,0.214286,0.222222,0.5,0.25,0.142857,0.333333,0.3125,0.222222,0.25,0.555556,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.66,0.72093,0.828571,0.647059,0.7,0.756098,0.609756,0.631579,0.810811,0.769231,0.666667,0.666667,0},
      {0,0.830508,0.775,0.72549,0.810811,0.815789,0.848485,0.75,0.837838,0.791667,0.8,0.809524,0.88,0},
      {0,0.795455,0.684211,0.756757,0.702703,0.767442,0.727273,0.828571,0.736842,0.734694,0.769231,0.767442,0.765957,0},
      {0,0.8,0.75,0.735294,0.71875,0.825,0.6875,0.72093,0.8,0.72973,0.769231,0.796296,0.742857,0},
      {0,0.711111,0.633333,0.74359,0.74359,0.785714,0.815789,0.775,0.823529,0.695652,0.71875,0.676471,0.811321,0},
      {0,0.526316,0.666667,0.833333,0.694444,0.8125,0.75,0.575758,0.613636,0.875,0.666667,0.694444,0.697674,0},
      {0,0.644068,0.615385,0.638298,0.698113,0.76087,0.612903,0.681818,0.608696,0.829268,0.59375,0.71875,0.553571,0},
      {0,0.4,0.181818,0.157895,0.35,0.478261,0.636364,0.352941,0.222222,0.285714,0.315789,0.263158,0.304348,0},
      {0,0.684211,0.689655,0.666667,0.657143,0.425,0.485714,0.542857,0.513514,0.71875,0.514286,0.866667,0.611111,0},
      {0,0.733333,0.411765,0.555556,0.789474,0.761905,0.72,0.65,0.454545,0.357143,0.62963,0.566667,0.571429,0},
      {0,0,0.666667,0.416667,0.571429,0.545455,0.6,0.363636,0.727273,0.411765,0.555556,0.333333,0.727273,0},
      {0,0.466667,0.571429,0.222222,0.5625,0.5,0.625,0.285714,0.222222,0.6,0.538462,0.6,0.466667,0},
      {0,0.333333,0.230769,0.333333,0.142857,0.375,0.2,0.444444,0.25,0,0.6,0.3,0.571429,0},
      {0,0,0.375,0.25,0.333333,0.6,0.166667,0.125,0.428571,0.555556,0.5,0.833333,0.272727,0},
      {0,0.1,0.25,0.222222,0.111111,0.142857,0.25,0.285714,0.333333,0.5,0.181818,0,0.2,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.841667,0.76087,0.835052,0.84,0.861702,0.762887,0.840909,0.77907,0.763889,0.785714,0.860759,0.846847,0},
      {0,0.878261,0.815217,0.905405,0.873418,0.818182,0.894231,0.831579,0.875,0.84375,0.83908,0.847826,0.874016,0},
      {0,0.836207,0.821053,0.87037,0.867347,0.866667,0.865169,0.771739,0.860215,0.891892,0.904762,0.820225,0.838384,0},
      {0,0.836207,0.848101,0.850575,0.835052,0.817204,0.878049,0.848485,0.879518,0.833333,0.779221,0.848837,0.879032,0},
      {0,0.82,0.918605,0.87013,0.843373,0.833333,0.85567,0.842697,0.903846,0.8,0.75,0.833333,0.784946,0},
      {0,0.767442,0.822581,0.756757,0.714286,0.783784,0.695652,0.836066,0.8375,0.791667,0.807692,0.782051,0.735849,0},
      {0,0.72381,0.75641,0.710526,0.75,0.786667,0.666667,0.831169,0.727273,0.689655,0.787234,0.735632,0.728155,0},
      {0,0.386364,0.513514,0.536585,0.410256,0.4375,0.461538,0.62963,0.282609,0.461538,0.452381,0.44186,0.388889,0},
      {0,0.606742,0.671233,0.625,0.607595,0.623188,0.657895,0.626667,0.712329,0.608696,0.697674,0.628205,0.649351,0},
      {0,0.641791,0.754717,0.707317,0.622222,0.777778,0.755102,0.638889,0.596774,0.574074,0.68,0.659574,0.671642,0},
      {0,0.807692,0.551724,0.611111,0.52381,0.62069,0.6,0.5,0.52381,0.684211,0.571429,0.730769,0.923077,0},
      {0,0.631579,0.647059,0.277778,0.64,0.733333,0.52,0.571429,0.681818,0.47619,0.473684,0.590909,0.689655,0},
      {0,0.44,0.428571,0.473684,0.333333,0.583333,0.333333,0.357143,0.466667,0.388889,0.5,0.416667,0.684211,0},
      {0,0.296296,0.285714,0.416667,0.333333,0.458333,0.529412,0.407407,0.5,0.6,0.285714,0.5,0.586207,0},
      {0,0.178571,0.26087,0.181818,0.26087,0.315789,0.375,0.380952,0.333333,0.416667,0.210526,0.25,0.368421,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.825397,0.884211,0.89,0.880952,0.87619,0.888889,0.903614,0.817204,0.895833,0.905263,0.858586,0.849558,0},
      {0,0.865546,0.890244,0.816092,0.875,0.918367,0.916667,0.88172,0.873786,0.871429,0.825,0.909091,0.863248,0},
      {0,0.873874,0.868687,0.88172,0.819149,0.858696,0.882353,0.847826,0.870968,0.887324,0.866667,0.920455,0.903509,0},
      {0,0.928058,0.907692,0.88,0.845361,0.833333,0.887755,0.931818,0.853933,0.818182,0.931507,0.847826,0.912621,0},
      {0,0.852941,0.869048,0.883117,0.880952,0.897727,0.873016,0.825397,0.907895,0.842105,0.868421,0.901408,0.951923,0},
      {0,0.833333,0.819444,0.833333,0.851351,0.876712,0.885714,0.938462,0.861111,0.848485,0.732394,0.827586,0.811321,0},
      {0,0.769912,0.825243,0.878049,0.757895,0.764045,0.756757,0.781609,0.879121,0.759036,0.84507,0.777778,0.830189,0},
      {0,0.44898,0.59375,0.529412,0.375,0.571429,0.418605,0.407407,0.625,0.5,0.344828,0.526316,0.533333,0},
      {0,0.703297,0.701493,0.677419,0.672131,0.653846,0.794118,0.671642,0.726027,0.650794,0.710145,0.711538,0.657407,0},
      {0,0.7125,0.791667,0.793103,0.6875,0.754386,0.711864,0.758621,0.759259,0.72549,0.596491,0.784314,0.777778,0},
      {0,0.821429,0.76,0.576923,0.703704,0.956522,0.857143,0.863636,0.724138,0.590909,0.8,0.55,0.774194,0},
      {0,0.558824,0.703704,0.478261,0.478261,0.625,0.619048,0.882353,0.636364,0.666667,0.631579,0.545455,0.833333,0},
      {0,0.454545,0.714286,0.625,0.368421,0.526316,0.8,0.266667,0.642857,0.571429,0.85,0.521739,0.9375,0},
      {0,0.3,0.636364,0.375,0.380952,0.578947,0.35,0.478261,0.65,0.625,0.571429,0.5,0.555556,0},
      {0,0.263158,0.166667,0.142857,0.222222,0.25,0.5,0.6,0.642857,0.352941,0.416667,0.352941,0.411765,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.912698,0.896907,0.903614,0.846154,0.968421,0.950495,0.902439,0.782609,0.89,0.857143,0.863636,0.896,0},
      {0,0.864286,0.824074,0.902778,0.851852,0.885496,0.884211,0.896552,0.8625,0.964286,0.934579,0.947368,0.903846,0},
      {0,0.881818,0.860215,0.920455,0.914286,0.891892,0.881188,0.96875,0.934783,0.891089,0.880435,0.891304,0.901639,0},
      {0,0.911504,0.897727,0.847059,0.912088,0.923913,0.930556,0.912621,0.9125,0.916667,0.910256,0.942857,0.916667,0},
      {0,0.896552,0.965517,0.920455,0.928571,0.923077,0.948052,0.909091,0.873418,0.906977,0.852273,0.855263,0.919192,0},
      {0,0.861386,0.863636,0.84375,0.842105,0.896552,0.7875,0.947368,0.895522,0.810811,0.890411,0.90411,0.872549,0},
      {0,0.853448,0.797297,0.835443,0.930556,0.82716,0.857143,0.864198,0.849462,0.865672,0.846154,0.818182,0.794872,0},
      {0,0.675676,0.83871,0.541667,0.571429,0.5,0.463415,0.622642,0.40625,0.594595,0.580645,0.558824,0.5625,0},
      {0,0.782609,0.784615,0.681159,0.805556,0.725806,0.703704,0.8,0.714286,0.779221,0.772727,0.786667,0.807229,0},
      {0,0.723404,0.809524,0.826087,0.763158,0.833333,0.791667,0.833333,0.729167,0.803922,0.833333,0.893617,0.843137,0},
      {0,0.8,0.869565,0.724138,0.571429,0.777778,0.736842,0.758621,0.666667,0.863636,0.869565,0.666667,0.785714,0},
      {0,0.55,0.631579,0.5,0.833333,0.76,0.708333,0.647059,0.5,0.888889,0.807692,0.85,0.733333,0},
      {0,0.37037,0.785714,0.470588,0.409091,0.7,0.625,0.75,0.636364,0.578947,0.647059,0.666667,0.777778,0},
      {0,0.444444,0.6,0.45,0.5,0.529412,0.714286,0.5,0.823529,0.666667,0.666667,0.73913,0.586207,0},
      {0,0.153846,0.352941,0.6,0.352941,0.444444,0.363636,0.133333,0.428571,0.785714,0.714286,0.625,0.588235,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.873684,0.870588,0.928571,0.897727,0.892857,0.906542,0.9375,0.870588,0.930693,0.855263,0.913043,0.894737,0},
      {0,0.963303,0.931818,0.95,0.871795,0.909091,0.938272,0.850575,0.880435,0.923913,0.884615,0.956522,0.945455,0},
      {0,0.91453,0.918605,0.925,0.873684,0.905882,0.897727,0.94186,0.902778,0.925926,0.901408,0.886364,0.918182,0},
      {0,0.939394,0.934211,0.947368,0.911392,0.804878,0.913043,0.901408,0.896104,0.849315,0.975,0.94898,0.918919,0},
      {0,0.885714,0.947368,0.898734,0.902174,0.876923,0.886076,0.915254,0.927536,0.90411,0.802632,0.915663,0.831579,0},
      {0,0.823529,0.940299,0.864865,0.842105,0.88,0.90625,0.911765,0.867647,0.9,0.943182,0.924731,0.878788,0},
      {0,0.86,0.857143,0.866667,0.831325,0.869565,0.785714,0.928571,0.908046,0.879518,0.833333,0.896104,0.865169,0},
      {0,0.659091,0.525,0.5,0.55814,0.627907,0.425,0.540541,0.6,0.517241,0.65625,0.622222,0.710526,0},
      {0,0.807018,0.731343,0.793651,0.782609,0.688525,0.769231,0.818182,0.8,0.704918,0.866667,0.78,0.819444,0},
      {0,0.836364,0.833333,0.72,0.75,0.918919,0.8,0.897436,0.870968,0.762712,0.814815,0.897436,0.890909,0},
      {0,0.74359,0.789474,0.5625,0.722222,0.826087,0.647059,0.8,0.954545,0.684211,0.695652,0.952381,0.740741,0},
      {0,0.666667,0.791667,0.684211,0.85,0.777778,0.652174,0.846154,0.823529,0.555556,0.785714,0.857143,0.791667,0},
      {0,0.708333,0.636364,0.590909,0.666667,0.777778,0.842105,0.923077,0.789474,0.4375,0.615385,0.9,0.740741,0},
      {0,0.538462,0.666667,0.55,0.4,0.777778,0.555556,0.545455,0.789474,0.823529,0.666667,0.818182,0.555556,0},
      {0,0.45,0.384615,0.416667,0.111111,0.25,0.705882,0.181818,0.529412,0.461538,0.647059,0.4,0.538462,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.887755,0.842697,0.811765,0.935065,0.912281,0.911392,0.902439,0.844156,0.911392,0.920635,0.845238,0.961905,0},
      {0,0.913043,0.871795,0.948718,0.887324,0.929412,0.898551,0.9,0.882353,0.901235,0.921348,0.94186,0.968421,0},
      {0,0.97561,0.888889,0.881579,0.875,0.951807,0.921053,0.915663,0.948276,0.9375,0.923077,0.925926,0.933962,0},
      {0,0.945652,0.883721,0.897059,0.896552,0.911392,0.987654,0.936709,0.948718,0.915493,0.912281,0.985075,0.956522,0},
      {0,0.885714,0.934211,0.932203,0.909091,0.942857,0.95082,0.966667,0.892308,0.920635,0.92,0.90411,0.876543,0},
      {0,0.95082,0.932203,0.91358,0.859375,0.869565,0.881579,0.927273,0.796875,0.910448,0.803279,0.85,0.850746,0},
      {0,0.897959,0.881579,0.789474,0.901408,0.918033,0.870588,0.891892,0.871795,0.898734,0.893939,0.909091,0.916667,0},
      {0,0.388889,0.518519,0.727273,0.6,0.565217,0.571429,0.8,0.666667,0.62069,0.5,0.75,0.46,0},
      {0,0.92,0.813559,0.781818,0.895522,0.885246,0.814815,0.84127,0.74,0.807692,0.816667,0.696429,0.8,0},
      {0,0.803922,0.714286,0.852941,0.772727,0.8125,0.891304,0.894737,0.8,0.804348,0.761905,0.794118,0.851852,0},
      {0,0.705882,0.714286,0.866667,0.909091,0.833333,0.846154,0.764706,0.894737,0.857143,0.956522,0.866667,0.814815,0},
      {0,0.826087,0.826087,0.647059,0.705882,0.8125,0.692308,0.9,0.666667,0.857143,0.909091,0.8,0.777778,0},
      {0,0.681818,0.777778,0.733333,0.411765,0.692308,0.769231,0.684211,0.8,0.761905,0.583333,0.545455,0.631579,0},
      {0,0.769231,0.533333,0.642857,0.526316,0.615385,0.722222,0.6875,0.615385,0.846154,0.666667,0.866667,0.466667,0},
      {0,0.105263,0.3125,0.111111,0.666667,0.6,0.625,0.3,0.65,0.8,0.4,0.727273,0.727273,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.945148,0.949153,0.917647,0.910112,0.921687,0.915663,0.924731,0.900552,0.915254,0.871166,0.946429,0.893939,0},
      {0,0.933333,0.890909,0.946746,0.93865,0.966102,0.95858,0.88535,0.936047,0.939394,0.913043,0.935484,0.943662,0},
      {0,0.939086,0.955696,0.954545,0.901316,0.939597,0.935714,0.953757,0.937888,0.910256,0.907895,0.952756,0.930108,0},
      {0,0.940594,0.93038,0.92,0.939024,0.954839,0.943662,0.962687,0.882353,0.952,0.955128,0.935714,0.928571,0},
      {0,0.929412,0.945205,0.902778,0.948718,0.9375,0.948276,0.916084,0.937931,0.95,0.919708,0.930556,0.886364,0},
      {0,0.898734,0.927536,0.882812,0.898438,0.872881,0.946154,0.948052,0.893617,0.923664,0.884058,0.892857,0.897436,0},
      {0,0.86631,0.878788,0.898649,0.899371,0.843972,0.87013,0.890511,0.890411,0.915033,0.838323,0.890756,0.908108,0},
      {0,0.614583,0.545455,0.577465,0.6,0.541667,0.640625,0.655172,0.615385,0.676471,0.607143,0.565217,0.609091,0},
      {0,0.840909,0.910569,0.846847,0.809524,0.791045,0.914062,0.909091,0.796117,0.850877,0.855932,0.918182,0.869231,0},
      {0,0.846939,0.888889,0.845238,0.896907,0.865169,0.878049,0.866667,0.898876,0.829268,0.785714,0.898734,0.897638,0},
      {0,0.807692,0.829268,0.897436,0.894737,0.742857,0.853659,0.756757,0.893617,0.75,0.875,0.904762,0.823529,0},
      {0,0.785714,0.730769,0.612903,0.622222,0.8,0.90625,0.75,0.878788,0.848485,0.857143,0.625,0.822222,0},
      {0,0.736842,0.724138,0.62963,0.681818,0.744186,0.8,0.666667,0.72973,0.763158,0.709677,0.857143,0.829787,0},
      {0,0.666667,0.703704,0.6,0.448276,0.8125,0.6875,0.521739,0.761905,0.71875,0.633333,0.75,0.723404,0},
      {0,0.34375,0.48,0.483871,0.565217,0.586207,0.542857,0.32,0.666667,0.64,0.730769,0.5,0.526316,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.920455,0.948387,0.931507,0.905405,0.932836,0.937984,0.86014,0.87234,0.885246,0.927152,0.921429,0.911602,0},
      {0,0.922156,0.944882,0.917355,0.949275,0.941935,0.929134,0.912409,0.907801,0.95302,0.959184,0.96875,0.927778,0},
      {0,0.945122,0.941667,0.935484,0.924812,0.955882,0.936508,0.96063,0.933333,0.968992,0.944882,0.904412,0.949153,0},
      {0,0.95,0.948148,0.921739,0.938356,0.921739,0.93,0.91791,0.934783,0.923077,0.887931,0.939655,0.964286,0},
      {0,0.953846,0.907407,0.922481,0.888,0.909091,0.97479,0.953271,0.961538,0.941667,0.911765,0.884892,0.925676,0},
      {0,0.899281,0.927083,0.919643,0.913043,0.969697,0.903226,0.938144,0.931034,0.924528,0.95,0.912621,0.916031,0},
      {0,0.874214,0.962406,0.864865,0.887931,0.915888,0.87963,0.951613,0.884892,0.883721,0.912752,0.9375,0.888889,0},
      {0,0.58209,0.622642,0.6,0.672131,0.5,0.577778,0.745098,0.538462,0.65625,0.591837,0.653846,0.704918,0},
      {0,0.904,0.892473,0.880435,0.828283,0.757576,0.864078,0.908046,0.891566,0.912621,0.853448,0.852273,0.902439,0},
      {0,0.85567,0.871429,0.898551,0.796296,0.909091,0.902778,0.907895,0.903226,0.971014,0.813953,0.807018,0.928571,0},
      {0,0.694444,0.794872,0.857143,0.975,0.833333,0.964286,0.820513,0.92,0.9,0.806452,0.8,0.777778,0},
      {0,0.789474,0.777778,0.818182,0.714286,0.935484,0.928571,0.8,0.806452,0.909091,0.90625,0.84375,0.935484,0},
      {0,0.613636,0.793103,0.777778,0.653846,0.863636,0.846154,0.6875,0.75,0.793103,0.777778,0.891892,0.685714,0},
      {0,0.666667,0.7,0.62069,0.5,0.772727,0.714286,0.652174,0.736842,0.8,0.722222,0.882353,0.7,0},
      {0,0.382353,0.416667,0.583333,0.611111,0.653846,0.473684,0.611111,0.722222,0.714286,0.590909,0.388889,0.592593,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.915254,0.945312,0.886364,0.93985,0.956522,0.897436,0.944444,0.846154,0.945312,0.891473,0.945205,0.969512,0},
      {0,0.939597,0.937008,0.946154,0.903704,0.973913,0.942857,0.846626,0.982759,0.97479,0.934641,0.953846,0.963415,0},
      {0,0.946108,0.951389,0.968,0.953846,0.954887,0.923077,0.954955,0.944,0.92126,0.957265,0.930233,0.93617,0},
      {0,0.940789,0.957983,0.948276,0.947826,0.896552,0.923664,0.946429,0.971223,0.924528,0.921053,0.992126,0.935294,0},
      {0,0.969325,0.934783,0.97561,0.87619,0.933333,0.962264,0.944954,0.952756,0.962264,0.907563,0.928571,0.89172,0},
      {0,0.941606,0.918919,0.915254,0.952,0.906542,0.87963,0.894737,0.88,0.911765,0.899083,0.947368,0.942857,0},
      {0,0.943038,0.937984,0.931034,0.882353,0.930435,0.878261,0.908257,0.915385,0.87963,0.957983,0.934307,0.949275,0},
      {0,0.68,0.571429,0.767442,0.658537,0.55102,0.62963,0.734694,0.632653,0.595238,0.701754,0.666667,0.621212,0},
      {0,0.904,0.901099,0.910256,0.858696,0.75,0.74359,0.911392,0.8875,0.864198,0.893617,0.908163,0.896226,0},
      {0,0.868687,0.85,0.844828,0.794521,0.936508,0.861538,0.896104,0.965517,0.909091,0.857143,0.890411,0.903614,0},
      {0,0.926829,0.758621,0.954545,0.769231,0.814815,0.8,0.83871,0.896552,0.882353,0.90625,0.83871,0.804348,0},
      {0,0.705882,0.794118,0.714286,0.705882,0.73913,0.827586,0.851852,0.807692,0.769231,0.733333,0.805556,0.894737,0},
      {0,0.741935,0.606061,0.944444,0.653846,0.896552,0.727273,0.823529,0.631579,0.833333,0.866667,0.913043,0.763158,0},
      {0,0.655172,0.625,0.764706,0.681818,0.8,0.733333,0.6875,0.73913,0.933333,0.9,0.75,0.888889,0},
      {0,0.615385,0.666667,0.307692,0.615385,0.6875,0.642857,0.55,0.65,0.75,0.791667,0.538462,0.68,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.915344,0.926174,0.917355,0.931034,0.930435,0.924528,0.932836,0.88189,0.950311,0.927536,0.956522,0.945122,0},
      {0,0.965318,0.957983,0.968504,0.963235,0.97541,0.961538,0.92126,0.948276,0.951724,0.942149,0.978417,0.976331,0},
      {0,0.96319,0.90625,0.954545,0.95082,0.963636,0.971429,0.968,0.960317,0.976923,0.929204,0.930556,0.968354,0},
      {0,0.916129,0.911765,0.926829,0.96,0.863248,0.9375,0.932773,0.948718,0.936,0.933884,0.933333,0.968153,0},
      {0,0.922581,0.941748,0.954545,0.932692,0.944444,0.958678,0.957265,0.854545,0.951456,0.915094,0.937008,0.863014,0},
      {0,0.944828,0.941748,0.953488,0.905263,0.940594,0.931373,0.93578,0.946429,0.915888,0.925532,0.914286,0.909091,0},
      {0,0.934211,0.9375,0.941176,0.923077,0.904,0.884298,0.915094,0.900901,0.902985,0.854167,0.95082,0.907692,0},
      {0,0.646154,0.59322,0.591837,0.659574,0.537313,0.62963,0.647059,0.625,0.672727,0.641509,0.678571,0.618421,0},
      {0,0.895238,0.880734,0.772277,0.847059,0.831579,0.914286,0.91954,0.824742,0.875,0.85567,0.902913,0.883721,0},
      {0,0.864198,0.967742,0.931034,0.910256,0.815789,0.816327,0.868421,0.857143,0.903226,0.914286,0.968254,0.956522,0},
      {0,0.805556,0.909091,0.892857,0.903226,0.791667,0.88,0.705882,0.884615,0.888889,0.911765,0.71875,0.893617,0},
      {0,0.75,0.75,0.703704,0.615385,0.933333,0.933333,0.645161,1,0.909091,0.814815,0.884615,0.882353,0},
      {0,0.736842,0.708333,0.619048,0.709677,0.714286,0.9,0.724138,0.894737,0.818182,0.785714,0.84,0.777778,0},
      {0,0.641026,0.818182,0.789474,0.444444,0.842105,0.68,0.882353,0.863636,0.821429,0.666667,0.736842,0.821429,0},
      {0,0.387097,0.411765,0.5,0.533333,0.6,0.655172,0.56,0.6875,0.818182,0.6,0.68,0.551724,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.916084,0.9375,0.942731,0.940367,0.932039,0.933333,0.927039,0.861905,0.926087,0.895652,0.968468,0.939394,0},
      {0,0.954064,0.935185,0.932692,0.947619,0.942584,0.944162,0.898618,0.965,0.942708,0.958525,0.926471,0.942982,0},
      {0,0.94382,0.942857,0.935484,0.941704,0.958904,0.938326,0.944206,0.961165,0.947115,0.940928,0.962766,0.96063,0},
      {0,0.949416,0.941748,0.924883,0.92,0.938462,0.928571,0.962085,0.938776,0.948113,0.910448,0.985075,0.940711,0},
      {0,0.948207,0.936842,0.961111,0.97,0.955665,0.962162,0.947115,0.956044,0.959064,0.915,0.9375,0.907749,0},
      {0,0.930041,0.953488,0.957895,0.920732,0.949045,0.936782,0.918478,0.900524,0.949153,0.909091,0.936782,0.959016,0},
      {0,0.891892,0.92381,0.897561,0.921212,0.914141,0.892308,0.89604,0.880503,0.925532,0.923913,0.918033,0.887597,0},
      {0,0.672269,0.659794,0.619565,0.651163,0.551282,0.683673,0.733333,0.635135,0.705128,0.630952,0.67033,0.589744,0},
      {0,0.913978,0.926471,0.899225,0.926667,0.771812,0.870968,0.900709,0.896552,0.936508,0.903614,0.914286,0.896226,0},
      {0,0.924528,0.8625,0.923077,0.910891,0.911111,0.851064,0.834951,0.914286,0.87156,0.876106,0.940171,0.870229,0},
      {0,0.842105,0.775,0.86,0.833333,0.87037,0.903846,0.852941,0.877551,0.882353,0.910714,0.95122,0.964286,0},
      {0,0.734375,0.829268,0.763636,0.826087,0.777778,0.714286,0.804878,0.829268,0.763158,0.756098,0.884615,0.867925,0},
      {0,0.79661,0.735294,0.7,0.794872,0.829268,0.823529,0.878049,0.895833,0.782609,0.822222,0.942857,0.775,0},
      {0,0.75,0.714286,0.628571,0.62963,0.64,0.857143,0.702703,0.731707,0.767442,0.757576,0.705882,0.8,0},
      {0,0.342105,0.5,0.368421,0.5,0.6,0.56,0.615385,0.703704,0.787879,0.666667,0.526316,0.694444,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    },
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0.935223,0.953846,0.957895,0.9447,0.958333,0.94709,0.962441,0.913876,0.971831,0.932292,0.951923,0.966418,0},
      {0,0.977358,0.974093,0.956044,0.925581,0.96988,0.967213,0.886256,0.977901,0.948718,0.960784,0.956731,0.97026,0},
      {0,0.984375,0.946809,0.961326,0.95,0.981481,0.973684,0.970149,0.990148,0.953125,0.963158,0.979275,0.938389,0},
      {0,0.954545,0.964912,0.906077,0.96,0.880435,0.943182,0.970238,0.962963,0.922078,0.964286,0.954023,0.964981,0},
      {0,0.965957,0.97006,0.944099,0.948864,0.977401,0.951515,0.961957,0.939891,0.963855,0.909574,0.951807,0.919431,0},
      {0,0.946237,0.931973,0.937931,0.901099,0.957317,0.958824,0.931429,0.914286,0.930636,0.953642,0.922581,0.959799,0},
      {0,0.951923,0.909574,0.94012,0.91875,0.937143,0.915152,0.974194,0.922581,0.938356,0.945455,0.949367,0.976852,0},
      {0,0.677419,0.679487,0.608696,0.69697,0.626667,0.662338,0.676056,0.670886,0.69863,0.690141,0.637681,0.674699,0},
      {0,0.929078,0.909836,0.902655,0.923077,0.830508,0.943089,0.957983,0.937008,0.917293,0.925,0.944444,0.921986,0},
      {0,0.90566,0.913978,0.892857,0.921348,0.942529,0.901235,0.897436,0.961538,0.9,0.903614,0.949367,0.893805,0},
      {0,0.818182,0.888889,0.860465,0.878049,0.83871,0.813953,0.935484,0.875,0.8125,0.875,1,0.930233,0},
      {0,0.9,0.926829,0.774194,0.774194,0.883721,0.885714,0.68,0.833333,0.916667,0.925926,0.90625,0.823529,0},
      {0,0.764706,0.703704,0.818182,0.636364,0.758621,0.842105,0.625,0.777778,0.875,0.75,0.92,0.806452,0},
      {0,0.678571,0.72,0.583333,0.758621,0.823529,0.578947,0.837838,0.925926,0.633333,0.785714,0.913043,0.826087,0},
      {0,0.45,0.434783,0.666667,0.72,0.695652,0.888889,0.545455,0.380952,0.6875,0.64,0.615385,0.65625,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
}
};


  int tmpPtBin = FindElectronEfficiencyBin( Pt , ptBins, 15);
  int tmpEtaBin = FindElectronEfficiencyBin( Eta , etaBins, 16);
  int tmpPhiBin = FindElectronEfficiencyBin( Phi , phiBins, 12);
  return Efficiency[tmpPtBin][tmpEtaBin][tmpPhiBin];
}




double GetElectronEfficiencyPtEta(double Pt, double Eta) {

  double ptBins[16] = {5,6,7,8,9,10,12,14,16,18,20,25,30,35,40,50};
  double etaBins[17] = {0,0.2,0.4,0.6,0.8,1,1.2,1.4442,1.566,1.8,2,2.1,2.2,2.3,2.4,2.5,2.6};


  double Efficiency[17][18] = {
    {0,0.0436187,0.0390016,0.0377953,0.0520505,0.04811,0.0479574,0.0326241,0.0185185,0.0261866,0.0273723,0.0278884,0.0162602,0.0138249,0.0163934,0.0133333,0,0    },
    {0,0.0392157,0.0408805,0.0408805,0.024055,0.0342205,0.049505,0.0526316,0.0544218,0.0328467,0.040724,0.0784314,0.056,0.0104167,0.0879121,0.0410959,0,0    },
    {0,0.0944882,0.105943,0.127717,0.083558,0.0966767,0.0945122,0.0779944,0.0758294,0.141956,0.164444,0.144231,0.0967742,0.149123,0.0786517,0.114583,0,0    },
    {0,0.473441,0.508235,0.587196,0.591133,0.504348,0.439153,0.371134,0.237624,0.351955,0.422535,0.379845,0.330579,0.22807,0.147826,0.170213,0,0    },
    {0,0.626243,0.695279,0.714579,0.729167,0.680942,0.654229,0.572354,0.262136,0.471322,0.503571,0.512987,0.417808,0.35,0.271845,0.278261,0,0    },
    {0,0.701349,0.805344,0.753452,0.760915,0.749425,0.697517,0.662768,0.322275,0.5975,0.599315,0.51145,0.47482,0.333333,0.373737,0.201923,0,0    },
    {0,0.816578,0.858515,0.84982,0.845662,0.835317,0.775824,0.739766,0.440994,0.643013,0.670455,0.643885,0.581301,0.447236,0.431452,0.292887,0,0    },
    {0,0.87094,0.875445,0.87344,0.882883,0.881743,0.841183,0.801661,0.49011,0.692666,0.736248,0.749164,0.640569,0.586364,0.490476,0.346154,0,0    },
    {0,0.890987,0.891892,0.900973,0.910714,0.909004,0.867945,0.84308,0.574837,0.764908,0.808362,0.761905,0.716049,0.605932,0.602871,0.456647,0,0    },
    {0,0.898592,0.919173,0.909348,0.913215,0.88959,0.889503,0.864807,0.5803,0.780355,0.828467,0.764479,0.751111,0.714286,0.63913,0.45283,0,0    },
    {0,0.890256,0.915638,0.92389,0.931697,0.916763,0.878827,0.888268,0.586387,0.822715,0.813121,0.837104,0.78125,0.68,0.65896,0.49359,0,0    },
    {0,0.91832,0.933042,0.934679,0.936533,0.927811,0.906024,0.882321,0.603448,0.860795,0.867837,0.83499,0.772182,0.741648,0.673973,0.527607,0,0    },
    {0,0.913364,0.935935,0.94186,0.933249,0.928028,0.925373,0.903247,0.621053,0.871181,0.881316,0.841076,0.844612,0.756839,0.692029,0.552529,0,0    },
    {0,0.924528,0.939062,0.945267,0.94265,0.936813,0.917595,0.922764,0.65008,0.872458,0.880096,0.849206,0.783099,0.776316,0.765957,0.633065,0,0    },
    {0,0.928363,0.959975,0.954111,0.931322,0.926241,0.931034,0.912615,0.626453,0.865539,0.898795,0.846995,0.811912,0.763934,0.749077,0.580769,0,0    },
    {0,0.926986,0.941108,0.947936,0.940698,0.944973,0.935701,0.905237,0.649219,0.895913,0.892498,0.879725,0.797101,0.814741,0.72549,0.563686,0,0    },
    {0,0.949941,0.955906,0.966202,0.946324,0.949977,0.937191,0.940719,0.667035,0.920667,0.914099,0.877551,0.859649,0.7737,0.758065,0.613281,0,0}
  };


  int tmpPtBin = FindElectronEfficiencyBin( Pt , ptBins, 15);
  int tmpEtaBin = FindElectronEfficiencyBin( Eta , etaBins, 16);
  return Efficiency[tmpPtBin][tmpEtaBin];
}
