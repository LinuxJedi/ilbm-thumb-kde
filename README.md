# ilbm-thumb-kde

This is a plugin for KDE Plasma to provide thumbnail support for Amiga IFF / ILBM files in Dolphin.

## Build Instructions

Dependencies:
* cmake
* extras-cmake-modules
* qtbase5-dev
* kio-dev
* libgraphicsmagick1-dev

The following instructions will build the plugin:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release
make
```

Watch for any errors in any step, you won't be able to continue until they are resolved.

Once this completes you can install using:

```
sudo make install
```

# Other Environments

For GNOME and other display environments, I have included `ilbm.thumbnailer`. This should be copied into `/user/share/thumbnailers` to add support. The thumbnailer file runs ImageMagick from command line to do the conversion, so you do not need this plugin. Unfortunately KDE Plasma does not support the thumbnailer standard.
