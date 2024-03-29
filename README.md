# Circle Algorithms

Six algorithms that draw a circle in a 2D grid. Sample images are the following:

![img](./src/samples.png)

## Time Complexity

1. **Algorithm 1: Brute Force**

- Time Complexity: $O(R^2)$

- Explanation: The algorithm uses two nested loops to iterate through all the pixels in a square bounding box around the circle. The condition inside the loop checks if the pixel is inside the circle using the circle equation $x^2 + y^2 = R^2$.

```c++
void algo1(Mat* img, int radius, int cx, int cy) {
	for(int y=-radius; y<=radius; y++)
    		for(int x=-radius; x<=radius; x++)
        		if(x*x+y*y <= radius*radius)
            			img->at<uchar>(cx+x, cy+y) = 255;
}
```

2. **Algorithm 2: Bresenham's Line Drawing**

- Time Complexity: $O(R^2)$

- Explanation: Although Bresenham's algorithm is usually associated with line drawing, the adaptation used here still involves iterating through a bounding box around the circle. The isqrt (integer square root) function and the second loop introduce additional constant factors but don't affect the overall complexity. The height is calculated with the circle equation $x^2 + y^2 = R^2$, and its worse case scenario is when the height equals the radius, thus $O(R^2)$.

```c++
void algo2(Mat* img, int radius, int cx, int cy) {
	for (int x = -radius; x < radius; x++) {
    		int height = (int)isqrt(radius * radius - x * x);
    		for (int y = -height; y < height; y++)
        		img->at<uchar>(x + cx, y + cy) = 255;
	}
}
```

3. **Algorithm 3: Midpoint Circle Algorithm**

- Time Complexity: $O(R)$

- Explanation: The Midpoint Circle Algorithm is more efficient than the brute-force approach. It only iterates through a single octant of the circle and uses symmetry to compute the other points. The overall time complexity is linear with respect to the radius. 

```c++
void algo3(Mat* img, int radius, int cx, int cy) {
	int x = radius;
    	int y = 0;
    	int xChange = 1 - (radius << 1);
    	int yChange = 0;
    	int radiusError = 0;
	while (x >= y) {
		for (int i = cx - x; i <= cx + x; i++) {
		    img->at<uchar>(i, cy + y) = 255;
		    img->at<uchar>(i, cy - y) = 255;
		}
		for (int i = cx - y; i <= cx + y; i++) {
		    img->at<uchar>(i, cy + x) = 255;
		    img->at<uchar>(i, cy - x) = 255;
		}
		y++;
		radiusError += yChange;
		yChange += 2;
		if (((radiusError << 1) + xChange) > 0)	{
		    x--;
		    radiusError += xChange;
		    xChange += 2;
		}
	}
}
```

4. **Algorithm 4: Bresenham's Circle Drawing**

- Time Complexity: $O(R^2)$

- Explanation: Similar to Algorithm 3, this implementation of Bresenham's Circle Drawing algorithm exploits symmetry to only compute points in one octant. The time complexity is linear with respect to the radius. It does look similar to #2 but the difference lies in the inner loop:

	- Algorithm 2 uses an inner loop over the height (calculated based on the circle equation) for each x-coordinate within the given radius.

	- Algorithm 4 uses an inner loop over the y-coordinate directly calculated based on the circle equation.

```c++
void algo4(Mat* img, int radius, int cx, int cy) {
	for (int x = -radius; x < radius ; x++) {
		int hh = (int)isqrt(radius * radius - x * x);
		int rx = cx + x;
		int ph = cy + hh;
		for (int y = cy-hh; y < ph; y++)
        		img->at<uchar>(rx, y) = 255;
	}
}
```

5. **Algorithm 5: Coordinate-Based Approach**

- Time Complexity: $O(R^2)$

- Explanation: The algorithm iterates through a square bounding box around the circle, similar to Algorithm 1. While the constant factors may differ, the overall time complexity is quadratic with respect to the radius. It's one loop, yes, but it traverses a distance of $R^2$.

```c++
void algo5(Mat* img, int radius, int cx, int cy) {
	int r2 = radius * radius;
	int area = r2 << 2; // r2 * 4
	int rr = radius << 1;

	for (int i = 0; i < area; i++) {
    		int tx = (i % rr) - radius;
    		int ty = (i / rr) - radius;

    		if (tx * tx + ty * ty <= r2)
        		img->at<uchar>(cx + tx, cy + ty) = 255;
	}
}
```

6. **Algorithm 6: Brute Force with Polar Coordinates**

- Time Complexity: $O(R \times 360)$

- Explanation: The outer loop runs "radius" times, and the inner loop runs 360 times for each iteration of the outer loop.

```c++
void algo6(Mat* img, int radius, int cx, int cy, uint8_t color) {
	for (int r = 1; r < radius; r += 1) {
		for (double a = 0.0; a < 360.0; a += 5.0) {
			int x = cx + r * cos(a * 3.1416 / 180.0);
			int y = cy + r * sin(a * 3.1416 / 180.0);
			img->at<uchar>(x, y) = color;
		}
	}
}
```

This clearly is the slowest algorithm, not because of its time complexity, but for the redundancy of the pixels computed. In the execution time comparison plot, all algorithms look like the following:

![img](./src/plot.png)

And this rules out the possibility of using algorithm #6 if performance is the aim. With the purpose of choosing another one, let's plot without the big difference that the algorithm #6 represents:

![img](./src/plot2.png)

Here, we can clearly see algorithm #3 is the fastest one.

## Run The Code

1. You must have installed in your system:

- OpenCV for C++

- CMake ^3.12

2. Type on the root folder of the repo:

```bash
cmake .
make
./main
```

## Sources

- The algorithms are not mine, they were taken from here: https://stackoverflow.com/questions/1201200/fast-algorithm-for-drawing-filled-circles
