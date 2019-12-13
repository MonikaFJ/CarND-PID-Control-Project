#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID(double Kp, double Ki, double Kd): Kp_(Kp), Ki_(Ki), Kd_(Kd)
{
  p_error_ = 0;
  i_error_ = 0;
  d_error_ = 0;

  sum_cte = 0;
  prev_cte = 0;

  initialized = false;
}

PID::~PID() {}


void PID::UpdateError(double cte) {
  if (!initialized){
    initialized = true;
    prev_cte = cte;
  }
  sum_cte +=cte;
  p_error_ = Kp_*cte;
  d_error_ = Kd_ * cte-prev_cte;
  i_error_ = Ki_ * sum_cte;

  prev_cte = cte;
  /**
   * TODO: Update PID errors based on cte.
   */

}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  return p_error_ + d_error_ + i_error_;
}