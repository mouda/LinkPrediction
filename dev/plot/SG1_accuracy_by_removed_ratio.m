close all;
clear
CN_true = zeros(4,10);
CN_false = zeros(4,10);
CN=zeros(4,10,2);
RA_true = zeros(4,10);
RA_false = zeros(4,10);
RA=zeros(4,10,2);
RAC_true = zeros(4,10);
RAC_false = zeros(4,10);
RAC=zeros(4,10,2);
strFlag = {'CN','RA','RAC'};
strAnswer = {'true','false'};
for p = 1:4
    for i = 1:3
        for j = 1:2
            strFile=sprintf('data_SG3_sorted_random/SG3_sorted_random_p_%d_%s_%s.txt',p*5,strFlag{i},strAnswer{j});
            if i == 1
                CN(p,:,j)=dlmread(strFile);
            elseif i ==2
                RA(p,:,j)=dlmread(strFile);
            elseif i == 3
                RAC(p,:,j)=dlmread(strFile);
            end
        end
    end
end



CN_accuracy = (CN(:,:,1) + CN(:,:,2))/2;
RA_accuracy = (RA(:,:,1) + RA(:,:,2))/2;
RAC_accuracy = (RAC(:,:,1) + RAC(:,:,2))/2;
x = [5 10 15 20];

str=sprintf('Resource Allocation with Community');
errorbar(x,mean(RAC_accuracy,2),std(RAC_accuracy'),'*-','LineWidth',1.5,'Color',[0.5 0.5 1],'DisplayName',str,'MarkerSize',10); hold on;
%plot(x,mean(RAC_accuracy,2),'*-','LineWidth',1.5,'Color',[0.5 0.5 1],'DisplayName',str,'MarkerSize',10); hold off;
str=sprintf('Resource Allocation');
errorbar(x,mean(RA_accuracy,2),std(RA_accuracy'),'^--','LineWidth',1.5,'Color','k','DisplayName',str,'MarkerSize',10); hold on;
%plot(x,mean(RA_accuracy,2),'^--','LineWidth',1.5,'Color','k','DisplayName',str,'MarkerSize',10); hold on;
str=sprintf('Common Neighbor');
errorbar(x,mean(CN_accuracy,2),std(CN_accuracy'),'o-.','LineWidth',1.5,'Color','r','DisplayName',str,'MarkerSize',10); hold off;
%plot(x,mean(CN_accuracy,2),'o-.','LineWidth',1.5,'Color','r','DisplayName',str,'MarkerSize',10); hold on;
%axis([4 22 0.5 0.7 ]);


legend('show');
xlabel('Edge removed ratio (%)');
ylabel('Predict accuracy (%)');
%title('Performance of SG1');
grid on;