# Cohen–Sutherland Line Clipping Algorithm

To implement the Cohen–Sutherland line clipping algorithm in Python, and to clip a given set of lines against a given rectangular window.

## **Input Data**

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

## Clipping results

### **ViewWindow** `(Xmin=50, Ymin=50, Xmax=200, Ymax=150)`

### Line 1 : `from (140, 70) to (185, 130)`

```text
RegionCode for start=0000, for end=0000
fully inside viewpoint
AFTER CLIPPING:  Line : from (140, 70) to (185, 130)
```

!["Line 1"](Line%201.png)

\newpage

### Line 2 : `from (10, 165) to (40, 190)`

```text
RegionCode for start=1001, for end=1001
completely outside
AFTER CLIPPING:  None
```

!["Line 2"](Line%202.png)

### Line 3 : `from (20, 125) to (250, 125)`

```text
RegionCode for start=0001, for end=0010

---Cutting the start point:: has code 0001
if any code is left 0001:: x'= Xmin, y'= ystart + m * (Xmin - xstart) --> x'= 50, y'= 125+0.0*(50-20)
---Cutting the end point:: has code 0010
if any code is right 0010:: x'= Xmax, y'= ystart + m * (Xmax - xstart) --> x'= 200, y'= 125.0+0.0*(200-50)
fully inside viewpoint
AFTER CLIPPING:  Line : from (50, 125.0) to (200, 125.0)
```

!["Line 3"](Line%203.png)

### Line 4 : `from (80, 20) to (80, 180)`

```text
RegionCode for start=0100, for end=1000

---Cutting the start point:: has code 0100
---Cutting the end point:: has code 1000
fully inside viewpoint
AFTER CLIPPING:  Line : from (80, 50) to (80, 150)
```

!["Line 4"](Line%204.png)

### Line 5 : `from (20, 20) to (150, 200)`

```text
RegionCode for start=0101, for end=1000

---Cutting the start point:: has code 0101
if any code is bottom 0100:: x'= xstart + 1/m * (Ymin - ystart), y'= Ymin --> x'= 20+1/1.3846153846153846*(50-20), y'= 50
---Cutting the start point:: has code 0001
if any code is left 0001:: x'= Xmin, y'= ystart + m * (Xmin - xstart) --> x'= 50, y'= 50+1.3846153846153846*(50-41.66666666666667)
---Cutting the end point:: has code 1000
if any code is top 1000:: x'= xstart + 1/m * (Ymax - ystart), y'= Ymax --> x'= 50+1/1.3846153846153846*(150-61.53846153846153), y'= 150
fully inside viewpoint
AFTER CLIPPING:  Line : from (50, 61.53846153846153) to (113.88888888888889, 150)
```

!["Line 5"](Line%205.png)

\newpage

### Line 6 : `from (41, 20) to (187, 180)`

```text
RegionCode for start=0101, for end=1000

---Cutting the start point:: has code 0101
if any code is bottom 0100:: x'= xstart + 1/m * (Ymin - ystart), y'= Ymin --> x'= 41+1/1.095890410958904*(50-20), y'= 50
---Cutting the end point:: has code 1000
if any code is top 1000:: x'= xstart + 1/m * (Ymax - ystart), y'= Ymax --> x'= 68.375+1/1.095890410958904*(150-50), y'= 150
fully inside viewpoint
AFTER CLIPPING:  Line : from (68.375, 50) to (159.625, 150)

```

!["Line 6"](Line%206.png)

## **Questions to Answer**

**1\. Which line was trivially accepted and which was trivially rejected? Give the region codes that told you, and  state the bitwise test you used in each case.**  

Line 1 `from (140, 70) to (185, 130)` trivially Accepted. As RegionCode for start=0000, for end=0000
and Line 2 `from (10, 165) to (40, 190)` Trivially rejected. As RegionCode for start=1001, for end=1001

**2\. One of the six lines needed three passes through the loop, while the others needed two or none. Which  line was it, and why did computing the first intersection point not finish the job?**  

Line 5: `from (20, 20) to (150, 200)` Needs 3 passes through the loop.  
Computing the first intersection did not complete as we first cut the `start` point with `bottom` and then `left` two consecutive cuts.

**3\. For your own line L6, which two edges of the window did it cross, and what are the clipped endpoints?  Give the coordinates to three decimal places.**  

It crosses bottom and Top edges.  
Clipped EndPoints are `from (68.375, 50) to (159.625, 150)`

**4\. The region code has four bits. How many different regions does this divide the plane into, and why is the  code of a point inside the window 0000?**

TBRL : 4 bits can divide into 9 regions  
inside window points is 0000 as it is not in any of TBRL, all the codes are treated like this:  
top=no=0, bottom=no=0, right=no=0, left=no=0
