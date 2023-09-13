 %% ************************************************************************
% Model         :   Open Loop Control of 3-phase motors
% Description   :   Set Parameters for Open Loop Control of 3-phase motors
% File name     :   mcb_open_loop_control_data_MCSPTE1AK144.m
%
% Copyright 2022 The MathWorks, Inc.

%% Non - configurable parameters 
%Set PWM Switching frequency
PWM_frequency 	= 20e3;         %Hz         // Switching frequency, example is configured only for this frequency

% Set Sample Times
T_pwm           = 1/PWM_frequency;  %sec    // PWM switching time period
Ts          	= 2*T_pwm;          %sec    // Sample time for controller
Ts_uart         = 0.03;         %Sec        // Sample time for UART TX  

%% Configurable Parameters - Update and run this script to update base workspace

% Set data type for controller & code-gen
dataType = 'single';            % Floating point code-generation

% System Parameters // Hardware parameters 

% Update motor details below
motor.polePairs     = 2;            %       // Pole Pairs for the motor
motor.base_speed    = 2000;         %rpm    // Rated speed (Synchronous Speed)

% Update inverter's DC-link voltage below
inverter.V_dc       = 12;           %volts  // DC-link voltage of inverter
inverter.ISenseMax      = 15.625;   %Amps   // Max current that can be measured by ADC
inverter.CtSensAOffset  = 2027;     %Counts // ADC Offset for phase-A
inverter.CtSensBOffset  = 2038;     %Counts // ADC Offset for phase-B

% Target com port
Target.comport              = 'COM4';       % Serial communication port of the device;

% Derive Parameters
%Get base frequency from: Speed (rpm) = 60*freq/polePairs
motor.base_freq     = motor.base_speed*motor.polePairs/60;  