% Model      :   Open loop control of PMSM

clear ;
clc

%% Sample Times
PWM_Frequency           = 20e3;             % Hz - PWM frequency
PWM_Period              = 8000;             % uint16 - PWM Timer modulo
PWM_DutyScale           = 32768;            % uint16 - PWM duty cycle scale 
T_pwm                   = 1/PWM_Frequency;  % sec - PWM switching time period
Ts                      = 2 * T_pwm;        % sec - Sample time for current controller
Ts_simulink             = T_pwm;            % sec - Sample time for model simulation
Ts_motor                = T_pwm;            % sec - Sample time for motor simulation
Ts_inverter             = T_pwm;            % sec - Sample time for average value inverter
Ts_speed                = 10 * Ts;          % sec - Sample time for speed controller

target.serialBaud       = 230400; 
target.comport = 'COM4';
dataType = 'single';

%% Inverter Parameters
inverter.Rshunt     = 0.010;      % Ohm - Shunt resistor
inverter.MaxADCCnt  = 16383;      % 14-bit ADC resolution
inverter.HalfADCCnt = 8192;       % Half of the 14-bit ADC resolution
inverter.AOffset    = 8184;       % Counts - Ia offset
inverter.BOffset    = 8184;       % Counts - Ib offset
inverter.Rds_on     = 35e-3;      % Ohm
inverter.R_board    = inverter.Rds_on + inverter.Rshunt/3; % Ohm
inverter.V_dc       = 12;
inverter.V_max      = 45;
inverter.VoltPerCount = inverter.V_max/inverter.MaxADCCnt;
inverter.AMPPerCount  = -31.25/inverter.HalfADCCnt;
inverter.ISenseMax  = abs(inverter.HalfADCCnt * inverter.AMPPerCount);

%% Open Loop Parameters
Vd_Ref_openLoop_PU = 0.15;        % PU - D axis voltage applied for open-loop start-up
openLoopSpeed      = 500;         % rpm - Max speed for open-loop regime

%% Fault Parameters
overVoltage  = 16; % V
underVoltage = 8;  % V