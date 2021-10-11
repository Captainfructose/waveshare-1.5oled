# Documentation for the waveshare 1.5 inch oled display grafix class.


I wrote this class to make using the waveshare 1.5 inch oled display esier to use. This is class is opensource but if you do use it please give credit. If it helps you please feel free to share it so it can help others as this was my whole goal in creating this class. 



## Methods:

> void setBarColor(color);

This classs sets the color for the bar in the horizontal and vertical bar graphs. It can take in the built in colors or the hex value for any color that is desired.

&nbsp;

>void setGraphColor(color);

This class sets the color for the frame of the bar graphs as well as the gauge. It takes in the built in colors or the hex value of any color that you want.

&nbsp;

>void setTextColor(color);

This method set the color for the text. It will take the built in colors or a hex value of any color you want.

&nbsp;

>void setGaugeText(bool text);

This method enables or disables the numerical readout in the gauge method. Takes either true or false as input.

&nbsp;

>void initScreen(void);

This method initialises the screen. This needs to be first for the screen will not display anything.

&nbsp;

>void HBarGraph(X position, y Position, width, height, value, maximum value);

This method displays a horizontal bar graph.

&nbsp;

>void VBarGraph(x position, y position, width, height, value, maximum value);

This method displays a vertical bar graph.

&nbsp;

>void drawRect(x position, y position, width, height);

This method draws an empty rectangle on the display.

&nbsp;

>void drawFRect(x position, y position, width, height);

This method draws a filled rectangle on the display.

&nbsp;

>void drawLine(x position 1, y position 1, x position 2, y position 2);

This method draws a line between two points.

&nbsp;

>void drawCircle(x position, y position, radius);

This method draws an empty circle around the specified position.

&nbsp;

>void drawFCircle(x position, y position, radius);

This method draws a filled circle around the specified position.

&nbsp;

>void drawTriangle(x position 1, y position 1, x position 2, y position 2, x position 3, y position 3);

This method draws a triangle with three points.

&nbsp;

>void drawRoundRect(x position, y position, width, height, radius);

This method draws a rectangle with rounded corners. The amount of rounding is specified by the radius.

&nbsp;

>void drawGauge(x position, y position, value, maximum value, radius);

This method draws a semicircle gauge with size specified by radius. The color of the needle is set by the setBarColor method. The color of the housing is specified by the setGaugeColor method.

&nbsp;

>void setColor(color);

This method sets the color for the lines, triangle and circle methods.

&nbsp;

>void setFillColor(color);

This method sets the infill color for the filled rectangle, and filled circle.

&nbsp;

>void writeNumber(x position, y position, number);

This method writes a number to the display and will actively update the number.

&nbsp;

>void writeText(x position, y position, text);

This method writes text to the display.

