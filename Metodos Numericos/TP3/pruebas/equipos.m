function [As,bs] = equipos()
    inicio = 1987;
    fin = 2016;
    anios = fin - inicio +1;
    As = {};
    bs = {};
    for i = 1:anios
        fileID = fopen(strcat('estadisticasEquipos/equipos',int2str(inicio+i-1),'.txt'),'r');
        fileID2 = fopen(strcat('estadisticasEquipos/equiposMisc',int2str(inicio+i-1),'.txt'),'r');
        sizeA = [8 Inf];                            %cambiar el 3 a mano por la cantidad de parametros
        sizeB = [1 Inf];
        A = fscanf(fileID,'%f %f %f %f %f %f %f %f', sizeA);       %   idem cantidad de %f
        B = fscanf(fileID2,'%f', sizeB);
        A = A';
        B = B';
        A = [A B];
        %RB^2
        A(:,2) = A(:,2).^2;
        %sqrt(TOV)
        A(:,5) = sqrt(A(:,5));
        %FTperc^2
        A(:,6) = A(:,6).^2;
        %sqrt(log(PF))
        A(:,8) = sqrt(log(A(:,8)));
        
        As(i) = {A};
        
        fileIDb = fopen(strcat('stats/winrate/leagues_NBA_',int2str(inicio+i-1),'_winrate.csv'),'r');
        sizeb = [1 Inf];
        b = fscanf(fileIDb,'%f', sizeb);
        b = b';
        bs(i) = {b};
        
        fclose('all');
    end
end