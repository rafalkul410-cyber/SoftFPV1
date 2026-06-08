
%%m zalozone parametry

FPV_mass=0.8;
A=0.03; %pole rzutu z porzdu
Cd = 0.8; %uśredniony wsp oporu
p_0=1013.25; %hPa
T=0.1;
Ts=0.005;
takeOffDuration=2;
ks=0;
g=9.81;
takeoffgain=1.2;
MaxThrustSaturation=16.0;%% w newtonach max 4 silników TĄ WAROŚĆ TRZEBA WYZNACZYĆ

Q2Ts = forcetomotors();

% Rotor Dynamics  do pliku %%

Vehicle.Rotor.theta0=0.0;
Vehicle.Rotor.theta1=0.0005;
Vehicle.Rotor.lock=10.0;
Vehicle.Rotor.Ct=0.085;
Vehicle.Rotor.radius=0.0635;
Vehicle.Rotor.area=0.01267;
Vehicle.Rotor.Cq=0.007;
