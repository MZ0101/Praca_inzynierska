# **Project of microstructure analysis of SOFC (Solid Oxide Fuel Cell) fuel cell electrodes.**

## **Description**
The project was created to search for the shortest wipes in the microstructures of SOFC fuel cells (solid oxide fuel cells). 
The program uses the Dijkstra and A* algorithms and the Qt library to process images with the .BMP extension. 
Additionally, the Qt library was used to create a simple user interface.

## **Program Operation**

The images on which the program works have dimensions of 200x200 pixels, which can be treated as a pixel graph. Pixels in images come in black, white and various shades of gray. Currently, the algorithm works in such a way that if a pixel is white, a hydrogen molecule can pass through that area. To run the algorithm, the user must select the starting and ending points, i.e. the image number and pixel coordinates. Coordinates can be entered from the keyboard or select points with the mouse by clicking on a pixel in the image. The program also allows you to select the number of coordinate sets on which the algorithm should operate - the user can select one or ten sets. If ten data sets are selected, the average road cost will also be calculated.

## **Image Processing**

The image-based program resulting from the algorithm is visualized in images. Blue pixels represent visited pixels, green pixels represent the shortest path, and red pixels represent starting and starting points.

## **Types of Shortest Path Search**
Currently, the program offers three different search criteria for the shortest source:

- Cost to Reach the Vertex (Dijkstra's Algorithm): This algorithm provides the best results, but may be time-consuming.<br>
- Actual Cost + Euclidean Distance (Algorithm A):* This mode tracks the cost to reach the vertex and the estimated distance, which is calculated as Euclidean distance. It is slightly less accurate than Dikstra's algorithm, but on average half as fast.<br>
- Far Euclidean (Algorithm A):* This mode is the fastest, but always produces the most inaccurate results. It can be used to check whether a shortest path exists.<br>

## **Possible Extensions**
The project can be developed by adding new features:

- More path finding algorithms can be added to add more options to the user.<br>
- Added the function of saving the results of the algorithm directly to an .xlsx or .txt file, which will facilitate the analysis of the results.<br>
- Control the size of windows in the program depending on the display resolution.
- Allowing the user to view processing results across different data sets.<br>
- Allow user to select path search criterion from results overview.<br>
- Create an installer that will make it easier for other users to install the program.<br>
- You can optimize the performance of the program.<br>
