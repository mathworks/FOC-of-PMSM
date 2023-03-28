%% ************************************************************************
% Model         :   PMSM Field Oriented Control
% Description   :   Set Parameters for PMSM Field Oriented Control
% File name     :   mcb_pmsm_foc_hall_MCSPTE1AK144_data.m

% Copyright 2021 The MathWorks, Inc.

%% Parameters needed for Offset computation are
% target.PWM_Counter_Period  - PWM counter value for epwm blocks
% target.CPU_frequency       - CPU frequency of the microcontroller
% Ts                         - Control sample time
% PU_System.N_base           - Base speed for per unit conversion
% pmsm.p                     - Number pole pairs in the motor

% Other parameters are not mandatory for offset computation
%% Set PWM Switching frequency
PWM_frequency 	= 20e3;    %Hz          // converter s/w freq - Chaning here 
                           %            // alone will not change PWM frequency in example.
T_pwm           = 1/PWM_frequency;  %s  // PWM switching time period
 
%% Set Sample Times
Ts          	= T_pwm * 2;  %sec        // simulation time step for controller
Ts_simulink     = T_pwm;      %sec        // simulation time step for model simulation
Ts_motor        = T_pwm;      %Sec        // Simulation sample time
Ts_inverter     = T_pwm;      %sec        // simulation time step for average value inverter
Ts_speed        = 20*Ts;      %Sec        // Sample time for speed controller
Ts_uart         = 0.01;       %Sec        // Sample time for UART TX  

%% Configurable parameters
%% Set data type for controller & code-gen
dataType = 'single';          % Floating point code-generation

%% System Parameters // Hardware parameters 

pmsm.model  = 'LINIX-45ZVN24';  %           // Manufacturer Model Number
pmsm.sn     = '40';             %           // Manufacturer Model Number
pmsm.p      = 2;                %           // Pole Pairs for the motor
pmsm.Rs     = 0.56;             %Ohm        // Shunt Resistor
pmsm.Ld     = 0.375e-3;         %H          // D-axis inductance value
pmsm.Lq     = 0.435e-3;         %H          // Q-axis inductance value
pmsm.J      = 0.12e-4;          %Kg-m2      // Inertia in SI units
pmsm.B      = 0.1e-6;           %Kg-m2/s    // Friction Co-efficient
pmsm.Ke     = 5.8;              %Bemf Const	// Vline_peak/krpm
pmsm.Kt     = 0.097;            %Nm/A       // Torque constant
pmsm.I_rated= 2.3;              %A      	// Rated current (phase-peak)
pmsm.N_max  = 4000;             %rpm        // Max speed
pmsm.QEPIndexOffset = 0.1712;   %0.6879/4;	%PU position// QEP Offset
pmsm.QEPSlits       = 1000;     %           // QEP Encoder Slits
pmsm.PositionOffset = 0.3855;
pmsm.FluxPM     = (pmsm.Ke)/(sqrt(3)*2*pi*1000*pmsm.p/60);               %PM flux computed from Ke
pmsm.T_rated    = (3/2)*pmsm.p*pmsm.FluxPM*pmsm.I_rated;   %Get T_rated from I_rated

Target.model                = 'EVB_S32K144';% Manufacturer Model Number
Target.CPU_frequency        = 80e6;    %(Hz)   // Clock frequency
Target.PWM_frequency        = PWM_frequency;   %// PWM frequency
Target.PWM_Counter_Period   = round(Target.CPU_frequency/Target.PWM_frequency); %(PWM timer counts)
%% Parameters below are not mandatory for offset computation

% inverter = mcb_SetInverterParameters('MOTORGD');
inverter.model          = 'MOTORGD3000-KIT'; % Manufacturer Model Number
inverter.sn             = 'rev1';   % Manufacturer Serial Number
inverter.V_dc           = 12;       %V      // DC Link Voltage of the Inverter
inverter.ISenseMax      = 15.625;   %Amps   // Max current that can be measured by ADC
inverter.I_trip         = 31.25;    %Amps   // Max current for trip
inverter.Rds_on         = 35e-3;    %Ohms   // Rds ON
inverter.Rshunt         = 0.010;    %Ohms   // Rshunt
inverter.MaxADCCnt      = 4095;     %Counts // ADC Counts Max Value
inverter.CtSensAOffset  = 2027;     %Counts // ADC Offset for phase-A
inverter.CtSensBOffset  = 2038;     %Counts // ADC Offset for phase-B
inverter.ADCGain        = 1;        %       // ADC Gain factor scaled by SPI
inverter.R_board        = inverter.Rds_on + inverter.Rshunt/3;  %Ohms
%% Derive Characteristics

pmsm.N_base = mcb_getBaseSpeed(pmsm,inverter);

%% PU System details // Set base values for pu conversion

PU_System = mcb_SetPUSystem(pmsm,inverter);

%% Controller design
PI_params = mcb.internal.SetControllerParameters(pmsm,inverter,PU_System,T_pwm,Ts,Ts_speed);

%Updating delays for simulation
PI_params.delay_Currents    = int32(Ts/Ts_simulink);
PI_params.delay_Position    = int32(Ts/Ts_simulink);
PI_params.delay_Speed       = int32(Ts_speed/Ts_simulink);
PI_params.delay_Speed1      = (PI_params.delay_IIR + 0.5*Ts)/Ts_speed;
% 
% % mcb_getControlAnalysis(pmsm,inverter,PU_System,PI_params,Ts,Ts_speed); 
