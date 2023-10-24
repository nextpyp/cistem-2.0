# *cis*TEM-2.0

### Building from source

1. First, launch the singularity container and enable the Intel compiler:
<pre>
singularity shell -B /opt/apps cistem_dev_env_latest.sif
source  /opt/apps/rhel8/intel-2020/compilers_and_libraries/linux/bin/compilervars.sh intel64
</pre>

2. Build wxWidget which is the prerequisite library to build cisTEM. First, download the source for [wxWidget 3.0.4](https://github.com/wxWidgets/wxWidgets/releases/tag/v3.0.4):
<pre>
wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.4/wxWidgets-3.0.4.zip
unzip wxWidgets-3.0.4.zip -d wxWidgets-3

cd wxWidgets-3

./configure CXX=icpc CC=icc --disable-precomp-headers --prefix=$(pwd) --with-libnotify=no --disable-shared --without-gtkprint --with-libjpeg=builtin --with-libpng=builtin --with-libtiff=builtin --with-zlib=builtin --with-expat=builtin --disable-compat28 --without-liblzma --without-libjbig CFLAGS="-no-multibyte-chars" CXXFLAGS="-no-multibyte-chars"

make -j4
make install
</pre>

3. Build cisTEM-2.0 packages using the wxWidgets library you just built (specify the corresponding path using `--with-xw-config`)
<pre>
git clone git@github.com:nextpyp/cistem-2.0.git
cd cistem-2.0

./regenerate_project.b

mkdir build

cd build
../configure CFLAGS="-no-multibyte-chars" CXXFLAGS="-no-multibyte-chars" --enable-staticmode --enable-openmp --with-wx-config=/path_to_your_wxwidgets/wx-config --prefix=$(pwd)

make -j4
make install
</pre>
