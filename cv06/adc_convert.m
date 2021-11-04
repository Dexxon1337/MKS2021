ntc_vals = csvread("ntc.csv");
t = ntc_vals(:,1);
r = ntc_vals(:,2);
ad = zeros(156,1);
for i=1:156
   ad(i) = 1024 * (r(i)/(r(i)+10)); 
end
ad = ad(:,1);
plot(ad, t);
p = polyfit(ad, t, 5);
ad2 = 0:1023;
t2 = round(polyval(p, ad2), 1);
hold on, plot(ad2, t2, "r");
dlmwrite("data.dlm", t2*10, ",");