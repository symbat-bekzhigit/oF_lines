# Light at the end of the tunnel

This is openFrameworks application that makes a drawing with lines and points that can be controlled by sliders. The way the lines interact under certain parameters creates the feeling of being in a 3d space - something similar to a tunnel - and the dense distribution of those lines near the center results in a bright rectangular spot right at the center of the window, that's why I decided to name the project 'Light at the end of the tunnel'.

In my applicattion, there are 2 different sliders:
- sliders which control the number of lines
- sliders which control the color of the lines

Using sliders under the label "Distribution", we can increase and decrease the number of lines. All the lines originate from the center, however, while the first slider draws lines that are spreading horizontally, the second slider draws lines that are spreading vertically.

The color of those two groups of lines is controlled by the sliders located under the label "Colors". The x, y,and z values of those sliders correspond to R, G ,B values, respectively.

Sometimes those two groups of lines can overlap, and sometimes they work along to create a perfect rectangle.

![](bin/data/image2.png)

![](bin/data/image1.png)
