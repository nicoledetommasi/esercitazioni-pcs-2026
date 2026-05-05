
% Dimensioni dell'input
size = [1 11 21 31 41 51 61 71 81 91];

% Tempi di esecuzione (in secondi)
Bubble = [2.08e-09 2.6667e-07 8.9e-07 2.00125e-06 3.18667e-06 4.46125e-06 6.47792e-06 7.57541e-06 8.96459e-06 9.59167e-06];
Insertion = [1.67e-09 2.8291e-07 2.5833e-07 4.3875e-07 6.6333e-07 9.2e-07 1.20917e-06 1.31875e-06 1.63958e-06 3.08708e-06];
Selection = [4.58e-09 2.4208e-07 6.3292e-07 1.21625e-06 1.83041e-06 2.57417e-06 3.62459e-06 4.15791e-06 4.76291e-06 9.07834e-06];
Mergesort = [1.66e-09 7.275e-07 1.44834e-06 2.24667e-06 3.12833e-06 4.07541e-06 4.90917e-06 4.99167e-06 5.78792e-06 8.93375e-06];
Quicksort = [4.58e-09 2.1458e-07 4.8916e-07 7.9916e-07 1.08959e-06 1.43583e-06 1.80416e-06 1.85083e-06 2.0075e-06 4.40833e-06];
stdSort = [4.58e-09 1.2166e-07 4.7417e-07 6.0625e-07 8.4959e-07 1.1375e-06 1.40375e-06 1.47375e-06 1.565e-06 3.86875e-06];


figure 
semilogy(size, Bubble, 'k','LineWidth',2, 'DisplayName','Bubble sort');
hold on
semilogy(size, Insertion, 'g','LineWidth',2,'DisplayName','Insertion sort');
semilogy(size, Mergesort, 'r','LineWidth',2,'DisplayName','Merge sort');
semilogy(size, Quicksort,'LineWidth',2,'DisplayName','Quicksort');
semilogy(size, stdSort,'b','LineWidth',2,'DisplayName','std_sort');
xlabel('Dimensione Array (n)');
ylabel('Tempo (s)');
title('Confronto Tempi di Esecuzione');
legend('Location', 'northwest'); 
grid on;