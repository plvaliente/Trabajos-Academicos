function [Cs,ds] = jugadores(e1,e2,e3,e4,e5,e6)
    inicio = 2011;
    fin = 2016;
    anios = fin - inicio +1;
    Cs = {};
    ds = {};
    for i = 1:anios
        fileID = fopen(strcat('estadisticasJugadores/equipos',int2str(inicio+i-1),'.txt'),'r');
        sizeA = [6 Inf];                            %cambiar el 4 a mano por la cantidad de parametros
        C = fscanf(fileID,'%f %f %f %f %f %f', sizeA);    %   idem cantidad de %f
        C = C';
        C(:,1) = C(:,1).^e1;
        C(:,2) = C(:,2).^e2;
        C(:,3) = C(:,3).^e3;
        C(:,4) = C(:,4).^e4;
        C(:,3) = C(:,5).^e5;
        C(:,4) = C(:,6).^e6;
        Cs(i) = {C};
        
        fileIDb = fopen(strcat('stats/winrate/leagues_NBA_',int2str(inicio+i-1),'_winrate.csv'),'r');
        sizeb = [1 Inf];
        d = fscanf(fileIDb,'%f', sizeb);
        d = d';
        ds(i) = {d};
        
        fclose('all');
    end
end