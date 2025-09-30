/*-----------------------------------------------------------------------------
* Copyright 2013-2017 NXP
*
* SPDX-License-Identifier: BSD-3-Clause
* The BSD-3-Clause license can be found at https://spdx.org/licenses/BSD-3-Clause.html
*-----------------------------------------------------------------------------*/

/*!
 * @file tpp_mc33937.h
 *
 * Register map for GD3000, MC33937 and MC34937 Three Phase 
 * Field Effect Transistor Pre-driver.
 *
 */

#ifndef TPP_MC33937_H_
#define TPP_MC33937_H_

/* Serial input commands. */

/* NULL command. */
#define TPP_NULL_CMD      0x00U

#define TPP_NULL_STATUS0  0x00U
#define TPP_NULL_STATUS1  0x01U
#define TPP_NULL_STATUS2  0x02U
#define TPP_NULL_STATUS3  0x03U

/* MASK0 command. */
#define TPP_MASK0_CMD       0x20U

#define TPP_MASK0_OT_MASK   0x01U
#define TPP_MASK0_DES_MASK  0x02U
#define TPP_MASK0_UV_MASK   0x04U
#define TPP_MASK0_OC_MASK   0x08U

#define TPP_MASK0_OT_SHIFT  0x00U
#define TPP_MASK0_DES_SHIFT 0x01U
#define TPP_MASK0_UV_SHIFT  0x02U
#define TPP_MASK0_OC_SHIFT  0x03U
  
#define TPP_MASK0_MASK      0x0FU

#define TPP_MASK0_OT_INT_ENABLED   (0x01 << TPP_MASK0_OT_SHIFT)
#define TPP_MASK0_OT_INT_DISABLED  (0x00 << TPP_MASK0_OT_SHIFT)

#define TPP_MASK0_DES_INT_ENABLED  (0x01 << TPP_MASK0_DES_SHIFT)
#define TPP_MASK0_DES_INT_DISABLED (0x00 << TPP_MASK0_DES_SHIFT)

#define TPP_MASK0_UV_INT_ENABLED   (0x01 << TPP_MASK0_UV_SHIFT)
#define TPP_MASK0_UV_INT_DISABLED  (0x00 << TPP_MASK0_UV_SHIFT)

#define TPP_MASK0_OC_INT_ENABLED   (0x01 << TPP_MASK0_OC_SHIFT)
#define TPP_MASK0_OC_INT_DISABLED  (0x00 << TPP_MASK0_OC_SHIFT)

/* MASK1 command. */
#define TPP_MASK1_CMD        0x30U

#define TPP_MASK1_PHS_MASK   0x01U
#define TPP_MASK1_FRM_MASK   0x02U
#define TPP_MASK1_WRT_MASK   0x04U
#define TPP_MASK1_RST_MASK   0x08U

#define TPP_MASK1_PHS_SHIFT  0x00U
#define TPP_MASK1_FRM_SHIFT  0x01U
#define TPP_MASK1_WRT_SHIFT  0x02U
#define TPP_MASK1_RST_SHIFT  0x03U

#define TPP_MASK1_MASK       0x0FU

#define TPP_MASK1_PHS_INT_ENABLED   (0x01 << TPP_MASK1_PHS_SHIFT)
#define TPP_MASK1_PHS_INT_DISABLED  (0x00 << TPP_MASK1_PHS_SHIFT)

#define TPP_MASK1_FRM_INT_ENABLED   (0x01 << TPP_MASK1_FRM_SHIFT)
#define TPP_MASK1_FRM_INT_DISABLED  (0x00 << TPP_MASK1_FRM_SHIFT)

#define TPP_MASK1_WRT_INT_ENABLED   (0x01 << TPP_MASK1_WRT_SHIFT)
#define TPP_MASK1_WRT_INT_DISABLED  (0x00 << TPP_MASK1_WRT_SHIFT)

