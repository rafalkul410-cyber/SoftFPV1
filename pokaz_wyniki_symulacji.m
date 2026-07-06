function pokaz_wyniki_symulacji(czas_in, varargin)
    % Ustalenie siatki (2 kolumny)
    liczba_elementow = length(varargin);
    kolumny = 2; 
    if liczba_elementow == 1
        kolumny = 1;
    end
    wiersze = ceil(liczba_elementow / kolumny);

    % Wyciągnięcie wektora czasu ze struktury
    czas = czas_in.signals.values;
    
    % Tworzenie czystego, białego okna
    figure('Color', 'w');

    % Rysowanie w pętli dla każdego przekazanego sygnału
    for i = 1:liczba_elementow
        subplot(wiersze, kolumny, i);
        
        % Pobranie i-tego sygnału
        sygnal = varargin{i};
        dane_y = sygnal.signals.values;
        
        % Rysowanie linii
        plot(czas, dane_y, 'LineWidth', 1.2);
        
        % Stylizacja
        grid on;
        xlabel('t [s]');
        
        % Podpisanie osi Y automatycznie na podstawie nazwy wpisanej w komendzie
        nazwa_zmiennej = inputname(i+1); 
        if ~isempty(nazwa_zmiennej)
            podzial = split(nazwa_zmiennej, '.');
            nazwa_zmiennej = podzial{end};
            nazwa_zmiennej = strrep(nazwa_zmiennej, '_', '\_'); % Zabezpieczenie przed znakiem podkreślenia
            ylabel(nazwa_zmiennej);
        else
            ylabel(sprintf('Sygnał %d', i));
        end
    end
end