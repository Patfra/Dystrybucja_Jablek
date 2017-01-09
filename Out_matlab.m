%Musimy poda� numer wiersza i numer kolumny od kt�rej Matlab ma zacz�� (W CSV
%numeruje od zera).
clear all;
dane= csvread('Out_2_8.csv',1,0);

iter=dane(:,1);
f_celu_best=dane(:,2);
kara_best=dane(:,3);
mutacje_best=dane(:,4);
f_celu_worst=dane(:,5);
kara_worst=dane(:,6);
mutacje_worst=dane(:,7);

figure()
plot(iter,f_celu_best,'b')
hold on;
plot(iter,f_celu_worst,'r')
xlabel('numer iteracji')
title('Warto�� funkcji celu dla najlepszego i najgorszego osobnika w pokoleniu')
% figure()
% plot(iter,kara_best,'b')
% hold on;
% plot(iter,kara_worst,'r')
% xlabel('numer iteracji')
% title('Warto�� kary dla najlepszego i najgorszego osobnika w pokoleniu')
% 
% figure()
% plot(iter,mutacje_best,'b')
% hold on;
% plot(iter,mutacje_worst,'r')
% xlabel('numer iteracji')
% title('Ilo�� mutacji najlepszego i najgorszego osobnika')