#define TPP_MASK1_RST_INT_ENABLED   (0x01 << TPP_MASK1_RST_SHIFT)
#define TPP_MASK1_RST_INT_DISABLED  (0x00 << TPP_MASK1_RST_SHIFT)

/* MODE command. */
#define TPP_MODE_CMD         0x40U

#define TPP_MODE_LOCK_MASK   0x01U
#define TPP_MODE_FULL_MASK   0x02U
#define TPP_MODE_DESF_MASK   0x08U

#define TPP_MODE_LOCK_SHIFT  0x00U
#define TPP_MODE_FULL_SHIFT  0x01U
#define TPP_MODE_DESF_SHIFT  0x03U

#define TPP_MODE_MASK        0x0BU

#define TPP_MODE_LOCK_ENABLED    (0x01 << TPP_MODE_LOCK_SHIFT)
#define TPP_MODE_LOCK_DISABLED   (0x00 << TPP_MODE_LOCK_SHIFT)

#define TPP_MODE_FULL_ENABLED    (0x01 << TPP_MODE_FULL_SHIFT)
#define TPP_MODE_FULL_DISABLED   (0x00 << TPP_MODE_FULL_SHIFT)

#define TPP_MODE_DESF_ENABLED    (0x00 << TPP_MODE_DESF_SHIFT)
#define TPP_MODE_DESF_DISABLED   (0x01 << TPP_MODE_DESF_SHIFT)

/* CLINT0 command. */
#define TPP_CLINT0_CMD       0x60U

#define TPP_CLINT0_OT_MASK   0x01U
#define TPP_CLINT0_DES_MASK  0x02U
#define TPP_CLINT0_UV_MASK   0x04U
#define TPP_CLINT0_OC_MASK   0x08U

#define TPP_CLINT0_OT_SHIFT  0x00U
#define TPP_CLINT0_DES_SHIFT 0x01U
#define TPP_CLINT0_UV_SHIFT  0x02U
#define TPP_CLINT0_OC_SHIFT  0x03U

#define TPP_CLINT0_MASK  0x0FU
  
/* CLINT1 command. */
#define TPP_CLINT1_CMD        0x70U

#define TPP_CLINT1_PHS_MASK   0x01U
#define TPP_CLINT1_FRM_MASK   0x02U
#define TPP_CLINT1_WRT_MASK   0x04U
#define TPP_CLINT1_RST_MASK   0x08U

#define TPP_CLINT1_PHS_SHIFT  0x00U
#define TPP_CLINT1_FRM_SHIFT  0x01U
#define TPP_CLINT1_WRT_SHIFT  0x02U
#define TPP_CLINT1_RST_SHIFT  0x03U

#define TPP_CLINT1_MASK       0x0FU

/* DEADTIME command. */
#define TPP_DEADTIME_CMD             0x80U
 
#define TPP_DEADTIME_CALIB_MASK      0x01U

#define TPP_DEADTIME_CALIB_SHIFT     0x00U

#define TPP_DEADTIME_MASK            0x01U

#define TPP_DEADTIME_CALIB_ZERO      0x00U
#define TPP_DEADTIME_CALIB_DEADTIME  0x01U

/* Serial output registers. */

/* STATUS0 register. */
/* Read by sending NULL0 command and any other command. */
#define TPP_STATUS0_OT_MASK    0x01U
#define TPP_STATUS0_DES_MASK   0x02U
#define TPP_STATUS0_UV_MASK    0x04U
#define TPP_STATUS0_OC_MASK    0x08U
#define TPP_STATUS0_PHS_MASK   0x10U
#define TPP_STATUS0_FRM_MASK   0x20U
#define TPP_STATUS0_WRT_MASK   0x40U
#define TPP_STATUS0_RST_MASK   0x80U

