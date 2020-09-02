function hornox20()

ifid = fopen('test9020c.in');

isofid1 = fopen('isofile1020c');
isofid2 = fopen('isofile3020c');
isofid3 = fopen('isofile5020c');
isofid4 = fopen('isofile7020c');
isofid5 = fopen('isofile9020c');
isofids = [isofid1, isofid2, isofid3, isofid4, isofid5];

angulos = 20;
radios = [10,30,50,70,90];
ndisc = 3 ;
radioi = 10;
radioe = 100;
puntos = angulos*radios(1);
caloriso = 500;
deltaAng = 2*pi/angulos;
deltaRad = (radioe-radioi)/(radios(3)-1);

%armado de b 
b = zeros(puntos,1);
baux = fscanf(ifid,'%f',2*angulos);
b(1:angulos) = baux(1:angulos);
b(end-angulos+1:end) = baux(angulos+1:end);

%xdib = zeros(puntos,1);
%ydib = zeros(puntos,1);

%pis = linspace(0,2*pi,angulos+1);
%pis = pis(1:angulos);

%for i=1:radios(1)
%    radAct = radioi + deltaRad*(i-1); 
%    for j=1:angulos;
%       xdib(idx(i,j,angulos)) = cos(pis(j))*radAct;
%       ydib(idx(i,j,angulos)) = sin(pis(j))*radAct;
%    end
%end

%aca ploteo las isotermas

theta=linspace(0,2*pi,angulos+1);
interno=linspace(radioi,radioi,angulos+1);
externo=linspace(radioe,radioe,angulos+1);
figure;

polar(theta,externo);
hold on;
polar(theta,interno);

radioiso1 = fscanf(isofids(1), '%f',angulos);
radioiso1 = [radioiso1; radioiso1(1)];
radioiso1 = radioiso1';
polar(theta,radioiso1, '--*');

radioiso2 = fscanf(isofids(2), '%f',angulos);
radioiso2 = [radioiso2; radioiso2(1)];
radioiso2 = radioiso2';
polar(theta,radioiso2, 's');

radioiso3 = fscanf(isofids(3), '%f',angulos);
radioiso3 = [radioiso3; radioiso3(1)];
radioiso3 = radioiso3';
polar(theta,radioiso3, '-o');

radioiso4 = fscanf(isofids(4), '%f',angulos);
radioiso4 = [radioiso4; radioiso4(1)];
radioiso4 = radioiso4';
polar(theta,radioiso4, 'x');

radioiso5 = fscanf(isofids(5), '%f',angulos);
radioiso5 = [radioiso5; radioiso5(1)];
radioiso5 = radioiso5';
polar(theta,radioiso5, '+');


hold off;
pause;

