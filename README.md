# Halftoner
This algorithm creates halftoned bmp image from full RGB bmp image.
Halftone rules are written in patterns file.
They are 10 3x3 matricies of ones and zeros.
Each matrix is used for a 10% band of grayscale values.
Input file is input.bmp, and generated output file will be output.bmp.
Output will be around 9 times bigger than input, because every input pixel is mapped into 9 pixel sqare of output matrix.
To run program, just execute Halftoner.exe.
