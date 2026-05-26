function [Q, errest] = rombergs_method(f, a, b)
% Autor: Julian Kasiński
% Funkcja przybliżająca wartość całki funkcji f na przedziale [a, b]
% kwadraturą T8,8, T7,7 i G17, zwracająca wartość wyliczoną kwadraturą T8,8
% i oszacowanie "pół-względnego" błędu obliczonego przybliżenia całki
% kwadraturą T8,8

[Q7, Q] = t(f, a, b, 9);
Q17 = g17(f, a, b);

% Szacowanie "pół-względnego" błędu obliczonego przybliżenia całki
divisor = max([1, Q, -Q]);
dividend = max([abs(Q - Q7), abs(Q - Q17)]);
errest = dividend / divisor;

