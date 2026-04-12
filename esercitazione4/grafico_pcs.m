% N: Dimensione del problema
N = [4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192];

% Vettore Colonna 1
time_bubble = [7.08e-07, 6.25e-07, 2.333e-06, 7.625e-06, 3.0958e-05, 0.000121416, ...
          0.000414083, 0.00196108, 0.00522762, 0.0169492, 0.045768, 0.17451];

% Vettore Colonna 2
time_insertion = [1.25e-07, 4.16e-07, 9.17e-07, 2.625e-06, 9e-06, 4.7917e-05, ...
             0.000100125, 0.000392208, 0.00174346, 0.00443371, 0.012845, 0.0481327];

% Vettore Colonna 3
time_selection = [2.08e-07, 6.25e-07, 1.583e-06, 4.625e-06, 1.5041e-05, 4.1583e-05, ...
             0.000287167, 0.000677042, 0.00209908, 0.00512008, 0.0156125, 0.0614109];
% Vettore Colonna 4
time_std = [1.834e-06, 2.9667e-05, 1.792e-06, 9.459e-06, 8.834e-06, 1.55e-05, ...
            5.1584e-05, 8.9875e-05, 0.000222334, 0.00029925, 0.00044225, 0.000993083];
figure  
plot(N,time_bubble, 'k','LineWidth',2);
hold on
plot(N,time_insertion, 'r','LineWidth',2);
plot(N,time_selection, 'g','LineWidth',2);
plot(N,time_std,'LineWidth',2);

grid on 
xlabel("Dimensione vettore");
ylabel("Tempo in secondi");
title(" Rappresentazione durata algoritmi di ordinamento");
legend("Tempo Bubble sort","Tempo Insertion sort","Tempo Selection sort","Tempo std sort");
