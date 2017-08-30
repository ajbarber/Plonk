# Plonk

3D OpenGL Animation Loader/Viewer written in C++14.

## What it does
Using the [Assimp](assimp.sourceforge.net) library loads a 3d animation model in Collada, 3DS, X, Obj, STL and other formats.

### Compiling

```
$> ./configure
```
then
```
$> make

```

### Example dependencies using an ubuntu based distribution:

```
$> sudo apt-get install gcc g++ pkg-config make libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev libglew-dev libsoil-dev libglm-dev libpng-dev libsfml-dev libassimp-dev
```

If you have problems the output of the configure script might provide clues as to what libs are missing on your system. 

### Usage

```
$> plonk examplemodel.obj
```
You can try it with the supplied model in this repo, `boblampclean.md5mesh`.

`Mouse left click` controls orientation of the model on screen.

`Mouse middle click` zooms the camera in and out.

## Contributing

I need help testing model formats and all the code changes that follow. Fork and submit your PR if interested
