x=87:1:99;
y=0:1:16;
x = [x y];
xla = 07:1:16;
%%
lOf = [];
lDef = [];
for i = 1:30
    Ro=cell2mat(D(i));
    lrd = Ro*XdCVA;
    err = mean((lrd-cell2mat(jB(i))).^2);
    lDef = [lDef err];
end
for i = 1:30
    Ro=cell2mat(O(i));
    lro = Ro*XoCVA;
    erro = mean((lro-cell2mat(jB(i))).^2);
    lOf = [lOf erro];
end
hold on;
plot(lOf,'r');
plot(lDef,':');
hold off;
%%
lI = [];
for i = 1:30
    Ri=cell2mat(I(i));
    lri = Ri*xIcv;
    erri = mean((lri-cell2mat(bI(i))).^2);
    lI= [lI erri];
end
plot(lI);
%%
lI = [];
for i = 1:30
    Ri=cell2mat(I(i));
    lri = Ri*xIcv;
    erri = mean((lri-cell2mat(bI(i))).^2);
    lI= [lI erri];
end
lA = [];
for i = 1:30
    Ra=cell2mat(A(i));
    lra = Ra*XaCV;
    erra = mean((lra-cell2mat(Be(i))).^2);
    lA= [lA erra];
end
hold on;
plot(lA, ':');
plot(lI,'r');
hold off;