#!/bin/sh

archive_base_name=choreonoid-2.2.0

rm -fr ${archive_base_name}
rm -fr ${archive_base_name}-$1.tar.gz
cp -fr /home/mrp/catkin_ws/devel  ${archive_base_name}
tar -czf ${archive_base_name}-$1.tar.gz ${archive_base_name}
rm -fr ${archive_base_name}
