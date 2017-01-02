%Musimy podaæ numer wiersza i numer kolumny od której Matlab ma zacz¹æ (W CSV
%numeruje od zera).
clear all;
close all;
dane= csvread('Out_1.csv',1,0);

iter=dane(:,1);
f_celu_best=dane(:,2);
kara_best=dane(:,3);
mutacje_best=dane(:,4);
f_celu_worst=dane(:,5);
kara_worst=dane(:,6);
mutacje_worst=dane(:,7);

figure(1)
plot(iter,f_celu_best,'b')
hold on;
plot(iter,f_celu_worst,'r')
xlabel('numer iteracji')
title('Wartoœæ funkcji celu dla najlepszego i najgorszego osobnika w pokoleniu')
figure(2)
plot(iter,kara_best,'b')
hold on;
plot(iter,kara_worst,'r')
xlabel('numer iteracji')
title('Wartoœæ kary dla najlepszego i najgorszego osobnika w pokoleniu')

figure(3)
plot(iter,mutacje_best,'b')
hold on;
plot(iter,mutacje_worst,'r')
xlabel('numer iteracji')
title('Iloœæ mutacji najlepszego i najgorszego osobnika')



