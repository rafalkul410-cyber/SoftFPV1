function pokaz_wyniki_symulacji(czas, varargin)
    % Czas: wektor czasu (np. T)
    % varargin: lista zmiennych (np. throttle_ref, pitch_ref, ...)
    
    figure('Color', 'w');
    liczba_wykresow = length(varargin);
    
    kolumny = 2; 
    wiersze = ceil(liczba_wykresow / kolumny);

    for i = 1:liczba_wykresow
        subplot(wiersze, kolumny, i);
        
        dane = varargin{i};
        % Wyciągamy czystą nazwę zmiennej, którą wpisałeś w nawiasie
        nazwa = inputname(i+1); 
        
        % Rysowanie (obsługa formatów Simulinka)
        plot(czas, bezpiecznie_pobierz(dane), 'LineWidth', 1.2);
        
        grid on;
        xlabel('t [s]');
        
        % Ustawienie opisu osi Y (bez jednostek, z obsługą podkreślników)
        if ~isempty(nazwa)
            ylabel(strrep(nazwa, '_', '\_'));
        else
            ylabel(['Sygnał ', num2str(i)]);
        end
    end
end

function dane = bezpiecznie_pobierz(wejscie)
    % Sprawdza czy to timeseries, struct czy zwykła tablica
    if isa(wejscie, 'timeseries')
        dane = wejscie.Data;
    elseif isstruct(wejscie) && isfield(wejscie, 'signals')
        dane = wejscie.signals.values;
    else
        dane = wejscie;
    end
    dane = squeeze(double(dane));
end