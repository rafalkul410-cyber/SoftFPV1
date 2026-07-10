function wykresy(czas_in, varargin)
% Funkcja rysująca wykresy z Simulinka.
% Użycie: wykresy(out.T, out.throttle_ref, out.pitch_ref, out.x_s, ...)
% czas_in - wektor czasu (jako pierwszy argument)
% varargin - dowolna liczba kolejnych sygnałów do narysowania

    % 1. Wyciągnięcie wektora czasu (odporność na różne formaty Simulinka)
    if isa(czas_in, 'timeseries')
        czas = czas_in.Data;
    elseif isstruct(czas_in)
        czas = czas_in.signals.values;
    else
        czas = czas_in; % Zwykła tablica (najczęstszy przypadek)
    end

    % 2. Ustalenie siatki (2 kolumny, odpowiednia liczba wierszy)
    liczba_wykresow = length(varargin);
    kolumny = 2; 
    if liczba_wykresow == 1
        kolumny = 1; % Jeśli podasz tylko jeden sygnał, daj na cały ekran
    end
    wiersze = ceil(liczba_wykresow / kolumny);

    % 3. Tworzenie okna
    figure('Color', 'w'); % Białe tło (jak na Twoim wzorze)

    % 4. Rysowanie w pętli
    for i = 1:liczba_wykresow
        subplot(wiersze, kolumny, i);
        
        sygnal = varargin{i};
        
        % Wydobycie danych (Timeseries, Structure lub Array)
        if isa(sygnal, 'timeseries')
            dane_y = sygnal.Data;
        elseif isstruct(sygnal)
            dane_y = sygnal.signals.values;
        else
            dane_y = sygnal;
        end
        
        % Ochrona przed błędem różnej długości wektorów (np. czas vs sygnał)
        if length(czas) ~= length(dane_y)
            % Jeśli długości się różnią, ucinamy do krótszego
            min_len = min(length(czas), length(dane_y));
            plot(czas(1:min_len), dane_y(1:min_len), 'LineWidth', 1.2);
        else
            plot(czas, dane_y, 'LineWidth', 1.2);
        end
        
        % Stylizacja wykresu
        grid on;
        xlabel('t [s]');
        
        % 5. Automatyczne pobieranie nazwy do osi Y
        % inputname() pobiera oryginalną nazwę zmiennej wpisaną w wywołaniu funkcji
        nazwa_zmiennej = inputname(i+1); 
        
        if ~isempty(nazwa_zmiennej)
            % Usunięcie prefiksu "out." (np. out.pitch_ref -> pitch_ref)
            podzial = split(nazwa_zmiennej, '.');
            nazwa_zmiennej = podzial{end};
            
            % MATLAB interpretuje "_" jako indeks dolny, musimy to zabezpieczyć
            nazwa_zmiennej = strrep(nazwa_zmiennej, '_', '\_'); 
            ylabel(nazwa_zmiennej);
        else
            ylabel(sprintf('Sygnał %d', i));
        end
    end
end