#define TPP_STATUS0_OT_SHIFT   0x00U
#define TPP_STATUS0_DES_SHIFT  0x01U
#define TPP_STATUS0_UV_SHIFT   0x02U
#define TPP_STATUS0_OC_SHIFT   0x03U
#define TPP_STATUS0_PHS_SHIFT  0x04U
#define TPP_STATUS0_FRM_SHIFT  0x05U
#define TPP_STATUS0_WRT_SHIFT  0x06U
#define TPP_STATUS0_RST_SHIFT  0x07U

/* STATUS1 register. */
/* Read by sending NULL1 command. */
#define TPP_STATUS1_LOCK_MASK   0x01U
#define TPP_STATUS1_FULL_MASK   0x02U
#define TPP_STATUS1_DTCAL_MASK  0x08U
#define TPP_STATUS1_DTOVF_MASK  0x10U
#define TPP_STATUS1_DTZER_MASK  0x20U
#define TPP_STATUS1_DESF_MASK   0x40U

#define TPP_STATUS1_LOCK_SHIFT  0x00U
#define TPP_STATUS1_FULL_SHIFT  0x01U
#define TPP_STATUS1_DTCAL_SHIFT 0x03U
#define TPP_STATUS1_DTOVF_SHIFT 0x04U
#define TPP_STATUS1_DTZER_SHIFT 0x05U
#define TPP_STATUS1_DESF_SHIFT  0x06U

/* STATUS2 register. */
/* Read by sending NULL2 command. */
#define TPP_STATUS2_OT_MASK   0x01U
#define TPP_STATUS2_DES_MASK  0x02U
#define TPP_STATUS2_UV_MASK   0x04U
#define TPP_STATUS2_OC_MASK   0x08U
#define TPP_STATUS2_PHS_MASK  0x10U
#define TPP_STATUS2_FRM_MASK  0x20U
#define TPP_STATUS2_WRT_MASK  0x40U
#define TPP_STATUS2_RST_MASK  0x80U

#define TPP_STATUS2_OT_SHIFT   0x00U
#define TPP_STATUS2_DES_SHIFT  0x01U
#define TPP_STATUS2_UV_SHIFT   0x02U
#define TPP_STATUS2_OC_SHIFT   0x03U
#define TPP_STATUS2_PHS_SHIFT  0x04U
#define TPP_STATUS2_FRM_SHIFT  0x05U
#define TPP_STATUS2_WRT_SHIFT  0x06U
#define TPP_STATUS2_RST_SHIFT  0x07U

/* STATUS3 register. */
/* Read by sending NULL3 command. */
/* Deadtime calibration value */

/* INIT, SLEEP, STANDBY -> ACTIVE delay constants - in us */
#define TPP_RESET_DELAY     2500  /* Waiting time after RST pin is set in microseconds. Minimal value: 2 ms. */
#define TPP_ENABLE_DELAY       1  /* Waiting time between EN1 and EN2 are set and low side outputs toggling in microseconds. Minimal value: 280 ns. */
#define TPP_LS_TOGGLE_DELAY    1  /* Time for low side outputs toggling during initialization in microseconds. Minimal value: 1 us. */
#define TPP_HS_TOGGLE_DELAY   16  /* Time for high side outputs toggling during initialization in microseconds. Minimal value: dead time (maximum is typically 15 us) + 100 ns. */

/* STANDBY -> ACTIVE specific delay constants - in us */
#define TPP_LS_TOGGLE_DELAY_STANDBY   1  /* Time for low side outputs toggling during initialization in microseconds. Minimal value: 100 ns. */

/* API specific features */
#define TPP_PULSE_WIDTH_CAL_COEF         16  /* Coefficient used for pulse width dead time calibration. */
#define TPP_INTERNAL_TIME_BASE_PERIOD    59  /* Dead time resolution in nanoseconds @17 MHz. */
#define TPP_DEADTIME_MAX_VALUE        15000  /* Maximum dead time value in ns for 17 MHz internal time base clock */

#endif
