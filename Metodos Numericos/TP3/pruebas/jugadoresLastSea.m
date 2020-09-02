function [matrizOf, matrizDef, ds] = jugadoresLastSea()
    inicio = 2011;
    fin = 2016;
    anios = fin - inicio +1;
    matrizOf = {};
    matrizDef = {};
    ds = {};
    for i = 1:anios
        fileID1 = fopen(strcat('estadisticasJugadores/equiposDef',int2str(inicio+i-1),'.txt'),'r');
        fileID2 = fopen(strcat('estadisticasJugadores/equiposDWS',int2str(inicio+i-1),'.txt'),'r');
        fileID3 = fopen(strcat('estadisticasJugadores/equiposOf',int2str(inicio+i-1),'.txt'),'r');
        fileID4 = fopen(strcat('estadisticasJugadores/equiposOWS',int2str(inicio+i-1),'.txt'),'r');
        
        sizeDa = [4 Inf];
        sizeDb = [1 Inf];
        sizeOa = [5 Inf];
        sizeOb = [1 Inf];
        
        Da = fscanf(fileID1,'%f %f %f %f', sizeDa);    %   idem cantidad de %f
        Db = fscanf(fileID2,'%f', sizeDb);
        Oa = fscanf(fileID3,'%f %f %f %f %f', sizeOa);
        Ob = fscanf(fileID4,'%f', sizeOb);
        
        Da = Da';
        Db = Db';
        Oa = Oa';
        Ob = Ob';
        
        D = [Da Db];
        O = [Oa Ob];
        
        matrizDef(i) = {D};
        matrizOf(i) = {O};
        
        fileIDb = fopen(strcat('stats/winrate/leagues_NBA_',int2str(inicio+i-1),'_winrate.csv'),'r');
        sizeb = [1 Inf];
        d = fscanf(fileIDb,'%f', sizeb);
        d = d';
        ds(i) = {d};
        
        fclose('all');
    end
end