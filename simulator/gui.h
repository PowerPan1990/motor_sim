#pragma once

#include "scalar.h"
#include "sim_params.h"
#include "sim_state.h"
#include <array>

inline void rolling_buffer_advance_idx(const size_t rolling_buffer_capacity,
                                       int* next_idx, bool* wrap_around) {
    ++(*next_idx);
    if ((*next_idx) >= rolling_buffer_capacity) {
        (*next_idx) = 0;
        (*wrap_around) = true;
    }
}

inline int get_rolling_buffer_count(const size_t rolling_buffer_capacity,
                                    const int next_idx,
                                    const bool wrap_around) {
    if (wrap_around) {
        return rolling_buffer_capacity;
    }
    return next_idx;
}

inline int get_rolling_buffer_offset(const size_t rolling_buffer_capacity,
                                     const int next_idx,
                                     const bool wrap_around) {
    if (wrap_around) {
        return next_idx;
    }
    return 0;
}

constexpr int kNumRollingPts = 200;

struct VizData {
    std::array<Scalar, 50> circle_xs;
    std::array<Scalar, 50> circle_ys;

    std::array<Scalar, 2> angle_xs_rotor;
    std::array<Scalar, 2> angle_ys_rotor;

    std::array<Scalar, 2> bEmf_xs;
    std::array<Scalar, 2> bEmf_ys;

    int rolling_buffers_next_idx = 0;
    bool rolling_buffers_wrap_around = false;
    std::array<Scalar, kNumRollingPts> rolling_timestamps;
    std::array<std::array<Scalar, kNumRollingPts>, 3> rolling_phase_vs;
    std::array<std::array<Scalar, kNumRollingPts>, 3> rolling_is;
    std::array<std::array<Scalar, kNumRollingPts>, 3> rolling_bEmfs;
    std::array<Scalar, kNumRollingPts> rolling_torques;
    std::array<Scalar, kNumRollingPts> rolling_rotor_angular_vel;
};

void init_viz_data(VizData* viz_data);

void run_gui(SimParams* sim_params, SimState* sim_state, bool* should_step,
             VizData* viz_data);