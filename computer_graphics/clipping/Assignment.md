# **Cohen–Sutherland Line Clipping Algorithm**

### **Aim**

To implement the Cohen–Sutherland line clipping algorithm in Python, and to clip a given set of lines against a  given rectangular window.

### **Your Own Input Line**

Let a \= the second-last digit of your roll number, and b \= the last digit.

 Line L6 : from (40 \+ a, 20\) to (190 − b, 180\)

For example, a roll number ending in 47 gives a \= 4 and b \= 7, so L6 runs from (44, 20\) to (183, 180). Write your  own a, b and L6 at the top of your answer sheet before you begin.

### **Input Data**

Clipping window: lower-left corner (50, 50), upper-right corner (200, 150).

Clip each of the following six lines against this window.

| Line | From | To |
| ----- | :---: | :---: |
| L1 | (140, 70\) | (185, 130\) |
| L2 | (10, 165\) | (40, 190\) |
| L3 | (20, 125\) | (250, 125\) |
| L4 | (80, 20\) | (80, 180\) |
| L5 | (20, 20\) | (150, 200\) |
| L6 | (40 \+ a, 20\) | (190 − b, 180\) |

*Work out for yourself which of these are trivially accepted, which are trivially rejected, and which have to be  clipped. Do not assume — let the region codes decide.*

### **Tasks**

Write ONE Python program (clipping\_\<your roll no\>.py) that does the following.

**Task 1 — Region code**

Write a function that takes a point (x, y) and returns its 4-bit region code with respect to the window, using the  bit order taught in the class (TOP, BOTTOM, RIGHT, LEFT).

**Task 2 — Clipping**

Write a function that takes the two endpoints of a line and returns either the clipped endpoints, or an indication  that the line is rejected. Apply the trivial accept test, then the trivial reject test, and only then compute an  intersection with one boundary and repeat.

**Task 3 — Print the result table**  
For each of the six lines, print one row containing: the line name, both endpoints, the region code of each  endpoint as four bits, the outcome (accepted / rejected / clipped), the number of times the loop ran, and the  clipped endpoints.

**Task 4 — Draw the figure**

Draw the clipping window as a rectangle, all six input lines as dashed lines, and the surviving portions as thick  solid lines. Use a 1 : 1 aspect ratio and save the figure as a PNG file.

### **Expected Output**

Your figure should look like this. The dashed lines are the inputs and the thick lines are the parts that survive  the clipping.

![][image1]  
*L6 in the figure is drawn for a roll number ending in 47\. Your L6 will be in a slightly different position.*

### **Questions to Answer**

Answer in your own words, two or three sentences each.

1\. Which line was trivially accepted and which was trivially rejected? Give the region codes that told you, and  state the bitwise test you used in each case.

2\. One of the six lines needed three passes through the loop, while the others needed two or none. Which  line was it, and why did computing the first intersection point not finish the job?

3\. For your own line L6, which two edges of the window did it cross, and what are the clipped endpoints?  Give the coordinates to three decimal places.

4\. The region code has four bits. How many different regions does this divide the plane into, and why is the  code of a point inside the window 0000?

### **Instructions**

1\. Write both functions yourself, from the steps taught in the theory class. Do not use any ready-made  clipping routine, and do not use matplotlib clipping options such as set\_clip\_box or clip\_on. 2\. Print every region code as four bits, for example 0101, and not as a decimal number. 3\. The intersection points will not be whole numbers. Print them to three decimal places; do not round them  to integers.

4\. Matplotlib is to be used only to draw the window, the input lines and the clipped lines you have computed. 5\. Use a 1 : 1 aspect ratio, otherwise the window will not look rectangular.  
6\. If you save the figure into a folder, create that folder first, or the program will stop with a file-not-found  error.

### **Submission**

To be submitted at the end of today’s laboratory session. Submit one ZIP file named with your roll number,  containing:

• clipping\_\<your roll no\>.py — your program, with comments.

• The PNG figure produced by your program.

• One Word or PDF file containing your values of a and b, the printed result table, the figure, and your  answers to the four questions.
