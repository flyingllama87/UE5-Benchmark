# UE5 Benchmark

- This is source & content for a simple Unreal Engine 5.4 benchmark application.
- I couldn't find a free cross platform UE benchmark tool so I made one. In short, fab.com content + Camera on a spline + Some code = Benchmark application.
- At the end of the benchmark the results are stored in `BenchmarkResults.txt`.
- Made in a few days without knowing anything about UE.
- Don't take the assets from this project without understanding the licensing for them. See CREDITS.txt file for more. 

# Download Binaries

### Windows DL
https://musicgen.net/start/UE5Benchmark-Windows.zip

### Linux DL
https://musicgen.net/start/UE5Benchmark-Linux.zip

# Screenshots

![Alt text](/Screenshots/screen1.png?raw=true "Screenshot 1")
![Alt text](/Screenshots/screen4.png?raw=true "Screenshot 2")
![Alt text](/Screenshots/screen3.png?raw=true "Screenshot 3")

# Project Structure

- The BenchmarkManager class stores all logic and data for the benchmark - FPS history, current renderer, resolution, etc. 
- The MyCameraActor class is responsible for the the camera movement and view.
- The FPSHUD class is for the on-screen UI. The EndScreenWidget blueprint widget contains the end screen UI.

# Credits/Licensing

See CREDITS.txt for full asset credits and licenses.

Special shoutouts to:
- Pack Dev for [Cave Ruins](https://www.fab.com/listings/c437d905-5078-4e59-88ed-d585ef20050b)
- Bugrimov Maksim for [Fantasy Characters (Pack)](https://www.fab.com/listings/f5816915-86d9-4bef-b8f3-921408ae240b)

UE5 Benchmark by Morgan Robertson
https://morganrobertson.net