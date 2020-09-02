function [Cs,ds] = metrica3()
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
        %STL^2
        C(:,4) = C(:,4).^2;
	%BLK^2        
	C(:,8) = C(:,8).^2;
	%log(PF)
        C(:,9) = log(C(:,9));
        
        Cs(i) = {C};
        
        fileIDb = fopen(strcat('stats/winrate/leagues_NBA_',int2str(inicio+i-1),'_winrate.csv'),'r');
        sizeb = [1 Inf];
        d = fscanf(fileIDb,'%f', sizeb);
        d = d';
        ds(i) = {d};
        
        fclose('all');
    end
end
