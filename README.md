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
### Usage

```
$> plonk examplemodel.obj
```
You can try it with the supplied model in this repo, `boblampclean.md5mesh`.

`Mouse left click` controls orientation of the model on screen.

`Mouse middle click` zooms the camera in and out.

## Contributing

I need help testing model formats and all the code changes that follow. Fork and submit your PR if interested!!
