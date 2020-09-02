k1F5ext = [188.201760,209.350755,240.588436,397.595073,451.150435,521.604170,573.174043,748.799679,874.796789,1173.945600];
k3F5ext = [200.065745,222.090694,250.668927,387.860208,442.071308,510.679579,571.024019,719.802857,867.778884,1173.445152];
k5F5ext = [199.955144,217.978472,249.513121,379.958048,430.455346,495.053185,556.424098,719.038805,864.629052,1163.856279];

k1F10ext = [246.803965,269.802023,315.644364,578.077429,697.440951,812.518723,944.757237,1101.000966,1308.506691,1813.938072];
k3F10ext = [263.880963,301.125864,356.142080,584.341484,703.002398,819.807056,939.120756,1087.788234,1315.686229,1803.277000];
k5F10ext = [261.906215,299.024752,355.725540,566.586453,672.817273,788.428773,918.772916,1065.014160,1303.574003,1795.810046];

k1F5 = [188.201760,209.350755,240.588436,397.595073,451.150435,521.604170,573.174043];
k3F5 = [200.065745,222.090694,250.668927,387.860208,442.071308,510.679579,571.024019];
k5F5 = [199.955144,217.978472,249.513121,379.958048,430.455346,495.053185,556.424098];

k1F10 = [246.803965,269.802023,315.644364,578.077429,697.440951,812.518723,944.757237];
k3F10 = [263.880963,301.125864,356.142080,584.341484,703.002398,819.807056,939.120756];
k5F10 = [261.906215,299.024752,355.725540,566.586453,672.817273,788.428773,918.772916];


alphasext = [1,5,10,20,30,40,50,75,100,150]
alphas = [1,5,10,20,30,40,50]

hold on
plot(alphasext,k1F5ext,'-.og')
plot(alphasext,k3F5ext,'-.xr')
plot(alphasext,k5F5ext,'-.*b')
plot(alphasext,k1F10ext,'-og')
plot(alphasext,k3F10ext,'-xr')
plot(alphasext,k5F10ext,'-*b')
hold off