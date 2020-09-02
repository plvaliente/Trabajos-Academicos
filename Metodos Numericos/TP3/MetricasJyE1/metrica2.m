function [Cs,ds] = metrica2()
    inicio = 1987;
    fin = 2016;
    anios = fin - inicio +1;
    Cs = {};
    ds = {};
    for i = 1:anios
        fileID = fopen(strcat('estadisticasJugadores/equipos',int2str(inicio+i-1),'.txt'),'r');
        sizeA = [9 Inf];
        C = fscanf(fileID,'%f %f %f %f %f %f %f %f %f', sizeA);
        C = C';
        %log(TOV)
        C(:,5) = log(C(:,5));
        Cs(i) = {C};
        
        fileIDb = fopen(strcat('stats/winrate/leagues_NBA_',int2str(inicio+i-1),'_winrate.csv'),'r');
        sizeb = [1 Inf];
        d = fscanf(fileIDb,'%f', sizeb);
        d = d';
        ds(i) = {d};
        
        fclose('all');
    end
end
