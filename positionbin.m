%Kex simple positioning for a kanyl
%Comparing two different known positions to see if we could calculate the
%difference, using simple Anger Logic
 clc
 clear all
 close all
%% 
%Looking at 1 second of sampling

%counts per bin at position 0
counts_bin01 = [117270 126713 129593 76433 101327 13828 26544 749 1937 37 55 25 0];

%counts per bin at position 1
counts_bin11 = [57127 66562 63338 83054 80626 73663 84863 24901 39166 2463 5209 144 162];

% summation of position*count for pos 0
summ = 0;
for i = 1:13

    product = i*counts_bin01(i);
    summ = summ + product;


end
%postion 0
position01 = summ/sum(counts_bin01);

%summation of position*count for pos 1
summ = 0;
for i = 1:13

    product = i*counts_bin11(i);
    summ = summ + product;


end
%postion 1
position11 = summ/sum(counts_bin11);
%% 
%Looking at 61 seconds of sampling

%counts per bin at position 0
counts_bin061 = [6996928 7564985 7755880 4564046 6059590 841063 1577458 44687 112293 2582 4752 1299 1783];

%counts per bin at position 1
counts_bin161 = [3435735 3994038 3798132 4982190 4835314 4416198 5095454 1499211 2336558 144110 313349 4706 12726];

%summation of position*count for pos 0
summ = 0;
for i = 1:13
    
    product = i*counts_bin061(i);
    summ = summ + product;
end
%position 0
position061 = summ/sum(counts_bin061);

%summation of position*count for pos 1
summ = 0;
for i = 1:13
   product = i*counts_bin161(i);
   summ = summ + product;
end
%position 1
position161 = summ/sum(counts_bin161);

fprintf('At 2 seconds of sampling, position0 is %d and position1 is %d\n', position01, position11)
fprintf('At 61 seconds of sampling, position0 is %d and position1 is %d\n', position061, position161);

colpos = [position01 position11 position061 position161; 0 0 0 0];
c = [0.1 0.2];

figure(1)
bar(counts_bin01);
title('First position, 2 seconds acquisition')

figure(2)
bar(counts_bin11);
title('Second position, 2 seconds acquisition')

figure(3)
bar(counts_bin061);
title('First position, 61 seconds acquisition')

figure(4)
bar(counts_bin161);
title('Second position, 61 seconds acquisition')

% 
% figure(1)
% scatter(colpos(1,1:2),colpos(2,1:2),100,c,'filled');
% xlim([3 5])
% ylim([-1 1])
% title('1 seconds of sampling')
% 
% figure(2)
% scatter(colpos(1,3:4),colpos(2,3:4),100,c,'filled');
% xlim([3 5])
% ylim([-1 1])
% title('61 seconds of sampling')






