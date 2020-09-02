
[As,bs] = metricalineal();
[Bs,bs] = metrica1();
[Cs,bs] = metrica2();
[Ds,bs] = metrica3();
Xlineal = validationTemp(As,bs);
Xmetrica1 = validationTemp(Bs,bs);
Xmetrica2 = validationTemp(Cs,bs);
Xmetrica3 = validationTemp(Ds,bs);


%%

[x1, anios] = size(bs);
MSlineal = [];
MSmetrica1 = [];
MSmetrica2 = [];
MSmetrica3 = [];

for i = 1:anios
    bRes = cell2mat(As(i)) * Xlineal ;
    err = mean((bRes-cell2mat(bs(i))).^2);
    MSlineal = [MSlineal err];
end

for i = 1:anios
    bRes = cell2mat(Bs(i)) * Xmetrica1 ;
    err = mean((bRes-cell2mat(bs(i))).^2);
    MSmetrica1 = [MSmetrica1 err];
end

for i = 1:anios
    bRes = cell2mat(Cs(i)) * Xmetrica2 ;
    err = mean((bRes-cell2mat(bs(i))).^2);
    MSmetrica2 = [MSmetrica2 err];
end

for i = 1:anios
    bRes = cell2mat(Ds(i)) * Xmetrica3 ;
    err = mean((bRes-cell2mat(bs(i))).^2);
    MSmetrica3 = [MSmetrica3 err];
end


%%

hold on
plot(x, MSlineal,'r')
plot(x, MSmetrica1, '--')
plot(x, MSmetrica2, 'b')
plot(x, MSmetrica3, 'g')

hold off

%%

[Es,bs] = equipos(1,1,1,1,1,1);
[Fs,bs] = equipos(2,2,2,1,1,1/2);
[Gs,bs] = equipos(1/2,1,1,2,2,1);

Xlineal = validationTemp(Es,bs);
Xmetrica1 = validationTemp(Fs,bs);
Xmetrica2 = validationTemp(Gs,bs);

%%

[x1, anios] = size(bs);
MSlineal = [];
MSmetrica1 = [];
MSmetrica2 = [];

for i = 1:anios
    bRes = cell2mat(Es(i)) * Xlineal ;
    err = mean((bRes-cell2mat(bs(i))).^2);
    MSlineal = [MSlineal err];
end

for i = 1:anios
    bRes = cell2mat(Fs(i)) * Xmetrica1 ;
    err = mean((bRes-cell2mat(bs(i))).^2);
    MSmetrica1 = [MSmetrica1 err];
end

for i = 1:anios
    bRes = cell2mat(Gs(i)) * Xmetrica2 ;
    err = mean((bRes-cell2mat(bs(i))).^2);
    MSmetrica2 = [MSmetrica2 err];
end


%%

hold on
plot(x, MSlineal,'r')
plot(x, MSmetrica1, '--g')
plot(x, MSmetrica2, 'b')

hold off