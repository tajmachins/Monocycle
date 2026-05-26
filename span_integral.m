function [Q, errest] = span_integral(f, a, b, tol, recLev)
% Autor: Julian Kasiński
% Funkcja przybliżająca wartość całki funkcji f na przedziale [a, b]
% kwadraturą T8,8, starająca się osiągnąć błąd mniejszy niż podany w tol,
% wywołując się rekursywnie, ale nie więcej niż recLev razy

% Ustawienie wartości domyślnych dla tol i recLev
arguments
    f 
    a 
    b 
    tol = 1e-10
    recLev = 18
end

% Oszacowanie wartości całki kwadraturą t8,8 i błędu
[Q, errest] = rombergs_method(f, a, b);

% Wywołanie funkcji rekursywnie, jeśli limit nie jest osiągnięty, a 
% oszacowany błąd jest większy niż tol
if recLev >= 1 && errest > tol
    [Q, errest] = recursive(f, a, b, tol, recLev);
end
