#pragma once

#include "scalar.h"
#include <Eigen/Dense>

struct MotorState {
    // motor characteristics
    int num_pole_pairs = 4;
    Scalar rotor_inertia = 1; // moment of inertia
    Scalar mechanical_to_electrical_offset = 0;
    Scalar phase_inductance = 1e-3;
    Scalar phase_resistance = 1e-2;
    // normalized bEmf aka torque/current curve
    // odd coefficients of sine fourier expansion
    Eigen::Matrix<Scalar, 5, 1> normalized_bEmf_coeffs;
    std::array<Scalar, 3600> cogging_torque_map;
    std::array<Scalar, 3600> stiction_torque_map;

    Scalar rotor_angle = 0;
    Scalar rotor_angular_vel = 0;
    Scalar rotor_angular_accel = 0;
    Scalar electrical_angle = 0;
    Scalar torque = 0;
    Scalar neutral_voltage = 0;
    Eigen::Matrix<Scalar, 3, 1> pole_voltages =
        {}; // does this zero the entries?
    Eigen::Matrix<Scalar, 3, 1> phase_voltages = {};
    Eigen::Matrix<Scalar, 3, 1> phase_currents = {};
    Eigen::Matrix<Scalar, 3, 1> bEmfs = {};
    Eigen::Matrix<Scalar, 3, 1> normalized_bEmfs =
        {}; // units of V . s,
            // aka N . m / Amps
            // same thing as
            // - phase torque function
            // - derivative of rotor stator flux linkage wrt angle
};

inline void init_motor_state(MotorState* motor) {
    motor->pole_voltages.setZero();
    motor->phase_voltages.setZero();
    motor->phase_currents.setZero();
    motor->bEmfs.setZero();
    motor->normalized_bEmf_coeffs << 1, 0, 0, 0, 0;
}