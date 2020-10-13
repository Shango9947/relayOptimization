x = [0 1 NaN 0 4 NaN 0 1 NaN 1 4 NaN 1 1 NaN 4 4 NaN 4 6 NaN 4 5 NaN 4 7 NaN 4 8 NaN 4 8 NaN 8 8 NaN 6 5 NaN 6 7 NaN 6 8 NaN 1 5 NaN 5 7 NaN 7 8];
y = [0 1 NaN 0 0 NaN 0 -3 NaN 1 0 NaN 1 -3 NaN 0 4 NaN 0 0 NaN 0 -3 NaN 0 -1 NaN 0 0 NaN 4 4 NaN 4 0 NaN 0 -3 NaN 0 -1 NaN 0 0 NaN -3 -3 NaN -3 -1 NaN -1 0];
plot(x, y, 'LineWidth', 3);    %no marker!
hold on
x1 = [0 1 4 4 8 6 1 5 7 8];
y1 = [0 1 0 4 4 0 -3 -3 -1 0];
labels = ['0';'1';'2';'3';'4';'5';'6';'7';'8';'9']
plot(x1, y1, 'r.', 'MarkerSize', 25, 'LineStyle', 'none');
text(x1,y1,labels,'VerticalAlignment','bottom','HorizontalAlignment','right', 'FontSize', 15);
