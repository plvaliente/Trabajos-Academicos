lOv = [];
for i = 1:10
    Rv=cell2mat(Ae0(i));
    l0 = Rv*x0CV;
    er = mean((l0-cell2mat(be0(i))).^2);
    lOv = [lOv er];
end
plot(lOv,'r');