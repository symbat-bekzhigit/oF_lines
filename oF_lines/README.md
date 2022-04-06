# oF_lines
An openFrameworks app that makes a drawing with lines and points that can be controlled by sliders.

In my applicattion, there are 3 different sliders:
- sliders which control distribution of lines along the window of the app
- sliders which control the thickness of lines
- sliders which control color of the lines


Basically, there are 2 groups of lines, each consisting of 5 parallel lines. The first group consists of the lines located horizontally at a certain distance from other lines of the same group. This distance can be controlled by the slider located in the "Distribution" label. The second group consists of the lines located diagonally at a certain distance from each other, but here the lines, initially, are located parallel to each other, and as the distance between the lines increase, they start to move away from each other in a slightly non-proportional manner, causing some kind of assymetry.

The sliders which control the color of those lines are located under the "Colors" label. The color can be controlled by increasing/decreasing x,y,z values for each of the groups of lines, which correspond to RGB values.

The thickness of the lines are controlled by float sliders located under a "Thickness" label, and their values are restricted to the range of 1-20.

