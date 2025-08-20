% Intialization script for Field oriented control of PMSM

% Copyright 2023-2024 The MathWorks, Inc.

%% Sample times used in control algorithm
% Ts          	= T_pwm;            %sec    // Sample time for control system
% Ts_motor        = T_pwm/2;        %Sec    // Simulation time step for pmsm
Ts_speed        = 20*Ts;            %Sec    // Sample time for speed controller
Ts_SysControl   = 0.1;              %Sec

%% Motor parameters
pmsm.p                  = 2;
pmsm.I_rated            = 6;
pmsm.N_rated            = 4000;
pmsm.calibSpeed         = 60;
pmsm.QEPSlits           = 1000;     %           // QEP Encoder Slits
pmsm.QEPIndexPresent    = true;     %           // To avoid initial rotor alignment

pmsm.Rs       = 0.244;              %Ohm        // Stator Resistor
pmsm.Ld       = 0.1e-3;             %H          // D-axis inductance value
pmsm.Lq       = 0.114e-3;           %H          // Q-axis inductance value
pmsm.J        = 0.12e-4;            %Kg-m2      // Inertia in SI units
pmsm.B        = 0.1e-6;             %Kg-m2/s    // Friction Co-efficient
pmsm.Ke       = 2.52;               %Bemf Const	// Vpk_LL/krpm
pmsm.Kt       = 0.097;              %Nm/A       // Torque constant
pmsm.PositionOffset = 0;            % Position offset in radian;
pmsm.FluxPM   = (pmsm.Ke)/(sqrt(3)*2*pi*1000*pmsm.p/60); %PM flux computed from Ke
pmsm.T_rated  = mcbPMSMRatedTorque(pmsm);   %Get T_rated from I_rated
pmsm.V_max      = 45;            % V - Max measured voltage

% pmsm.N_base = mcb_getBaseSpeed(pmsm,inverter); %rpm // Base speed of motor at given Vdc
pmsm.N_base = pmsm.N_rated;

pmsm.OL2CL  = 0.2 * pmsm.N_base;
pmsm.CL2OL  = 0.1 * pmsm.N_base;
pmsm.Sensor = 'EEMF'; % FO,SMO,EEMF

%% PU System
PU_System.V_base   = inverter.V_dc/sqrt(3);
PU_System.I_base   = inverter.ISenseMax;
PU_System.N_base   = pmsm.N_base;
PU_System.T_base   = (3/2)*pmsm.p*pmsm.FluxPM*PU_System.I_base;
PU_System.P_base   = (3/2)*PU_System.V_base*PU_System.I_base;
