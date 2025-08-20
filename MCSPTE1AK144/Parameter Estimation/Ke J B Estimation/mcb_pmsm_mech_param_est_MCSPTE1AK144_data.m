%% ************************************************************************
% Model         :   PMSM parameter estimation
% Description   :   Set Parameters for PMSM parameter estimation
% File name     :   mcb_pmsm_mech_param_est_MCSPTE1AK144_data.m

% Copyright 2023 The MathWorks, Inc.

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
pmsm.I_rated= 2.3;              %A      	// Rated current (phase-peak)
pmsm.PositionOffset = 0.3855;
pmsm.N_base = 1500;

Target.model                = 'EVB_S32K144';% Manufacturer Model Number
Target.CPU_frequency        = 80e6;         %(Hz)   // Clock frequency
Target.PWM_frequency        = PWM_frequency;%// PWM frequency
Target.PWM_Counter_Period   = round(Target.CPU_frequency/Target.PWM_frequency); %(PWM timer counts)
Target.comport              = 'COM4';       % Serial communication port of the device


inverter.V_dc           = 12;       %V      // DC Link Voltage of the Inverter
inverter.ISenseMax      = 15.625;   %Amps   // Max current that can be measured by ADC
inverter.CtSensAOffset  = 2027;     %Counts // ADC Offset for phase-A
inverter.CtSensBOffset  = 2038;     %Counts // ADC Offset for phase-B




