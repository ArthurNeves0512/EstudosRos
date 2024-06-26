#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/droid/Documentos/EstudosRos/catkin_arthur/src/rosserial/rosserial_client"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/droid/Documentos/EstudosRos/catkin_arthur/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/droid/Documentos/EstudosRos/catkin_arthur/install/lib/python3/dist-packages:/home/droid/Documentos/EstudosRos/catkin_arthur/build/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/droid/Documentos/EstudosRos/catkin_arthur/build" \
    "/usr/bin/python3" \
    "/home/droid/Documentos/EstudosRos/catkin_arthur/src/rosserial/rosserial_client/setup.py" \
     \
    build --build-base "/home/droid/Documentos/EstudosRos/catkin_arthur/build/rosserial/rosserial_client" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/droid/Documentos/EstudosRos/catkin_arthur/install" --install-scripts="/home/droid/Documentos/EstudosRos/catkin_arthur/install/bin"
