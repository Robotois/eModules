cmd_Makefile := cd ..; /usr/lib/node_modules/node-gyp/gyp/gyp_main.py -fmake --ignore-environment "--toplevel-dir=." -I/home/pi/Projects/eModules/NodeLibrary/RotaryModule/build/config.gypi -I/usr/lib/node_modules/node-gyp/addon.gypi -I/home/pi/.node-gyp/6.5.0/include/node/common.gypi "--depth=." "-Goutput_dir=." "--generator-output=build" "-Dlibrary=shared_library" "-Dvisibility=default" "-Dnode_root_dir=/home/pi/.node-gyp/6.5.0" "-Dnode_gyp_dir=/usr/lib/node_modules/node-gyp" "-Dnode_lib_file=node.lib" "-Dmodule_root_dir=/home/pi/Projects/eModules/NodeLibrary/RotaryModule" binding.gyp
