function [MSerrores,MSE,y] = validationTemp(As,bs)
    [x1, anios] = size(As);
	y= [];
    MSerrores = [];
    for i = 1:(anios-5)
        A = [];
        b = [];
        for j = 1:5
            A = [A ; cell2mat(As(i+j-1))];
            b = [b ; cell2mat(bs(i+j-1))];
        end
        
        x = lsqlin(A,b);
        
        bRes = cell2mat(As(i+5)) * x;
        err = mean((bRes-cell2mat(bs(i+5))).^2);
        MSerrores = [MSerrores err];
		if err <= min(MSerrores)
            y=x;
    end
    MSE = mean(MSerrores);
end
