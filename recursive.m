function [Q, errest] = recursive(f, a, b, tol, recLev)
% Autor: Julian Kasiński
% Funkcja wywołująca funkcje span_integral na przepołownionym przedziale 
% [a, b]

% Oblicznie później wykorzystywanych zmiennych, by ograniczyć powtarzanie
% tych samych działań
tol2 = tol / 2;
recLev2 = recLev - 1;
c = (a + b) / 2;

% Wywoływanie funkcji span_integral i zsumowanie wyników
[Q, errest] = span_integral(f, a, c, tol2, recLev2);
[Q2, errest2] = span_integral(f, c, b, tol2, recLev2);
Q = Q + Q2; 
errest = errest + errest2;