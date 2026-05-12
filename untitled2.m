% Definicja danych testowych
x = [-1, 0, 1, 2, 7];          % Węzły
F = [-1, 10, -1, 2, 9];         % Wartości funkcji w węzłach
dInd = [2];           % Indeks węzła, dla którego znamy pochodną (x=1)
dVal = [-4];          % Wartość pochodnej dla węzła x=1

t = -2:0.1:7;         % Punkty, dla których chcemy narysować/obliczyć funkcję

% Wywołanie głównej funkcji
y = hermitek(t, x, F, dInd, dVal);

% Opcjonalne wyświetlenie wyników
plot(t, y);
grid on;