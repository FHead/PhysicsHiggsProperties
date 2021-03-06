#define CONST_PI 3.141592653589793238462643383279502884797169399375105820974944
#define CONST_MW 80.4
#define CONST_MZ 91.1876
#define CONST_WZ 2.4952
#define CONST_SW2 0.2313
// #define CONST_SW2 0.2397
#define CONST_SW sqrt(CONST_SW2)
#define CONST_CW sqrt(1-CONST_SW2)
#define CONST_ALPHA (1.0/127.916)
#define CONST_EE sqrt(4*CONST_PI*CONST_ALPHA)
#define CONST_ETA 0.15
#define CONST_GL (2*(-0.5+CONST_SW2)*sqrt(CONST_PI*CONST_ALPHA/(1-CONST_SW2)/CONST_SW2))
#define CONST_GR (2*CONST_SW2*sqrt(CONST_PI*CONST_ALPHA/(1-CONST_SW2)/CONST_SW2))
#define CONST_GQL_UP (2*(0.5-(2.0/3)*CONST_SW2)*sqrt(CONST_PI*CONST_ALPHA/(1-CONST_SW2)/CONST_SW2))
#define CONST_GQR_UP (2*(-2.0/3)*CONST_SW2*sqrt(CONST_PI*CONST_ALPHA/(1-CONST_SW2)/CONST_SW2))
#define CONST_GQL_DOWN (2*(-0.5+(1.0/3)*CONST_SW2)*sqrt(CONST_PI*CONST_ALPHA/(1-CONST_SW2)/CONST_SW2))
#define CONST_GQR_DOWN (2*(1.0/3)*CONST_SW2*sqrt(CONST_PI*CONST_ALPHA/(1-CONST_SW2)/CONST_SW2))
#define CONST_VH 246



