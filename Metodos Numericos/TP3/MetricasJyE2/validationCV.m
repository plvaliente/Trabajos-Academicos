function [MSerrores,MSE,y] = validationCV(As,bs)
    [x1, anios] = size(As);
    equipostotal = 0;
    A = [];
    b = [];
    y= [];
    for i = 1:anios
        [t1,t2] = size(cell2mat(bs(i)));
        equipostotal = equipostotal + t1;
        A = [A ; cell2mat(As(i))];
        b = [b ; cell2mat(bs(i))];
    end
    K = generarK10(equipostotal);
    equipostotal;
    [m,n] = size(K);
    MSerrores = [];
    for i = 1:n
        TrainAi = [];
        Trainbi = [];
        TestAi = [];
        Testbi = [];
        for j = 1:m;
            if K(j,i) == 1
                TrainAi = [TrainAi ; A(j,:)];
                Trainbi = [Trainbi ; b(j)];
            else
                TestAi = [TestAi ; A(j,:)];
                Testbi = [Testbi ; b(j)];
            end
        end
        x = lsqlin(TrainAi,Trainbi);
        bRes = TestAi*x;
        err = mean((bRes-Testbi).^2);
        MSerrores = [MSerrores err];
        if err <= min(MSerrores)
            y=x;
    end
    MSE = mean(MSerrores);
end
