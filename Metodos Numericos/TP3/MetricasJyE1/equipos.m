function [As,bs] = equipos(e1,e2,e3,e4,e5,e6)
    inicio = 1987;
    fin = 2016;
    anios = fin - inicio +1;
    As = {};
    bs = {};
    for i = 1:anios
        fileID = fopen(strcat('estadisticasEquipos/equipos',int2str(inicio+i-1),'.txt'),'r');
        sizeA = [6 Inf];                            %cambiar el 3 a mano por la cantidad de parametros
        A = fscanf(fileID,'%f %f %f %f %f %f', sizeA);       %   idem cantidad de %f
        A = A';
        A(:,1) = A(:,1).^e1;
        A(:,2) = A(:,2).^e2;
        A(:,3) = A(:,3).^e3;
        A(:,1) = A(:,4).^e4;
        A(:,2) = A(:,5).^e5;
        A(:,3) = A(:,6).^e6;
        
        As(i) = {A};
        
        fileIDb = fopen(strcat('stats/winrate/leagues_NBA_',int2str(inicio+i-1),'_winrate.csv'),'r');
        sizeb = [1 Inf];
        b = fscanf(fileIDb,'%f', sizeb);
        b = b';
        bs(i) = {b};
        
        fclose('all');
    end
end