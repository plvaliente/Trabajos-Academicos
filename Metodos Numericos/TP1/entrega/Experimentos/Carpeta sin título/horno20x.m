function horno20x()

%ifid = fopen('test9020c.in');


isofid1 = fopen('isofile2025c');
isofid2 = fopen('isofile2050c');
isofid3 = fopen('isofile2075c');
isofid4 = fopen('isofile20100c');
isofid5 = fopen('isofile2015c');

isofids = [isofid1, isofid2, isofid3, isofid4, isofid5];

angulos = [25,50,75,100,15];
radios = 20;
radioi = 10;
radioe = 100;
%puntos = angulos*radios(1);
%caloriso = 500;
%deltaAng = 2*pi/angulos;
%deltaRad = (radioe-radioi)/(radios-1);

%armado de b 
%b = zeros(puntos,1);
%baux = fscanf(ifid,'%f',2*angulos);
%b(1:angulos) = baux(1:angulos);
%b(end-angulos+1:end) = baux(angulos+1:end);

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

interno=linspace(radioi,radioi,angulos(4)+1);
externo=linspace(radioe,radioe,angulos(4)+1);

figure;
theta1=linspace(0,2*pi,angulos(1)+1);
theta2=linspace(0,2*pi,angulos(2)+1);
theta3=linspace(0,2*pi,angulos(3)+1);
theta4=linspace(0,2*pi,angulos(4)+1);
%theta5=linspace(0,2*pi,angulos(5)+1);


polar(theta4,externo);
hold on;
polar(theta4,interno);

radioiso1 = fscanf(isofids(1), '%f',angulos(1));
radioiso1 = [radioiso1; radioiso1(1)];
radioiso1 = radioiso1';
polar(theta1,radioiso1, '--*r');

radioiso2 = fscanf(isofids(2), '%f',angulos(2));
radioiso2 = [radioiso2; radioiso2(1)];
radioiso2 = radioiso2';
polar(theta2,radioiso2, 's');

radioiso3 = fscanf(isofids(3), '%f',angulos(3));
radioiso3 = [radioiso3; radioiso3(1)];
radioiso3 = radioiso3';
polar(theta3,radioiso3, '-o');


radioiso4 = fscanf(isofids(4), '%f',angulos(4));
radioiso4 = [radioiso4; radioiso4(1)];
radioiso4 = radioiso4';
polar(theta4,radioiso4, '--x');

%radioiso5 = fscanf(isofids(5), '%f',angulos(5));
%radioiso5 = [radioiso5, radioiso5(1)];
%radioiso5 = radioiso5';
%polar(theta5,radioiso5, '.');

hold off;
pause;

