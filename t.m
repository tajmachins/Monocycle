function [Q2, Q1] = t(f, a, b, n)
% Autor: Julian Kasiński
% Funkcja przybliżająca wartość całki funkcji f na przedziale [a, b]
% kwadraturą Tn-1,n-1 (Q1) i Tn-2,n-2 (Q2)

R1 = zeros(n, 1); % rząd tablicy Romberga który już wypełniliśmy
R2 = R1; % rząd tablicy Romberga na którym działamy
h = b - a; % długość podprzedziałów na których działamy
k = 1; % ilość przedziałów przy kwadraturze prostokątów do obliczania Ti,0
l = ones(n, 1); % tablica na potęgi 4

% Pierwszy element tablicy
R1(1) = 0.5 * h * (f(a) + f(b));

for i = 2:n
    h = h / 2; % skrócenie długości podprzedziałów na 2
    sum = 0; % suma używana do obliczenia złożonej kwadratury prostokątów
    for j = 1:k
        sum = sum + f(a + (2 * j - 1) * h);
    end
    R2(1) = 0.5 * R1(1) + sum * h; % wypełnianie 1 kolumny tablicy Romberga
    l(i) = l(i - 1) * 4; % wypełnianie tablicy potęg 4
    for j = 1:(i - 1) % wypełnianie innych kolumn tablicy Romberga
        j2 = j + 1;
        R2(j2) = ((l(j2) * R2(j)) - R1(j)) / (l(j2) - 1);
    end
    k = k * 2; 
    [R1, R2] = swap(R1, R2);
end

% zwracanie przybliżenia całki kwadraturami Tn-1,n-1 (Q1) i Tn-2,n-2 (Q2)
Q1 = R1(n);
Q2 = R2(n - 1);