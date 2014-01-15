close all;
clear
CN_true = zeros(4,10);
CN_false = zeros(4,10);
RA_true = zeros(4,10);
RA_false = zeros(4,10);
RAC_true = zeros(4,10);
RAC_false = zeros(4,10);

CN_true(1,:) = dlmread('data/SG1_p_5_CN_true.txt');
CN_false(1,:) = dlmread('data/SG1_p_5_CN_false.txt');
RA_true(1,:) = dlmread('data/SG1_p_5_RA_true.txt');
RA_false(1,:) = dlmread('data/SG1_p_5_RA_false.txt');
RAC_true(1,:) = dlmread('data/SG1_p_5_RAC_true.txt');
RAC_false(1,:) = dlmread('data/SG1_p_5_RAC_false.txt');

CN_true(2,:) = dlmread('data/SG1_p_10_CN_true.txt');
CN_false(2,:) = dlmread('data/SG1_p_10_CN_false.txt');
RA_true(2,:) = dlmread('data/SG1_p_10_RA_true.txt');
RA_false(2,:) = dlmread('data/SG1_p_10_RA_false.txt');
RAC_true(2,:) = dlmread('data/SG1_p_10_RAC_true.txt');
RAC_false(2,:) = dlmread('data/SG1_p_10_RAC_false.txt');

CN_true(3,:) = dlmread('data/SG1_p_15_CN_true.txt');
CN_false(3,:) = dlmread('data/SG1_p_15_CN_false.txt');
RA_true(3,:) = dlmread('data/SG1_p_15_RA_true.txt');
RA_false(3,:) = dlmread('data/SG1_p_15_RA_false.txt');
RAC_true(3,:) = dlmread('data/SG1_p_15_RAC_true.txt');
RAC_false(3,:) = dlmread('data/SG1_p_15_RAC_false.txt');

CN_true(4,:) = dlmread('data/SG1_p_20_CN_true.txt');
CN_false(4,:) = dlmread('data/SG1_p_20_CN_false.txt');
RA_true(4,:) = dlmread('data/SG1_p_20_RA_true.txt');
RA_false(4,:) = dlmread('data/SG1_p_20_RA_false.txt');
RAC_true(4,:) = dlmread('data/SG1_p_20_RAC_true.txt');
RAC_false(4,:) = dlmread('data/SG1_p_20_RAC_false.txt');

CN_accuracy = (CN_true + CN_false)/2;
RA_accuracy = (RA_true + RA_false)/2;
RAC_accuracy = (RAC_true + RAC_false)/2;
x = [5 10 15 20];

str=sprintf('Common Neighbor');
%errorbar(x,mean(CN_accuracy,2),std(CN_accuracy'),'o-.','LineWidth',1.5,'Color','r','DisplayName',str,'MarkerSize',10); hold on;
plot(x,mean(CN_accuracy,2),'o-.','LineWidth',1.5,'Color','r','DisplayName',str,'MarkerSize',10); hold on;
str=sprintf('Resource Allocation');
%errorbar(x,mean(RA_accuracy,2),std(RA_accuracy'),'^--','LineWidth',1.5,'Color','k','DisplayName',str,'MarkerSize',10); hold on;
plot(x,mean(RA_accuracy,2),'^--','LineWidth',1.5,'Color','k','DisplayName',str,'MarkerSize',10); hold on;
str=sprintf('Resource Allocation with Community');
%errorbar(x,mean(RAC_accuracy,2),std(RAC_accuracy'),'*-','LineWidth',1.5,'Color',[0.5 0.5 1],'DisplayName',str,'MarkerSize',10); hold off;
plot(x,mean(RAC_accuracy,2),'*-','LineWidth',1.5,'Color',[0.5 0.5 1],'DisplayName',str,'MarkerSize',10); hold off;

legend('show');
xlabel('Edge removed ratio (%)');
ylabel('Predict accuracy (%)');
title('Performance of SG1');
grid on;