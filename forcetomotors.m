function Q2Ts = forcetomotors()
    % --- Tutaj wklej swoje stałe geometryczne ---
    d = 0.15;
    R = 0.0635;
    Ct = 0.085;
    Cq = 0.005;
    
    % --- Obliczanie macierzy ---
    yawFactor = Cq / Ct * R;
    geomFactor = d * sqrt(2)/2;
    
    Ts2Q = [ 1,          1,          1,          1; ...
             yawFactor, -yawFactor,  yawFactor, -yawFactor; ...
            -geomFactor, -geomFactor,  geomFactor,  geomFactor; ...
            -geomFactor,  geomFactor,  geomFactor, -geomFactor];
        
    % --- Zwracamy macierz odwrotną ---
    Q2Ts = inv(Ts2Q);
end