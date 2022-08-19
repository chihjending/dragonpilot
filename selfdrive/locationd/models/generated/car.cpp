#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with sympy 1.9                        *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_6814212569071197423) {
   out_6814212569071197423[0] = delta_x[0] + nom_x[0];
   out_6814212569071197423[1] = delta_x[1] + nom_x[1];
   out_6814212569071197423[2] = delta_x[2] + nom_x[2];
   out_6814212569071197423[3] = delta_x[3] + nom_x[3];
   out_6814212569071197423[4] = delta_x[4] + nom_x[4];
   out_6814212569071197423[5] = delta_x[5] + nom_x[5];
   out_6814212569071197423[6] = delta_x[6] + nom_x[6];
   out_6814212569071197423[7] = delta_x[7] + nom_x[7];
   out_6814212569071197423[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7666174205888484741) {
   out_7666174205888484741[0] = -nom_x[0] + true_x[0];
   out_7666174205888484741[1] = -nom_x[1] + true_x[1];
   out_7666174205888484741[2] = -nom_x[2] + true_x[2];
   out_7666174205888484741[3] = -nom_x[3] + true_x[3];
   out_7666174205888484741[4] = -nom_x[4] + true_x[4];
   out_7666174205888484741[5] = -nom_x[5] + true_x[5];
   out_7666174205888484741[6] = -nom_x[6] + true_x[6];
   out_7666174205888484741[7] = -nom_x[7] + true_x[7];
   out_7666174205888484741[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8014857022495098622) {
   out_8014857022495098622[0] = 1.0;
   out_8014857022495098622[1] = 0;
   out_8014857022495098622[2] = 0;
   out_8014857022495098622[3] = 0;
   out_8014857022495098622[4] = 0;
   out_8014857022495098622[5] = 0;
   out_8014857022495098622[6] = 0;
   out_8014857022495098622[7] = 0;
   out_8014857022495098622[8] = 0;
   out_8014857022495098622[9] = 0;
   out_8014857022495098622[10] = 1.0;
   out_8014857022495098622[11] = 0;
   out_8014857022495098622[12] = 0;
   out_8014857022495098622[13] = 0;
   out_8014857022495098622[14] = 0;
   out_8014857022495098622[15] = 0;
   out_8014857022495098622[16] = 0;
   out_8014857022495098622[17] = 0;
   out_8014857022495098622[18] = 0;
   out_8014857022495098622[19] = 0;
   out_8014857022495098622[20] = 1.0;
   out_8014857022495098622[21] = 0;
   out_8014857022495098622[22] = 0;
   out_8014857022495098622[23] = 0;
   out_8014857022495098622[24] = 0;
   out_8014857022495098622[25] = 0;
   out_8014857022495098622[26] = 0;
   out_8014857022495098622[27] = 0;
   out_8014857022495098622[28] = 0;
   out_8014857022495098622[29] = 0;
   out_8014857022495098622[30] = 1.0;
   out_8014857022495098622[31] = 0;
   out_8014857022495098622[32] = 0;
   out_8014857022495098622[33] = 0;
   out_8014857022495098622[34] = 0;
   out_8014857022495098622[35] = 0;
   out_8014857022495098622[36] = 0;
   out_8014857022495098622[37] = 0;
   out_8014857022495098622[38] = 0;
   out_8014857022495098622[39] = 0;
   out_8014857022495098622[40] = 1.0;
   out_8014857022495098622[41] = 0;
   out_8014857022495098622[42] = 0;
   out_8014857022495098622[43] = 0;
   out_8014857022495098622[44] = 0;
   out_8014857022495098622[45] = 0;
   out_8014857022495098622[46] = 0;
   out_8014857022495098622[47] = 0;
   out_8014857022495098622[48] = 0;
   out_8014857022495098622[49] = 0;
   out_8014857022495098622[50] = 1.0;
   out_8014857022495098622[51] = 0;
   out_8014857022495098622[52] = 0;
   out_8014857022495098622[53] = 0;
   out_8014857022495098622[54] = 0;
   out_8014857022495098622[55] = 0;
   out_8014857022495098622[56] = 0;
   out_8014857022495098622[57] = 0;
   out_8014857022495098622[58] = 0;
   out_8014857022495098622[59] = 0;
   out_8014857022495098622[60] = 1.0;
   out_8014857022495098622[61] = 0;
   out_8014857022495098622[62] = 0;
   out_8014857022495098622[63] = 0;
   out_8014857022495098622[64] = 0;
   out_8014857022495098622[65] = 0;
   out_8014857022495098622[66] = 0;
   out_8014857022495098622[67] = 0;
   out_8014857022495098622[68] = 0;
   out_8014857022495098622[69] = 0;
   out_8014857022495098622[70] = 1.0;
   out_8014857022495098622[71] = 0;
   out_8014857022495098622[72] = 0;
   out_8014857022495098622[73] = 0;
   out_8014857022495098622[74] = 0;
   out_8014857022495098622[75] = 0;
   out_8014857022495098622[76] = 0;
   out_8014857022495098622[77] = 0;
   out_8014857022495098622[78] = 0;
   out_8014857022495098622[79] = 0;
   out_8014857022495098622[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6791547762604559707) {
   out_6791547762604559707[0] = state[0];
   out_6791547762604559707[1] = state[1];
   out_6791547762604559707[2] = state[2];
   out_6791547762604559707[3] = state[3];
   out_6791547762604559707[4] = state[4];
   out_6791547762604559707[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6791547762604559707[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6791547762604559707[7] = state[7];
   out_6791547762604559707[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3683219731909566018) {
   out_3683219731909566018[0] = 1;
   out_3683219731909566018[1] = 0;
   out_3683219731909566018[2] = 0;
   out_3683219731909566018[3] = 0;
   out_3683219731909566018[4] = 0;
   out_3683219731909566018[5] = 0;
   out_3683219731909566018[6] = 0;
   out_3683219731909566018[7] = 0;
   out_3683219731909566018[8] = 0;
   out_3683219731909566018[9] = 0;
   out_3683219731909566018[10] = 1;
   out_3683219731909566018[11] = 0;
   out_3683219731909566018[12] = 0;
   out_3683219731909566018[13] = 0;
   out_3683219731909566018[14] = 0;
   out_3683219731909566018[15] = 0;
   out_3683219731909566018[16] = 0;
   out_3683219731909566018[17] = 0;
   out_3683219731909566018[18] = 0;
   out_3683219731909566018[19] = 0;
   out_3683219731909566018[20] = 1;
   out_3683219731909566018[21] = 0;
   out_3683219731909566018[22] = 0;
   out_3683219731909566018[23] = 0;
   out_3683219731909566018[24] = 0;
   out_3683219731909566018[25] = 0;
   out_3683219731909566018[26] = 0;
   out_3683219731909566018[27] = 0;
   out_3683219731909566018[28] = 0;
   out_3683219731909566018[29] = 0;
   out_3683219731909566018[30] = 1;
   out_3683219731909566018[31] = 0;
   out_3683219731909566018[32] = 0;
   out_3683219731909566018[33] = 0;
   out_3683219731909566018[34] = 0;
   out_3683219731909566018[35] = 0;
   out_3683219731909566018[36] = 0;
   out_3683219731909566018[37] = 0;
   out_3683219731909566018[38] = 0;
   out_3683219731909566018[39] = 0;
   out_3683219731909566018[40] = 1;
   out_3683219731909566018[41] = 0;
   out_3683219731909566018[42] = 0;
   out_3683219731909566018[43] = 0;
   out_3683219731909566018[44] = 0;
   out_3683219731909566018[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3683219731909566018[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3683219731909566018[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3683219731909566018[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3683219731909566018[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3683219731909566018[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3683219731909566018[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3683219731909566018[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3683219731909566018[53] = -9.8000000000000007*dt;
   out_3683219731909566018[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3683219731909566018[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3683219731909566018[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3683219731909566018[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3683219731909566018[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3683219731909566018[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3683219731909566018[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3683219731909566018[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3683219731909566018[62] = 0;
   out_3683219731909566018[63] = 0;
   out_3683219731909566018[64] = 0;
   out_3683219731909566018[65] = 0;
   out_3683219731909566018[66] = 0;
   out_3683219731909566018[67] = 0;
   out_3683219731909566018[68] = 0;
   out_3683219731909566018[69] = 0;
   out_3683219731909566018[70] = 1;
   out_3683219731909566018[71] = 0;
   out_3683219731909566018[72] = 0;
   out_3683219731909566018[73] = 0;
   out_3683219731909566018[74] = 0;
   out_3683219731909566018[75] = 0;
   out_3683219731909566018[76] = 0;
   out_3683219731909566018[77] = 0;
   out_3683219731909566018[78] = 0;
   out_3683219731909566018[79] = 0;
   out_3683219731909566018[80] = 1;
}
void h_25(double *state, double *unused, double *out_2172051214329875381) {
   out_2172051214329875381[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3364051928398716628) {
   out_3364051928398716628[0] = 0;
   out_3364051928398716628[1] = 0;
   out_3364051928398716628[2] = 0;
   out_3364051928398716628[3] = 0;
   out_3364051928398716628[4] = 0;
   out_3364051928398716628[5] = 0;
   out_3364051928398716628[6] = 1;
   out_3364051928398716628[7] = 0;
   out_3364051928398716628[8] = 0;
}
void h_24(double *state, double *unused, double *out_7587553502939940622) {
   out_7587553502939940622[0] = state[4];
   out_7587553502939940622[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2519055319615021229) {
   out_2519055319615021229[0] = 0;
   out_2519055319615021229[1] = 0;
   out_2519055319615021229[2] = 0;
   out_2519055319615021229[3] = 0;
   out_2519055319615021229[4] = 1;
   out_2519055319615021229[5] = 0;
   out_2519055319615021229[6] = 0;
   out_2519055319615021229[7] = 0;
   out_2519055319615021229[8] = 0;
   out_2519055319615021229[9] = 0;
   out_2519055319615021229[10] = 0;
   out_2519055319615021229[11] = 0;
   out_2519055319615021229[12] = 0;
   out_2519055319615021229[13] = 0;
   out_2519055319615021229[14] = 1;
   out_2519055319615021229[15] = 0;
   out_2519055319615021229[16] = 0;
   out_2519055319615021229[17] = 0;
}
void h_30(double *state, double *unused, double *out_6112207235155681847) {
   out_6112207235155681847[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3552638413092900127) {
   out_3552638413092900127[0] = 0;
   out_3552638413092900127[1] = 0;
   out_3552638413092900127[2] = 0;
   out_3552638413092900127[3] = 0;
   out_3552638413092900127[4] = 1;
   out_3552638413092900127[5] = 0;
   out_3552638413092900127[6] = 0;
   out_3552638413092900127[7] = 0;
   out_3552638413092900127[8] = 0;
}
void h_26(double *state, double *unused, double *out_967317172040034310) {
   out_967317172040034310[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7105555247272772852) {
   out_7105555247272772852[0] = 0;
   out_7105555247272772852[1] = 0;
   out_7105555247272772852[2] = 0;
   out_7105555247272772852[3] = 0;
   out_7105555247272772852[4] = 0;
   out_7105555247272772852[5] = 0;
   out_7105555247272772852[6] = 0;
   out_7105555247272772852[7] = 1;
   out_7105555247272772852[8] = 0;
}
void h_27(double *state, double *unused, double *out_351929141530343503) {
   out_351929141530343503[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1377875101292475216) {
   out_1377875101292475216[0] = 0;
   out_1377875101292475216[1] = 0;
   out_1377875101292475216[2] = 0;
   out_1377875101292475216[3] = 1;
   out_1377875101292475216[4] = 0;
   out_1377875101292475216[5] = 0;
   out_1377875101292475216[6] = 0;
   out_1377875101292475216[7] = 0;
   out_1377875101292475216[8] = 0;
}
void h_29(double *state, double *unused, double *out_627123203814849392) {
   out_627123203814849392[0] = state[1];
}
void H_29(double *state, double *unused, double *out_335487625577075817) {
   out_335487625577075817[0] = 0;
   out_335487625577075817[1] = 1;
   out_335487625577075817[2] = 0;
   out_335487625577075817[3] = 0;
   out_335487625577075817[4] = 0;
   out_335487625577075817[5] = 0;
   out_335487625577075817[6] = 0;
   out_335487625577075817[7] = 0;
   out_335487625577075817[8] = 0;
}
void h_28(double *state, double *unused, double *out_2252476179278354148) {
   out_2252476179278354148[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5417886642646606391) {
   out_5417886642646606391[0] = 1;
   out_5417886642646606391[1] = 0;
   out_5417886642646606391[2] = 0;
   out_5417886642646606391[3] = 0;
   out_5417886642646606391[4] = 0;
   out_5417886642646606391[5] = 0;
   out_5417886642646606391[6] = 0;
   out_5417886642646606391[7] = 0;
   out_5417886642646606391[8] = 0;
}
void h_31(double *state, double *unused, double *out_8511427602559003794) {
   out_8511427602559003794[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3333405966521756200) {
   out_3333405966521756200[0] = 0;
   out_3333405966521756200[1] = 0;
   out_3333405966521756200[2] = 0;
   out_3333405966521756200[3] = 0;
   out_3333405966521756200[4] = 0;
   out_3333405966521756200[5] = 0;
   out_3333405966521756200[6] = 0;
   out_3333405966521756200[7] = 0;
   out_3333405966521756200[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_6814212569071197423) {
  err_fun(nom_x, delta_x, out_6814212569071197423);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7666174205888484741) {
  inv_err_fun(nom_x, true_x, out_7666174205888484741);
}
void car_H_mod_fun(double *state, double *out_8014857022495098622) {
  H_mod_fun(state, out_8014857022495098622);
}
void car_f_fun(double *state, double dt, double *out_6791547762604559707) {
  f_fun(state,  dt, out_6791547762604559707);
}
void car_F_fun(double *state, double dt, double *out_3683219731909566018) {
  F_fun(state,  dt, out_3683219731909566018);
}
void car_h_25(double *state, double *unused, double *out_2172051214329875381) {
  h_25(state, unused, out_2172051214329875381);
}
void car_H_25(double *state, double *unused, double *out_3364051928398716628) {
  H_25(state, unused, out_3364051928398716628);
}
void car_h_24(double *state, double *unused, double *out_7587553502939940622) {
  h_24(state, unused, out_7587553502939940622);
}
void car_H_24(double *state, double *unused, double *out_2519055319615021229) {
  H_24(state, unused, out_2519055319615021229);
}
void car_h_30(double *state, double *unused, double *out_6112207235155681847) {
  h_30(state, unused, out_6112207235155681847);
}
void car_H_30(double *state, double *unused, double *out_3552638413092900127) {
  H_30(state, unused, out_3552638413092900127);
}
void car_h_26(double *state, double *unused, double *out_967317172040034310) {
  h_26(state, unused, out_967317172040034310);
}
void car_H_26(double *state, double *unused, double *out_7105555247272772852) {
  H_26(state, unused, out_7105555247272772852);
}
void car_h_27(double *state, double *unused, double *out_351929141530343503) {
  h_27(state, unused, out_351929141530343503);
}
void car_H_27(double *state, double *unused, double *out_1377875101292475216) {
  H_27(state, unused, out_1377875101292475216);
}
void car_h_29(double *state, double *unused, double *out_627123203814849392) {
  h_29(state, unused, out_627123203814849392);
}
void car_H_29(double *state, double *unused, double *out_335487625577075817) {
  H_29(state, unused, out_335487625577075817);
}
void car_h_28(double *state, double *unused, double *out_2252476179278354148) {
  h_28(state, unused, out_2252476179278354148);
}
void car_H_28(double *state, double *unused, double *out_5417886642646606391) {
  H_28(state, unused, out_5417886642646606391);
}
void car_h_31(double *state, double *unused, double *out_8511427602559003794) {
  h_31(state, unused, out_8511427602559003794);
}
void car_H_31(double *state, double *unused, double *out_3333405966521756200) {
  H_31(state, unused, out_3333405966521756200);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_init(car);