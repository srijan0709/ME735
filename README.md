Running Instructions: make
					  ./bin/tf-animate

We declare that this assignment is our own work and that we have not plagarized or cpoied any section of code from any source which we have not explicitly cited.

We also declare that the first assignment was also completely our own work.

Note: Before saving the frames, create an empty folder name "frames" at the same level as the makefile

Command to stich the frames into a video: cat frames/* | ffmpeg -framerate 40 -f image2pipe -i - -c:v copy video.mkv

Necessary Controls:

To toggle keyframe control, press K, then:
S - Saves the current parameters in keyframe_temp.txt
L - Loads the parameters from keyframe.txt
P - Plays the animation
S - Plays and saves the frames of the anumation in the folder named "frames"

To toggle Camera and Lights control, press M, then:
1 - To switch to the camera
2 - To switch to the action camera of Vector Prime
3 - To switch to the action camera of Optimus Prime
4 - To toggle the global_light_1 on/off
5 - To toggle the global_light_2 on/off
6 - To toggle the global_light_3 on/off
7 - To toggle the global_light_4 on/off
7 - To toggle the headlights of Vector Prime
8 - To toggle the headlights of Optimus Prime
W,S - To rotate the camera along the x axis
A,D - To rotate the camera along the y axis
Q,E - To rotate the camera along the z axis
Numpad Keys:
4,6 - To translate the camera along the x axis
8,5 - To translate the camera along the y axis
7,9 - To translate the camera along the z axis

Note: Although our code supports variable intensity lights, we have only used intensities 1 and 0, i.e. on/off. Also, our code supports moving lights, but we have kept the global lights stationary so that the scene is well lit, unless they are off.

Youtube Links:
https://youtu.be/ZKhLhsw0pfQ (Without Audio)
https://youtu.be/UQj2B6HXvZM (With Audio)
