% Intialization script for open loop control of PMSM

% Copyright 2025 The MathWorks, Inc.

%% Sample times used in control algorithm
Ts_speed        = 20*Ts;            %Sec    // Sample time for speed controller
Ts_SysControl   = 0.01;            %Sec

%% Motor parameters
pmsm.p                  = 2;
pmsm.I_rated            = 6;
pmsm.N_rated            = 2200;
pmsm.calibSpeed         = 60;
pmsm.QEPSlits           = 1000;     %           // QEP Encoder Slits
pmsm.QEPIndexPresent    = true;     %           // To avoid initial rotor alignment

pmsm.Rs       = 0.192;              %Ohm        // Stator Resistor
pmsm.Ld       = 0.096e-3;           %H          // D-axis inductance value
pmsm.Lq       = 0.107e-3;           %H          // Q-axis inductance value
pmsm.J        = 0.12e-4;            %Kg-m2      // Inertia in SI units
pmsm.B        = 0.1e-6;             %Kg-m2/s    // Friction Co-efficient
pmsm.Ke       = 2.52;               %Bemf Const	// Vpk_LL/krpm
pmsm.Kt       = 0.097;              %Nm/A       // Torque constant
pmsm.PositionOffset = 0;            % Position offset in radian;
pmsm.FluxPM   = (pmsm.Ke)/(sqrt(3)*2*pi*1000*pmsm.p/60); %PM flux computed from Ke
pmsm.T_rated  = mcbPMSMRatedTorque(pmsm);   %Get T_rated from I_rated
