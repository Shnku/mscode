# Output  Analysis of Mix Drawing

## Output

![exact output according to given points](./out.png)

## Questiones

**1. How many points did each of the five parts generate? Which part produced the most, and why?**

* by trisul $161$ points.
* by durga's face generated $200$ points.
* by mahisasur's face $144$ points generated.
* by durga's body $304$ points ellipse generated.
* by mahisaur's body $208$ points ellipse generated.

So, total $(161+200+144+304+208)=1017$ points

**2. For the trishul, what are the values of dx and dy? What is it about these two values that makes the line come out at exactly 135°?**  
For slope calculation in trishul we should take absolute values: `dx = abs(x2 - x1)` and `dy = abs(y2 - y1)`.  
The step need to be determine $-1 \ or +1$ based on the negative or positive slope.

**3. Why does a circle allow 8-way symmetry while an ellipse allows only 4-way?**  
Circle is symmetric along 4-quadrants in 2d coordinate system as well as symmetric w.r.t $y=\pm x$ or $x=\pm y$.  
But ellipse only has 4-quadrant symmetry.

**4. If the radius of Durga's face were changed from 35 to 70, roughly how many points would that circle produce? Explain your reasoning without running the program.**  

for radius=35 it generates 200 points  
for x=y symmetry $35/2=17.5 $
and $(200/8)-8=25-8=17$  

for radius=25 it generates 144 points  
for x=y symmetry $25/2=12.5$  
and $(144/8)-8=18-8=10$  

similarly, radius=70, then approx no of points  points to be generated will be:  
$(70/2)*8=35*8=280$, with maybe some more or less 8 points

**5. Your Own Variation After the figure above is working, run your program once more with the radius of Durga's face changed from 35 to (35 + the last digit of your roll number), keeping everything else the same. Save this second figure as well, and state in your document how many points that circle produced this time.**  
last digit of roll no:3  
now 240 points produces.

also added some more moficications..

![modified output with new points](./out2.png)
