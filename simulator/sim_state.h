#pragma once

#include "scalar.h"
#include <Eigen/Dense>

struct SimState {
    Scalar time = 0;

    Scalar rotor_angle;
    Scalar rotor_angular_vel;
    Scalar rotor_angular_accel;

    Scalar electrical_angle;

    Scalar torque;

    Scalar neutral_voltage;
    std::array<int, 3> switches;
    Eigen::Matrix<Scalar, 3, 1> pole_voltages;
    Eigen::Matrix<Scalar, 3, 1> phase_voltages;
    Eigen::Matrix<Scalar, 3, 1> coil_currents;
    Eigen::Matrix<Scalar, 3, 1> bEmfs;
};

inline void init_sim_state(SimState* state) {
    state->switches = {};
    state->neutral_voltage = 0;
    state->pole_voltages.setZero();
    state->phase_voltages.setZero();
    state->coil_currents.setZero();
    state->bEmfs.setZero();
    state->rotor_angle = 0;
    state->rotor_angular_vel = 0;
    state->rotor_angular_accel = 0;
    state->electrical_angle = 0;
    state->torque = 0;
}