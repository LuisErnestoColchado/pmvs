# Patch-based Multi-view Stereo (PMVS)
## Dependences 

### Libraries
Install follow libraries: 
```
sudo apt-get install libxext6
sudo apt-get install libx11-dev
install libjpeg.so.62 => http://libjpeg.sourceforge.net/
sudo apt-get install libpthread-stubs0-dev
install liblapack => http://www.netlib.org/lapack/
install Blas => http://www.netlib.org/blas/
sudo apt-get install libc6-i386
sudo apt-get install libstdc++6
sudo apt-get install build-essential
install libXau => http://www.linuxfromscratch.org/blfs/view/8.2/x/libXau.html
install libXdmcp => http://www.linuxfromscratch.org/blfs/view/cvsx/libXdmcp.html
apt-get install libgfortran3
```

## Instalation 
Data folder should contain images and their information of intrinsic of camera model and extrinsic of each photographs.
We use our own Camera Calibration program for get these parameters for 3D reconstruction of Rings pattern. Our program is available in:

```
https://github.com/joseucsp/camera-calibration
```

On the other hands, we use the Structure from Motion (SFM) for 3D reconstruction of the Catholic University San Pablo , SFM is available in:

```
http://www.cs.cornell.edu/~snavely/bundler/
```

The data folder that we use is available in:

```
https://drive.google.com/open?id=1bCQYOzu4BSKNwKwzprBcFBO6A_OuHtCf
```

This data folder contain two different information.

```
- Images and files with P matrix in format txt of Rings pattern 
- Images and files with P matrix in format txt of the Catholic University San Pablo
```

Copy data folder in root.

```
.
├── ...
└── repository                   
│    ├── data
│    ├── program                  
└── ...
```

After, compile program with follow comands:

```
cd program/main
make  
```

## Execute

 ./pmvs2 ../../data/$namefolder /$optionfile.txt

For default, We have a two folders. 

```
$namefolder: can is "rings50" or "sanpa" 
$optionfile: can is "option.txt"
```

## 3D reconstruction Rings pattern

For this reconstruction, we use our Camera Calibration program and PMVS. Our Camera Calibration program get us the parameters intrinsic of camera model and extrinsic in format txt, for each photographs that we give it. The txt file containe the CONTOUR Matrix, that is the projection matrix P.

![alt text](https://raw.githubusercontent.com/LuisErnestoColchado/pmvs_ba/master/images/formula.png)

Where P is:

```
A*R*t 
```

Where A is intrisic matrix, R rotation matrix and t is translation matrix.

This Projection matrix is get from our Calibration camera program in format txt for each photographs. it is neccesary for execute PMVS.

![alt text](https://raw.githubusercontent.com/LuisErnestoColchado/pmvs_ba/master/images/txtmodel.png)

Finally, after execute PMVS, we get follow results:

![alt text](https://raw.githubusercontent.com/LuisErnestoColchado/pmvs_ba/master/images/rings.gif)

Link video:
[![3D reconstruction Rings pattern](https://img.youtube.com/vi/rssW4VEUaSY/0.jpg)](https://www.youtube.com/watch?v=rssW4VEUaSY)

## 3D reconstruction the Catholic University San Pablo

In the same way, the SFM also gives us the txt files for each photographs, that contain the projection matrix.


![alt text](https://github.com/LuisErnestoColchado/pmvs_ba.git/images/sanpablo.png)

Finally, after execute PMVS, we get follow results:

![alt text](https://raw.githubusercontent.com/LuisErnestoColchado/pmvs_ba/master/images/sanpablo.gif)

Link video:

[![3D reconstruction the Catholic University San Pablo](https://img.youtube.com/vi/tbi4XF5W5hQ/0.jpg)](https://www.youtube.com/watch?v=tbi4XF5W5hQ&feature=youtu.be)


