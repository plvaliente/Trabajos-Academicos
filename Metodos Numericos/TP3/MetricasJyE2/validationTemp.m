function X = validationTemp(As,bs)
    [x1, anios] = size(As);

    MSerrores = [];
    xs = [];
    errs = [];
    for i = 1:(anios-5)
        A = [];
        b = [];
        for j = 1:5
            A = [A ; cell2mat(As(i+j-1))];
            b = [b ; cell2mat(bs(i+j-1))];
        end
        %[s1,s2] = size(A)
        %size(b)
        x = lsqlin(A,b);
        
        bRes = cell2mat(As(i+5)) * x;
        err = mean((bRes-cell2mat(bs(i+5))).^2);
        MSerrores = [MSerrores err];
        xs = [xs x];
        errs = [errs err];
    end
    xs;
    [x, i] = min(errs);
    xst = xs';
    %X = xs(1:9,i);
    X = mean(xst);
    X = X';
end