%Musimy poda� numer wiersza i numer kolumny od kt�rej Matlab ma zacz�� (W CSV
%numeruje od zera).

dane= csvread('Out_.txt',1,0);

iter=dane(:,1);
f_celu_best=dane(:,2);
kara_best=dane(:,3);
mutacje_best=dane(:,4);
f_celu_worst=dane(:,5);
kara_worst=dane(:,6);
mutacje_worst=dane(:,7);

figure(1)
plot(iter,f_celu_best,'b')
xlabel('numer iteracji')
ylabel('Warto�� funkcji celu dla najlepszego osobnika w pokoleniu')

figure(2)
plot(iter,kara_best,'b')
xlabel('numer iteracji')
ylabel('Warto�� kary dla najlepszego osobnika w pokoleniu')

figure(3)
plot(iter,mutacje_best,'b')
xlabel('numer iteracji')
ylabel('Ilo�� mutacji najlepszego osobnika')

figure(4)
plot(iter,f_celu_worst,'b')
xlabel('numer iteracji')
ylabel('Warto�� funkcji celu dla najgorszego osobnika w pokoleniu')

figure(5)
plot(iter,kara_worst,'b')
xlabel('numer iteracji')
ylabel('Warto�� kary dla najgorszego osobnika w pokoleniu')

figure(6)
plot(iter,mutacje_worst,'b')
xlabel('numer iteracji')
ylabel('Ilo�� mutacji najgorszego osobnika')

