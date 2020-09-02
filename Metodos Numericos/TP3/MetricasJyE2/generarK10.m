function K10 = generarK10(N)
    Indices = crossvalind('Kfold', N, 10);
    K10 = zeros(N,10);
    for i = 1:10
        K10(:,i) = Indices; 
    end
    for i = 1:N
        for j = 1:10
            if K10(i,j) == j
                K10(i,j) = 0;
            else
                K10(i,j) = 1;
            end
        end
    end
end